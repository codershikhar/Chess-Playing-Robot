// Enables
int x_y_En = A0;
pinMode(x_y_En, OUTPUT);
int z_grab_En = A1;
pinMode(z_grab_En, OUTPUT);

// Y
int y_Speed = 3;
int y_motor_1 = 9;
int y_motor_2 = 8;
int y_motor_3 = 7;
int y_motor_4 = 6;

// X1 and X2
int x_Speed = 3;
int x_motor_1 = 13;
int x_motor_2 = 12;
int x_motor_3 = 11;
int x_motor_4 = 10;

// Grab
int grabSpeed = 5;
int grab_motor_1 = 13;
int grab_motor_2 = 12;
int grab_motor_3 = 11;
int grab_motor_4 = 10;

// Z1 and Z2
  // using L293D 
  // Ic Pins      arduino and motor
  //    2                 5
  //    7                 4
  //    10                3
  //    15                2
  //    Int1              9
  //    Int2              8
  //    Int3              7
  //    Int4              6
  //    3                 BLUE
  //    6                 ORANGE
  //    11                YELLOW
  //    14                PINK
int z_Speed = 10;
int z1_motor_1 = 5;
int z1_motor_2 = 4;
int z1_motor_3 = 3;
int z1_motor_4 = 2;
int z2_motor_1 = 9;
int z2_motor_2 = 8;
int z2_motor_3 = 7;
int z2_motor_4 = 6;

void setup() 
{
}

void loop() 
{
  grab_motor_release();
  grab_motor_grab();
  x_forward();
  x_backward();
  y_forward();
  y_backward();
  z1_up();
  z1_down();
}


void grab_motor_release()
{
  pinMode(grab_motor_1, OUTPUT);
  pinMode(grab_motor_2, OUTPUT);
  pinMode(grab_motor_3, OUTPUT);
  pinMode(grab_motor_4, OUTPUT);
  for(int i=0; i < 50; i++)
  {
    digitalWrite(grab_motor_1, HIGH);
    digitalWrite(grab_motor_2, HIGH);
    digitalWrite(grab_motor_3, LOW);
    digitalWrite(grab_motor_4, LOW);
    delay(grabSpeed);
      
    digitalWrite(grab_motor_1, LOW);
    digitalWrite(grab_motor_2, HIGH);
    digitalWrite(grab_motor_3, HIGH);
    digitalWrite(grab_motor_4, LOW);
    delay(grabSpeed);
    
    digitalWrite(grab_motor_1, LOW);
    digitalWrite(grab_motor_2, LOW);
    digitalWrite(grab_motor_3, HIGH);
    digitalWrite(grab_motor_4, HIGH);
    delay(grabSpeed);
    
    digitalWrite(grab_motor_1, HIGH);
    digitalWrite(grab_motor_2, LOW);
    digitalWrite(grab_motor_3, LOW);
    digitalWrite(grab_motor_4, HIGH);
    delay(grabSpeed);
  }
}

void grab_motor_grab()
{
  pinMode(grab_motor_1, OUTPUT);
  pinMode(grab_motor_2, OUTPUT);
  pinMode(grab_motor_3, OUTPUT);
  pinMode(grab_motor_4, OUTPUT);
  for(int i=0; i < 50; i++)
  {
    digitalWrite(grab_motor_1, HIGH);
    digitalWrite(grab_motor_2, LOW);
    digitalWrite(grab_motor_3, LOW);
    digitalWrite(grab_motor_4, HIGH);
    delay(grabSpeed);
      
    digitalWrite(grab_motor_1, LOW);
    digitalWrite(grab_motor_2, LOW);
    digitalWrite(grab_motor_3, HIGH);
    digitalWrite(grab_motor_4, HIGH);
    delay(grabSpeed);
    
    digitalWrite(grab_motor_1, LOW);
    digitalWrite(grab_motor_2, HIGH);
    digitalWrite(grab_motor_3, HIGH);
    digitalWrite(grab_motor_4, LOW);
    delay(grabSpeed);
    
    digitalWrite(grab_motor_1, HIGH);
    digitalWrite(grab_motor_2, HIGH);
    digitalWrite(grab_motor_3, LOW);
    digitalWrite(grab_motor_4, LOW);
    delay(grabSpeed);
  }
}

void x_forward()
{
  pinMode(x_motor_1, OUTPUT);
  pinMode(x_motor_2, OUTPUT);
  pinMode(x_motor_3, OUTPUT);
  pinMode(x_motor_4, OUTPUT);
  for(int i=0; i < 100; i++)
  {
    digitalWrite(x_motor_1, HIGH);
    digitalWrite(x_motor_2, LOW);
    digitalWrite(x_motor_3, LOW);
    digitalWrite(x_motor_4, LOW);
    delay(x_Speed);
      
    digitalWrite(x_motor_1, LOW);
    digitalWrite(x_motor_2, HIGH);
    digitalWrite(x_motor_3, LOW);
    digitalWrite(x_motor_4, LOW);
    delay(x_Speed);
    
    digitalWrite(x_motor_1, LOW);
    digitalWrite(x_motor_2, LOW);
    digitalWrite(x_motor_3, HIGH);
    digitalWrite(x_motor_4, LOW);
    delay(x_Speed);
    
    digitalWrite(x_motor_1, LOW);
    digitalWrite(x_motor_2, LOW);
    digitalWrite(x_motor_3, LOW);
    digitalWrite(x_motor_4, HIGH);
    delay(x_Speed);
  }
}

void x_backward()
{
  pinMode(x_motor_1, OUTPUT);
  pinMode(x_motor_2, OUTPUT);
  pinMode(x_motor_3, OUTPUT);
  pinMode(x_motor_4, OUTPUT);
  for(int i=0; i < 100; i++)
  {
    digitalWrite(x_motor_1, LOW);
    digitalWrite(x_motor_2, LOW);
    digitalWrite(x_motor_3, LOW);
    digitalWrite(x_motor_4, HIGH);
    delay(x_Speed);
      
    digitalWrite(x_motor_1, LOW);
    digitalWrite(x_motor_2, LOW);
    digitalWrite(x_motor_3, HIGH);
    digitalWrite(x_motor_4, LOW);
    delay(x_Speed);
    
    digitalWrite(x_motor_1, LOW);
    digitalWrite(x_motor_2, HIGH);
    digitalWrite(x_motor_3, LOW);
    digitalWrite(x_motor_4, LOW);
    delay(x_Speed);
    
    digitalWrite(x_motor_1, HIGH);
    digitalWrite(x_motor_2, LOW);
    digitalWrite(x_motor_3, LOW);
    digitalWrite(x_motor_4, LOW);
    delay(x_Speed);
  }
}

void y_forward()
{
  pinMode(y_motor_1, OUTPUT);
  pinMode(y_motor_2, OUTPUT);
  pinMode(y_motor_3, OUTPUT);
  pinMode(y_motor_4, OUTPUT);
  for(int i=0; i < 100; i++)
  {
    digitalWrite(y_motor_1, HIGH);
    digitalWrite(y_motor_2, LOW);
    digitalWrite(y_motor_3, LOW);
    digitalWrite(y_motor_4, LOW);
    delay(y_Speed);
      
    digitalWrite(y_motor_1, LOW);
    digitalWrite(y_motor_2, HIGH);
    digitalWrite(y_motor_3, LOW);
    digitalWrite(y_motor_4, LOW);
    delay(y_Speed);
    
    digitalWrite(y_motor_1, LOW);
    digitalWrite(y_motor_2, LOW);
    digitalWrite(y_motor_3, HIGH);
    digitalWrite(y_motor_4, LOW);
    delay(y_Speed);
    
    digitalWrite(y_motor_1, LOW);
    digitalWrite(y_motor_2, LOW);
    digitalWrite(y_motor_3, LOW);
    digitalWrite(y_motor_4, HIGH);
    delay(y_Speed);
  }
}

void y_backward()
{
  pinMode(y_motor_1, OUTPUT);
  pinMode(y_motor_2, OUTPUT);
  pinMode(y_motor_3, OUTPUT);
  pinMode(y_motor_4, OUTPUT);
  for(int i=0; i < 100; i++)
  {
    digitalWrite(y_motor_1, LOW);
    digitalWrite(y_motor_2, LOW);
    digitalWrite(y_motor_3, LOW);
    digitalWrite(y_motor_4, HIGH);
    delay(y_Speed);
      
    digitalWrite(y_motor_1, LOW);
    digitalWrite(y_motor_2, LOW);
    digitalWrite(y_motor_3, HIGH);
    digitalWrite(y_motor_4, LOW);
    delay(y_Speed);
    
    digitalWrite(y_motor_1, LOW);
    digitalWrite(y_motor_2, HIGH);
    digitalWrite(y_motor_3, LOW);
    digitalWrite(y_motor_4, LOW);
    delay(y_Speed);
    
    digitalWrite(y_motor_1, HIGH);
    digitalWrite(y_motor_2, LOW);
    digitalWrite(y_motor_3, LOW);
    digitalWrite(y_motor_4, LOW);
    delay(y_Speed);
  }
}

void z1_up()
{
  pinMode(z1_motor_1, OUTPUT);
  pinMode(z1_motor_2, OUTPUT);
  pinMode(z1_motor_3, OUTPUT);
  pinMode(z1_motor_4, OUTPUT);
  for(int i=0; i < 200; i++)
  {
    digitalWrite(z1_motor_1, LOW);
    digitalWrite(z1_motor_2, LOW);
    digitalWrite(z1_motor_3, HIGH);
    digitalWrite(z1_motor_4, LOW);
    z2_wind();
      
    digitalWrite(z1_motor_1, LOW);
    digitalWrite(z1_motor_2, HIGH);
    digitalWrite(z1_motor_3, LOW);
    digitalWrite(z1_motor_4, LOW);
    z2_wind();
    
    digitalWrite(z1_motor_1, LOW);
    digitalWrite(z1_motor_2, LOW);
    digitalWrite(z1_motor_3, LOW);
    digitalWrite(z1_motor_4, HIGH);
    z2_wind();
    
    digitalWrite(z1_motor_1, HIGH);
    digitalWrite(z1_motor_2, LOW);
    digitalWrite(z1_motor_3, LOW);
    digitalWrite(z1_motor_4, LOW);
    z2_wind();
  }
}

void z1_down()
{
  pinMode(z1_motor_1, OUTPUT);
  pinMode(z1_motor_2, OUTPUT);
  pinMode(z1_motor_3, OUTPUT);
  pinMode(z1_motor_4, OUTPUT);
  for(int i=0; i < 500; i++)
  {
    digitalWrite(z1_motor_1, HIGH);
    digitalWrite(z1_motor_2, LOW);
    digitalWrite(z1_motor_3, LOW);
    digitalWrite(z1_motor_4, LOW);
    z2_unwind();
      
    digitalWrite(z1_motor_1, LOW);
    digitalWrite(z1_motor_2, LOW);
    digitalWrite(z1_motor_3, LOW);
    digitalWrite(z1_motor_4, HIGH);
    z2_unwind();
    
    digitalWrite(z1_motor_1, LOW);
    digitalWrite(z1_motor_2, HIGH);
    digitalWrite(z1_motor_3, LOW);
    digitalWrite(z1_motor_4, LOW);
    z2_unwind();
    
    digitalWrite(z1_motor_1, LOW);
    digitalWrite(z1_motor_2, LOW);
    digitalWrite(z1_motor_3, HIGH);
    digitalWrite(z1_motor_4, LOW);
    z2_unwind();
  }
}

void z2_wind()
{
  pinMode(z2_motor_1, OUTPUT);
  pinMode(z2_motor_2, OUTPUT);
  pinMode(z2_motor_3, OUTPUT);
  pinMode(z2_motor_4, OUTPUT);
  for(int i=0; i < 5; i++)
  {
    digitalWrite(z2_motor_1, HIGH);
    digitalWrite(z2_motor_2, LOW);
    digitalWrite(z2_motor_3, LOW);
    digitalWrite(z2_motor_4, LOW);
    delay(z_Speed);
      
    digitalWrite(z2_motor_1, LOW);
    digitalWrite(z2_motor_2, HIGH);
    digitalWrite(z2_motor_3, LOW);
    digitalWrite(z2_motor_4, LOW);
    delay(z_Speed);
    
    digitalWrite(z2_motor_1, LOW);
    digitalWrite(z2_motor_2, LOW);
    digitalWrite(z2_motor_3, HIGH);
    digitalWrite(z2_motor_4, LOW);
    delay(z_Speed);
    
    digitalWrite(z2_motor_1, LOW);
    digitalWrite(z2_motor_2, LOW);
    digitalWrite(z2_motor_3, LOW);
    digitalWrite(z2_motor_4, HIGH);
    delay(z_Speed);
  }
}

void z2_unwind()
{
  pinMode(z2_motor_1, OUTPUT);
  pinMode(z2_motor_2, OUTPUT);
  pinMode(z2_motor_3, OUTPUT);
  pinMode(z2_motor_4, OUTPUT);
  for(int i=0; i < 2; i++)
  {
    digitalWrite(z2_motor_1, LOW);
    digitalWrite(z2_motor_2, LOW);
    digitalWrite(z2_motor_3, LOW);
    digitalWrite(z2_motor_4, HIGH);
    delay(z_Speed);
      
    digitalWrite(z2_motor_1, LOW);
    digitalWrite(z2_motor_2, LOW);
    digitalWrite(z2_motor_3, HIGH);
    digitalWrite(z2_motor_4, LOW);
    delay(z_Speed);
    
    digitalWrite(z2_motor_1, LOW);
    digitalWrite(z2_motor_2, HIGH);
    digitalWrite(z2_motor_3, LOW);
    digitalWrite(z2_motor_4, LOW);
    delay(z_Speed);
    
    digitalWrite(z2_motor_1, HIGH);
    digitalWrite(z2_motor_2, LOW);
    digitalWrite(z2_motor_3, LOW);
    digitalWrite(z2_motor_4, LOW);
    delay(z_Speed);
  }
}
