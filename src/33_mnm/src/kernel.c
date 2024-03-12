#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include "../include/gdt.h"
#include "libc/string.h"
#include <libc/stdio.h>
struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    
    init_gdt();

    char* hello_world = "Hello World!";
    size_t len = strlen(hello_world);
    //write to video memory
    char* video_memory = (char*)0x0b8000;

    //write hellow_world to video_memory:
    for (size_t i = 0; i < len; i++)
    {
        // første linje skriver til 
        video_memory[i*2] =  hello_world[i];
        video_memory[i*2+1] = 0x025;
    }

    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}