#include "lib_sockets.h"

int libSockets_SocketInit(lib_sockets_socket_t * a_socket)
{
    a_socket->my_addr.sun_family = LIB_SOCKETS_AF_UNIX;
    a_socket->my_addr.sun_path = my_addr;

    a_socket->srv_addr.sun_family = a_af;
    a_socket->srv_addr.sun_path = srv_addr;
}

int libSocket_SocketOpen(lib_sockets_socket_t * a_socket)
{
    memset();
}

extern int libSocket_SocketRcvFrom(lib_sockets_socket_t * a_socket)
{
    
}

extern int libSocket_SocketSendTo(lib_sockets_socket_t * a_socket)
{
    
}

extern int libSocket_SocketClose(lib_sockets_socket_t * a_socket)
{
    
}
