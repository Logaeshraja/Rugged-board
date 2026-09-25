/*
 * uart_led_control.c
 *
 * Embedded Linux C program using the MRAA library.
 * Reads single-character commands ('N' or 'F') over UART /dev/ttyS3
 * (TX-RX loopback connection) and controls a GPIO LED on pin 61.
 *
 *   'N' -> Turn LED ON
 *   'F' -> Turn LED OFF
 *
 * Build (example):
 *   gcc uart_led_control.c -o uart_led_control -lmraa
 *
 * Run (example):
 *   sudo ./uart_led_control
 */

#include <stdio.h>
#include <unistd.h>
#include "mraa/uart.h"
#include "mraa/gpio.h"

#define UART_DEV_PATH   "/dev/ttyS3"
#define UART_BAUDRATE   115200
#define LED_GPIO_PIN    61

int main()
{
    mraa_uart_context uart;
    mraa_gpio_context led;
    mraa_result_t status;
    char rx_buf[1];
    int bytes_read;

    /* ---------- Initialize UART ---------- */
    uart = mraa_uart_init_raw(UART_DEV_PATH);
    if (uart == NULL) {
        fprintf(stderr, "Failed to initialize UART on %s\n", UART_DEV_PATH);
        return 1;
    }

    status = mraa_uart_set_baudrate(uart, UART_BAUDRATE);
    if (status != MRAA_SUCCESS) {
        fprintf(stderr, "Failed to set UART baud rate\n");
        mraa_uart_stop(uart);
        return 1;
    }

    /* 8 data bits, no parity, 1 stop bit */
    mraa_uart_set_mode(uart, 8, MRAA_UART_PARITY_NONE, 1);
    mraa_uart_set_flowcontrol(uart, 0, 0);

    /* ---------- Initialize GPIO for LED ---------- */
    led = mraa_gpio_init(LED_GPIO_PIN);
    if (led == NULL) {
        fprintf(stderr, "Failed to initialize GPIO %d\n", LED_GPIO_PIN);
        mraa_uart_stop(uart);
        return 1;
    }

    mraa_gpio_dir(led, MRAA_GPIO_OUT);
    mraa_gpio_write(led, 0);   /* Start with LED OFF */

    printf("UART LED control started on %s (loopback). Waiting for commands...\n",
           UART_DEV_PATH);

    /* ---------- Main loop: read commands and control LED ---------- */
    while (1) {

        /* Wait until data is available (timeout in ms) */
        if (mraa_uart_data_available(uart, 1000)) {

            bytes_read = mraa_uart_read(uart, rx_buf, 1);

            if (bytes_read > 0) {
                printf("Received command: %c\n", rx_buf[0]);

                if (rx_buf[0] == 'N') {
                    mraa_gpio_write(led, 1);
                    printf("LED status: ON\n");
                }
                else if (rx_buf[0] == 'F') {
                    mraa_gpio_write(led, 0);
                    printf("LED status: OFF\n");
                }
                else {
                    printf("Unknown command. LED status unchanged.\n");
                }
            }
        }

        usleep(100000);  /* small delay: 100 ms */
    }

    /* ---------- Cleanup (unreachable in this infinite loop) ---------- */
    mraa_gpio_close(led);
    mraa_uart_stop(uart);

    return 0;
}
