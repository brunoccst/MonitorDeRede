#define rede

#include <netinet/ip_icmp.h> //header icmp
#include <netinet/icmp6.h> //header icmp6
#include <netinet/ip.h> //header ipv4
#include "Lists/List.h"

int recvICMP = 0;
int recvICMPRequest = 0;
int recvICMPReply = 0;

void analisaIP(struct ip ip_header)
{
    //inclui endereço destino na lista de endereços, e conta as aparições desse endereço
    include_addr(ip_header.ip_dst.s_addr);
    print_top_five();
}

void analisaICMP(struct icmphdr icmp)
{
    recvICMP++;
	if(icmp.type == ICMP_ECHO)
    {
        recvICMPRequest++;
    }
    else if(icmp.type == ICMP_ECHOREPLY)
    {
        recvICMPReply++;
    }

}

void analisaICMP6()
{
	//TODO: Implement
}

void printICMP()
{
	printf("Pacotes ICMP recebidos.............%i\n", recvICMP);
	printf("	Request....................%i\n", recvICMPRequest);
	printf("	Reply......................%i\n", recvICMPReply);
}
