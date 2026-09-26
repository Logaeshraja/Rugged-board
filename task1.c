#include <unistd.h>
#include "mraa/gpio.h"

#define TICK 50

int main()
{
    mraa_gpio_context led1 = mraa_gpio_init(61);
    mraa_gpio_context led2 = mraa_gpio_init(62);
    mraa_gpio_context led3 = mraa_gpio_init(63);

    mraa_gpio_dir(led1, MRAA_GPIO_OUT);
    mraa_gpio_dir(led2, MRAA_GPIO_OUT);
    mraa_gpio_dir(led3, MRAA_GPIO_OUT);

    int s1 = 0, s2 = 0, s3 = 0;
    int t1 = 0, t2 = 0, t3 = 0;

    while (1) {
        usleep(TICK * 1000);
        t1 += TICK; t2 += TICK; t3 += TICK;

        if (t1 >= 1000) { s1 = !s1; mraa_gpio_write(led1, s1); t1 = 0; }
        if (t2 >= 800)  { s2 = !s2; mraa_gpio_write(led2, s2); t2 = 0; }
        if (t3 >= 400)  { s3 = !s3; mraa_gpio_write(led3, s3); t3 = 0; }
    }

    return 0;
}
