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

}

void MG996R::move_to_angle(uint8_t angle){

}

MG996R::~MG996R(){
     
 }

}

