/*-------------------------------------------------------------*/
/* Exemplo Socket Raw - Captura pacotes recebidos na INTERFACE_DEFAULT */
/*-------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <math.h>
#include <inttypes.h>

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
	char *interfaceDoUsuario = argv[1];
	strcpy(ifr.ifr_name, interfaceDoUsuario);

	if(ioctl(sockd, SIOCGIFINDEX, &ifr) < 0)
		printf("\nerro no ioctl!\n\n");
	ioctl(sockd, SIOCGIFFLAGS, &ifr);
	ifr.ifr_flags |= IFF_PROMISC;
	ioctl(sockd, SIOCSIFFLAGS, &ifr);

	//variaveis de monitoramento
	int recvPackages = 0;
	int minPackSize = INT_MAX;
	int maxPackSize = 0;
	int packSize = 0;
	double size_med = 0;
	int posicaoNoBuffer = 0;

	//variaveis de pacotes
	struct ether_header ethernet;
	struct ip ipv4;
	struct ip6_hdr ipv6;

	// recepcao de pacotes
	while (1) {
   		recv(sockd,(char *) &buff1, sizeof(buff1), 0x0);

		packSize = 2 << (strlen(buff1)-1); //2^(package size) [in bytes]

		if (packSize < minPackSize) minPackSize = packSize;
		if (packSize > maxPackSize) maxPackSize = packSize;

		size_med = ((size_med * recvPackages) + packSize)/(recvPackages+1);
		recvPackages++;

		printf("Numero de pacotes recebidos: %d\n", recvPackages);
		printf("Tamanho médio de pacotes: %i\n", (int)size_med);
		printf("Menor pacote recebido ate o momento: %i\n", (int)minPackSize);
		printf("Maior pacote recebido ate o momento: %i\n\n", (int)maxPackSize);

		//ETHERNET
		memcpy(&ethernet,&buff1,sizeof(ethernet));
		posicaoNoBuffer = sizeof(ethernet);
		switch (ntohs(ethernet.ether_type))
		{
			case ETH_P_IP: //IPv4
				memcpy(&ipv4,&buff1[posicaoNoBuffer], sizeof(ipv4));
				posicaoNoBuffer += sizeof(ipv4);
				switch (ipv4.ip_p)
				{
					case 1: //ICMP
						break;
					case 6: //TCP
						break;
					case 17: //UDP
						break;
				}
				break;
			case ETH_P_IPV6: //IPv6
				memcpy(&ipv6,&buff1[posicaoNoBuffer], sizeof(ipv6));
				posicaoNoBuffer += sizeof(ipv6);
				switch (ipv6.ip6_nxt)
				{
					case 58: //IPv6-ICMP
						break;
					case 6: //TCP
						break;
					case 17: //UDP
						break;
				}
				break;
		}
	}
}

