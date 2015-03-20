#include <avr/io.h>
#include <util/delay.h>

void wiper(uint16_t a, uint16_t b, uint16_t c, void(*fn)(uint16_t))
{
        for (uint16_t i = a; i < b; i += c)
                fn(i);
        for (uint16_t i = b; i > a; i -= c)
                fn(i);
}

void servo_step(uint16_t i)
{
        OCR1A = i;
        OCR1B = i;
        _delay_ms(10);
}

int main()
{
        TCCR1A |= _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11); // non-inverting mode for OC1A
        TCCR1B |= _BV(WGM13) | _BV(WGM12) | _BV(CS11); // mode 14, prescaler

        ICR1 = 40000; // 320,000 / 8 = 40,000
        DDRB |= _BV(PB1) | _BV(PB2); // OC1A set to output

        for (;;) {
                wiper(900, 4500, 1, servo_step);
                        /*
                        OCR1A = 2000; // 0deg, PW = 1ms
                        _delay_ms(1000);
                        OCR1A = 3000; // 90deg, PW = 1.5ms
                        _delay_ms(1000);
                        OCR1A = 4000; // 180deg, PW = 2ms
                        _delay_ms(1000);
                        */
        }

        return 0;
}
