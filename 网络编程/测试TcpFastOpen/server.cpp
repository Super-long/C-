#include <string.h>         
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int portno = 5060;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int cfd;
    int sfd = socket(AF_INET, SOCK_STREAM, 0);   // Create socket
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    bind(sfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));      // Bind to well known address
    
    int qlen = 5;                 // Value to be chosen by application
    int err = setsockopt(sfd, IPPROTO_TCP/*SOL_TCP*/, 23/*TCP_FASTOPEN*/, &qlen, sizeof(qlen));
    
    listen(sfd,1);                // Mark socket to receive connections
 
    cfd = accept(sfd, NULL, 0);   // Accept connection on new socket
    while(1){
        int len = read(cfd,buffer,256);
        if(len)
             printf("tcp fast open: %s\\n",buffer);
        else
             break;
        // read and write data on connected socket cfd
    }
    
    close(cfd);
}