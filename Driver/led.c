#include "led.h"
#include "gd32f4xx.h"



typedef struct
{
	rcu_periph_enum rcu;
	uint32_t gpio;
	uint32_t pin;
} Led_GPIO_t;

static Led_GPIO_t g_gpioList[] =
{
	{RCU_GPIOB, GPIOB, GPIO_PIN_14},    //LED_0
	{RCU_GPIOB, GPIOB, GPIO_PIN_13},    //LED_1
	{RCU_GPIOB, GPIOB, GPIO_PIN_12},		//LED_2
	{RCU_GPIOB, GPIOB, GPIO_PIN_15}	    //EQW
};

#define LED_NUM_MAX (sizeof(g_gpioList) / sizeof(g_gpioList[0]))

/**
***********************************************************
* @brief LED硬件初始化
* @param
* @return 
***********************************************************
*/
void LedDrvInit(void)
{
	for (uint8_t i = 0; i < LED_NUM_MAX; i++)
	{
		rcu_periph_clock_enable(g_gpioList[i].rcu);
		gpio_mode_set(g_gpioList[i].gpio, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN, g_gpioList[i].pin);
		gpio_output_options_set(g_gpioList[i].gpio, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, g_gpioList[i].pin);
		gpio_bit_set(g_gpioList[i].gpio, g_gpioList[i].pin);
	}
}

/**
***********************************************************
* @brief 点亮LED
* @param ledNo，LED标号，0~2
* @return 
***********************************************************
*/
void TurnOnLed(uint8_t ledNo)
{
	if (ledNo >= LED_NUM_MAX)
	{
		return;
	}
	gpio_bit_reset(g_gpioList[ledNo].gpio, g_gpioList[ledNo].pin);
}
/**
***********************************************************
* @brief 熄灭LED
* @param ledNo，LED标号，0~2
* @return 
***********************************************************
*/
void TurnOffLed(uint8_t ledNo)
{
	if (ledNo >= LED_NUM_MAX)
	{
		return;
	}
	gpio_bit_set(g_gpioList[ledNo].gpio, g_gpioList[ledNo].pin);
}



/**
***********************************************************
* @brief LED状态取反
* @param ledNo，LED标号，0~2
* @return 
***********************************************************
*/
void ToggleLed(uint8_t ledNo)
{
	if (ledNo >= LED_NUM_MAX)
	{
		return;
	}
	FlagStatus bit_state;
	bit_state = gpio_input_bit_get(g_gpioList[ledNo].gpio, g_gpioList[ledNo].pin);
	bit_state = (FlagStatus)(1 - bit_state);
	gpio_bit_write(g_gpioList[ledNo].gpio, g_gpioList[ledNo].pin, bit_state);
}
