#include <stdio.h>
#include <mraa/gpio.h>
#include <unistd.h>

int main()
{
    mraa_gpio_context led1;
    mraa_gpio_context led2;
    mraa_gpio_context led3;
    mraa_gpio_context button;

    int count = 0;
    int state;
    int previous_state = 1;

    /* MRAA GPIO numbers */
    led1 = mraa_gpio_init(61);
    led2 = mraa_gpio_init(62);
    led3 = mraa_gpio_init(63);
    button = mraa_gpio_init(35);

    if (led1 == NULL || led2 == NULL ||
        led3 == NULL || button == NULL)
    {
        printf("GPIO initialization failed\n");
        return 1;
    }

    /* GPIO directions */
    mraa_gpio_dir(led1, MRAA_GPIO_OUT);
    mraa_gpio_dir(led2, MRAA_GPIO_OUT);
    mraa_gpio_dir(led3, MRAA_GPIO_OUT);
    mraa_gpio_dir(button, MRAA_GPIO_IN);

   

    printf("3 LED + 1 SWITCH Program Started\n");

    while (1)
    {
        state = mraa_gpio_read(button);

        /* Button is pressed */
        if (state == 0 && previous_state == 1)
        {
            count++;

            printf("Button pressed: %d time(s)\n", count);
             /* Initially all LEDs OFF */
	    mraa_gpio_write(led1, 1);
	    mraa_gpio_write(led2, 1);
	    mraa_gpio_write(led3, 1);

            /* Select LED according to press count */
            if (count == 1)
            {
                mraa_gpio_write(led1, 0);
		mraa_gpio_write(led2, 1);
		mraa_gpio_write(led3, 1);

                printf("LED1 ON\n");
            }
            else if (count == 2)
            {
                mraa_gpio_write(led1, 1);
		mraa_gpio_write(led2, 0);
                mraa_gpio_write(led3, 1);
		printf("LED2 ON\n");
            }
            else if (count == 3)
            {
                mraa_gpio_write(led1, 1);
		mraa_gpio_write(led2, 1);
		mraa_gpio_write(led3, 0);
                printf("LED3 ON\n");
            }
            else
            {
                count = 1;

		mraa_gpio_write(led1, 0);
		mraa_gpio_write(led2, 0);
                mraa_gpio_write(led3, 0);
                printf("Counter reset  LED1 ON\n");
            }
        }

        /* Button released -> ALL LEDs OFF */
        if (state == 1)
        {
            mraa_gpio_write(led1, 1);
            mraa_gpio_write(led2, 1);
            mraa_gpio_write(led3, 1);
        }

        previous_state = state;

        usleep(10000);
    }

    return 0;
}

