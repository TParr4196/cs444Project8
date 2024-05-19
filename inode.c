#include "inode.h"
#include "image.h"
#include "block.h"
#include "free.h"

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