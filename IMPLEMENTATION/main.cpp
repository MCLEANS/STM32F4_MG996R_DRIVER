#include "stm32f4xx.h"
#include "clockconfig.h"

#include "MG996R.h"

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
custom_libraries::MG996R servo1(TIM1,
                            custom_libraries::channel1,
                            GPIOE,
                            9,
                            custom_libraries::AF1,
                            PRESCALER,
                            ARR_VALUE);



  

  

int main(void) {
  /* Initialize the system clock */
  system_clock.initialize();
// for(volatile int i = 0; i < 7000000; i++){};
  //servo1.set_duty_cycle(4000);
 // = 90;
 //move_to_angle(90);


    
  while(1){
   
// for(volatile int i = 0; i < 7000000; i++){};
 // move_to_angle(0);
   //for(volatile int i = 0; i < 7000000; i++){};
 // move_to_angle(90);
   // for(volatile int i = 0; i < 7000000; i++){};
  //move_to_angle(180);
  //for(volatile int i = 0; i < 7000000; i++){};
  //move_to_angle(90);
 // for(volatile int i = 0; i < 7000000; i++){};
 // move_to_angle(0);

 // for(volatile int i = 0; i < 9000000; i++){};
  servo1.move_to_angle(0);
   //for(volatile int i = 0; i < 100000; i++){};
 servo1.move_to_angle(90);
   // for(volatile int i = 0; i < 100000; i++){};
  servo1.move_to_angle(180);
  //for(volatile int i = 0; i < 9000000; i++){};
  servo1.move_to_angle(90);
 //for(volatile int i = 0; i < 100000; i++){};
 servo1.move_to_angle(0);
  }
}
