#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mraa/uart.h>

#define UART_PORT "/dev/ttyS3"
#define BAUDRATE 9600

int main()
{
    mraa_uart_context uart;
    char tx_buffer[100];
    char rx_buffer[100];

    /* Initialize UART */
    uart = mraa_uart_init_raw(UART_PORT);

    if (uart == NULL)
    {
        printf("Unable to initialize UART %s\n", UART_PORT);
        return 1;
    }

    /* Set UART baud rate */
    if (mraa_uart_set_baudrate(uart, BAUDRATE) != MRAA_SUCCESS)
    {
        printf("Unable to set baud rate\n");
        mraa_uart_stop(uart);
        return 1;
    }

    printf("UART Loopback started on %s\n", UART_PORT);
    printf("Connect TX to RX.\n");
    printf("Type something and press ENTER:\n\n");

    while (1)
    {
        /* Get keyboard input */
        printf("Enter data: ");
        fflush(stdout);

        if (fgets(tx_buffer, sizeof(tx_buffer), stdin) == NULL)
        {
            break;
        }

        /* Send data through UART TX */
        mraa_uart_write(uart, tx_buffer, strlen(tx_buffer));

        /* Wait for loopback data */
        usleep(100000);

        /* Read received data */
        memset(rx_buffer, 0, sizeof(rx_buffer));

        int bytes_read = mraa_uart_read(
            uart,
            rx_buffer,
            sizeof(rx_buffer) - 1
        );

        if (bytes_read > 0)
        {
            rx_buffer[bytes_read] = '\0';

            printf("Received: %s", rx_buffer);
            fflush(stdout);
        }
        else
        {
            printf("No data received\n");
        }
    }

    /* Stop UART */
    mraa_uart_stop(uart);

    return 0;
}
