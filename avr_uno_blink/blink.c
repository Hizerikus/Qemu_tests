/*
 * blink.c - minimal blink sketch for ATmega328P (Arduino Uno) under QEMU.
 *
 * Toggles PB5 (on-board LED) and prints over UART each toggle,
 * so the blink is observable from the serial console.
 */

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

static void uart_init(void)
{
    /* 9600 baud @ 16 MHz, double-speed mode */
    UBRR0H = 0;
    UBRR0L = 103;
    UCSR0A = (1 << U2X0);
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

static void uart_putc(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
}

static void uart_puts(const char *s)
{
    while (*s)
        uart_putc(*s++);
}

int main(void)
{
    DDRB |= (1 << PB5);   /* PB5 as output */
    uart_init();

    uint8_t on = 1;
    for (;;) {
        if (on) {
            PORTB |= (1 << PB5);
            uart_puts("LED: ON\r\n");
        } else {
            PORTB &= ~(1 << PB5);
            uart_puts("LED: OFF\r\n");
        }
        on = !on;
        _delay_ms(500);
    }
}