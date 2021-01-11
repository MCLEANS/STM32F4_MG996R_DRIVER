#include "stm32f4xx.h"
#include "clockconfig.h"

#include "PWM.h"

#include <stdlib.h>

/**
 * Defined Auto Reload Value and prescaler to achieve 50hz frequency.
 */
#define PRESCALER 168
#define ARR_VALUE 10000


int starting_angle = 90;
int previous_angle = 0;

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


/**
 * Function to generate duty cycle from angle
 */
int get_duty_cycle_from_Angle(uint8_t angle){
  int start1 = 0;
  int start2 = 180;
  int stop1 = 500;
  int stop2 = 1000;
  int duty_cycle = (start2 + (stop2 - start2) * ((angle - start1)/(stop1-start1)));

  return duty_cycle;
}

/**
 * Function to move the servo onto a particular angle
 */
void move_to_angle(uint8_t angle){
  int differential_angle = previous_angle - angle;
  if(differential_angle < 0){
    for(int i =0 ; i < abs(differential_angle); i++){
      int duty_cycle_neg = get_duty_cycle_from_Angle(previous_angle+i);
      servo.set_duty_cycle(duty_cycle_neg);
      //Put a small delay
    }
  previous_angle = angle;
  }

  if(differential_angle > 0){
    for(int i = 0; i < abs(differential_angle); i++){
      int duty_cycle_pos = get_duty_cycle_from_Angle(previous_angle-i);
      servo.set_duty_cycle(duty_cycle_pos);
      //Put a small delay
    }
  previous_angle = angle;
  }

  if(differential_angle == 0){
    //Do nothing current PWM Signal perists
  }
  
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
  servo.set_duty_cycle(starting_angle);
  previous_angle = starting_angle;
  
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
