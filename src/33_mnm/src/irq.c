#include "interrupts.h"
#include "common.h"
#include "libc/stddef.h"
#include "libc/stdio.h"
#include "monitor.h"  // Include this line
#include "libc/string.h"
#include "input.h"

// irq.c
void timer_handler(registers_t* regs, void* data) {
    static uint32_t tick = 0;
    tick++;
    char buffer[50];
    //monitor_write("Timer interrupt: ", 17);
    //int_to_string(tick, buffer);
    //monitor_write(buffer, strlen(buffer));
    //monitor_put('\n');
}

void keyboard_handler(registers_t* regs, void* data) {
    unsigned char scancode = inb(0x60);
    char f = scancode_to_ascii(&scancode);
    unsigned char printarray[2];
    printarray[0]= f;
    printarray[1]= '\0';
    printf("%s", printarray);

}

void irq2_handler(registers_t* regs, void* data) {
    monitor_write("IRQ2 handled\n", 13);
}

void init_irq() {
    for (int i = 0; i < IRQ_COUNT; i++) {
        irq_handlers[i].data = NULL;
        irq_handlers[i].handler = NULL;
        irq_handlers[i].num = i;
    }
    register_irq_handler(IRQ0, timer_handler, NULL);
    register_irq_handler(IRQ1, keyboard_handler, NULL);
    register_irq_handler(IRQ2, irq2_handler, NULL);
}


void register_irq_handler(int irq, isr_t handler, void* ctx) {
    irq_handlers[irq].handler = handler;
    irq_handlers[irq].data = ctx;
}

void irq_handler(registers_t regs) {
    if (regs.int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);

    struct int_handler_t intrpt = irq_handlers[regs.int_no];
    if (intrpt.handler != 0) {
        intrpt.handler(&regs, intrpt.data);
    }
}
