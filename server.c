// Server side C/C++ program to demonstrate Socket programming 
/*
 * socket
 * setsocketopt
 * bind
 * listen
 * accept
 * send/read
 */

#ifdef __WIN32__
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>  
#endif
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define PORT 8080 
int main(int argc, char const *argv[]) {
    int server_fd; 
    int new_socket;
    int valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[4096] = {0};
       
    // creating socket file descriptor
    // SOCK_STREAM ==> TCP
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("socket created\n");
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(INADDR_ANY);
    address.sin_port = htons(PORT);
    
    // attach socket to port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    } 
    printf("binded and listening\n");
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    if ((new_socket = accept(server_fd, 
        (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("accepted from port\n");

    while (valread = read(new_socket , buffer, 4096)) {
        printf("%s\n",buffer );
        send(new_socket , buffer , strlen(buffer) , 0 );
        printf("Log message sent from server\n");
    }
    return 0;
} 