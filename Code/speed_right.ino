float dt_right = 0.04;

float speed_right(float rpm_speed_input) {
  omega_right_read = read_encoder_speed_right(dt_right*100); //input sampling time
  rotation_right_read = read_encoder_rotation_right();
  error_right = rpm_speed_input - omega_right_read;
//  teta_read = read_encoder_position(dt*100);
//  error_teta = teta_input - teta_read;

  proportional_right = error_right;
  integral_right = integral_right + (error_right * dt_right);
  derivative_right = (error_right - last_error_right) /  dt_right;
  pwm_pulse_right = Kp_right * proportional_right + Ki_right * integral_right + Kd_right * derivative_right;

  pwm_pulse_right = constrain(pwm_pulse_right, -255, 255);
  motor_right(pwm_pulse_right);
  motor_left(pwm_pulse_right);
  
  last_error_right = error_right;
//  last_error_teta_right = error_teta_right;
//  omega_read_last = omega_read;
//  teta_read_last = teta_read;
}
