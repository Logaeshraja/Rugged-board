#include <unistd.h>
#include <stdio.h>
#include <mraa/gpio.h>

int main() {
    mraa_gpio_context led;

    // Initialize GPIO 61
    led = mraa_gpio_init(61);
    if (led == NULL) {
        printf("Failed to initialize GPIO 61\n");
        return 1;
    }

    // Set GPIO as output
    if (mraa_gpio_dir(led, MRAA_GPIO_OUT) != MRAA_SUCCESS) {
        printf("Failed to set GPIO direction\n");
        mraa_gpio_close(led);
        return 1;
    }

    printf("LED blinking on GPIO 61...\n");

    // Blink LED continuously
    while (1) {
        mraa_gpio_write(led, 0);  // LED ON
        usleep(500000);           // 500 ms
        mraa_gpio_write(led, 1);  // LED OFF
        usleep(500000);           // 500 ms
    }

    mraa_gpio_close(led);
    return 0;
}
