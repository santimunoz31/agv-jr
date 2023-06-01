#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

#define PWM1_PIN 28
#define STBY1_PIN 22
#define ENA1_PIN 26
#define ENB1_PIN 27
#define ENCA1_PIN 3
#define ENCB1_PIN 4

int count1_value = 0;

void encoder1_callback(uint gpio,uint32_t events)
{
    if(gpio_get(ENCB1_PIN)>0){
        count1_value += 1;
    } else {
        count1_value -=1;
    }
}
void encoder_setup(int ENC1A, int ENC1B){
    gpio_init(ENC1A);
    gpio_init(ENC1B);
    gpio_set_dir(ENC1A,GPIO_IN);
    gpio_set_dir(ENC1B,GPIO_IN);
    gpio_pull_up(ENC1A);
    gpio_pull_up(ENC1B); 
    gpio_set_irq_enabled_with_callback(ENC1A,GPIO_IRQ_EDGE_RISE,1,encoder1_callback);
}


class motor {
    public:
    uint slice;
    uint channel;

    motor(int pwm, int stby, int enA, int enB){
        const int pwm_pin = pwm;
        const int stby_pin = stby;
        const int enA_pin = enA;
        const int enB_pin = enB;
        slice =  pwm_gpio_to_slice_num(pwm_pin);
        channel = pwm_gpio_to_channel(pwm_pin);

        gpio_init(stby_pin);
        gpio_init(enA_pin);
        gpio_init(enB_pin);
        gpio_set_dir(stby_pin,GPIO_OUT);
        gpio_set_dir(enA_pin,GPIO_OUT);
        gpio_set_dir(enB_pin,GPIO_OUT);
        gpio_put(stby_pin, 1);
        pwm_setup(pwm_pin, slice, channel);

    }

    void pwm_setup(uint pin, uint slice, uint channel)
    {
        // configurar gpio
        gpio_init(pin);
        gpio_set_function(pin, GPIO_FUNC_PWM);
        // configurar modulo PWM
        pwm_set_clkdiv(slice, 1.0); //definir el divisor de clk
        pwm_set_wrap(slice, 400);  //definir resolucion max 65536
        pwm_set_chan_level(slice, channel, 0); //iniciar programa con pwm en 0
        pwm_set_enabled(slice, true); //habilitar el slice
    }
};


int main()
{
    stdio_init_all();
    motor motor1(PWM1_PIN,STBY1_PIN,ENA1_PIN,ENB1_PIN);
    encoder_setup(ENCA1_PIN,ENCB1_PIN);
    // bucle principal
    while(true){
        gpio_put(ENA1_PIN, 1);
        gpio_put(ENB1_PIN, 0);
        //subida
        for(int i = 0; i <= 200; i++)
        {
            // encender el led con brillo bajo
            pwm_set_chan_level(motor1.slice, motor1.channel, i);
            sleep_ms(10);
        }
        printf("cuenta = %d\n",count1_value);
        //bajada
        for(int i = 200; i >= 0; i--)
        {
            // encender el led con brillo bajo
            pwm_set_chan_level(motor1.slice, motor1.channel, i);
            sleep_ms(10);
        }
        printf("cuenta = %d\n",count1_value);

        gpio_put(ENA1_PIN, 0);
        gpio_put(ENB1_PIN, 1);

        for(int i = 0; i <= 200; i++)
        {
            // encender el led con brillo bajo
            pwm_set_chan_level(motor1.slice, motor1.channel, i);
            sleep_ms(10);
        }
        printf("cuenta = %d\n",count1_value);

        //bajada
        for(int i = 200; i >= 0; i--)
        {
            // encender el led con brillo bajo
            pwm_set_chan_level(motor1.slice, motor1.channel, i);
            sleep_ms(10);
        }
        printf("cuenta = %d\n",count1_value);
    }
}