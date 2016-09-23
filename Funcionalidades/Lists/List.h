#ifndef LIST_H
#define LIST_H
#include <stdint.h>
typedef uint32_t in_addr_t;

typedef enum {
    UDP,TCP
} type_port;
typedef struct ent
{
    in_addr_t addr;
    int qtd;
} entry;

typedef struct port_ent
{
    u_int16_t port;
    int qtd;
    type_port type;
} port;

int cont_addr = 0;
int size_addr = sizeof(entry)*10;//Tamanho inicial
entry * list_addr = 0;


int cont_port = 0;
int size_port = sizeof(port)*10;//Tamanho inicial
port * list_port = 0;


void init(){
    if(!list_addr){
        list_addr = (entry *)malloc(size_addr);
        memset(list_addr,0,size_addr);
    }
    if(!list_port){
        list_port = (port *)malloc(size_port);
        memset(list_port,0,size_port);
    }
}
void reallocate_addr()
{
    if(size_addr <= sizeof(entry) * cont_addr)
    {
        size_addr*=2;
        entry * list_addr_aux = (entry *) malloc(size_addr);
        memset(list_addr_aux,0,size_addr);
        memcpy(list_addr_aux,list_addr, size_addr/2);
        list_addr = list_addr_aux;
    }
}
void reallocate_port()
{
    if(size_port <= sizeof(port) * cont_port)
    {
        size_port*=2;
        port * list_port_aux = (port *) malloc(size_port);
        memset(list_port_aux,0,size_port);
        memcpy(list_port_aux,list_port, size_port/2);
        list_port = list_port_aux;
    }
}

entry * find_addr(in_addr_t addr)
{
    init();
    int aux = cont_addr;
    entry * addr_entry = list_addr;
    while(aux--)
    {
        if(addr == (*addr_entry).addr){
            return addr_entry;
        }
        addr_entry++;
    }
    return 0;
}

port * find_port(u_int16_t port_number,type_port type)
{
    init();
    int aux = cont_port;
    port * port_entry = list_port;
    while(aux--)
    {
        if(port_number == (*port_entry).port && (*port_entry).type == type)
        {
            return port_entry;
        }
        port_entry++;
    }
    return 0;
}

void include_addr(in_addr_t addr)
{
    entry * addr_entry =  find_addr(addr);
    if(addr_entry)
    {
        (*addr_entry).qtd++;
        if(addr_entry > &list_addr[0])
        {
            entry * entry_aux = (entry *)malloc(sizeof(entry));
            entry * entry_anterior = addr_entry -1;
            while((*entry_anterior).qtd < (*addr_entry).qtd)
            {
                *entry_aux = *addr_entry;
                *addr_entry = *entry_anterior;
                *entry_anterior = *entry_aux;
                if(entry_anterior == &list_addr[0])
                    break;
                addr_entry--;
                entry_anterior--;
            }
        }
    }
    else
    {
        reallocate_addr();
        list_addr[cont_addr].addr = addr;
        list_addr[cont_addr++].qtd = 1;
    }
}


void include_port(u_int16_t port_number, type_port type)
{
    port * port_entry =  find_port(port_number,type);
    if(port_entry)
    {
        (*port_entry).qtd++;
        if(port_entry > &list_port[0])
        {
            port * port_aux = (port *)malloc(sizeof(port));
            port * port_anterior = port_entry -1;
            while((*port_anterior).qtd < (*port_entry).qtd)
            {
                *port_aux = *port_entry;
                *port_entry = *port_anterior;
                *port_anterior = *port_aux;
                if(port_anterior == &list_port[0])
                    break;
                port_entry--;
                port_anterior--;
            }
        }
    }
    else
    {
        reallocate_port();
        list_port[cont_port].port = port_number;
        list_port[cont_port].type = type;
        list_port[cont_port++].qtd = 1;
    }
}


#endif //LIST_H
