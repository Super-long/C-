#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <errno.h>
#include <string.h>
#include <unistd.h>   
#include <stdio.h>

int main(){
    struct sockaddr_in serv_addr;
    struct hostent *server;
 
    char *data = "Hello, tcp fast open";
    int data_len = strlen(data);    
    
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname("localhost");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(5060);
    int len = sendto(sfd, data, data_len, 0x20000000/*MSG_FASTOPEN*/, 
                (struct sockaddr *) &serv_addr, sizeof(serv_addr));
                
    printf("error: %s\\n",strerror(errno));
    close(sfd);
    sleep(5);    
}