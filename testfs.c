#include "image.h"
#include "block.h"
#include "free.h"
#include "inode.c"
#include "ctest.h"

#ifdef CTEST_ENABLE

void test_image_open(void){
    CTEST_ASSERT(image_open("image.txt",0)>=0, "image_open returns file descriptor");
}

void test_image_close(void){
    CTEST_ASSERT(image_close()==0, "image_close close() success");
}

void test_bread_bwrite(void){
    unsigned char block_map[4096]={1,1,1,1,1,1};
    bwrite(2,block_map);
    unsigned char buffer[4096]={0};
    CTEST_ASSERT(*bread(2,buffer)==*block_map, "bwrite fills buffer with disk image and bread was successful");
}

void test_alloc(void){
    unsigned char block[4096]={0};
    for(int i=0; i<BLOCK_SIZE; i++){
        block[i]=0xff;
    }
    bwrite(2, block);
    CTEST_ASSERT(alloc()==-1, "returns -1 if block map is full");
    set_free(block, 4, 0);
    set_free(block, 6, 0);
    set_free(block, 15, 0);
    set_free(block, 24, 0);
    bwrite(2, block);
    int chk1 = alloc()==4;
    int chk2 = alloc()==6;
    int chk3 = alloc()==15;
    int chk4 = alloc()==24;
    CTEST_ASSERT(chk1&&chk2&&chk3&&chk4, "alloc arbitrary empty values verified");
}

void test_set_free(void){
    unsigned char block[16]={0};
    set_free(block, 3, 1);
    set_free(block, 17, 1);
    set_free(block, 13, 0);
    set_free(block, 42, 1);
    unsigned char byte=block[0];
    int chk1 = byte & (1 << 3);
    byte=block[2];
    int chk2 = byte & (1 << 1);
    byte=block[1];
    int chk3 = !(byte & (1 << 5));
    byte=block[5];
    int chk4 = byte & (1 << 2);
    CTEST_ASSERT(chk1&&chk2&&chk3&&chk4, "set_free arbitrary sets verified");
}

void test_find_free(void){
    unsigned char block[4096]={0};
    for(int i=0; i<BLOCK_SIZE; i++){
        block[i]=0xff;
    }
    CTEST_ASSERT(find_free(block)==-1, "find_free returns -1 if block is full");
    set_free(block, 2, 0);
    set_free(block, 5, 0);
    set_free(block, 12, 0);
    set_free(block, 22, 0);
    int chk1 = find_free(block)==2;
    set_free(block, 2, 1);
    int chk2 = find_free(block)==5;
    set_free(block, 5, 1);
    int chk3 = find_free(block)==12;
    set_free(block, 12, 1);
    int chk4 = find_free(block)==22;
    CTEST_ASSERT(chk1&&chk2&&chk3&&chk4, "find_free arbitrary empty values verified");
}

void test_ialloc(void){
    unsigned char block[4096]={0};
    for(int i=0; i<BLOCK_SIZE; i++){
        block[i]=0xff;
    }
    bwrite(1, block);
    CTEST_ASSERT(ialloc()==-1, "returns -1 if inode map is full");
    set_free(block, 30000, 0);
    set_free(block, 30500, 0);
    set_free(block, 31000, 0);
    set_free(block, 32000, 0);
    bwrite(1, block);
    int chk1 = ialloc()==30000;
    int chk2 = ialloc()==30500;
    int chk3 = ialloc()==31000;
    int chk4 = ialloc()==32000;
    CTEST_ASSERT(chk1&&chk2&&chk3&&chk4, "ialloc arbitrary empty values verified");
}

int main(){
    CTEST_VERBOSE(1);

    test_image_open();

    test_bread_bwrite();

    test_set_free();

    test_find_free();

    test_ialloc();

    test_alloc();

    test_image_close();

    CTEST_RESULTS();

    CTEST_EXIT();
}

#else

int main(){

    image_open("image.txt",0);

    //initialize an empty data block
    unsigned char block[4096]={0};
    for(int i=0; i<BLOCK_SIZE; i++){
        block[i]=0x0;
    }

    //not sure what goes in the superblock so giving it empty block
    bread(0,block); //superblock
    bread(1,block); //inode_map
    bread(3,block); //inode_data_block_0
    bread(4,block); //inode_data_block_1
    bread(5,block); //inode_data_block_2
    bread(6,block); //inode_data_block_3

    for(int i=0; i<7; i++){
        set_free(block, i,1);
    }

    bread(2,block); //block_map
    
    image_close();
}

#endif