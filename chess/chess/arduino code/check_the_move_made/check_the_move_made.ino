// PINS
int pinP1 = 13;   // Push button
int pinM1 = 12;   // mux 1:2
int pinS1 = 11;   // mux 3:8 (1)
int pinS2 = 10;   // mux 3:8 (1)
int pinS3 = 9;   // mux 3:8 (1)
int pinS4 = 8;   // mux 3:8 (2/3) (2 when pinM1 is High, 3 when pinM1 is low)
int pinS5 = 7;   // mux 3:8 (2/3) (2 when pinM1 is High, 3 when pinM1 is low)
int pinS6 = 6;   // mux 3:8 (2/3) (2 when pinM1 is High, 3 when pinM1 is low)
int pinInput = 5; // to check if BLACK piece is there or not

// VARIABLES
static char chessBoard[8][8] = {
    {'r', 'k', 'b', 'q', 'a', 'b', 'k', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'K', 'B', 'Q', 'A', 'B', 'K', 'R'}};

static int afterMove[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}};

static int beforeMove[8][8] = { 
    {1, 1, 1, 1, 1, 1, 1, 1}, 
    {1, 1, 1, 1, 1, 1, 1, 1}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}};

const int position[8][8] = { 
    { 0,  1,  2,  3,  4,  5,  6,  7}, 
    { 8,  9, 10, 11, 12, 13, 14, 15}, 
    {16, 17, 18, 19, 20, 21, 22, 23}, 
    {24, 25, 26, 27, 28, 29, 30, 31}, 
    {31, 32, 33, 34, 35, 36, 37, 38}, 
    {39, 40, 41, 42, 44, 45, 46, 47}, 
    {48, 49, 50, 51, 52, 53, 54, 55}, 
    {56, 57, 58, 59, 60, 61, 62, 63}};

// FUNCTIONS DECLARATION
void pin_of_mux1(int i);
void pin_of_mux2(int j);
String compareBoards();
void makeMoveBlack(String Move);
void makeMoveWhite(String Move);

// FUNCTIONS DEFINATION
void pin_of_mux1(int i)
{
  switch(i)
  {
    case 0: digitalWrite(pinS1, LOW);
            digitalWrite(pinS2, LOW);
            digitalWrite(pinS3, LOW);
            break;
    case 1: digitalWrite(pinS1, LOW);
            digitalWrite(pinS2, LOW);
            digitalWrite(pinS3, HIGH);
            break;
    case 2: digitalWrite(pinS1, LOW);
            digitalWrite(pinS2, HIGH);
            digitalWrite(pinS3, LOW);
            break;
    case 3: digitalWrite(pinS1, LOW);
            digitalWrite(pinS2, HIGH);
            digitalWrite(pinS3, HIGH);
            break;
    case 4: digitalWrite(pinS1, HIGH);
            digitalWrite(pinS2, LOW);
            digitalWrite(pinS3, LOW);
            break;
    case 5: digitalWrite(pinS1, HIGH);
            digitalWrite(pinS2, LOW);
            digitalWrite(pinS3, HIGH);
            break;
    case 6: digitalWrite(pinS1, HIGH);
            digitalWrite(pinS2, HIGH);
            digitalWrite(pinS3, LOW);
            break;
    case 7: digitalWrite(pinS1, HIGH);
            digitalWrite(pinS2, HIGH);
            digitalWrite(pinS3, HIGH);
            break;
  }
}

void pin_of_mux2(int j)
{
  switch(j)
  {
    case 0: digitalWrite(pinS4, LOW);
            digitalWrite(pinS5, LOW);
            digitalWrite(pinS6, LOW);
            break;
    case 1: digitalWrite(pinS4, LOW);
            digitalWrite(pinS5, LOW);
            digitalWrite(pinS6, HIGH);
            break;
    case 2: digitalWrite(pinS4, LOW);
            digitalWrite(pinS5, HIGH);
            digitalWrite(pinS6, LOW);
            break;
    case 3: digitalWrite(pinS4, LOW);
            digitalWrite(pinS5, HIGH);
            digitalWrite(pinS6, HIGH);
            break;
    case 4: digitalWrite(pinS4, HIGH);
            digitalWrite(pinS5, LOW);
            digitalWrite(pinS6, LOW);
            break;
    case 5: digitalWrite(pinS4, HIGH);
            digitalWrite(pinS5, LOW);
            digitalWrite(pinS6, HIGH);
            break;
    case 6: digitalWrite(pinS4, HIGH);
            digitalWrite(pinS5, HIGH);
            digitalWrite(pinS6, LOW);
            break;
    case 7: digitalWrite(pinS4, HIGH);
            digitalWrite(pinS5, HIGH);
            digitalWrite(pinS6, HIGH);
            break;
  }
}

String compareBoards()
{
  int m[5], count=0, number;
  String Move = "", temp = "";
  for(int i=0; i<8; i++)
  {
    for(int j=0; j<8; j++)
    {
      if(afterMove[i][j] != beforeMove[i][j]) {m[count] = position[i][j];}
    }
  }
  if( chessBoard[m[0]/8][m[0]%8] == 'a' || chessBoard[m[0]/8][m[0]%8] == 'q' ||
      chessBoard[m[0]/8][m[0]%8] == 'r' || chessBoard[m[0]/8][m[0]%8] == 'b' ||
      chessBoard[m[0]/8][m[0]%8] == 'k' || chessBoard[m[0]/8][m[0]%8] == 'p')
      {
        Move = String(m[0]/8) + String(m[0]%8) + String(m[1]/8) + String(m[1]%8) + chessBoard[m[0]/8][m[0]%8];
      }else
      {
        Move = String(m[1]/8) + String(m[1]%8) + String(m[0]/8) + String(m[0]%8) + chessBoard[m[1]/8][m[1]%8];
      }
  return Move;
}

void makeMoveBlack(String Move)
{
  beforeMove[int(Move[0])][int(Move[1])] = 0;
  beforeMove[int(Move[2])][int(Move[3])] = 1;
  if (chessBoard[(int)(Move[0])-48][(int)(Move[1])-48] == 'p' && (Move[0]-48) >=6)
  {
      //if pawn promotion of BLACK
      chessBoard[(int)(Move[2])-48][(int)(Move[3])-48]= 'q';
      chessBoard[(int)(Move[0])-48][(int)(Move[1])-48] = ' ';
  }else
  {
      chessBoard[(int)(Move[2])-48][(int)(Move[3])-48] = chessBoard[(int)(Move[0])-48][(int)(Move[1])-48];
      chessBoard[(int)(Move[0])-48][(int)(Move[1])-48]= ' ';
  }
}

void makeMoveWhite(String Move)
{
  if (chessBoard[(int)(Move[0])-48][(int)(Move[1])-48] == 'P' && (Move[0]-48) <=1)
  {
      //if pawn promotion of WHITE
      chessBoard[(int)(Move[2])-48][(int)(Move[3])-48]= 'Q';
      chessBoard[(int)(Move[0])-48][(int)(Move[1])-48] = ' ';
  }else
  {
      chessBoard[(int)(Move[2])-48][(int)(Move[3])-48] = chessBoard[(int)(Move[0])-48][(int)(Move[1])-48];
      chessBoard[(int)(Move[0])-48][(int)(Move[1])-48]= ' ';
  }
}


void setup() 
{
  pinMode(pinP1, INPUT);
  pinMode(pinM1, OUTPUT);
  pinMode(pinS1, OUTPUT);
  pinMode(pinS2, OUTPUT);
  pinMode(pinS3, OUTPUT);
  pinMode(pinS4, OUTPUT);
  pinMode(pinS5, OUTPUT);
  pinMode(pinS6, OUTPUT);
  pinMode(pinInput, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  while(digitalRead(pinP1) == LOW){};   //High when the player makes his Move and presses the push button
  
  //LOGIC TO READ BOARD
  digitalWrite(pinM1, HIGH);  //when high muux 3:8 (2) is active
  for(int i=0; i<8; i++)
  {
    pin_of_mux1(i);
    for(int j=0; j<8; j++)
    {
      pin_of_mux2(j);
      delay(1);
      // High meance piece is present at that position
      if(digitalRead(pinInput) == HIGH){afterMove[i][j] = 1;}else{afterMove[i][j] = 0;}
    }
  }
  String Move = compareBoards(); //returns the Move human made
  Serial.flush();
  char move[5];
  Move.toCharArray(move, 5);
  Serial.write(move);
  makeMoveBlack(Move);
  while(Serial.available() == 0){}  //wait for comp to make a move
  Move = Serial.readString();
  Serial.flush();
  makeMoveWhite(Move);
}
