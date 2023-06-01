#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_PIN 28
#define STBY_PIN 22
#define ENA_PIN 26
#define ENB_PIN 27

int led_value = 0;


void setup(uint pin, uint slice, uint channel)
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

int main()
{
    uint slice =  pwm_gpio_to_slice_num(PWM_PIN);
    uint channel = pwm_gpio_to_channel(PWM_PIN);
    gpio_init(STBY_PIN);
    gpio_set_dir(STBY_PIN, GPIO_OUT);
    gpio_init(ENA_PIN);
    gpio_set_dir(ENA_PIN, GPIO_OUT);
    gpio_init(ENB_PIN);
    gpio_set_dir(ENB_PIN, GPIO_OUT);
    gpio_put(STBY_PIN, 1);
    setup(PWM_PIN, slice, channel);
    // bucle principal
        gpio_put(ENA_PIN, 1);
        gpio_put(ENB_PIN, 0);
        //subida
        for(int i = 0; i <= 200; i++)
        {
            // encender el led con brillo bajo
            pwm_set_chan_level(slice, channel, i);
            sleep_ms(10);
        }
        //bajada
        for(int i = 200; i >= 0; i--)
        {
            // encender el led con brillo bajo
            pwm_set_chan_level(slice, channel, i);
            sleep_ms(10);
        }
        gpio_put(ENA_PIN, 0);
        gpio_put(ENB_PIN, 1);
        for(int i = 0; i <= 200; i++)
        {
            // encender el led con brillo bajo
            pwm_set_chan_level(slice, channel, i);
            sleep_ms(10);
        }
        //bajada
        for(int i = 200; i >= 0; i--)
        {
            // encender el led con brillo bajo
            pwm_set_chan_level(slice, channel, i);
            sleep_ms(10);
        }
        
}