

#include <stdint.h>

#define RCC_Base		0x40021000
#define Port_A_Base		0x40010800
#define RCC_APB2ER 		*(volatile uint32_t *) (RCC_Base + 0x18)
#define GPIO_CRH	 	*(volatile uint32_t *) (Port_A_Base + 0x4)
#define GPIO_ODR		*(volatile uint32_t *) (Port_A_Base + 0x0C)


int main(void)
{
	RCC_APB2ER 	|=1<<2 ;
	GPIO_CRH 	&= 0xff0fffff ;
	GPIO_CRH 	|= 0x00200000;
	while (1)
	{
		GPIO_ODR |= 1<<13;
		for (int i=0 ; i<5000 ;i++);
		GPIO_ODR &= ~(1<<13);
		for (int i=0 ; i<5000 ;i++);
	}

	return 0 ;
}

