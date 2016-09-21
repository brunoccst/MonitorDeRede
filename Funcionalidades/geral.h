#define geral

#include <inttypes.h>

double minPack = INT_MAX;
double maxPack = 0;
double sizeMed = 0;
double packSize = 0;
int recvPacks = 0;

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
	printf("Numero de pacotes recebidos................%d\n", recvPacks);

	printf("Tamanho do pacote atual....................%i\n", (int)packSize);
	printf("Tamanho médio de pacotes...................%i\n", (int)sizeMed);

	printf("Menor pacote recebido ate o momento........%i\n", (int)minPack);
	printf("Maior pacote recebido ate o momento........%i", (int)maxPack);
}

