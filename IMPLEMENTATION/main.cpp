#include "stm32f4xx.h"
#include "clockconfig.h"

#include "PWM.h"

#define PRESCALER 234
#define ARR_VALUE 234

/**
 * 1. Clock period = 20ms (50Hz)
 * 2. When on-time is 1 ms the motor is at 0*.
 * 3. When on-time is 1.5ms the motor is at 90*.
 * 4. When on-time is 2ms the motor is at 180*.
 * 
 */
custom_libraries::clock_config system_clock;

/**
 * Initialize PWM object
 */
custom_libraries::PWM servo(TIM1,
                            custom_libraries::channel1,
                            GPIOA,
                            4,
                            custom_libraries::AF0,
                            PRESCALER,
                            ARR_VALUE);


int get_ARR_value(uint8_t angle){
  int start1 = 0;
  int start2 = 0;
  int stop1 = 0;
  int stop2 = 0;
  int  Auto_reload_value = (start2 + (stop2 - start2) * ((angle - start1)/(stop1-start1)));

  return Auto_reload_value;
}

int main(void) {
  
  system_clock.initialize();

  /**
   * begin PWM
   */
  servo.begin();

  /**
   * Set initial duty cycle
   */
  servo.set_duty_cycle(100);
  
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  
  GPIOA->MODER |= GPIO_MODER_MODER7_0;
  GPIOA->MODER |= GPIO_MODER_MODER6_0;

  GPIOA->ODR |= GPIO_ODR_ODR_6;
  GPIOA->ODR &= ~GPIO_ODR_ODR_7;  

  while(1){
    for(volatile int i = 0; i < 2000000; i++){}
    GPIOA->ODR ^= (1<<6);
    GPIOA->ODR ^= (1<<7);

  }
}
