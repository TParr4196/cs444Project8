#include "dir.h"
#include "inode.h"
#include "block.h"
#include "pack.h"
#include <stdio.h>

void mkfs(void){
    ;
}
struct directory *directory_open(int inode_num){
    (void)inode_num;
    return NULL;
}

int directory_get(struct directory *dir, struct directory_entry *ent){
    (void)dir;
    (void)ent;
    return 0;
}

void directory_close(struct directory *d){
    (void)d;
}

void ls(void){
    struct directory *dir;
    struct directory_entry ent;

    dir=directory_open(0);

    while (directory_get(dir, &ent) != -1)
        printf("%d %s\n", ent.inode_num, ent.name);

    directory_close(dir);
}