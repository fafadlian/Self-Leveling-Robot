float dt=0.04;
float a=12.5;

float velocity_profile(float omega_ref, int item){
  if (item==49)
  {
    while(omega_input<omega_ref)
    {
      omega_input+=dt*a;
      speed_right(omega_input);
      Serial.print("Omega Input :");
      Serial.println(omega_input);
    }
  }
  else
  {
    while(omega_input>omega_ref)
    {
      omega_input-=dt*a;
      speed_right(omega_input);
      Serial.print("Omega Input :");
      Serial.println(omega_input);
    }
    
  }
}
