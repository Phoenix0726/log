#include "disk.h"
#include <cstdio>
#include <iostream>


int main()
{
    init();
    // int table[HEAD_ITEM_COUNT];
    // read_table(table);
    // std::cout << "------------------table---------------" << std::endl;
    // for (int i = 0; i < HEAD_ITEM_COUNT; i++) std::cout << table[i] << ' ';
    // std::cout << std::endl;
    int data[BLOCK_SIZE] = {1, 2, 3};
    write_log_block(37, data);
    int buffer[BLOCK_SIZE];
    read_block(37, buffer);
    printf("%d %d %d\n", buffer[0], buffer[1], buffer[2]);
    
    init();
    read_block(37, buffer);
    printf("%d %d %d\n", buffer[0], buffer[1], buffer[2]);
    return 0;
}