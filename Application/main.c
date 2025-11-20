#include "gd32f4xx.h"
#include "main.h"
#include "systick.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"



//【LED任务】
//任务优先级
#define LED_TASK_PRIO	(tskIDLE_PRIORITY + 1)
//任务堆栈大小	
#define LED_STK_SIZE 		50  
//任务句柄
TaskHandle_t LEDTask_Handler;
//任务函数
void LED_Task(void *pvParameters);

//【Debug任务】
//任务优先级
#define Debug_TASK_PRIO		(tskIDLE_PRIORITY + 2)
//任务堆栈大小	
#define Debug_STK_SIZE 		512  
//任务句柄
TaskHandle_t Debug_Task_Handler;
//任务函数
void Debug_Task(void *pvParameters);




/**********************************************************************************************************
* 函 数 名: RTOS_Init
* 功能说明: RTOS初始化，用于创建任务
* 形 参：无
* 返 回 值: 无
**********************************************************************************************************/
void RTOS_Init(void)
{
	taskENTER_CRITICAL();           //进入临界区
	//创建LED任务
	xTaskCreate((TaskFunction_t )LED_Task,     	
							(const char*    )"LED_task",   	
							(uint16_t       )LED_STK_SIZE, 
							(void*          )NULL,				
							(UBaseType_t    )LED_TASK_PRIO,	
							(TaskHandle_t*  )&LEDTask_Handler); 
					
	//创建Debug任务
	xTaskCreate((TaskFunction_t )Debug_Task,     	
							(const char*    )"Debug_task",   	
							(uint16_t       )Debug_STK_SIZE, 
							(void*          )NULL,				
							(UBaseType_t    )Debug_TASK_PRIO,	
							(TaskHandle_t*  )&Debug_Task_Handler); 
							
	taskEXIT_CRITICAL();            //退出临界区	
	vTaskStartScheduler();          //开启任务调度
}

void LED_Task(void *pvParameters)
{
	for(;;)
	{
		ToggleLed(0);
		 vTaskDelay(500);
	}
		


}

void Debug_Task(void *pvParameters)
{
	while(1)
	{
	ToggleLed(1);
		 vTaskDelay(500);

	
	}
		

}

int main(void)
{
	systick_config();
	LedDrvInit();
	RTOS_Init();

	while(1)
	{
	
	}


}
