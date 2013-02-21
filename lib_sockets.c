#include "lib_sockets.h"

static lib_sockets_socket_queue_t socketQueue = 
{
    -1,
     0   
 };

// API FUNCTIONS

int libSockets_SocketInit(lib_sockets_socket_t * a_socket)
{
    a_socket->sock_af = LIB_SOCKETS_AF_UNIX;
    a_socket->sock_type = LIB_SOCKETS_TYPE_DGRAM;
    a_socket->sock_proto = 0;
    a_socket->sock_flags = 0;
    a_socket->addr_len = 0;
    
    bzero(&a_socket->srv_addr, sizeof(a_socket->srv_addr));
    bzero(&a_socket->cli_addr, sizeof(a_socket->cli_addr));
    a_socket->srv_addr.sun_family = a_socket->sock_af;
    a_socket->srv_addr.sun_path = LIB_SOCKETS_SERVER_PATH;
}

int libSocket_SocketCreate(lib_sockets_socket_t * a_socket)
{
    if((a_socket->sock_fd = socket(  a_socket->sock_af,
                                     a_socket->sock_type,
                                     a_socket->sock_proto
                                   )) == -1
       )
    {     
        printf("libSocket_SocketOpen(): Failed to open socket. Exiting...\n",);
        return -1;
    }
    else
    {     
        printf("libSocket_SocketOpen(): Created socket with descriptor %d\n", a_socket->sock_fd);
        return a_socket->sock_fd;
    }
}

int libSocket_SocketBind(lib_sockets_socket_t * a_socket)
{
    if(bind( a_socket->sock_fd, 
             (struct sockaddr*) &a_socket->srv_addr, 
             sizeof(a_socket->srv_addr)
            ) == -1
        
       )
    {
        printf( "libSocket_SocketBind(): Failed to bind socket %d to address %s\n",
                a_socket->sock_fd,
                a_socket->srv_addr.sun_path
               );
        return -1;
    }
    else
    {
        printf( "libSocket_SocketBind(): Successful\n" );
        return 0;
    }
}

int libSocket_SocketRcvFrom(lib_sockets_socket_t * a_socket)
{
    a_socket->addr_len = sizeof(a_socket->cli_addr);
    if(recvfrom( a_socket->sock_fd, 
                 a_socket->buf, 
                 LIB_SOCKETS_BUFFER_LENGTH,
                 a_socket->sock_flags,
                 (struct sockaddr*)a_socket->cli_addr,
                 &a_socket->addr_len
               ) == -1
       )
    {
        printf( "libSocket_SocketRcvFrom(): Failed to Rx data\n" );
        return -1;
    }
    else
    {
        printf( "libSocket_SocketRcvFrom(): Received packet from %s. Data: %s\n",
                a_socket->cli_addr.sun_path,
                a_socket->buf
              );
        return 0;
    }
}

int libSocket_SocketSendTo(lib_sockets_socket_t * a_socket)
{
    a_socket->addr_len = sizeof(a_socket->srv_addr);
    if(sendto( a_socket->sock_fd, 
                 a_socket->buf, 
                 LIB_SOCKETS_BUFFER_LENGTH,
                 a_socket->sock_flags,
                 (struct sockaddr*)a_socket->srv_addr,
                 &a_socket->addr_len
               ) == -1
       )
    {
        printf( "libSocket_SocketSendTo(): Failed to Tx data to %s\n",
                a_socket->srv_addr.sun_path
               );
        return -1;
    }
    else
    {
        printf( "libSocket_SocketSendTo(): Transmitted packet to %s. Data: %s\n",
                a_socket->srv_addr.sun_path,
                a_socket->buf
              );
        return 0;
    }
}

int libSocket_SocketClose(lib_sockets_socket_t * a_socket)
{
    close(a_socket->sock_fd);
    bzero(a_socket, sizeof(lib_sockets_socket_t));
}
