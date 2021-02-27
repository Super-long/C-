#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/un.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
  
int main()  
{  
  /* create a socket */  
  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);  
    
  struct sockaddr_un address;  
  address.sun_family = AF_UNIX;  

  // 网络套接字通过IP端口识别机器，域套接字需要指定套接字文件的路径
  strcpy(address.sun_path, "server_socket");  
    
  /* connect to the server */  
  int result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));  
  if(result == -1)  
  {  
    perror("connect failed: ");  
    exit(1);  
  }  
    
  /* exchange data */  
  char ch = 'A';  
  write(sockfd, &ch, 1);  
  read(sockfd, &ch, 1);  
  printf("get char from server: %c\n", ch);  
    
  /* close the socket */  
  close(sockfd);  
    
  return 0;  
}