#include "stm32f4xx.h"
#include "clockconfig.h"

#include "PWM.h"

#include <stdlib.h>

/**
 * Defined Auto Reload Value and prescaler to achieve 50hz frequency.
 */

/* Configuration prescaler and Auto Reload value for 84MHz APB bus */
#define PRESCALER 84
#define ARR_VALUE 40000

/* Configuration prescaler and Auto Reload value for 42MHz APB bus*/
#define PRESCALER_1 84
#define ARR_VALUE_1 20000

#define DUTY_CYCLE_MIN 1000
#define DUTY_CYCLE_MAX 4000
#define ANGLE_MIN 0
#define ANGLE_MAX 180


int previous_angle = 0;
int previous_duty_cycle_1 = 0;
int previous_duty_cycle = 0;

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
custom_libraries::PWM servo1(TIM1,
                            custom_libraries::channel1,
                            GPIOE,
                            9,
                            custom_libraries::AF1,
                            PRESCALER,
                            ARR_VALUE);


/**
 * custom map function
 */
int map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * Function to generate duty cycle from angle
 */
int get_duty_cycle_from_Angle(uint8_t angle){
  int duty_cycle = map(angle,ANGLE_MIN,ANGLE_MAX,DUTY_CYCLE_MIN,DUTY_CYCLE_MAX);
  return duty_cycle;
}


/**
 * Function to move the servo onto a particular angle
 */
void move_to_angle(uint16_t angle_to, int &angle_from){
  
  /* calculate differential duty cycle */
  int differential_angle = angle_from - angle_to;
  if(differential_angle < 0){
      GPIOE->MODER &= ~(1 << (9*2));
	  GPIOE->MODER |= (1 << ((9*2)+1));
    for(int i = 0 ; i < abs(differential_angle); i++){
      //int duty_cycle_neg_diff = get_duty_cycle_from_Angle(previous_angle+i);s
    
      servo1.set_duty_cycle(get_duty_cycle_from_Angle(angle_from+i));
 
      //Put a small delay
      for(volatile int i = 0; i < 300000; i++){}
    }
         GPIOE->MODER &= ~(1 << (9*2));
	GPIOE->MODER &= ~(1 << ((9*2)+1));
    //Set pin to alternate function mode
  angle_from = angle_to;
  
  }

  if(differential_angle > 0){
        GPIOE->MODER &= ~(1 << (9*2));
	  GPIOE->MODER |= (1 << ((9*2)+1));
    for(int i = 0; i < abs(differential_angle); i++){
      //int duty_cycle_pos_diff = get_duty_cycle_from_Angle(previous_angle-i);
      servo1.set_duty_cycle(get_duty_cycle_from_Angle(angle_from-i));
     
      //Put a small delay
      for(volatile int i = 0; i < 350000; i++){}
    }
     GPIOE->MODER &= ~(1 << (9*2));
	GPIOE->MODER &= ~(1 << ((9*2)+1));
  angle_from = angle_to;
  }

  if(differential_angle == 0){
    //Do nothing current PWM Signal perists
  }

  //Set pin to alternate function mode
	
  

  
}

int main(void) {
  /* Initialize the system clock */
  system_clock.initialize();
  servo1.begin();
  servo1.set_duty_cycle(1000);
  previous_angle = 0;
// for(volatile int i = 0; i < 7000000; i++){};
  //servo1.set_duty_cycle(4000);
 // previous_angle = 90;
 //move_to_angle(90,previous_angle);


    
  while(1){
   
// for(volatile int i = 0; i < 7000000; i++){};
 // move_to_angle(0,previous_angle);
   //for(volatile int i = 0; i < 7000000; i++){};
 // move_to_angle(90,previous_angle);
   // for(volatile int i = 0; i < 7000000; i++){};
  //move_to_angle(180,previous_angle);
  //for(volatile int i = 0; i < 7000000; i++){};
  //move_to_angle(90,previous_angle);
 // for(volatile int i = 0; i < 7000000; i++){};
 // move_to_angle(0,previous_angle);

 // for(volatile int i = 0; i < 9000000; i++){};
  move_to_angle(0,previous_angle);
   //for(volatile int i = 0; i < 100000; i++){};
 move_to_angle(90,previous_angle);
   // for(volatile int i = 0; i < 100000; i++){};
  move_to_angle(180,previous_angle);
  //for(volatile int i = 0; i < 9000000; i++){};
  move_to_angle(90,previous_angle);
 //for(volatile int i = 0; i < 100000; i++){};
 move_to_angle(0,previous_angle);
  }
}
