
/*
Author: Luis Mikhail Palomino Paucar
Codigo: 014100965c
Fecha: 20/03/2022
Proposito: este programa envia un mensaje mediante el
protocolo sctp
instalar las siguientes librerias en una distribución debian/ubuntu
sudo apt-get install lksctp-tools
sudo apt-get install libsctp-dev
Compilación: gcc client_stcp_ip.c -o cliente -Wall -lsctp
*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
//#include <winsock.h>
#include <netinet/sctp.h>

#define BUFFSIZE 512

void AvisarError(char *mensaje)
{
	perror(mensaje);
	exit(1);
}

int main(int argc, char *argv[])
{
	//Variables
	int sock;
	struct sockaddr_in echoserver;
	char buffer[BUFFSIZE];
	unsigned int echolen;
	int received = 0;

	//Verificar argumentos necesarios para correr programa
	if(argc !=4)
	{
		fprintf(stderr, "USO: Cliente <ip de servidor> <mensaje> <puerto>\n");
		exit(1);
	}
	//Crear el socket TCP
	if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_SCTP))<0)
	{
		AvisarError("No se pudo crear socket");
	}

	//Construir la estructura sockaddr_in del servidor

	//limpiar la estructura
	memset(&echoserver, 0, sizeof(echoserver));

	//Protocolo de Internet/IP
	echoserver.sin_family = AF_INET;

	//Direccion IP
	echoserver.sin_addr.s_addr = inet_addr(argv[1]);

	//Puerto del servidor
	echoserver.sin_port = htons(atoi(argv[3]));

	//Establecer la conexion
	if(connect(sock,(struct sockaddr *) &echoserver, sizeof(echoserver))<0)
	{
		AvisarError("No se pudo conectar al servidor");
	}

	//Enviar el mensaje al servidor
	echolen = strlen(argv[2]);

	if(send(sock, argv[2], echolen, 0) != echolen)
	{
		AvisarError("Inconsistencia en el numero de bytes enviados");
	}

	//Recibir el mensaje de vuelta desde el servidor
	fprintf(stdout, "Nombre del servidor: ");

	while(received < echolen)
	{
		int bytes = 0;
		if((bytes = recv(sock, buffer, BUFFSIZE-1, 0)) <1)
		{
			AvisarError("No se pudo recibir bytes desde el servidor");
		}

		received += bytes;
		buffer[bytes] ='\0';
		//Cerciorarse que la cadena termine en \0
		printf("%s", buffer);
	}
	fprintf(stdout, "\n");
	close(sock);
	exit(0);
}


