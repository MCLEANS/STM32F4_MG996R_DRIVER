#ifndef _MG996R_H
#define _MG996R_H

#include "stm32f4xx.h"
#include "PWM.h"

#include <stdlib.h>

/**
 * 1. Clock period = 20ms (50Hz)
 * 2. When on-time is 1 ms the motor is at 0*.
 * 3. When on-time is 1.5ms the motor is at 90*.
 * 4. When on-time is 2ms the motor is at 180*.
 * 
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

#define INITIAL_POSITITON 90

namespace custom_libraries{
class MG996R : public PWM{
    private:
        int starting_angle = 90;
        int previous_angle = 0;
    private:
    public:
    public:
        MG996R(TIM_TypeDef *TIMER,
                channel input_channel,
                GPIO_TypeDef *PORT,
                uint8_t PIN,
                alternate_function pin_function,
                uint16_t prescaler,
                uint16_t auto_reload_value);
        int map(long x, long in_min, long in_max, long out_min, long out_max);
        int get_duty_cycle_from_Angle(uint8_t angle);
        void move_to_angle(uint16_t angle_to);
        ~MG996R();


};

}

#endif //_MG996R_H