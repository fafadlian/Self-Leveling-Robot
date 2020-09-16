#define RB1 22
#define RB2 23
#define pwm_right 11

void motor_init_right() {
  pinMode(RB1, OUTPUT);
  pinMode(RB2, OUTPUT);
  pinMode(pwm_right, OUTPUT);
}

void motor_right(float pwm) {
  if (pwm > 0) {
    digitalWrite(RB1, LOW);//kalau terbalik tukar LOW & HIGH
    digitalWrite(RB2, HIGH);
    analogWrite(pwm_right, pwm);
  } else if (pwm < 0) {
    digitalWrite(RB1, HIGH);//kalau terbalik tukar LOW & HIGH
    digitalWrite(RB2, LOW);
    analogWrite(pwm_right, -pwm);
  } else if (pwm == 0) {
    digitalWrite(RB1, HIGH);
    digitalWrite(RB2, HIGH);
    analogWrite(pwm_right, pwm);
  }
}
