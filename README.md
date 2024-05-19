# Test File System

## Building
`make` to build. An executable called `testfs` will be produced.
`make clean` to remove .o build products
`make pristine` to clean up all build products

## Files
`testfs.c`: Project 3 of cs444 designed to explore use of semaphores through producer/consumer threads.
`block.c`: defines functions to read and write to and from buffers and the disk
`image.c`: defines functionalilty to open, close, and store a global file descriptor representing a disk
`inode.c`: 
`free.c`: contains functions to set or find individual free bits in a block
`block.h`: header file for block.c
`image.h`: header file for image.c
`ctest.h`: header file for Beej's Test Code
`inode.h`: header file for inode.c
`free.h`: header file for free.c

## Data
makes use of reading and writing to a text file in order to help simulate management of a disk on a computer. 
It is partitioned into blocks of size 4096 bytes. These bytes are represented by the unsigned char type.

## Functions
`main`
    `image_open`: opens a global file descriptor representing the disk
    `image_close`: closes the global file descriptor
    `bread`: writes an unsigned char array to the designated block
    `bwrite`: writes from the "disk" to the provided buffer
    `ialloc`: allocates and returns the index of the first free inode in the inode map
        `find_free`: finds the first 0 bit in an unsigned char array
        `set_free`: sets the designated index of an unsigned char array to the designated value
    `alloc`:

## Notes
