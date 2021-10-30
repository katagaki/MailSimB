#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <time.h>
#include <unistd.h> // Program will only work on UNIX systems
#include <vector>
#include "mail.h"
#include "queue.h"

#ifndef WAIT_TIME
#define WAIT_TIME 500
#endif

// Function to generate random content for simulated mail
std::string generateContent() {
    auto randchar = []() -> char {
        const char charset[] =
        "0123456789"
        "abcdef";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(32, 0);
    std::generate_n(str.begin(), 32, randchar);
    return str;
}

// Main entry point of the program
int main() {
    
    unsigned minutesToSimulate = 0,
             totalEmailsReceived = 0,
             totalEmailsSent = 0,
             totalEmailsInQueue = 0;
    std::vector<unsigned> emailsSentPerMinute,
                          emailsRequeued,
                          emailsInQueue;
    Queue<Mail>* queue = new Queue<Mail>();
    
    // Initialize new seed
    srand(time(NULL));
    
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Welcome to the Mail Simulator." << std::endl << std::endl;
    std::cout << "The Mail Simulator will simulate the sending of emails with a failure rate of 25%. In any given minute, up to 30 emails will be received, and up to 30 emails will be sent." << std::endl << std::endl;
    std::cout << "How many minutes would you like to simulate? ";
    std::cin >> minutesToSimulate;
    
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Now simulating " << minutesToSimulate << " minute(s) worth of emails..." << std::endl << std::endl;
    
    // Initialize log
    emailsSentPerMinute.assign(minutesToSimulate, 0);
    emailsRequeued.assign(minutesToSimulate, 0);
    emailsInQueue.assign(minutesToSimulate, 0);
    
    for (int i = 0; i < minutesToSimulate; ++i) {
        
        std::cout << "\033[2J\033[1;1H";
        std::cout << "[TIME] Simulating minute " << i + 1 << "..." << std::endl;
        
        // Assume email rate is 0-60 (average 30)
        int emailsReceived = rand() % 61;

        // Log total emails received
        totalEmailsReceived += emailsReceived;
        
        // Receive simulated emails
        for (int j = 0; j < emailsReceived; ++j) {
            
            usleep(WAIT_TIME);
            
            // Create the email object
            std::string content = generateContent();
            Mail* newMail = new Mail(content);
            newMail -> setStatus(MailStatus::Received);
            
            std::cout << "[RECV] Adding email with content '" << content << "' to the queue..." << std::endl;
            
            // Enqueue email object
            queue -> enqueue(*newMail);
            
        }
        
        // Send simulated emails
        for (int j = 0; j < (queue -> size() > 30 ? 30 : queue -> size()); ++j) {
            
            usleep(WAIT_TIME);
            
            // Determine if mail will fail to send
            bool mailWillFail = (rand() % 4 + 1) == 1;
            
            if (mailWillFail) {
                
                std::cout << "[SEND] Failing email with content '" << queue -> itemInQueue().getContent() << "'..." << std::endl;
                
                // Log count of emails requeued
                ++emailsRequeued[i];
                
                // Requeue failed email
                queue -> itemInQueue().setStatus(MailStatus::Failed);
                queue -> requeueItemInQueue();
                
            } else {
                
                std::cout << "[SEND] Sending email with content '" << queue -> itemInQueue().getContent() << "'..." << std::endl;
                
                // Log count of emails sent
                ++emailsSentPerMinute[i];
                ++totalEmailsSent;
                
                // Dequeue email sent
                queue -> dequeue();
                
            }
            
        }
        
        emailsInQueue[i] = queue -> size();
        
    }
    
    std::cout << "\033[2J\033[1;1H";
    std::cout << "The Mail Simulator has completed processing emails." << std::endl << std::endl;
    std::cout << "---------- Statistics ----------" << std::endl;
    std::cout << "Total emails processed  : " << totalEmailsSent << std::endl;
    std::cout << "Average emails received : " << totalEmailsReceived / minutesToSimulate << std::endl;
    std::cout << "Average emails sent     : " << totalEmailsSent / minutesToSimulate << std::endl;
    std::cout << "Average emails in queue : " << std::accumulate(emailsInQueue.begin(), emailsInQueue.end(), decltype(emailsInQueue)::value_type(0)) / minutesToSimulate << std::endl;
    std::cout << "Average emails requeued : " << std::accumulate(emailsRequeued.begin(), emailsRequeued.end(), decltype(emailsRequeued)::value_type(0)) / minutesToSimulate << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < emailsSentPerMinute.size(); ++i) {
        std::cout << "Email sent in minute " << std::setfill('0') << std::setw(2) << i + 1;
        std::cout << " : " << emailsSentPerMinute[i] << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
    std::cout << std::endl;
    
    delete queue;
    
    return 0;
}
