int speed = 10;
void setup() 
{
  // using L293D 
  // Ic Pins      arduino and motor
  //    2                 12
  //    7                 11
  //    10                10
  //    15                9
  //    Int1              8
  //    Int2              7
  //    Int3              6
  //    Int4              5
  //    3                 BLUE
  //    6                 ORANGE
  //    11                YELLOW
  //    14                PINK
Serial.begin(250000);
pinMode(12, OUTPUT);  
pinMode(11, OUTPUT);
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);
pinMode(7, OUTPUT);  
pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
pinMode(4, OUTPUT);
}

void loop() 
{
    digitalWrite(12, HIGH);
//    digitalWrite(11, LOW);
//    digitalWrite(10, LOW);
//    digitalWrite(9, LOW);
//    Serial.println("Up");
//    motor_up();
//    Serial.println("Down");
//    motor_down();
}

void motor_up()
{
  for(int i=0; i < 200; i++)
  {
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    //motor_wind();
      
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    //motor_wind();
    
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    //motor_wind();
    
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    //motor_wind();
  }
}

void motor_down()
{
  for(int i=0; i < 500; i++)
  {
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    //motor_unwind();
      
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    //motor_unwind();
    
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    //motor_unwind();
    
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    //motor_unwind();
  }
}

void motor_wind()
{
  for(int i=0; i < 5; i++)
  {
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    delay(speed);
      
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    delay(speed);
    
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    delay(speed);
    
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    delay(speed);
  }
}

void motor_unwind()
{
  for(int i=0; i < 2; i++)
  {
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    delay(speed);
      
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    delay(speed);
    
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    delay(speed);
    
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    delay(speed);
  }
}
