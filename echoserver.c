#include <stdio.h>


open_listenfd(char *port){
    struct addrinfo hints, *list *ptr;
    int listenfd;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;
    Getaddrinfo(NULL, port, &hints, &listp);

    for(p = listp; p; p=ai_next){
        if((listenfd=socket(p->ai_family, p->ai_socktype, p-> ai_protocol))<0){
            continue;
        }
        
        Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));
        
        if(bind(listenfd, p->ai_addr, p->ai_addrlen)==0) break;
        close(listenfd);
    }

    Freeaddinfo(listp);
    if(!p) return -1;
    
    if(listen(listenfd,LISTENQ)<0){
        Close(listenfd);
        return -1;
    }

    return listenfd;
}

int main(int argc, char **argv){
      
      int listenfd = open_listenfd(argv[1]);
      while(1){
          int fd = accept(listenfd, NULL, NULL);
          char buffer[1024];
          int n = read(fd, buffer, sizeof(buffer));
          write(fd, buffer, n);
          close(fd);
      }
}

