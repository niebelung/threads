#ifndef _LIB_SOCKETS_H_
#define _LIB_SOCKETS_H_

// INCLUDES

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

//DEFINES

#define LIB_SOCKET_SERVER_PATH   "/tmp/server"
#define LIB_SOCKET_BUFFER_LENGTH 256
#define LIB_SOCKET_AF_UNIX AF_UNIX 
#define LIB_SOCKET_TYPE_DGRAM SOCK_DGRAM
//#define 

typedef
struct sLibSocketsSocket
{
    int sock_fd;
    int sock_af;
    int sock_type;
    struct sockaddr_un my_addr;  
    struct sockaddr_un srv_addr;  
    struct sockaddr_un cli_addr;  
    int addr_len;
    char buf[LIB_SOCKET_BUFFER_LENGTH];
} lib_sockets_socket_t;

// PROTOTYPES

extern int libSocket_SocketOpen(lib_sockets_socket_t * a_socket);
extern int libSocket_SocketRcvFrom(lib_sockets_socket_t * a_socket);
extern int libSocket_SocketSendTo(lib_sockets_socket_t * a_socket);
extern int libSocket_SocketClose(lib_sockets_socket_t * a_socket);

#endif
