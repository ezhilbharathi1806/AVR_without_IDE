// Default clock source is internal 8MHz RC oscillator
//#define F_CPU 8000000UL

#include "blink.h"

int main()
{
    blink_led_init();

    while (1)
    {
        blink_led();
    }
    return 0;
}