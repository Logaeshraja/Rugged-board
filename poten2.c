#include <stdio.h>
#include <unistd.h>
#include "mraa/aio.h"
#include "mraa/gpio.h"

#define ADC_PIN  6
#define LED1     61
#define LED2     62
#define LED3     63
#define MAX      1023

int main()
{
    mraa_aio_context adc = mraa_aio_init(ADC_PIN);
    mraa_gpio_context l1 = mraa_gpio_init(LED1);
    mraa_gpio_context l2 = mraa_gpio_init(LED2);
    mraa_gpio_context l3 = mraa_gpio_init(LED3);

    mraa_gpio_dir(l1, MRAA_GPIO_OUT);
    mraa_gpio_dir(l2, MRAA_GPIO_OUT);
    mraa_gpio_dir(l3, MRAA_GPIO_OUT);

    printf("Reading potentiometer..\n");

    while (1) {
        int value = mraa_aio_read(adc);
        printf("ADC Value: %d\n", value);

        if (value < 20) {
            mraa_gpio_write(l1, 1);
            mraa_gpio_write(l2, 0);
            mraa_gpio_write(l3, 0);
        }
        else if (value < 30) {
            mraa_gpio_write(l1, 1);
            mraa_gpio_write(l2, 1);
            mraa_gpio_write(l3, 0);
        }
        else {
            mraa_gpio_write(l1, 0);
            mraa_gpio_write(l2, 0);
            mraa_gpio_write(l3, 0);
        }

        sleep(1);
    }

    return 0;
}
