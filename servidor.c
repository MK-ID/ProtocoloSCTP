/*
Nombre: servidor SCTP
proposito: recibe mensaje y lo envia devuelta al cliente mediante
el protocolo de sctp
autor: Luis Mikhail Palomino Paucar - 014100965c@uandina.edu.pe
instalar las siguientes librerias en una distribución debian/ubuntu
sudo apt-get install lksctp-tools
sudo apt-get install libsctp-dev
Compilación: gcc servidor.c -o sctp -Wall -lsct

*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
//hjgfds
#include <limits.h>
#include <unistd.h>

#define MAXPENDING 5 /*numero maximo de conexiones*/
#define BUFFSIZE 32

void AvisarError(char *mensaje){
    perror(mensaje);
    exit(1);
}
void AtenderCliente(int sock){
    //variables
    char buffer[BUFFSIZE];
    int received = 0;
    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, HOST_NAME_MAX + 1);

    //recibir mensaje

    if((received=recv(sock,buffer,BUFFSIZE,0))<1){
        AvisarError("No se pudo recibir bytes inciales del cliente");
        close(sock);

    }
    
    //envia bytes y verifica mas datos entrantes
    //hostname;

    while(received>0){
        //enviar deveulta los datos recibidos
        if (send(sock,hostname,sizeof(hostname),0) ==received){
            AvisarError("\nNo se pudo enviar bytes al cliente");
        }
        //verificar mas datos
        if ((received=recv(sock,buffer,BUFFSIZE,0))<0){
            AvisarError("\nNo se pudo recibir bytes adicionales del cliente");
        }
    }

    close(sock);
}
int main(int argc,char *argv[]){
    int serversock;
    int clientsock;
    struct sockaddr_in echoserver;
    struct sockaddr_in echoclient;
    if (argc !=2){
        fprintf(stderr,"USO: servidor <puerto>\n");
        exit(1);
    }
    //crear en socket tcp
    if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_SCTP))<0){
        AvisarError("No se pudo crear socket!");
    }
    /*Construir la estructura sockaddr_in del servidor*/
    //limpiar la estructura
    memset(&echoserver,0,sizeof(echoserver));
    //protocolo internet/ip
    echoserver.sin_family = AF_INET;
    //direccion de ingreso
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY);
    //PUERTO EN QUE ESCUCHA EL SERVIDOR
    echoserver.sin_port = htons(atoi(argv[1]));
    //enlazar el socket del servidor
    if (bind(serversock,(struct sockaddr *)&echoserver,sizeof(echoserver))<0){
        AvisarError("No se pudo enlazar el socket de servidor!");
    }
    //escuchar en el socket del servidor
    if (listen(serversock, MAXPENDING)<0){
        AvisarError("No se pudo escuchar en e socket del servidor");
    }
    //ejecutar hasta que se de la orden de cancelar
    while(1){
        unsigned int clientlen=sizeof(echoclient);
        //esperar conexion de cliente
        if ((clientsock=accept(serversock,(struct sockaddr *)&echoclient,&clientlen))<0){
            AvisarError("No se pudo aceptar conexion de cliente");
        }
        printf("\n========================================");
        fprintf(stdout,"\nCliente conectado con IP: <%s>\n",inet_ntoa(echoclient.sin_addr));
        printf("\n========================================");
        AtenderCliente(clientsock);   
    }
}

