#include "guid.h"

#include <string.h>
#include <time.h>

//基准时钟：2019 - 01 - 1 00:00 : 00
#define BASE_TIME   1546272000

//每一group独享一个id生成种子
static int serial_inedx_table[MAX_GROUP + 1] = { 0 };
static time_t last_time = 0;

size_t new_guid(size_t group, size_t index){
    group %= MAX_GROUP;
    index %= MAX_INDEX;

    time_t now_time;
    time(&now_time);
    size_t serial_index = 0;
    if (now_time > last_time) {
        serial_inedx_table[group] = 0;
    }
    else {
        serial_index = ++serial_inedx_table[group];
        //种子溢出以后，时钟往前推
        if (serial_index >= MAX_SNUM) {
            serial_inedx_table[group] = 0;
            last_time = ++now_time;
            serial_index = 0;
        }
    }
    return ((last_time - BASE_TIME) << (SNUM_BITS + GROUP_BITS + INDEX_BITS)) |
            (serial_index << (GROUP_BITS + INDEX_BITS)) | (index << GROUP_BITS) | group;
}
