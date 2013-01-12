#ifndef _EPOLL_FD_I_
#define _EPOLL_FD_I_

namespace ff {

class epoll_fd_i
{
public:
    virtual ~epoll_fd_i(){}

    virtual int socket() = 0;
    virtual int handle_epoll_read()  = 0;
    virtual int handle_epoll_write() = 0;
    virtual int handle_epoll_del() = 0;

    virtual void close() = 0;
};

}

#endif
