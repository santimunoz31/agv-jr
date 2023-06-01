#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

#define ENCA_PIN 3
#define ENCB_PIN 4

int count_value = 0;

void encoder_callback(uint gpio,uint32_t events)
{

    if(gpio_get(ENCB_PIN)>0){
        count_value += 1;
    } else {
        count_value -=1;
    }
}

int main()
{
    stdio_init_all();
    gpio_init(ENCA_PIN);
    gpio_set_dir(ENCA_PIN,GPIO_IN);
    gpio_init(ENCB_PIN);
    gpio_set_dir(ENCB_PIN,GPIO_IN);
    gpio_pull_up(ENCA_PIN);
    gpio_pull_up(ENCB_PIN);

    gpio_set_irq_enabled_with_callback(ENCA_PIN,GPIO_IRQ_EDGE_RISE,1,encoder_callback);

    while(true)
    {
       printf("cuenta = %d\n",count_value);
       sleep_ms(250);
    }
}