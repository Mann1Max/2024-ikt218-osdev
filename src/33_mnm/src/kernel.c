#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include "../include/gdt.h"
#include "libc/string.h"
#include <libc/stdio.h>
#include "../include/idt.h"
#include "../include/interrupts.h"
#include "monitor.h"

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    monitor_initialize();
    init_gdt();
    init_idt();
    init_irq();

   // init_interrupts();

   char* hello_world = "Hello World!\n";
    size_t len = strlen(hello_world);
    monitor_write(hello_world, len);

    //asm volatile("int $0x0");
   
    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}