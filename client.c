#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


int open_clientfd(char *hostname, char *port){
    struct addrinfo hints, *listp, *p;
    int connectfd;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
    getaddrinfo(hostname, port, &hints, &listp);
    for(p=listp; p; p=p->ai_next){
        if((connectfd = socket(p->ai_family, p->ai_socktype , p->ai_protocol))<0)
            continue;

        if((connect(connectfd, p->ai_addr, p->ai_addrlen)) != -1)
            break;
        close(connectfd);
    }
    freeaddrinfo(listp);
    if(!p) return -1;
    else return connectfd;
}

int main(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "usage: %s <hostname> <port>\n", argv[0]);
        return -1;
    }
    int connectfd= open_clientfd(argv[1],argv[2]);
    char buffer[1024];
      fgets(buffer, sizeof(buffer), stdin);
      write(connectfd, buffer, strlen(buffer));
      int n = read(connectfd, buffer, sizeof(buffer));
      buffer[n]='\0';
      printf("%s", buffer);
      close(connectfd);
      

}


    
