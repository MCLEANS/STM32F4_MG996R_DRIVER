#ifndef _MG996R_H
#define _MG996R_H

#include "stm32f4xx.h"
#include "PWM.h"

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
        ~MG996R();


};

}

#endif //_MG996R_H