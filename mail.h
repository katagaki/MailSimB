#include <string>
#ifndef MAIL
#define MAIL

enum MailStatus {
    Received = 1000,
    Sent = 1500,
    Failed = 4000
};

class Mail {
    
private:
    
    std::string content;
    MailStatus status;
    
public:
    
    Mail(std::string content);
    
    std::string getContent();
    MailStatus getStatus();
    
    void setStatus(MailStatus newStatus);
    
};

#endif
