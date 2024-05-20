#include "inode.h"
#include "image.h"
#include "block.h"
#include "free.h"
#include <stdio.h>

static struct inode incore[MAX_SYS_OPEN_FILES] = {0};

int ialloc(void){
    //get inode map
    unsigned char buffer[4096]={0};
    bread(1, buffer);

    //find and set as used first available free inode
    int index=find_free(buffer);
    if (index<0)
        return -1;
    
    set_free(buffer, index, 1);

    //write new map back out to disk
    bwrite(1, buffer);

    return index;
}

struct inode *incore_find_free(void){
    for(int i=0; i<MAX_SYS_OPEN_FILES; i++){
        if(incore[i].ref_count==0){
            return incore+i;
        }
    }
    return NULL;
}

struct inode *incore_find(unsigned int inode_num){
    for(int i=0; i<MAX_SYS_OPEN_FILES; i++){
        if(incore[i].ref_count == 0 && incore[i].inode_num==inode_num){
            return incore+i;
        }
    }
    return NULL;
}

void incore_free_all(void){
    for(int i=0; i<MAX_SYS_OPEN_FILES; i++){
        incore[i].ref_count=0;
    }
}

void incore_all_used(void){
    for(int i=0; i<MAX_SYS_OPEN_FILES; i++){
        incore[i].ref_count=1;
    }
}