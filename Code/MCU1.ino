
#define display_lcd HIGH
#define display_monitor HIGH
#define display_plotter LOW
#define serial_input HIGH

#define LED 13

float omega_serial;
float omega_input = 0;
float omega_ref = 0;

int flagminus;
char flagawal = '<';
unsigned long Millis = 0;

int item;

float omega_right_read;
float omega_right_read_last;

float omega_left_read;
float omega_left_read_last;

float rotation_right_read;
float rotation_left_read;

float rotation_right;
float rotation_left;

float error_right = 0;
float last_error_right = 0;
float pwm_pulse_right = 0;

float Kp_right = 1;
float Ki_right = 0.5;
float Kd_right = 0;

float proportional_right = 0;
float integral_right = 0;
float derivative_right = 0;

int counter_encoder_right = 0;
int counter_encoder_left = 0;
int last_counter_encoder_right = 0;
int last_counter_encoder_left = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  motor_init_right();
  motor_init_left();
  encoder_interrupt_right_init();

  
}

void loop()
{
  if (serial_input)
  {
    while(Serial.available())
    {
      item = Serial.read();
      Serial.println(item);
      switch(item)
      {
        case 49:
          omega_ref += 10;
          Serial.print("|| Omega Ref: ");
          Serial.print(omega_ref);
          break;
        case 50:
          omega_ref -= 10;
          Serial.print("|| Omega Ref: ");
          Serial.print(omega_ref);
          break;
        case 51:
          omega_ref = 0;
          Serial.print("|| Omega Ref: ");
          Serial.print(omega_ref);
          break;
        case 52:

          break;
      }

    }

       // Serial.print("|| Omega input: ");
       // Serial.println(omega_input);  

          
//      Serial.print(" || Rotation :");
//      Serial.print(rotation_right_read);      
//      Serial.print("|| Omega : ");
//      Serial.print(omega_right_read);
//      Serial.print("|| PWM_Pulse :");
//      Serial.print(pwm_pulse_right);
//      Serial.print("|| Error_right :");
//      Serial.println(error_right);
  }
//  speed_right(omega_input);
    velocity_profile(omega_ref,item);
}
