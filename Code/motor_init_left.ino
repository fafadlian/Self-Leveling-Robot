#define LB1 24
#define LB2 25
#define pwm_left 12

void motor_init_left() {
  pinMode(LB1, OUTPUT);
  pinMode(LB2, OUTPUT);
  pinMode(pwm_left, OUTPUT);
}

void motor_left(float pwm) {
  if (pwm > 0) {
    digitalWrite(RB1, LOW);//kalau terbalik tukar LOW & HIGH
    digitalWrite(RB2, HIGH);
    analogWrite(pwm_left, pwm);
  } else if (pwm < 0) {
    digitalWrite(LB1, HIGH);//kalau terbalik tukar LOW & HIGH
    digitalWrite(LB2, LOW);
    analogWrite(pwm_left, -pwm);
  } else if (pwm == 0) {
    digitalWrite(LB1, HIGH);
    digitalWrite(LB2, HIGH);
    analogWrite(pwm_left, pwm);
  }
}
