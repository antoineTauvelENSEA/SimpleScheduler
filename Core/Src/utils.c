#include "main.h"
#include "ssd1315.h"
#include <stdio.h>
#include <stdlib.h>
#include "fonts.h"

int global_led_period=1000;
extern UART_HandleTypeDef huart2;

void readUSART(void){
	char ch;
	char stringBuf[32];
	int status=HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, 0);
	if (status==HAL_OK){
		switch (ch){
		case '+' : 	global_led_period+=200;
		  sprintf(stringBuf,"Period = %d",global_led_period);
		  ssd1315_DrawString(0,0,stringBuf,&Font_7x10);
		  ssd1315_Refresh();
					break;
		case '-' : 	global_led_period-=200;
					  sprintf(stringBuf,"Period = %d   ",global_led_period);
					  ssd1315_DrawString(0,0,stringBuf,&Font_7x10);
					  ssd1315_Refresh();
					  break;

		}
	}
}

void displayLED(void){
	if((HAL_GetTick()%global_led_period)<global_led_period/2){
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
	}
	else{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
	}
}
