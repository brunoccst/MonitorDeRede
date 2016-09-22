#ifndef LIST_H
#define LIST_H
#include <stdint.h>
#include "../geral.h"
typedef uint32_t in_addr_t;
typedef struct ent
{
    in_addr_t addr;
    int qtd;
} entry;

int cont_addr = 0;
int size = sizeof(entry)*10;//Tamanho inicial
entry * list_addr = 0;


void init(){
    if(!list_addr){
        list_addr = (entry *)malloc(size);
        memset(list_addr,0,size);
    }
}
void reallocate_addr()
{
    if(size <= sizeof(entry) * cont_addr)
    {
        size*=2;
        entry * list_addr_aux = (entry *) malloc(size);
        memset(list_addr_aux,0,size);
        memcpy(list_addr_aux,list_addr, size/2);
        list_addr = list_addr_aux;
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

int get_qtd_addr(in_addr_t addr)
{
    entry * addr_entry =  find_addr(addr);
    return addr_entry ? (*addr_entry).qtd : 0;
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

void print_top_five()
{
    int cont = 5 < cont_addr ? 5 : cont_addr;
    printf("------IPs mais acessados:------\n");
    char * s = 0;
    while(cont)
    {
        s = in_addr_t_toString(list_addr[cont-1].addr);
        printf("----Top %i : IP: %s    Quantidade: %i\n",cont,s,list_addr[cont-1].qtd);
        cont--;
    }
    printf("-------------------------------\n");
}

#endif //LIST_H
