#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#define LISTENQ 1024
int open_listenfd(char *port){
    struct addrinfo hints, *listp, *p;
    int listenfd;
    int optval=1;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;
    getaddrinfo(NULL, port, &hints, &listp);
    for(p = listp; p; p=p->ai_next){
        if((listenfd=socket(p->ai_family, p->ai_socktype, p-> ai_protocol))<0){
            continue;
        }
        
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));
        
        if(bind(listenfd, p->ai_addr, p->ai_addrlen)==0) break;
        close(listenfd);
    }
    freeaddrinfo(listp);
    if(!p) return -1;
    
    if(listen(listenfd,LISTENQ)<0){
        close(listenfd);
        return -1;
    }
    return listenfd;
}
int main(int argc, char **argv){
    if(argc!=2) return -1;
      
      int listenfd = open_listenfd(argv[1]);
      while(1){
          int fd = accept(listenfd, NULL, NULL);
          char buffer[1024];
          int n = read(fd, buffer, sizeof(buffer));
          write(fd, buffer, n);
          close(fd);
      }
      
}

