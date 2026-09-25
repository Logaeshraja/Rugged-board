#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define LED_DIR   "/sys/class/gpio/PC13/direction"
#define LED_VALUE "/sys/class/gpio/PC13/value"

int main()
{
    int fd;
    int count = 20;

    /* Set GPIO direction */
    fd = open(LED_DIR, O_WRONLY);
    if (fd < 0)
    {
        perror("Unable to open GPIO direction");
        return 1;
    }

    write(fd, "out", 3);
    close(fd);

    /* Open GPIO value */
    fd = open(LED_VALUE, O_WRONLY);
    if (fd < 0)
    {
        perror("Unable to open GPIO value");
        return 1;
    }

    printf("LED blinking on PC13...\n");

    while (count--)
    {
        write(fd, "1", 1);
        printf("LED ON\n");
        usleep(500000);

        write(fd, "0", 1);
        printf("LED OFF\n");
        usleep(500000);
    }

    write(fd, "0", 1);
    close(fd);

    printf("Blinking completed.\n");

    return 0;
}
