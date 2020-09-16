#define pin_encoder_La 17
#define pin_encoder_Lb 18
#include "PinChangeInt.h"

bool state_encoder_La;
bool state_encoder_Lb;

float omega_left;

void encoder_interrupt_left_init() {
  pinMode(pin_encoder_La, INPUT);
  pinMode(pin_encoder_Lb, INPUT);
  state_encoder_La = digitalRead(pin_encoder_La);
  state_encoder_Lb = digitalRead(pin_encoder_Lb);
  attachPinChangeInterrupt(digitalPinToInterrupt(pin_encoder_La), ext_int_additional_handler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin_encoder_Lb), ext_int3_handler, CHANGE);
  digitalWrite(pin_encoder_La, HIGH); //turn pull up resistor on
  digitalWrite(pin_encoder_Lb, HIGH);
}

void ext_int_additional_handler() {
  state_encoder_La = !state_encoder_La;
  if (state_encoder_La == 1) {
    if (state_encoder_Lb == 0) counter_encoder_left++;
    else counter_encoder_left--;
  }
  else {
    if (state_encoder_Lb == 1) counter_encoder_left++;
    else counter_encoder_left--;
  }
}

void ext_int3_handler() {
  state_encoder_Lb = !state_encoder_Lb;
  if (state_encoder_Lb == 1) {
    if (state_encoder_La == 1) counter_encoder_left++;
    else counter_encoder_left--;
  }
  else {
    if (state_encoder_La == 0) counter_encoder_left++;
    else counter_encoder_left--;
  }
}

float read_encoder_speed_left(int delta_left) {
  omega_left = (float) ((((float)(counter_encoder_left)) - ((float)(last_counter_encoder_left))) * ((float)(60)*60) / (900*delta_left)) ;
  last_counter_encoder_left = counter_encoder_left;
  return -1 * omega_left;
}

float read_encoder_rotation_left() {
  // 230.4 counter = 1 rotation
  rotation_left = (float) (((float)(counter_encoder_left)) / (900) );
  return rotation_left;
}

//float read_encoder_position(int delta)
//{
//  teta = (float) (((float)(counter_encoder))*(360)/(230.4));
//  return teta;
//}
void timer_intterupt_init() {
  /*initialize timer1*/ 
    noInterrupts();          // disable global interrupts
    TCCR1A = 0;              // set entire TCCR1A register to 0
    TCCR1B = 0;              // same for TCCR1B
  /*(target time) = (timer resolution) * (# timer counts + 1)*/
  /* 16MHz Xtal --> 1/(16*10^6 / 1024) = 6.4e-5 seconds*/
  /*(# timer counts + 1) = (target time) / (timer resolution)
    (# timer counts + 1) = (1 s) / (6.4e-5 s)
    (# timer counts + 1) = 15625
    (# timer counts) = 15625 - 1 = 15624*/
  /*(# timer counts) = (target time / timer resolution) - 1*/      
    OCR1A = 780;             // set compare match register to desired timer count: OCR1A = 15624;
    
    TCCR1B |= (1 << WGM12);  // turn on CTC mode:    
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);   // Set CS10 and CS12 bits for 1024 prescaler:    
    TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt:
    interrupts();            // enable global interrupts
}

ISR(TIMER1_COMPA_vect) { 
/*timer compare interrupt service routine*/
//  PID_speed(omega_input);
}
