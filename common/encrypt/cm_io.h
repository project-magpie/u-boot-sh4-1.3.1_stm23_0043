#ifndef	__CM_IO_H
#define	__CM_IO_H

#define	 ClockOut()	SET_PIO_PIN(PIO_PORT(3), 4, STPIO_OUT)
#define Clocklow(void)	STPIO_SET_PIN(PIO_PORT(3), 4, 0)
#define ClockHigh(void)	STPIO_SET_PIN(PIO_PORT(3), 4, 0)
#define DataOut(void)	SET_PIO_PIN(PIO_PORT(3), 2, STPIO_OUT)
#define DataIn(void)	SET_PIO_PIN(PIO_PORT(3), 2, STPIO_IN)
#define Datalow(void)	STPIO_SET_PIN(PIO_PORT(3), 2, 0)
#define DataHigh(void)	STPIO_SET_PIN(PIO_PORT(3), 2, 1)
#define DataRd(void)	STPIO_GET_PIN(3, 2)

#endif
