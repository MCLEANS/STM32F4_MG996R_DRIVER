#include "MG996R.h"

namespace custom_libraries{

MG996R::MG996R(TIM_TypeDef *TIMER,
                channel input_channel,
                GPIO_TypeDef *PORT,
                uint8_t PIN,
                alternate_function pin_function,
                uint16_t prescaler,
                uint16_t auto_reload_value):PWM(TIMER,
                                                input_channel,
                                                PORT,
                                                PIN,
                                                pin_function,
                                                prescaler,
                                                auto_reload_value){

 }

uint16_t MG996R::get_duty_cycle_from_Angle(uint8_t angle){
    int duty_cycle = (START2 + (STOP2 - START2) * ((angle - START1)/(STOP1-START1)));
    return duty_cycle;
}

void MG996R::move_to_angle(uint8_t new_duty_cycle,uint16_t &previous_duty_cycle){
    uint16_t delta_duty_cycle = previous_duty_cycle - new_duty_cycle;
    if(delta_duty_cycle < 0){
        for(volatile uint16_t i = 0; i < abs(delta_duty_cycle); i++){
            set_duty_cycle(previous_duty_cycle + i);
        }
        previous_duty_cycle = new_duty_cycle;
    }
    else if(delta_duty_cycle > 0){
        for(volatile uint16_t i = 0; i < abs(delta_duty_cycle); i++){
            set_duty_cycle(previous_duty_cycle - i);
        }
        previous_duty_cycle = new_duty_cycle;
    }
    else{
        /**
         * Do something default here
         */
    }
}

MG996R::~MG996R(){
     
 }

}

