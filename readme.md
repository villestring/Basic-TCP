TCP Socket Programming using C.
Run server:
    gcc -o server server.c
Run client:
    gcc -o client client.c

The client sends a counter message to server with an interval of 5 seconds;
The server reads the message and echos back to the client.

Client is set to terminate after one minute default.