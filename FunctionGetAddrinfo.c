/*  
    PUCMINAS - Campus Poços de Caldas
    Código em C para resolver nomes DNS para IPv4 e IPv6
    7 Período
    Disciplina: Laboratório de Gerência de redes
    Aluno: Vinícius Roberto Martins
 */


#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

main(int argc, char *argv[])
{
        int soc = 00;
        struct addrinfo hints,*results,*res;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        if (argc <1 || *argv[1] == '\0')
            exit(EXIT_FAILURE);

        int m = getaddrinfo(argv[1],NULL,&hints,&results);
        if (m<0)
        {
                printf("getaddrinfo error :  %s\n", gai_strerror(m));
                return 1;
        }
        res=results;
        
        do{
            if(res->ai_family == AF_INET6)
            {
                struct sockaddr_in6* a= (struct sockaddr_in6*)res->ai_addr;
                char straddr[INET6_ADDRSTRLEN];
                printf("IP v6 - %s\n",inet_ntop(AF_INET6, &a->sin6_addr, straddr, sizeof(straddr)));
            }
            if(res->ai_family == AF_INET)
            {
                struct sockaddr_in* b= (struct sockaddr_in*)res->ai_addr;
                const char* dotted_decimal1 = inet_ntoa(b->sin_addr);
                printf("IP v4 - %s\n",dotted_decimal1);
            }
        }
        while((res=res->ai_next) !=NULL);

        return 0;
}