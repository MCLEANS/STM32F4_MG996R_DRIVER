#include "MG996R.h"

#define START1 0
#define START2 180
#define STOP1 500
#define STOP2 1000

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

void MG996R::move_to_angle(uint8_t angle){

}

MG996R::~MG996R(){
     
 }

}

