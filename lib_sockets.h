#ifndef _LIB_SOCKETS_H_
#define _LIB_SOCKETS_H_

// INCLUDES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

//DEFINES

#define LIB_SOCKETS_MAX_SOCKETS 5
#define LIB_SOCKETS_SERVER_PATH   "/tmp/server"
#define LIB_SOCKETS_BUFFER_LENGTH 256
#define LIB_SOCKETS_AF_UNIX AF_UNIX 
#define LIB_SOCKETS_TYPE_DGRAM SOCK_DGRAM
//#define 

typedef
struct sLibSocketsSocket
{
    int sock_fd;
    int sock_af;
    int sock_type;
    int sock_proto;
    int addr_len;
    int sock_flags;
    struct sockaddr_un srv_addr;  
    struct sockaddr_un cli_addr;  
    char buf[LIB_SOCKETS_BUFFER_LENGTH];
} lib_sockets_socket_t;

// PROTOTYPES

extern int libSocket_SocketCreate(lib_sockets_socket_t * a_socket);
extern int libSocket_SocketRcvFrom(lib_sockets_socket_t * a_socket);
extern int libSocket_SocketSendTo(lib_sockets_socket_t * a_socket);
extern int libSocket_SocketClose(lib_sockets_socket_t * a_socket);

#endif
