#include "idt.h"
#include "./libc/string.h"
#include "memory.h"
#include "interrupts.h"
#include "libc/stddef.h"


// Define an IDT with 256 entries
static struct idt_entry_t idt[IDT_ENTRIES];
static struct idt_ptr_t idt_ptr;

extern void idt_flush(uint32_t);
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = sel;
    idt[num].zero = 0;
    idt[num].flags = flags | 0x60;
}

void init_idt() {
    idt_ptr.limit = (sizeof(struct idt_entry_t) * IDT_ENTRIES) - 1;
    idt_ptr.base = (uint32_t)&idt;

    for (int i = 0; i < IDT_ENTRIES; i++) {
    idt[i].base_low = 0x0000;
    idt[i].base_high = 0x0000;
    idt[i].selector = 0x08;
    idt[i].zero = 0x00;
    idt[i].flags = 0x8E;

	int_handlers[i].handler = NULL;
  }

    memset(&idt, 0, sizeof(struct idt_entry_t) * IDT_ENTRIES);

    // Set individual IDT entries (ISR handlers)

    init_interrupts();

    
    idt_load(&idt_ptr);
}

void idt_load(struct idt_ptr_t *idt_ptr) {
    asm volatile("lidt (%0)" : : "r" (idt_ptr));
}
