#ifndef LIST_H
#define LIST_H
#include <stdint.h>
typedef uint32_t in_addr_t;
typedef struct ent
{
    in_addr_t addr;
    int qtd;
} entry;

int get_qtd_addr(in_addr_t addr);
void include_addr(in_addr_t addr);
void print_top_five();

#endif //LIST_H
