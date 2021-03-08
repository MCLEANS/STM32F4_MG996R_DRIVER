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

#define START1 1000
#define START2 2000
#define STOP1 0
#define STOP2 180


int starting_angle = 90;
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

custom_libraries::PWM servo2(TIM3,
                            custom_libraries::channel1,
                            GPIOC,
                            6,
                            custom_libraries::AF2,
                            PRESCALER_1,
                            ARR_VALUE_1);


/**
 * Function to generate duty cycle from angle
 */
int get_duty_cycle_from_Angle(uint8_t angle){

  int duty_cycle = (START2 + (STOP2 - START2) * ((angle - START1)/(STOP1-START1)));

  return duty_cycle;
}

/**
 * Function to move the servo onto a particular angle
 */
void move_to_angle(uint16_t current_cycle, int &previous_cycle){
  int differential_cycle = previous_cycle - current_cycle;
  if(differential_cycle < 0){
    for(int i =0 ; i < abs(differential_cycle); i++){
      //int duty_cycle_neg_diff = get_duty_cycle_from_Angle(previous_angle+i);
     servo1.set_duty_cycle(previous_cycle+i);
      //Put a small delay
      for(volatile int i = 0; i < 20000; i++){}
    }
  previous_cycle = current_cycle;
  
  }

  if(differential_cycle > 0){
    for(int i = 0; i < abs(differential_cycle); i++){
      //int duty_cycle_pos_diff = get_duty_cycle_from_Angle(previous_angle-i);
      servo1.set_duty_cycle(previous_cycle-i);
      //Put a small delay
      for(volatile int i = 0; i < 20000; i++){}
    }
  previous_cycle = current_cycle;
  }

  if(differential_cycle == 0){
    //Do nothing current PWM Signal perists
  }
  
}


void move_to_angle_2(uint16_t current_cycle, int &previous_cycle){
  int differential_cycle = previous_cycle - current_cycle;
  if(differential_cycle < 0){
    for(int i =0 ; i < abs(differential_cycle); i++){
      //int duty_cycle_neg_diff = get_duty_cycle_from_Angle(previous_angle+i);
     servo2.set_duty_cycle(previous_cycle+i);
      //Put a small delay
      for(volatile int i = 0; i < 2000; i++){}
    }
  previous_cycle = current_cycle;
  
  }

  if(differential_cycle > 0){
    for(int i = 0; i < abs(differential_cycle); i++){
      //int duty_cycle_pos_diff = get_duty_cycle_from_Angle(previous_angle-i);
      servo2.set_duty_cycle(previous_cycle-i);
      //Put a small delay
      for(volatile int i = 0; i < 2000; i++){}
    }
  previous_cycle = current_cycle;
  }

  if(differential_cycle == 0){
    //Do nothing current PWM Signal perists
  }
  
}


int main(void) {
  /**
   * initialization of system clock
   */
  system_clock.initialize();

  /**
   * begin PWM
   */
  servo1.begin();
  servo2.begin();

  /**
   * Set initial duty cycle
   */
  servo2.set_duty_cycle(1000);
  previous_duty_cycle_1 = 1000;
  for(volatile uint64_t i = 0; i < 5000000; i++){}
  
 servo1.set_duty_cycle(4000);
 previous_duty_cycle = 4000;
 for(volatile uint64_t i = 0; i < 5000000; i++){}
  
  while(1){
  /*servo1.set_duty_cycle(4000);
    for(volatile uint64_t i = 0; i < 10000000; i++){}
     servo1.set_duty_cycle(3000);
    for(volatile uint64_t i = 0; i < 10000000; i++){}
    */
 // servo2.set_duty_cycle(1500);
    //for(volatile uint64_t i = 0; i < 10000000; i++){}
   // move_to_angle( 2500,previous_duty_cycle);

   // servo1.set_duty_cycle(4000);
   // for(volatile uint64_t i = 0; i < 3000000; i++){}
   //  servo1.set_duty_cycle(3000);
   //for(volatile uint64_t i = 0; i < 12000000; i++){}
    move_to_angle_2(1000,previous_duty_cycle_1);
    //servo2.set_duty_cycle(1750);
    //for(volatile uint64_t i = 0; i < 10000000; i++){}
  //  move_to_angle(1750,previous_duty_cycle);
  //for(volatile int i = 0; i < 50000; i++){}
    //servo2.set_duty_cycle(2000);
    //for(volatile uint64_t i = 0; i < 10000000; i++){}
   // for(volatile int i = 0; i < 5000000; i++){}
  //  move_to_angle(4000,previous_duty_cycle);
     //servo2.set_duty_cycle(1750);
    //for(volatile uint64_t i = 0; i < 10000000; i++){}
    //move_to_angle(1750,previous_duty_cycle);
   /* servo.set_duty_cycle(6000);
    for(volatile uint64_t i = 0; i < 10000000; i++){}
    
*/

move_to_angle_2(3000,previous_duty_cycle_1);
  
  }
}
