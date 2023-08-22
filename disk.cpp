#include "disk.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>


FILE* file;

void init() {
    file = fopen("disk.img", "r+");
    // init_table();    **只在最开始时调用一次，初始化磁盘**
    recover();
}

void read_block(int block_id, void* buffer) {
    fseek(file, block_id * BLOCK_SIZE, SEEK_SET);
    fread(buffer, BLOCK_SIZE, 1, file);
}

void write_block(int block_id, const void* data) {
    fseek(file, block_id * BLOCK_SIZE, SEEK_SET);
    fwrite(data, BLOCK_SIZE, 1, file);
}

void write_data_block(int block_id, const void* data) {
    write_block(block_id, data);
    remove_log_block(block_id);
}

void write_log_block(int block_id, const void* data) {
    int table[HEAD_ITEM_COUNT];
    // 修改日志表
    read_table(table);
    for (int i = 0; i < HEAD_ITEM_COUNT; i++) {
        // 第i项对应第i个日志块状态，-1表示未使用
        if (table[i] == -1) {
            write_block(i + HEAD_BLOCK_COUNT, data);
            // table[i]表示第i个日志块对应block_id数据块
            table[i] = block_id;
            break;
        }
    }
    // 写回日志表
    write_table(table);
}

void remove_log_block(int block_id) {
    int table[HEAD_ITEM_COUNT];
    read_table(table);
    for (int i = 0; i < HEAD_ITEM_COUNT; i++) {
        // 找到block_id数据块对应的日志块位置
        if (table[i] == block_id) {
            table[i] = -1;
            break;
        }
    }
    write_table(table);
}

void recover_block(int block_id) {
    int table[HEAD_ITEM_COUNT];
    read_table(table);
    int data_block_id = table[block_id - HEAD_BLOCK_COUNT];
    void* data = (void*)malloc(BLOCK_SIZE);
    // 从日志块中读出数据
    read_block(block_id, data);
    // 把数据写到对应日志块中
    write_data_block(data_block_id, data);
}

void recover() {
    int table[HEAD_ITEM_COUNT];
    read_table(table);
    for (int i = 0; i < HEAD_ITEM_COUNT; i++) {
        if (table[i] != -1) {
            recover_block(i + HEAD_BLOCK_COUNT);
        }
    }
}

void read_table(void* table) {
    fseek(file, 0, SEEK_SET);
    fread(table, BLOCK_SIZE, HEAD_BLOCK_COUNT, file);
}

void write_table(const void* table) {
    fseek(file, 0, SEEK_SET);
    fwrite(table, BLOCK_SIZE, HEAD_BLOCK_COUNT, file);
}

void init_table() {
    // 初始化日志表
    int table[HEAD_ITEM_COUNT];
    memset(table, -1, HEAD_SIZE);
    write_table(table);
}
