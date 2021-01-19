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

#define START1 0
#define START2 180
#define STOP1 500
#define STOP2 1000

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
        uint16_t get_duty_cycle_from_Angle(uint8_t angle);
        void move_to_angle(uint8_t new_duty_cycle, uint16_t &previous_duty_cycle);
        ~MG996R();


};

}

#endif //_MG996R_H