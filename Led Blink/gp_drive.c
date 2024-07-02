#include "gp_drive.h"

void init_GP(unsigned short port, unsigned short pin, unsigned short mode, unsigned short confg){


	volatile unsigned long * CR;
	unsigned short tPIN = pin;
	unsigned short offset = 0x00;
	
	if(pin > 7){
		
		tPIN -= 8;
		offset = 0x01;
	}
	
	if(port == 1){ //Enabling port A
	
		RCC_APB2ENR |= 4;
		CR = (volatile unsigned long *) (&GPIO_A + offset);
	}
	else if(port == 2){ //Enabling port B
	
		RCC_APB2ENR |= 8;
		CR = (volatile unsigned long *) (&GPIO_B + offset);
	}
	else if(port == 3){ //Enabling port C
	
		RCC_APB2ENR |= 16;
		CR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	
	*CR &= ~(0xf << (tPIN * 4)); //Reset the target pin
	*CR |= ((mode << (tPIN * 4)) | (confg << (tPIN*4+2))); //setup the pin configuration


}
int R_GP(unsigned short port, unsigned short pin){

	volatile unsigned long * IDR;
	unsigned short offset = 0x02;
	
	if(port == 1){ //Enabling port A
	
		IDR = (volatile unsigned long *) (&GPIO_A + offset);
	}
	else if(port == 2){ //Enabling port B
	
		IDR = (volatile unsigned long *) (&GPIO_B + offset);
	}
	else if(port == 3){ //Enabling port C
	
		IDR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	return (*IDR & (0x1<<pin))>>pin;

}

void W_GP(unsigned short port, unsigned short pin, unsigned short status){

	volatile unsigned long * ODR;
	unsigned short offset = 0x03;
	
	if(port == 1){ //Enabling port A
	
		ODR = (volatile unsigned long *) (&GPIO_A + offset);
	}
	else if(port == 2){ //Enabling port B
	
		ODR = (volatile unsigned long *) (&GPIO_B + offset);
	}
	else if(port == 3){ //Enabling port C
	
		ODR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	status ? (*ODR |= (status<<pin)) : (*ODR &= ~(1<<pin));

}

void toggle(unsigned short port, unsigned short pin){

	if(R_GP(port, pin)){
			W_GP(port, pin, 0);
	}
	else{
		W_GP(port, pin, 1);
	}

}