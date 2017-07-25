int readPin1 = 8;
int readPin2 = 9;
int readPin3 = 10;
int readPin4 = 11;
int readPin5 = 12;
int readPin6 = 13;
int inputPin1 = A0;

int Board[][8] = 
{ {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 0, 1}};

long arrayToInt(int Board[][8])
{
  long n=0;
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      n = (n << 1) + Board[i][j];
    }
  }
  return n;
}

void intToArray(long n, int (&board)[8][8])
{
  for(int i = 7; i > -1; i--)
  {
    for(int j = 7; j > -1; j--)
    {
      board[i][j] = n & 1;
      n = n >> 1;
    }
  }
}

void readBoard() 
{
  for(int i=0; i<8; i++)
  {
    switch(i)
    {
      case 0: digitalWrite(readPin6, HIGH);
              digitalWrite(readPin5, HIGH);
              digitalWrite(readPin4, HIGH);
              break;
      case 1: digitalWrite(readPin6, LOW);
              digitalWrite(readPin5, HIGH);
              digitalWrite(readPin4, HIGH);
              break;
      case 2: digitalWrite(readPin6, HIGH);
              digitalWrite(readPin5, LOW);
              digitalWrite(readPin4, HIGH);
              break;
      case 3: digitalWrite(readPin6, LOW);
              digitalWrite(readPin5, LOW);
              digitalWrite(readPin4, HIGH);
              break;
      case 4: digitalWrite(readPin6, HIGH);
              digitalWrite(readPin5, HIGH);
              digitalWrite(readPin4, LOW);
              break;
      case 5: digitalWrite(readPin6, LOW);
              digitalWrite(readPin5, HIGH);
              digitalWrite(readPin4, LOW);
              break;
      case 6: digitalWrite(readPin6, HIGH);
              digitalWrite(readPin5, LOW);
              digitalWrite(readPin4, LOW);
              break;
      case 7: digitalWrite(readPin6, LOW);
              digitalWrite(readPin5, LOW);
              digitalWrite(readPin4, LOW);
              break;
    }
    for(int j=0; j<8; j++)
    {
      switch(j)
      {
        case 0: digitalWrite(readPin3, LOW);
                digitalWrite(readPin2, LOW);
                digitalWrite(readPin1, LOW);
                delay(10);
                Board[i][j] = digitalRead(inputPin1);
                break;
        case 1: digitalWrite(readPin3, HIGH);
                digitalWrite(readPin2, LOW);
                digitalWrite(readPin1, LOW);
                delay(10);
                Board[i][j] = digitalRead(inputPin1);
                break;
        case 2: digitalWrite(readPin3, LOW);
                digitalWrite(readPin2, HIGH);
                digitalWrite(readPin1, LOW);
                delay(10);
                Board[i][j] = digitalRead(inputPin1);
                break;
        case 3: digitalWrite(readPin3, HIGH);
                digitalWrite(readPin2, HIGH);
                digitalWrite(readPin1, LOW);
                delay(10);
                Board[i][j] = digitalRead(inputPin1);
                break;
        case 4: digitalWrite(readPin3, LOW);
                digitalWrite(readPin2, LOW);
                digitalWrite(readPin1, HIGH);
                delay(10);
                Board[i][j] = digitalRead(inputPin1);
                break;
        case 5: digitalWrite(readPin3, HIGH);
                digitalWrite(readPin2, LOW);
                digitalWrite(readPin1, HIGH);
                delay(10);
                Board[i][j] = digitalRead(inputPin1);
                break;
        case 6: digitalWrite(readPin3, LOW);
                digitalWrite(readPin2, HIGH);
                digitalWrite(readPin1, HIGH);
                delay(10);
                Board[i][j] = digitalRead(inputPin1);
                break;
        case 7: digitalWrite(readPin3, HIGH);
                digitalWrite(readPin2, HIGH);
                digitalWrite(readPin1, HIGH);
                delay(10);
                Board[i][j] = digitalRead(inputPin1);
                break;
      }
    }
  }
}

void setup() 
{
  Serial.begin(9600);
  pinMode(readPin1, OUTPUT);
  pinMode(readPin2, OUTPUT);
  pinMode(readPin3, OUTPUT);
  pinMode(readPin4, OUTPUT);
  pinMode(readPin5, OUTPUT);
  pinMode(readPin6, OUTPUT);
  pinMode(inputPin1, INPUT);
}
void loop()
{
//  readBoard();
  long n = arrayToInt(Board);
  Serial.println(n);
  delay(1000);
  while(Serial.available() <= 0){}
  char flag = Serial.read();    // 1 if good 0 if not good
  if(flag == '1')
  {
    delay(1000);
    while(Serial.available() <= 0){}
    String move = Serial.readString();    // 1 if good 0 if not good
//    makeMove(move);
  }else
  {
    Board[4][7] = 0;
  }
}
