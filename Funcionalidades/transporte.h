#define transporte

#include <netinet/udp.h> //header udp
#include <netinet/tcp.h> //header tcp
#include "geral.h"
#include "Lists/List.h"

struct tcphdr tcp;
struct udphdr udp;

int load_tcp(char * buffer)
{
    memcpy(&tcp, buffer, sizeof(tcp));
    return sizeof(tcp);
}
void analisaTCP()
{
    recvTCP++;
    include_port(tcp.th_dport,TCP);
}
void printTCP()
{
    
}

int load_udp(char * buffer)
{
    memcpy(&udp, buffer, sizeof(udp));
    return sizeof(udp);
}
void analisaUDP()
{
    recvUDP++;
    include_port(udp.uh_dport,UDP);
}
void printUDP()
{

}
