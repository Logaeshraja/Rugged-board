#include <stdio.h>
#include <unistd.h>
#include "mraa/aio.h"

#define ADC_PIN 6   /* Change to actual ADC pin number on RB-A5D2X */

int main()
{
    mraa_aio_context adc = mraa_aio_init(ADC_PIN);

    if (adc == NULL) {
        printf("Failed to initialize ADC pin %d\n", ADC_PIN);
        return 1;
    }

    printf("Reading potentiometer..\n");

    while (1) {
        int value = mraa_aio_read(adc);
        printf("Raw ADC Value: %d\n", value);
        sleep(1);
    }

    mraa_aio_close(adc);
    return 0;
}
