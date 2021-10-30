#include "mail.h"

Mail::Mail(std::string content) {
    this -> content = content;
}
    
std::string Mail::getContent() {
    return content;
}

MailStatus Mail::getStatus() {
    return status;
}
    
void Mail::setStatus(MailStatus newStatus) {
    status = newStatus;
}
