#define pin_encoder_Ra 5
#define pin_encoder_Rb 4

bool state_encoder_Ra;
bool state_encoder_Rb;

float omega_right;

void encoder_interrupt_right_init() {
  pinMode(pin_encoder_Ra, INPUT);
  pinMode(pin_encoder_Rb, INPUT);
  state_encoder_Ra = digitalRead(pin_encoder_Ra);
  state_encoder_Rb = digitalRead(pin_encoder_Rb);
  attachInterrupt(digitalPinToInterrupt(pin_encoder_Ra), ext_int5_handler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin_encoder_Rb), ext_int4_handler, CHANGE);
  digitalWrite(pin_encoder_Ra, HIGH); //turn pull up resistor on
  digitalWrite(pin_encoder_Rb, HIGH);
}

void ext_int5_handler() {
  state_encoder_Ra = !state_encoder_Ra;
  if (state_encoder_Ra == 1) {
    if (state_encoder_Rb == 0) counter_encoder_right++;
    else counter_encoder_right--;
  }
  else {
    if (state_encoder_Rb == 1) counter_encoder_right++;
    else counter_encoder_right--;
  }
}

void ext_int4_handler() {
  state_encoder_Rb = !state_encoder_Rb;
  if (state_encoder_Rb == 1) {
    if (state_encoder_Ra == 1) counter_encoder_right++;
    else counter_encoder_right--;
  }
  else {
    if (state_encoder_Ra == 0) counter_encoder_right++;
    else counter_encoder_right--;
  }
}

float read_encoder_speed_right(int delta_right) {
  omega_right = (float) ((((float)(counter_encoder_right)) - ((float)(last_counter_encoder_right))) * ((float)(60)*60) / (900*delta_right)) ;
  last_counter_encoder_right = counter_encoder_right;
  return -1 * omega_right;
}

float read_encoder_rotation_right() {
  // 230.4 counter = 1 rotation
  rotation_right = (float) (((float)(counter_encoder_right)) / (900) );
  return rotation_right;
}

//float read_encoder_position(int delta)
//{
//  teta = (float) (((float)(counter_encoder))*(360)/(230.4));
//  return teta;
//}
