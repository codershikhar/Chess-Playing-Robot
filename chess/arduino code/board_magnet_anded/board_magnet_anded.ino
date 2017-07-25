int readPinGND = 31;
int readPinVcc = 33;
int readPinEn = 41;
int readPin1 = 47;     // 8
int readPin2 = 45;     // 9
int readPin3 = 43;    // 10
int readPin4 = 39;    // 11
int readPin5 = 37;    // 12
int readPin6 = 35;    // 13
int inputPin1 = A0;

//char chessBoard[ ][8] = {
//    {'r', 'k', 'b', 'q', 'a', 'b', 'k', 'r'},
//    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
//    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
//    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
//    {'R', 'K', 'B', 'Q', 'A', 'B', 'K', 'R'}};
//
//int previousBoard[][8] = 
//{ {1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1},
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {0, 0, 0, 0, 0, 0, 0, 0}};

int currentBoard[][8] = 
{ {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}};

int tempBoard[][8] = 
{ {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}};

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
                tempBoard[i][j] = digitalRead(inputPin1);
                break;
        case 1: digitalWrite(readPin3, HIGH);
                digitalWrite(readPin2, LOW);
                digitalWrite(readPin1, LOW);
                delay(10);
                tempBoard[i][j] = digitalRead(inputPin1);
                break;
        case 2: digitalWrite(readPin3, LOW);
                digitalWrite(readPin2, HIGH);
                digitalWrite(readPin1, LOW);
                delay(10);
                tempBoard[i][j] = digitalRead(inputPin1);
                break;
        case 3: digitalWrite(readPin3, HIGH);
                digitalWrite(readPin2, HIGH);
                digitalWrite(readPin1, LOW);
                delay(10);
                tempBoard[i][j] = digitalRead(inputPin1);
                break;
        case 4: digitalWrite(readPin3, LOW);
                digitalWrite(readPin2, LOW);
                digitalWrite(readPin1, HIGH);
                delay(10);
                tempBoard[i][j] = digitalRead(inputPin1);
                break;
        case 5: digitalWrite(readPin3, HIGH);
                digitalWrite(readPin2, LOW);
                digitalWrite(readPin1, HIGH);
                delay(10);
                tempBoard[i][j] = digitalRead(inputPin1);
                break;
        case 6: digitalWrite(readPin3, LOW);
                digitalWrite(readPin2, HIGH);
                digitalWrite(readPin1, HIGH);
                delay(10);
                tempBoard[i][j] = digitalRead(inputPin1);
                break;
        case 7: digitalWrite(readPin3, HIGH);
                digitalWrite(readPin2, HIGH);
                digitalWrite(readPin1, HIGH);
                delay(10);
                tempBoard[i][j] = digitalRead(inputPin1);
                break;
      }
    }
  }
}

void getBoard()
{
//  for(int i=0; i<8; i++)
//  {for(int j=0; j<8; j++)
//  {currentBoard[i][j] = 1;}}
//  readBoard();
//  for(int i=0; i<8; i++)
//  {for(int j=0; j<8; j++)
//  {currentBoard[i][j] = currentBoard[i][j] & tempBoard[i][j];}}
//  readBoard();
//  for(int i=0; i<8; i++)
//  {for(int j=0; j<8; j++)
//  {currentBoard[i][j] = currentBoard[i][j] & tempBoard[i][j];}}
//  readBoard();
//  for(int i=0; i<8; i++)
//  {for(int j=0; j<8; j++)
//  {currentBoard[i][j] = currentBoard[i][j] & tempBoard[i][j];}}
//  readBoard();
//  for(int i=0; i<8; i++)
//  {for(int j=0; j<8; j++)
//  {currentBoard[i][j] = currentBoard[i][j] & tempBoard[i][j];}}
  readBoard();
  for(int i=0; i<8; i++)
  {
//    for(int j=0; j<8; j++)
//    {
//      Serial.print(currentBoard[i][j]);
//      Serial.print("   ");
//    }
//    Serial.print("\t");
    for(int j=0; j<8; j++)
    {
      Serial.print(tempBoard[i][j]);
      Serial.print("   ");
    }
    Serial.println("");
  }
}

void sendBoards()
{
  Serial.println(arrayToInt(currentBoard));
  delay(10);
  while(Serial.available()){}
}
void setup() 
{
  Serial.begin(9600);
  pinMode(readPinGND, OUTPUT);
  pinMode(readPinVcc, OUTPUT);
  pinMode(readPinEn, OUTPUT);
  digitalWrite(readPinGND, LOW);
  digitalWrite(readPinVcc, HIGH);
  digitalWrite(readPinEn, HIGH);
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
  getBoard();
//digitalWrite(readPin3, LOW);
//digitalWrite(readPin2, LOW);
//digitalWrite(readPin1, LOW);
//digitalWrite(readPin6, HIGH);
//digitalWrite(readPin5, HIGH);
//digitalWrite(readPin4, HIGH);
//  Serial.println(arrayToInt(currentBoard));
//Serial.println(analogRead(A0));
  Serial.println("\n");
  delay(1000);
}
