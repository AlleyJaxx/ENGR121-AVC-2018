#include <stdio.h>
#include "E101.h"

int main() {
	init();
	
	int adc_reading = 0;
	int adc_reading2 = 0;
	int adc_reading3 = 0;
	
	for (int x = 1; x < 10; x = x + 1) {
		adc_reading = read_analog(0);
		adc_reading2 = read_analog(1);
		adc_reading3 = read_analog(2);
		
		
		sleep1(1, 0);
		
		printf("%d, %d, %d,", adc_reading, adc_reading2, adc_reading3);
	
}

return 0;
}
