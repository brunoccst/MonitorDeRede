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

struct ether_header ethernet;

void printEthernet(){
	printf("MAC Destino: %x:%x:%x:%x:%x:%x \n", ethernet.ether_dhost[0],ethernet.ether_dhost[1],ethernet.ether_dhost[2],ethernet.ether_dhost[3],ethernet.ether_dhost[4],ethernet.ether_dhost[5]);
	printf("MAC Origem: %x:%x:%x:%x:%x:%x \n", ethernet.ether_shost[0],ethernet.ether_shost[1],ethernet.ether_shost[2],ethernet.ether_shost[3],ethernet.ether_shost[4],ethernet.ether_shost[5]);
	if (ethernet.ether_type == 0x0800)
	{
//		printf("Tipo: %x \n", ethernet.ether_type);
		printf("ip");
	}
	//printf("Tipo: %u \n", (unsigned int)ethernet.ether_type);
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

	//memset das structs
	memset(&ethernet,0,sizeof(ethernet));


	// recepcao de pacotes
	while (1) {
   		recv(sockd,(char *) &buff1, sizeof(buff1), 0x0);

		memcpy(&ethernet,&buff1,sizeof(ethernet));
		printEthernet();

		
	}
}
