#ifndef GERAL_H
#define GERAL_H
#include <inttypes.h>
#include <arpa/inet.h>
#include "Lists/List.h"

double minPack = INT_MAX;
double maxPack = 0;
double sizeMed = 0;
double packSize = 0;
int recvPacks = 0;


int recvICMP = 0;
int recvICMPRequest = 0;
int recvICMPReply = 0;

int recvUDP = 0;
int recvTCP = 0;
int tcpConnectionsStarted = 0;


//metodos auxiliares
double max(double a, double b)
{
	if (a > b) return a;
	return b;
}

double min(double a, double b)
{
	if (a < b) return a;
	return b;
}

//metodos essenciais
void analisaTamanho(unsigned char buff1[])
{
	packSize = 2 << (strlen(buff1)-1); //2^(package size) [in bytes]

	minPack = min(packSize, minPack);
	maxPack = max(packSize, maxPack);

	sizeMed = ((sizeMed * recvPacks) + packSize)/(recvPacks + 1);
	recvPacks++;
}

void printTamanhos()
{
	printf("Numero de pacotes recebidos.....................%d\n", recvPacks);

	printf("Tamanho do pacote atual.........................%i\n", (int)packSize);
	printf("Tamanho médio de pacotes........................%i\n", (int)sizeMed);

	printf("Menor pacote recebido ate o momento.............%i\n", (int)minPack);
	printf("Maior pacote recebido ate o momento.............%i\n", (int)maxPack);
}
void printICMP()
{
	printf("\nPacotes ICMP recebidos..........................%i\n", recvICMP);
	printf("	Request.................................%i\n", recvICMPRequest);
	printf("	Reply...................................%i\n", recvICMPReply);
}
char * in_addr_t_toString(in_addr_t ip_addr){
	return inet_ntoa(*(struct in_addr *)&ip_addr);
}

void print_top_five()
{
    int cont = 5 < cont_addr ? 5 : cont_addr;
    printf("\nIPs mais acessados\n");
    char * s = 0;
    while(cont)
    {
        s = in_addr_t_toString(list_addr[cont-1].addr);
        printf("	Top %i IP  -  %s\n",cont,s);
        printf("	      Quantidade........................%i\n",list_addr[cont-1].qtd);
        cont--;
    }
}

void printData(){
	printf("\n\n------------------[INICIO DO PACOTE]-------------------\n\n");
	printTamanhos();
	printICMP();
    print_top_five();
	printf("\n\n--------------------[FIM DO PACOTE]---------------------\n\n");

}

#endif