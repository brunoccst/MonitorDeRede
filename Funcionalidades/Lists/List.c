#include <string.h>
#include <stdlib.h>
#include "List.h"

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
        memset(list_addr,0,size);
        memcpy(list_addr_aux,list_addr, size/2);
        free(list_addr);
        list_addr = list_addr_aux;
    }
}

void find_addr(in_addr_t addr, entry * addr_entry)
{
    init();
    int aux = cont_addr;
    addr_entry = list_addr;
    while(aux--)
    {
        if(addr == (*(addr_entry++)).addr)
            return;
    }
    addr_entry = 0;
}

int get_qtd_addr(in_addr_t addr)
{
    entry * addr_entry = 0;
    find_addr(addr,addr_entry);
    return addr_entry ? (*addr_entry).qtd : 0;
}
void include_addr(in_addr_t addr)
{
    entry * addr_entry = 0;
    find_addr(addr,addr_entry);
    // TODO INSERIR NA POSIÇÃO ORDENADO PELA QUANTIDADE
    if(addr_entry)
    {
        (*addr_entry).qtd++;
        if(addr_entry != &addr_entry[0])
        {
            entry * entry_aux;
            entry * entry_anterior = addr_entry -1;
            while((*entry_anterior).qtd < (*addr_entry).qtd++)
            {
                *entry_aux = *addr_entry;
                *addr_entry = *entry_anterior;
                *entry_anterior = *entry_aux;
                addr_entry--;
                if(entry_anterior == &addr_entry[0])
                    break;
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
    int cont = 5;
    printf("------IPs mais acessados:------\n");
    while(cont--)
    {
        if(list_addr[cont-1].qtd == 0)
            continue;
        printf("----Top %i : IP:    Quantidade\n",cont);
    }
    printf("-------------------------------\n");
}