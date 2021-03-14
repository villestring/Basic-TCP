// Client side C/C++ program to demonstrate Socket programming 
/*
 * socket
 * connect
 * send/read
 */
#ifdef __WIN32__
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h> 
#endif
#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/time.h>
#define PORT 8080 
#define PERIOD 5000000 // 5 seconds
#define CYCLE 12 // 12 cycles makes up for 1 minutes, default


// get microseconds
unsigned long now() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}


// takes an argument of ipv4 or ipv6 address
// eg: 123.456.78.9
int main(int argc, char const *argv[]) {
    int sock = 0;
    int valread;
    struct sockaddr_in serv_addr;
    char buffer[4096] = {0};
    
    // SOCK_STREAM ==> TCP
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);   
    // convert ipv4 and ipv6 addresses from text to binary form
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)  {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    } 
   
    printf("trying to connect\n");
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    int count = 0;
    char msg_buffer[4096] = {0};
    // mark the time where one loop starts
    unsigned long sending_msg = now();
    while (count <= CYCLE) {
        
        count += 1;
        sprintf(msg_buffer, "The current count is %d\n", count);

        send(sock , msg_buffer , strlen(msg_buffer) , 0 );
        printf("Hello message sent from client\n");
        valread = read(sock , buffer, 4096);
        printf("%s\n",buffer );
        // mark the time that a response is received from the server
        unsigned long response_rec = now();

        // sleep over the remaining time, so that a message is sent given seconds
        if (PERIOD > (response_rec - sending_msg)) {
            usleep(PERIOD - (response_rec - sending_msg));
        }
        sending_msg = now();
    }
    return 0;
} 