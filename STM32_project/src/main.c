/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include <string.h>
#include <stdint.h>


#define TRUE 1
#define FALSE 0
#define NOT_PRESSED FALSE
#define PRESSED TRUE

#ifdef USE_SEMIHOSTING
	// used for semi hosting
	// using semi-hosting cause need to buy UART
	extern void initialise_monitor_handles();
#endif

static void prvSetupUART();
void prvSetupHardware();

void printmsg(char* msg);

void led_task_handler(void* params);
void button_task_handler(void* params);

void prvSetupGPIO();

char usr_msg[250];

uint8_t button_status_flag = NOT_PRESSED;

int main(void)
{

#ifdef USE_SEMIHOSTING
	initialise_monitor_handles();
	printf("Printing using semi-hosting\n");
#endif

	RCC_DeInit();

	SystemCoreClockUpdate();

	prvSetupHardware();


	xTaskCreate(led_task_handler, "LED-TASK", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(button_task_handler, "BUTTON-TASK", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();

	for(;;);
}


void led_task_handler(void* params) {

	while(1) {
		if (button_status_flag == PRESSED) {
			GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_SET);
		} else {
			GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_RESET);
		}
	}

}

void button_task_handler(void* params) {

	while(1) {
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1) {
			button_status_flag = PRESSED;
		} else {
			button_status_flag = NOT_PRESSED;
		}
	}

}


static void prvSetupUART() {
	GPIO_InitTypeDef gpio_uart_pins;
		USART_InitTypeDef uart_2_init;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_APB1PeriphClockCmd(GPIOA, ENABLE);

		// pa2 tx, pa3 rx
		memset(&gpio_uart_pins, 0, sizeof(gpio_uart_pins));
		gpio_uart_pins.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
		gpio_uart_pins.GPIO_Mode = GPIO_Mode_AF;
		gpio_uart_pins.GPIO_PuPd = GPIO_PuPd_UP;

		GPIO_Init(GPIOA, &gpio_uart_pins);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);	//PA2
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);	//PA3

		memset(&uart_2_init, 0, sizeof(uart_2_init));
		uart_2_init.USART_BaudRate = 115200;
		uart_2_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		uart_2_init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
		uart_2_init.USART_Parity = USART_Parity_No;
		uart_2_init.USART_StopBits = USART_StopBits_1;
		uart_2_init.USART_WordLength = USART_WordLength_9b;

		USART_Init(USART2, &uart_2_init);
		USART_Cmd(USART2, ENABLE);
}

void prvSetupHardware() {
	prvSetupGPIO();
	prvSetupUART();
}

void prvSetupGPIO() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef button_init;
	GPIO_InitTypeDef led_init;

	led_init.GPIO_Mode = GPIO_Mode_OUT;
	led_init.GPIO_OType = GPIO_OType_PP;
	led_init.GPIO_Pin = GPIO_Pin_12;
	led_init.GPIO_Speed = GPIO_Low_Speed;
	led_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &led_init);

	button_init.GPIO_Mode = GPIO_Mode_IN;
	button_init.GPIO_OType = GPIO_OType_PP;
	button_init.GPIO_Pin = GPIO_Pin_0;
	button_init.GPIO_Speed = GPIO_Low_Speed;
	button_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &button_init);

}

void printmsg(char* msg) {
	for (uint32_t i=0; i<strlen(msg); i++) {
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET);
		USART_SendData(USART2, msg[i]);
	}
}












