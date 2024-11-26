#include <avr/io.h>
#include <util/delay.h>

void blink_led_init(void){
    DDRB |= (1 << PB0);
}
void blink_led(void){
    PORTB |= (1 << PB0);
    _delay_ms(1000);
    PORTB &= ~(1 << PB0);
    _delay_ms(1000);
}