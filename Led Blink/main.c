#include "gp_drive.h"

void delays(int time);

int main(){
	
	init_GP(PC, 13, OUT10, O_GP_PP);
	
	while(1){
		delays(1000000);
		toggle(PC, 13);
	}
}


void delays(int time){

	int i;
	for(i=0;i<time;i++){
	
	}

}

