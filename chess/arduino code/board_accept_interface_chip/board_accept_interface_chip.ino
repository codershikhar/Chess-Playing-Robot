int D0 = 13;
int D1 = 12;
int S0 = 11;
int S1 = 10;
int S2 = 9;
int S3 = 8;
int S4 = 7;
int S5 = 6;
int O0 = 3;
int board[8][8];
void setup() 
{
  Serial.begin(9600);
  pinMode(O0, INPUT);
  pinMode(S5, OUTPUT);
  pinMode(S4, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
}

void loop() 
{
//  digitalWrite(S5, LOW);
//  digitalWrite(S4, LOW);
//  digitalWrite(S3, LOW);
//  digitalWrite(S2, LOW);
//  digitalWrite(S1, LOW);
//  digitalWrite(S0, LOW);
  for(int i=0; i<8; i++)
  {
    for(int j=0; j<8; j++)
    {
      board[i][j] = 0;
    }
  }
  see_board(0);
  Serial.println("");
  Serial.println("");
  see_board(1);
  Serial.println("");
  Serial.println("");
  see_board(2);
  Serial.println("");
  Serial.println("");
  delay(999999999);
}

void see_board(int n)
{
  for(int i=0; i<8; i++)
  {
    switch(i)
    {
      case 0: digitalWrite(S0, LOW);
              digitalWrite(S1, LOW);
              digitalWrite(S2, LOW);
              break;
      case 1: digitalWrite(S0, HIGH);
              digitalWrite(S1, LOW);
              digitalWrite(S2, LOW);
              break;
      case 2: digitalWrite(S0, LOW);
              digitalWrite(S1, HIGH);
              digitalWrite(S2, LOW);
              break;
      case 3: digitalWrite(S0, HIGH);
              digitalWrite(S1, HIGH);
              digitalWrite(S2, LOW);
              break;
      case 4: digitalWrite(S0, LOW);
              digitalWrite(S1, LOW);
              digitalWrite(S2, HIGH);
              break;
      case 5: digitalWrite(S0, HIGH);
              digitalWrite(S1, LOW);
              digitalWrite(S2, HIGH);
              break;
      case 6: digitalWrite(S0, LOW);
              digitalWrite(S1, HIGH);
              digitalWrite(S2, HIGH);
              break;
      case 7: digitalWrite(S0, HIGH);
              digitalWrite(S1, HIGH);
              digitalWrite(S2, HIGH);
              break;
    }
    for(int j=0; j<8; j++)
    {
      switch(j)
      {
        case 0: digitalWrite(S3, LOW);
                digitalWrite(S4, LOW);
                digitalWrite(S5, LOW);
                delay(10);
                Serial.print(digitalRead(O0));
                board[i][j] |= digitalRead(O0);
                Serial.print("\t");
                break;
        case 1: digitalWrite(S3, HIGH);
                digitalWrite(S4, LOW);
                digitalWrite(S5, LOW);
                delay(10);
                Serial.print(digitalRead(O0));
                board[i][j] |= digitalRead(O0);
                Serial.print("\t");
                break;
        case 2: digitalWrite(S3, LOW);
                digitalWrite(S4, LOW);
                digitalWrite(S5, HIGH);
                delay(10);
                Serial.print(digitalRead(O0));
                board[i][j] |= digitalRead(O0);
                Serial.print("\t");
                break;
        case 3: digitalWrite(S3, HIGH);
                digitalWrite(S4, LOW);
                digitalWrite(S5, HIGH);
                delay(10);
                Serial.print(digitalRead(O0));
                board[i][j] |= digitalRead(O0);
                Serial.print("\t");
                break;
        case 4: digitalWrite(S3, LOW);
                digitalWrite(S4, HIGH);
                digitalWrite(S5, LOW);
                delay(10);
                Serial.print(digitalRead(O0));
                board[i][j] |= digitalRead(O0);
                Serial.print("\t");
                break;
        case 5: digitalWrite(S3, HIGH);
                digitalWrite(S4, HIGH);
                digitalWrite(S5, LOW);
                delay(10);
                Serial.print(digitalRead(O0));
                board[i][j] |= digitalRead(O0);
                Serial.print("\t");
                break;
        case 6: digitalWrite(S3, LOW);
                digitalWrite(S4, HIGH);
                digitalWrite(S5, HIGH);
                delay(10);
                Serial.print(digitalRead(O0));
                board[i][j] |= digitalRead(O0);
                Serial.print("\t");
                break;
        case 7: digitalWrite(S3, HIGH);
                digitalWrite(S4, HIGH);
                digitalWrite(S5, HIGH);
                delay(10);
                Serial.print(digitalRead(O0));
                board[i][j] |= digitalRead(O0);
                Serial.print("\t");
                break;
      }
    }
    Serial.println("");
  }
  Serial.println("");
}
