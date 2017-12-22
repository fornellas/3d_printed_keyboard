#include "Timer.h"
#include <avr/interrupt.h>

uint32_t seconds;

ISR(TIMER1_COMPA_vect)
{
  seconds++;
}

void Timer_Init(void)
{
  cli();
  OCR1A = 1.0 / ( (1.0 / 1)  / F_CPU * 1024);
  TCCR1B |= (1 << WGM12) |  (1<<CS12) | (1<<CS10);
  TIMSK1 |= (1 << OCIE1A);
  TCNT1 = 0;
  seconds = 0;
  sei();
}

uint32_t Timer_Secs(void)
{
	uint32_t read_seconds;

	cli();
	read_seconds = seconds;
	sei();

	return read_seconds;
}