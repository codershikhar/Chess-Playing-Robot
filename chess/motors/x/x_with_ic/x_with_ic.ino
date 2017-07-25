int speed = 1000;
int pin1 = 12;
int pin2 = 11;
void setup() 
{
  // put your setup code here, to run once:
pinMode(pin1, OUTPUT);
pinMode(pin2, OUTPUT);
Serial.begin(9600);
}

void loop() 
{
//    digitalWrite(pin1, LOW);
//    digitalWrite(pin2, HIGH);
    motor_forward();
    motor_backward();
}


void motor_forward()
{
  for(int i=0; i < 500; i++)
  {
    Serial.println("1");
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    delay(speed);

    Serial.println("2");
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    delay(speed);

    Serial.println("3");
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    delay(speed);

    Serial.println("4");
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    delay(speed);
  }
}

void motor_backward()
{
  for(int i=0; i < 500; i++)
  {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    delay(speed);
      
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    delay(speed);
    
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    delay(speed);
    
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    delay(speed);
  }
}
