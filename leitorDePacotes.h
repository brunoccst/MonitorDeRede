#define leitorDePacotes.h

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

void printEthernet(struct ether_header ethernet)
{
	printf("-----------------\n[ETHERNET]\n");
	printf("MAC Destino: %s \n", (char *) ether_ntoa((struct ether_addr *) ethernet.ether_dhost));

	printf("MAC Origem: %s \n", (char *) ether_ntoa((struct ether_addr *) ethernet.ether_shost));

	printf("Tipo: %x\n", ntohs(ethernet.ether_type));
}
