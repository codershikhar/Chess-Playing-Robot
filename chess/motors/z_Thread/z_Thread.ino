int speed = 2  ;
void setup() 
{
  // using L293D 
  // Ic Pins      arduino and motor
  //    2                 12
  //    7                 11
  //    10                10
  //    15                9
  //    3                 BLUE
  //    6                 ORANGE
  //    11                YELLOW
  //    14                PINK
Serial.begin(250000);
pinMode(12, OUTPUT);  
pinMode(11, OUTPUT);
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);
}

void loop() 
{
//    motor_forward();
    motor_backward();
}


void motor_forward()
{
  for(int i=0; i < 1000; i++)
  {
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    delay(speed);
      
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    delay(speed);
    
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    delay(speed);
    
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    delay(speed);
  }
}

void motor_backward()
{
  for(int i=0; i < 5000; i++)
  {
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    delay(speed);
      
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    delay(speed);
    
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    delay(speed);
    
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    delay(speed);
  }
}
