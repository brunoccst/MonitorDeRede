#define rede

#include <netinet/ip_icmp.h> //header icmp
#include <netinet/icmp6.h> //header icmp6

int recvICMP = 0;
int recvICMPRequest = 0;
int recvICMPReply = 0;

void analisaICMP(struct icmphdr icmp)
{
	
}

void analisaICMP6()
{
	//TODO: Implement
}

void printICMP()
{
	printf("Pacotes ICMP recebidos.............%i", recvICMP);
	printf("	Request....................%i", recvICMPRequest);
	printf("	Reply......................%i", recvICMP);
}
