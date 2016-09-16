/*-------------------------------------------------------------*/
/* Exemplo Socket Raw - Captura pacotes recebidos na interface */
/*-------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

/* Diretorios: net, netinet, linux contem os includes que descrevem */
/* as estruturas de dados do header dos protocolos   	  	        */

#include <net/if.h>  //estrutura ifr
#include <netinet/ether.h> //header ethernet
#include <net/ethernet.h> //header ethernet
#include <netinet/ip.h> //header ipv4
#include <netinet/ip6.h> //header ipv6
#include <netinet/udp.h> //header udp
#include <netinet/tcp.h> //header tcp
#include <netinet/ip_icmp.h> //header icmp
#include <netinet/icmp6.h> //header icmp6
#include <net/if_arp.h> //header arp
//TODO: Adicionar o header dns
#include <netinet/in.h> //definicao de protocolos
#include <arpa/inet.h> //funcoes para manipulacao de enderecos IP

#include <netinet/in_systm.h> //tipos de dados

#define BUFFSIZE 1518

// Atencao!! Confira no /usr/include do seu sisop o nome correto
// das estruturas de dados dos protocolos.

  unsigned char buff1[BUFFSIZE]; // buffer de recepcao

  int sockd;
  int on;
  struct ifreq ifr;

struct ethernet_package{
	unsigned char dest[6];
	unsigned char host[6];
	unsigned char type[2];
};
struct IP_package{
	unsigned char Version;
	unsigned char IHL;
	unsigned char ToS[2];
	unsigned char ToL[4];
	unsigned char Id[4];
	unsigned char Flags_Offset[4];
	unsigned char TTL[2];
	unsigned char Potocol[2];
	unsigned char Checksum[4];
	unsigned char src_addres[8];
	unsigned char dst_addres[8];
	unsigned char options[8];
};
struct ethernet_package ethernet;
struct IP_package ip;

//unsigned short int getType(struct ethernet_package ether){
//	return ((ether.type[0] << 1) & 0xff00) + ether.type[1];
//}

void printIP(){	
	memset(&ip,0,sizeof(ip));
	memcpy(&ip,&buff1,sizeof(ip));
}
void printEthernet(){
	memset(&ethernet,0,sizeof(ethernet));
	memcpy(&ethernet,&buff1,sizeof(ethernet));
	printf("MAC Destino: %x:%x:%x:%x:%x:%x \n", ethernet.dest[0],
												ethernet.dest[1],
												ethernet.dest[2],
												ethernet.dest[3],
												ethernet.dest[4],
												ethernet.dest[5]);
	printf("MAC Origem: %x:%x:%x:%x:%x:%x \n", 	ethernet.host[0],
											   	ethernet.host[1],
											   	ethernet.host[2],
											   	ethernet.host[3],
											   	ethernet.host[4],
											   	ethernet.host[5]);
	
	printf("Tipo: %02x%02x \n", ethernet.type[0],ethernet.type[1]);
	if( 0x08 == ethernet.type[0] && 
		0x0 == ethernet.type[1] )
	{
		printIP();
	}
}
int main(int argc,char *argv[])
{
    /* Criacao do socket. Todos os pacotes devem ser construidos a partir do protocolo Ethernet. */
    /* De um "man" para ver os parametros.*/
    /* htons: converte um short (2-byte) integer para standard network byte order. */
    if((sockd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
       printf("Erro na criacao do socket.\n");
       exit(1);
    }

	// O procedimento abaixo eh utilizado para "setar" a interface em modo promiscuo
	strcpy(ifr.ifr_name, "enp4s0");
	if(ioctl(sockd, SIOCGIFINDEX, &ifr) < 0)
		printf("erro no ioctl!");
	ioctl(sockd, SIOCGIFFLAGS, &ifr);
	ifr.ifr_flags |= IFF_PROMISC;
	ioctl(sockd, SIOCSIFFLAGS, &ifr);
	int num_pck = 0;
	double size_med = 0;
	int aux = 0; 
	// recepcao de pacotes
	while (1) {
   		recv(sockd,(char *) &buff1, sizeof(buff1), 0x0);
		if(strlen(buff1) > 0){
			aux = 2 << (strlen(buff1)-1);
			size_med = ((size_med * num_pck) + aux)/(num_pck+1);
			num_pck++;
			printf("\nTamanho pacote:%d", aux);
			printf("\nNumero de pacotes recebidos: %d \nTamanho médio de pacotes: %f\n",num_pck,size_med);
		}
		//printEthernet();

		
	}
}
