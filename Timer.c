#include "Timer.h"
#include <avr/interrupt.h>

uint32_t millis;

ISR(TIMER1_COMPA_vect)
{
  millis++;
}

void Timer_Init(void)
{
  cli();
  OCR1A = 1.0 / ( (1.0 / 0.001)  / F_CPU * 1024);
  TCCR1B |= (1 << WGM12) |  (1<<CS12) | (1<<CS10);
  TIMSK1 |= (1 << OCIE1A);
  TCNT1 = 0;
  millis = 0;
  sei();
}

uint32_t Timer_Millis(void)
{
	uint32_t read_millis;

	cli();
	read_millis = millis;
	sei();

	return read_millis;
}

uint32_t Timer_Secs(void)
{
	return Timer_Millis() / 1000;
}