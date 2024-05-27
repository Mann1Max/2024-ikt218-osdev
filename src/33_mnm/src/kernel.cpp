extern "C" int kernel_main(void);

int kernel_main(){

    register_irq_handler(IRQ1, keyboard_handler, NULL);


    while(true){};
    return 0;
}