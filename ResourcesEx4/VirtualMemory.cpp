//
// Created by pajaro770 on 7/16/24.
//
#include "VirtualMemory.h"
#include "MemoryConstants.h"
#include "PhysicalMemory.h"
#include "math.h"

#define OFFSET_MASK (uint64_t)(pow(2,OFFSET_WIDTH)-1);

/*
 * Initialize the virtual memory
 */
void VMinitialize(){
    //Clear first table
    for (uint64_t i = 0; i < PAGE_SIZE; ++i) {
        VMwrite(i, 0);
    }
}



/* writes a word to the given virtual address
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */

void create_new_table();

/* reads a word from the given virtual address
 * and puts its content in *value.
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */
int VMread(uint64_t virtualAddress, word_t* value){
    word_t addr1;
    word_t addr2;
    word_t addr3;
    word_t addr4;

    uint64_t t1 = virtualAddress >> (OFFSET_WIDTH*TABLES_DEPTH);
    PMread(t1, &addr1);

    uint64_t t2 = virtualAddress >> (OFFSET_WIDTH*(TABLES_DEPTH-1));
    t2 = t2 & OFFSET_MASK;
    PMread(addr1*PAGE_SIZE + t2, &addr2);

    uint64_t t3 = virtualAddress >> (OFFSET_WIDTH*(TABLES_DEPTH-2));
    t3 = t3 & OFFSET_MASK;
    PMread(addr2*PAGE_SIZE + t3, &addr3);

    uint64_t t4 = virtualAddress >> (OFFSET_WIDTH*(TABLES_DEPTH-3));
    t4 = t4 & OFFSET_MASK;
    PMread(addr3*PAGE_SIZE + t4, &addr4);

    uint64_t t5 = virtualAddress & OFFSET_MASK;
    PMread(addr4*PAGE_SIZE + t5, value);
}

int VMwrite(uint64_t virtualAddress, word_t value){
    word_t addr1;
    word_t addr2;
    word_t addr3;
    word_t addr4;

    uint64_t t1 = virtualAddress >> (OFFSET_WIDTH*TABLES_DEPTH);
    PMread(t1, &addr1);

    if(addr1 == 0){
        create_new_table();
    }

    uint64_t t2 = virtualAddress >> (OFFSET_WIDTH*(TABLES_DEPTH-1));
    t2 = t2 & OFFSET_MASK;
    PMread(addr1*PAGE_SIZE + t2, &addr2);

    uint64_t t3 = virtualAddress >> (OFFSET_WIDTH*(TABLES_DEPTH-2));
    t3 = t3 & OFFSET_MASK;
    PMread(addr2*PAGE_SIZE + t3, &addr3);

    uint64_t t4 = virtualAddress >> (OFFSET_WIDTH*(TABLES_DEPTH-3));
    t4 = t4 & OFFSET_MASK;
    PMread(addr3*PAGE_SIZE + t4, &addr4);

    uint64_t t5 = virtualAddress & OFFSET_MASK;
    PMwrite(addr4*PAGE_SIZE + t5, value);
}

