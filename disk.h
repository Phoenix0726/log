#ifndef DISK_H
#define DISK_H


#define BLOCK_SIZE 64
#define LOG_AREA_BLOCK_COUNT 16
#define LOG_AREA_SIZE LOG_AREA_BLOCK_COUNT * BLOCK_SIZE
#define HEAD_BLOCK_COUNT 1
#define HEAD_SIZE HEAD_BLOCK_COUNT * BLOCK_SIZE
#define HEAD_ITEM_COUNT HEAD_SIZE / 4
#define LOG_OFF HEAD_SIZE
#define DATA_OFF LOG_OFF + LOG_AREA_SIZE


void init();

void read_block(int block_id, void* buffer);

void write_block(int block_id, const void* data);

void write_data_block(int block_id, const void* data);

void write_log_block(int block_id, const void* data);

void remove_log_block(int block_id);

void recover_block(int block_id);

void recover();

void read_table(void* table);

void write_table(const void* table);

void init_table();


#endif