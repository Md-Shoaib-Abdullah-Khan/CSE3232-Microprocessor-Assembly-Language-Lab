#include "stm32f10x.h"
#include "gp_drive.h"


void systik_init();
void DelayMillis();
void delays(int time);

int main(){
	
	init_GP(PA, 0, IN, I_PP);
	init_GP(PC, 13, OUT10, O_GP_PP);
	systik_init();
	
	while(1){
		delays(1000);
		toggle(PC, 13);
		
	}
}

void systik_init(){
	
	
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00ffffff;
	SysTick->VAL = 0;
	SysTick->CTRL |= 5;
	
}
void DelayMillis(){
	SysTick->LOAD = 0x1A5E0 - 1;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x10000) == 0);
	
}

void delays(int time){

int i;
	for(i=0;i<time;i++){
		DelayMillis();
	
	}

}

