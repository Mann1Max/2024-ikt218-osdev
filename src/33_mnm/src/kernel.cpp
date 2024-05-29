extern "C"{
    #include "libc/system.h"
    #include "memory.h"
    #include "common.h"
    #include "interrupts.h"
    #include "input.h"
    #include "pit.h"
    #include "monitor.h"
}

// Existing global operator new overloads
void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}


extern "C" int kernel_main(void);

int kernel_main(){
while(true){
    int counter = 0;

        printf("Debug: Starting loop.\n");
        monitor_write("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);

        sleep_busy(1);
        monitor_write("[%d]: Slept using busy-waiting.\n", counter++);

        monitor_write("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        sleep_interrupt(1);
        monitor_write("[%d]: Slept using interrupts.\n", counter++);
 };    return 0;
}