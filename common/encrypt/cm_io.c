#include "asm/io.h"
#include "asm/pio.h"

#define PIO_BASE  		0xb8020000
#define	I2C_PORT		3
#define	I2C_PORT_ADDR	PIO_PORT(3)

void	ClockOut(void)
{
	SET_PIO_PIN(I2C_PORT_ADDR, 0, STPIO_OUT);
}

void	ClockLow(void)
{
	STPIO_SET_PIN(I2C_PORT_ADDR, 0, 0);
}

void	ClockHigh(void)
{
	STPIO_SET_PIN(I2C_PORT_ADDR, 0, 1);
}

void	DataOut(void)
{
	SET_PIO_PIN(I2C_PORT_ADDR, 1, STPIO_OUT);
}

void	DataIn(void)
{
	SET_PIO_PIN(I2C_PORT_ADDR, 1, STPIO_IN);
}

void	Datalow(void)
{
	STPIO_SET_PIN(I2C_PORT_ADDR, 1, 0);
}

void	DataHigh(void)
{
	STPIO_SET_PIN(I2C_PORT_ADDR, 1, 1);
}

unsigned char	DataRd(void)
{
	return STPIO_GET_PIN(I2C_PORT, 1);
}


