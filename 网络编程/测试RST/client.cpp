#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include <time.h>
#include <sys/time.h>
#include<stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define SERVER_PORT 33333
#define MAXLEN 65535

void client_handle(int sock);


int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        printf("input args %d: %s\n", i, argv[i]);
    }
    struct sockaddr_in seraddr;
    int server_port = SERVER_PORT;
    if (2 == argc) {
        server_port = atoi(argv[1]);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr);
    seraddr.sin_port = htons(server_port);

    if (-1 == connect(sock, (struct sockaddr *)&seraddr, sizeof(seraddr))) {
        perror("connect failure");
        exit(EXIT_FAILURE);
    }
    client_handle(sock);

    return 0;
}

void client_handle(int sock) {
    char sendbuf[MAXLEN], recvbuf[MAXLEN];
    bzero(sendbuf, MAXLEN);
    bzero(recvbuf, MAXLEN);
    int n = 0;

    while (1) {
        if (NULL == fgets(sendbuf, MAXLEN, stdin)) {
            break;
        }
        // 按`#`号退出
        if ('#' == sendbuf[0]) {
            break;
        }
        struct timeval start, end;
        gettimeofday(&start, NULL);
        write(sock, sendbuf, strlen(sendbuf));
        n = read(sock, recvbuf, MAXLEN);
        printf("返回值为%d\n", n);
        if (n < 0) {
            perror("read failure.\n");
            for (size_t i = 0; i < 10; i++)
            {
                printf("nihao\n");
            }
            
            exit(EXIT_FAILURE);
        }
        if (0 == n) {
            break;
        }
        write(STDOUT_FILENO, recvbuf, n);
        gettimeofday(&end, NULL);
        printf("time diff=%ld microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec)));
    }

    close(sock);
}
