#include "stm32f4xx.h"
#include "clockconfig.h"

#include "MG996R.h"

#include <stdlib.h>
#include <sstream>

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
                            custom_libraries::AF1);

custom_libraries::MG996R servo2(TIM2,
                                custom_libraries::channel4,
                                GPIOB,
                                11,
                                custom_libraries::AF1);


int main(void) {
  /* Initialize the system clock */
  system_clock.initialize();

  while(1){   
    servo1.move_to_angle(20); 
   for(volatile int i = 0; i < 30000000; i++){}
    servo2.move_to_angle(110);
    for(volatile int i = 0; i < 300000; i++){}
    
    servo1.move_to_angle(200); 
   for(volatile int i = 0; i < 300000; i++){}
    servo2.move_to_angle(60); 
    for(volatile int i = 0; i < 30000000; i++){}
    
  }
}
