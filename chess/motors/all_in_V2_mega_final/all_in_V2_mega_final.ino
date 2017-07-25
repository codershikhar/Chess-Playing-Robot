// current possitions
int currentX = 0;
int currentY = 0;

// Y
int y_Speed = 3;
int y_motor_en = 1;
int y_motor_1 = 0;
int y_motor_2 = 14;
int y_motor_3 = 15;
int y_motor_4 = 16;

// X1 and X2
int x_Speed = 3;
int x_motor_en = 7;
int x_motor_1 = 6;
int x_motor_2 = 5;
int x_motor_3 = 4;
int x_motor_4 = 3;

// Grab
int grabSpeed = 5;
int grab_motor_1 = A7;
int grab_motor_2 = A8;
int grab_motor_3 = A9;
int grab_motor_4 = A10;

int z_Speed = 10;
int z1_motor_1 = 18;
int z1_motor_2 = 19;
int z1_motor_3 = 20;
int z1_motor_4 = 21;
int z2_motor_1 = A7;
int z2_motor_2 = A8;
int z2_motor_3 = A9;
int z2_motor_4 = A10;

void setup()
{
  setPinModes();
}

void loop()
{
  //  grab_motor_release();
  //  grab_motor_grab();
    x_forward(100);
    x_backward(100);
  //  y_forward();
  //  y_backward();
  //  z1_up();
  //  z1_down();
//  String move = "6151 ";
//  if (move[4] == ' ') // if not capturing
//  {
//    //go to place
//    x_forward(move.substring(0, 1).toInt() * 1160);
//    currentX = move.substring(0, 1).toInt();
//    y_forward(move.substring(1, 2).toInt() * 1160);
//    currentY = move.substring(1, 2).toInt();
//
//    // grab piece
//    z1_down();
//    grab_motor_grab();
//    z1_up();
//
//    // go to location
//    if (currentX > move.substring(2, 3).toInt())
//    {
//      x_forward((move.substring(2, 3).toInt() - currentX) * 1160);
//      currentX = move.substring(2, 3).toInt();
//    } else
//    {
//      x_backward((currentX - move.substring(2, 3).toInt()) * 1160);
//      currentX = move.substring(2, 3).toInt();
//    }
//    if (currentY > move.substring(3, 4).toInt())
//    {
//      y_forward((move.substring(3, 4).toInt() - currentY) * 1160);
//      currentY = move.substring(3, 4).toInt();
//    } else
//    {
//      y_backward((currentY - move.substring(3, 4).toInt()) * 1160);
//      currentY = move.substring(3, 4).toInt();
//    }
//
//    // drop the piece
//    z1_down();
//    grab_motor_release();
//    z1_up();
//
//    // back to normal possition
//    x_backward(currentX * 1160);
//    currentX = 0;
//    y_backward(currentY * 1160);
//    currentY = 0;
//  } else    // if capturing
//  {
//    //go to place to capture
//    x_forward(move.substring(2, 3).toInt() * 1160);
//    currentX = move.substring(2, 3).toInt();
//    y_forward(move.substring(3, 4).toInt() * 1160);
//    currentY = move.substring(3, 4).toInt();
//
//    // grab piece to capture
//    z1_down();
//    grab_motor_grab();
//    z1_up();
//
//    // go to location to drop captured piece
//    y_backward((move.substring(3, 4).toInt() + 1) * 1160);
//    currentY = -1;
//    z1_down();
//    grab_motor_release();
//    z1_up();
//
//    //go to place to pick our piece
//    if (move.substring(0, 1).toInt() > currentX)
//    {
//      x_forward((move.substring(0, 1).toInt() - currentX) * 1160);
//      currentX = move.substring(0, 1).toInt();
//    } else
//    {
//      x_forward((currentX - move.substring(0, 1).toInt()) * 1160);
//      currentX = move.substring(0, 1).toInt();
//    }
//    y_forward((move.substring(1, 2).toInt() - currentY) * 1160);
//    currentY = move.substring(1, 2).toInt();
//    
//    // grab piece
//    z1_down();
//    grab_motor_grab();
//    z1_up();
//    
//    // go to location
//    if (currentX > move.substring(2, 3).toInt())
//    {
//      x_forward((move.substring(2, 3).toInt() - currentX) * 1160);
//      currentX = move.substring(2, 3).toInt();
//    } else
//    {
//      x_backward((currentX - move.substring(2, 3).toInt()) * 1160);
//      currentX = move.substring(2, 3).toInt();
//    }
//    if (currentY > move.substring(3, 4).toInt())
//    {
//      y_forward((move.substring(3, 4).toInt() - currentY) * 1160);
//      currentY = move.substring(3, 4).toInt();
//    } else
//    {
//      y_backward((currentY - move.substring(3, 4).toInt()) * 1160);
//      currentY = move.substring(3, 4).toInt();
//    }
//    
//    // drop the piece
//    z1_down();
//    grab_motor_release();
//    z1_up();
//    
//    // back to normal possition
//    x_backward(currentX * 1160);
//    currentX = 0;
//    y_backward(currentY * 1160);
//    currentY = 0;
//  }
}

void setPinModes()
{
  pinMode(y_motor_en, OUTPUT);
  pinMode(y_motor_1, OUTPUT);
  pinMode(y_motor_2, OUTPUT);
  pinMode(y_motor_3, OUTPUT);
  pinMode(y_motor_4, OUTPUT);

  pinMode(x_motor_en, OUTPUT);
  pinMode(x_motor_1, OUTPUT);
  pinMode(x_motor_2, OUTPUT);
  pinMode(x_motor_3, OUTPUT);
  pinMode(x_motor_4, OUTPUT);

  pinMode(grab_motor_1, OUTPUT);
  pinMode(grab_motor_2, OUTPUT);
  pinMode(grab_motor_3, OUTPUT);
  pinMode(grab_motor_4, OUTPUT);

  pinMode(z1_motor_1, OUTPUT);
  pinMode(z1_motor_2, OUTPUT);
  pinMode(z1_motor_3, OUTPUT);
  pinMode(z1_motor_4, OUTPUT);
  pinMode(z2_motor_1, OUTPUT);
  pinMode(z2_motor_2, OUTPUT);
  pinMode(z2_motor_3, OUTPUT);
  pinMode(z2_motor_4, OUTPUT);
}

void grab_motor_release()
{
  digitalWrite(grab_motor_1, LOW);
  digitalWrite(grab_motor_2, LOW);
  digitalWrite(grab_motor_3, LOW);
  digitalWrite(grab_motor_4, LOW);
  for (int i = 0; i < 50; i++)
  {
    digitalWrite(grab_motor_1, HIGH);
    digitalWrite(grab_motor_2, HIGH);
    delay(grabSpeed);

    digitalWrite(grab_motor_1, LOW);
    digitalWrite(grab_motor_3, HIGH);
    delay(grabSpeed);

    digitalWrite(grab_motor_2, LOW);
    digitalWrite(grab_motor_4, HIGH);
    delay(grabSpeed);

    digitalWrite(grab_motor_1, HIGH);
    digitalWrite(grab_motor_3, LOW);
    delay(grabSpeed);
  }
}

void grab_motor_grab()
{
  digitalWrite(grab_motor_1, LOW);
  digitalWrite(grab_motor_2, LOW);
  digitalWrite(grab_motor_3, LOW);
  digitalWrite(grab_motor_4, LOW);
  for (int i = 0; i < 50; i++)
  {
    digitalWrite(grab_motor_1, HIGH);
    digitalWrite(grab_motor_4, HIGH);
    delay(grabSpeed);

    digitalWrite(grab_motor_1, LOW);
    digitalWrite(grab_motor_3, HIGH);
    delay(grabSpeed);

    digitalWrite(grab_motor_2, HIGH);
    digitalWrite(grab_motor_4, LOW);
    delay(grabSpeed);

    digitalWrite(grab_motor_1, HIGH);
    digitalWrite(grab_motor_3, LOW);
    delay(grabSpeed);
  }
}

void x_forward(int n)
{
  digitalWrite(x_motor_1, LOW);
  digitalWrite(x_motor_2, LOW);
  digitalWrite(x_motor_3, LOW);
  digitalWrite(x_motor_4, LOW);
  digitalWrite(x_motor_en, HIGH);
  for (int i = 0; i < n; i++)
  {
    digitalWrite(x_motor_1, HIGH);
    digitalWrite(x_motor_4, LOW);
    delay(x_Speed);

    digitalWrite(x_motor_1, LOW);
    digitalWrite(x_motor_2, HIGH);
    delay(x_Speed);

    digitalWrite(x_motor_2, LOW);
    digitalWrite(x_motor_3, HIGH);
    delay(x_Speed);

    digitalWrite(x_motor_3, LOW);
    digitalWrite(x_motor_4, HIGH);
    delay(x_Speed);
  }
  digitalWrite(x_motor_en, LOW);
}

void x_backward(int n)
{
  digitalWrite(x_motor_1, LOW);
  digitalWrite(x_motor_2, LOW);
  digitalWrite(x_motor_3, LOW);
  digitalWrite(x_motor_4, LOW);
  digitalWrite(x_motor_en, HIGH);
  for (int i = 0; i < n; i++)
  {
    digitalWrite(x_motor_1, LOW);
    digitalWrite(x_motor_4, HIGH);
    delay(x_Speed);

    digitalWrite(x_motor_3, HIGH);
    digitalWrite(x_motor_4, LOW);
    delay(x_Speed);

    digitalWrite(x_motor_2, HIGH);
    digitalWrite(x_motor_3, LOW);
    delay(x_Speed);

    digitalWrite(x_motor_1, HIGH);
    digitalWrite(x_motor_2, LOW);
    delay(x_Speed);
  }
  digitalWrite(x_motor_en, LOW);
}

void y_forward(int n)
{
  digitalWrite(y_motor_1, LOW);
  digitalWrite(y_motor_2, LOW);
  digitalWrite(y_motor_3, LOW);
  digitalWrite(y_motor_4, LOW);
  digitalWrite(y_motor_en, HIGH);
  for (int i = 0; i < n; i++)
  {
    digitalWrite(y_motor_1, HIGH);
    digitalWrite(y_motor_4, LOW);
    delay(y_Speed);

    digitalWrite(y_motor_1, LOW);
    digitalWrite(y_motor_2, HIGH);
    delay(y_Speed);

    digitalWrite(y_motor_2, LOW);
    digitalWrite(y_motor_3, HIGH);
    delay(y_Speed);

    digitalWrite(y_motor_3, LOW);
    digitalWrite(y_motor_4, HIGH);
    delay(y_Speed);
  }
  digitalWrite(y_motor_en, LOW);
}

void y_backward(int n)
{
  digitalWrite(y_motor_1, LOW);
  digitalWrite(y_motor_2, LOW);
  digitalWrite(y_motor_3, LOW);
  digitalWrite(y_motor_4, LOW);
  digitalWrite(y_motor_en, HIGH);
  for (int i = 0; i < n; i++)
  {
    digitalWrite(y_motor_1, LOW);
    digitalWrite(y_motor_4, HIGH);
    delay(y_Speed);

    digitalWrite(y_motor_3, HIGH);
    digitalWrite(y_motor_4, LOW);
    delay(y_Speed);

    digitalWrite(y_motor_2, HIGH);
    digitalWrite(y_motor_3, LOW);
    delay(y_Speed);

    digitalWrite(y_motor_1, HIGH);
    digitalWrite(y_motor_2, LOW);
    delay(y_Speed);
  }
  digitalWrite(y_motor_en, LOW);
}

void z1_up()
{
  digitalWrite(z1_motor_1, LOW);
  digitalWrite(z1_motor_2, LOW);
  digitalWrite(z1_motor_3, LOW);
  digitalWrite(z1_motor_4, LOW);
  for (int i = 0; i < 500; i++)
  {
    digitalWrite(z1_motor_1, LOW);
    digitalWrite(z1_motor_3, HIGH);
    z2_wind();

    digitalWrite(z1_motor_2, HIGH);
    digitalWrite(z1_motor_3, LOW);
    z2_wind();

    digitalWrite(z1_motor_2, LOW);
    digitalWrite(z1_motor_4, HIGH);
    z2_wind();

    digitalWrite(z1_motor_1, HIGH);
    digitalWrite(z1_motor_4, LOW);
    z2_wind();
  }
}

void z1_down()
{
  digitalWrite(z1_motor_1, LOW);
  digitalWrite(z1_motor_2, LOW);
  digitalWrite(z1_motor_3, LOW);
  digitalWrite(z1_motor_4, LOW);
  for (int i = 0; i < 500; i++)
  {
    digitalWrite(z1_motor_1, HIGH);
    digitalWrite(z1_motor_3, LOW);
    z2_unwind();

    digitalWrite(z1_motor_1, LOW);
    digitalWrite(z1_motor_4, HIGH);
    z2_unwind();

    digitalWrite(z1_motor_2, HIGH);
    digitalWrite(z1_motor_4, LOW);
    z2_unwind();

    digitalWrite(z1_motor_2, LOW);
    digitalWrite(z1_motor_3, HIGH);
    z2_unwind();
  }
}

void z2_wind()
{
  digitalWrite(z2_motor_1, LOW);
  digitalWrite(z2_motor_2, LOW);
  digitalWrite(z2_motor_3, LOW);
  digitalWrite(z2_motor_4, LOW);
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(z2_motor_1, HIGH);
    digitalWrite(z2_motor_4, LOW);
    delay(z_Speed);

    digitalWrite(z2_motor_1, LOW);
    digitalWrite(z2_motor_2, HIGH);
    delay(z_Speed);

    digitalWrite(z2_motor_2, LOW);
    digitalWrite(z2_motor_3, HIGH);
    delay(z_Speed);

    digitalWrite(z2_motor_3, LOW);
    digitalWrite(z2_motor_4, HIGH);
    delay(z_Speed);
  }
}

void z2_unwind()
{
  digitalWrite(z2_motor_1, LOW);
  digitalWrite(z2_motor_2, LOW);
  digitalWrite(z2_motor_3, LOW);
  digitalWrite(z2_motor_4, LOW);
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(z2_motor_1, LOW);
    digitalWrite(z2_motor_4, HIGH);
    delay(z_Speed);

    digitalWrite(z2_motor_3, HIGH);
    digitalWrite(z2_motor_4, LOW);
    delay(z_Speed);

    digitalWrite(z2_motor_2, HIGH);
    digitalWrite(z2_motor_3, LOW);
    delay(z_Speed);

    digitalWrite(z2_motor_1, HIGH);
    digitalWrite(z2_motor_2, LOW);
    delay(z_Speed);
  }
}
