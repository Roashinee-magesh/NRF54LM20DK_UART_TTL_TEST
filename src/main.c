
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/uart.h>
#include <stdio.h>
#include <stdint.h>

#define UART_NODE DT_NODELABEL(uart21)

static const struct device *uart_dev =
    DEVICE_DT_GET(UART_NODE);

int main(void)
{
    uint8_t received_char;

    if (!device_is_ready(uart_dev))
    {
        printk("UART20 device not ready!\n");
        return 0;
    }

    printk("UART20 RX TEST STARTED - 9600 baud\n");

    while (1)
    {
        if (uart_poll_in(uart_dev, &received_char) == 0)
        {
            printk("Received: 0x%02X | ASCII: %c\n",
                   received_char,
                   (received_char >= 32 && received_char <= 126)
                       ? received_char : '.');
        }

        k_sleep(K_MSEC(1));
    }

    return 0;
}
