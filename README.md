# Protocolo SCTP
Protocolo SCTP Implementado en C
##### Table of Contents  
[Para distribuciones basadas en Debian/Ubuntu](https://github.com/MK-ID/ProtocoloSCTP/edit/master/README.md#debianubuntu)  
[Para distribuciones basadas en RedHat/Centos](https://github.com/MK-ID/ProtocoloSCTP/edit/master/README.md#redhatcentos)  


## Debian/Ubuntu
Para distribuciones basadas en Debian/Ubuntu
#### Actualizar repositorios
`$ sudo apt-get update`

`$ sudo apt-get upgrade`

#### Instalar Compilador y dependencias
`$ sudo apt-get install gcc`

`$ sudo apt-get install lksctp-tools`

`$ sudo apt-get install libsctp-dev`

## RedHat/Centos
Para distribuciones basadas en RedHat/Centos
#### Actualizar repositorios
`$ sudo yum update`

`$ sudo yum upgrade`

#### Instalar Compilador y dependencias
`$ sudo yum install gcc`

`$ sudo yum install lksctp-tools`

`$ sudo yum install libsctp-dev`


## Compilación
`$ gcc servidor.c -o sctpServer -Wall -lsct`

`$ gcc client_stcp_ip.c -o clienteSctp -Wall -lsctp`


## Ejecución
`$ ./sctpServer <Puerto>`

`$ ./clienteSctp <IP SERVIDOR> <Cadena> <Puerto>`
