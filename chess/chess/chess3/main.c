#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// all function declarations
void printBoard();
void allMoves();
char* pawnMoves(char* movesList, int i);
char* knightMoves(char* movesList, int i);
char* queenMoves(char* movesList, int i);
char* rookMoves(char* movesList, int i);
char* bishopMoves(char* movesList, int i);
char* kingMoves(char* movesList, int i);
void findKing();
int kingNotChecked();       // true = 1, false = 0
void makeMove(int x1, int y1, int x2, int y2, char piece);
void undoMove(int x1, int y1, int x2, int y2, char piece, char capture);
int AlphaBeta(int depth, int beta, int alpha, char* movesList, int player);
int ratingTheMove(int list, int depth);
void flipBoard();
int rateAttack();
int rateMaterial();
int rateMoveability(int list, int depth);
int ratePositional();
void sortList(char* list);

// Variables
char board[8][8] = {
    {'r', 'k', 'b', ' ', 'a', 'b', 'k', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', 'K', ' ', ' ', 'Q', ' ', 'q', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', ' ', 'B', ' ', 'A', 'B', 'K', 'R'}};

int kingPositionBlack=0, kingPositionWhite=0, globalDepth = 4;

char globalString[1000], globalMove4[20];

int pawnBoard[8][8]={
    { 0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    { 5,  5, 10, 25, 25, 10,  5,  5},
    { 0,  0,  0, 20, 20,  0,  0,  0},
    { 5, -5,-10,  0,  0,-10, -5,  5},
    { 5, 10, 10,-20,-20, 10, 10,  5},
    { 0,  0,  0,  0,  0,  0,  0,  0}};

int rookBoard[8][8]={
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 5, 10, 10, 10, 10, 10, 10,  5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    { 0,  0,  0,  5,  5,  0,  0,  0}};

int knightBoard[8][8]={
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}};

int bishopBoard[8][8]={
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}};

int queenBoard[8][8]={
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {  0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}};

int kingMidBoard[8][8]={
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    { 20, 20,  0,  0,  0,  0, 20, 20},
    { 20, 30, 10,  0,  0, 10, 30, 20}};

int kingEndBoard[8][8]={
    {-50,-40,-30,-20,-20,-30,-40,-50},
    {-30,-20,-10,  0,  0,-10,-20,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-30,  0,  0,  0,  0,-30,-30},
    {-50,-30,-30,-30,-30,-30,-30,-50}};

//Functions
void printBoard()
{
    int i=0, j=0;
    printf("      0  1  2  3  4  5  6  7\n\n\n");
    for(i=0; i<8; i++)
    {
        printf( "%d    ", i);
        for(j=0; j<8; j++)
        {
            if(board[i][j] == ' '){printf(" . ");}else{printf(" %c ", board[i][j]);}
        }
        printf("\n\n");
    }
}

void allMoves()
{
    char movesList[1000];        //movesformat {x1, y1, x2, y3, captured piece(p, )};
    int i=0, temp;
    movesList[0] = '\0';
    for(i=0; i<64; i++)
    {
        temp = i;   // if this is not included the i jumps from one count to 69 and this switch run only once.
        switch(board[i/8][i%8])
        {
            case 'P' :  movesList[1000] = pawnMoves(movesList, i);
                break;

            case 'K' :  movesList[1000] = knightMoves(movesList, i);
                break;

            case 'R' :  movesList[1000] = rookMoves(movesList, i);
                break;

            case 'Q' :  movesList[1000] = queenMoves(movesList, i);
                break;

            case 'A' :  movesList[1000] = kingMoves(movesList, i);
                break;

            case 'B' :  movesList[1000] = bishopMoves(movesList, i);
                break;
        }
    }
    strcpy(globalString, movesList);
}

char* pawnMoves(char* movesList, int index)
{
    int i=0, r=index/8, c=index%8, temp=1;
    char capturedPiece, move[5];

    //Pawn Capture
    for(i=-1; i<=1; i+=2)
    {
        if((board[r-1][c+i] == 'a' || board[r-1][c+i] == 'q' ||
            board[r-1][c+i] == 'r' || board[r-1][c+i] == 'b' ||
            board[r-1][c+i] == 'k' || board[r-1][c+i] == 'p') &&
           (r-1)>=2 && (c+i)>=0 && (r-1)<8 && (c+i)<8)
        {
                capturedPiece = board[r-1][c+i];
                board[r][c]=' ';
                board[r-1][c+i] = 'P';
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r-1 + 48);
                    move[3] = (char)(c+i + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    movesList[strlen(movesList)-1] = '\0';
                    movesList[strlen(movesList)-1] = '\0';
                }
                board[r][c] = 'P';
                board[r-1][c+i] = capturedPiece;
        }
    }

    // pawn movement +1
    if(r >= 2 && board[r-1][c] == ' ')
    {
        capturedPiece = ' ';
        board[r][c]=' ';
        board[r-1][c] = 'P';
        if(kingNotChecked() == 1)
        {
            move[0] = (char)(r + 48);
            move[1] = (char)(c + 48);
            move[2] = (char)(r-1 + 48);
            move[3] = (char)(c + 48);
            move[4] = capturedPiece;
            strcat(movesList, move);
            movesList[strlen(movesList)-1] = '\0';
            movesList[strlen(movesList)-1] = '\0';
        }
        board[r][c] = 'P';
        board[r-1][c] = capturedPiece;
    }

    // pawn movement +2
    if(r == 6 && board[r-2][c] == ' ' && board[r-1][c] == ' ')
    {
        capturedPiece = ' ';
        board[r][c]=' ';
        board[r-2][c] = 'P';
        if(kingNotChecked() == 1)
        {
            move[0] = (char)(r + 48);
            move[1] = (char)(c + 48);
            move[2] = (char)(r-2 + 48);
            move[3] = (char)(c + 48);
            move[4] = capturedPiece;
            strcat(movesList, move);
            movesList[strlen(movesList)-1] = '\0';
            movesList[strlen(movesList)-1] = '\0';
        }
        board[r][c] = 'P';
        board[r-2][c] = capturedPiece;
    }

    // pawn promotion without capture
    if(r == 1 && board[r-1][c] == ' ')
    {
        capturedPiece = ' ';
        board[r][c] = ' ';
        board[r-1][c] = 'Q';
        if(kingNotChecked() == 1)
        {
            move[0] = (char)(r + 48);
            move[1] = (char)(c + 48);
            move[2] = (char)(r-1 + 48);
            move[3] = (char)(c + 48);
            move[4] = capturedPiece;
            strcat(movesList, move);
            movesList[strlen(movesList)-1] = '\0';
            movesList[strlen(movesList)-1] = '\0';
        }
        board[r][c] = 'P';
        board[r-1][c] = capturedPiece;
    }

    // Pawn Promotion With Capture
    for(i=-1; i<=1; i+=2)
    {
        if((board[r-1][c+i] == 'a' || board[r-1][c+i] == 'q' ||
            board[r-1][c+i] == 'r' || board[r-1][c+i] == 'b' ||
            board[r-1][c+i] == 'k' || board[r-1][c+i] == 'p') &&
           (c+i)>=0 && (c+i)<8 && r == 1)
        {
                capturedPiece = board[r-1][c+i];
                board[r][c]=' ';
                board[r-1][c+i] = 'Q';
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r-1 + 48);
                    move[3] = (char)(c+i + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    movesList[strlen(movesList)-1] = '\0';
                    movesList[strlen(movesList)-1] = '\0';
                }
                board[r][c] = 'P';
                board[r-1][c+i] = capturedPiece;
        }
    }
    return movesList;
}
char* knightMoves(char* movesList, int i)
{
    int j=0, k=0, r=i/8, c=i%8, temp=1;
    char capturedPiece, move[5];
    for(j=-1; j<=1; j+=2)
    {
        for(k=-1; k<=1; k+=2)
        {
            if((board[r+j][c+k*2] == 'a' || board[r+j][c+k*2] == 'q' ||
                board[r+j][c+k*2] == 'r' || board[r+j][c+k*2] == 'b' ||
                board[r+j][c+k*2] == 'k' || board[r+j][c+k*2] == 'p' ||
                board[r+j][c+k*2] == ' ') && (r+j)>=0 && (c+k*2)>=0 &&
               (r+j)<8 && (c+k*2)<8)
            {
                if(board[r+j][c+k*2] == ' ')
                {
                    capturedPiece = ' ';
                }else
                {
                    capturedPiece = board[r+j][c+k*2];
                }

                board[r][c]=' ';
                board[r+j][c+k*2] = 'K';
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r+j + 48);
                    move[3] = (char)(c+k*2 + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    if(c==0)
                    {
                        movesList[strlen(movesList)-1] = '\0';
                    }else
                    {
                        movesList[strlen(movesList)-1] = '\0';
                        //movesList[strlen(movesList)-1] = '\0';
                    }
                }
                board[r][c] = 'B';
                board[r+j][c+k*2] = capturedPiece;
            }

            if((board[r+j*2][c+k] == 'a' || board[r+j*2][c+k] == 'q' ||
                board[r+j*2][c+k] == 'r' || board[r+j*2][c+k] == 'b' ||
                board[r+j*2][c+k] == 'k' || board[r+j*2][c+k] == 'p' ||
                board[r+j*2][c+k] == ' ') && (r+j*2)>=0 && (c+k)>=0 &&
               (r+j*2)<8 && (c+k)<8)
            {
                if(board[r+j*2][c+k] == ' ')
                {
                    capturedPiece = ' ';
                }else
                {
                    capturedPiece = board[r+j*2][c+k];
                }

                board[r][c]=' ';
                board[r+j*2][c+k] = 'K';
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r+j*2 + 48);
                    move[3] = (char)(c+k + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    if(c==0)
                    {
                        movesList[strlen(movesList)-1] = '\0';
                    }else
                    {
                        movesList[strlen(movesList)-1] = '\0';
                        //movesList[strlen(movesList)-1] = '\0';
                    }
                }
                board[r][c] = 'K';
                board[r+j*2][c+k] = capturedPiece;
            }
        }
    }
    return movesList;
}
char* rookMoves(char* movesList, int i)
{
    int j=0, k=0, r=i/8, c=i%8, temp=1;
    char capturedPiece, move[5];
    for(j=-1; j<2; j++)
    {
        for(k=-1; k<2; k++)
        {
            temp = 1;
            while(board[r+j*temp][c+k*temp] == ' ' && (r+j*temp)>=0 && (c+k*temp)>=0 &&
                  (r+j*temp)<8 && (c+k*temp)<8 && (j == 0 || k == 0))
            {
                capturedPiece = ' ';
                board[r][c]=' ';
                board[r+j*temp][c+k*temp] = 'R';
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r+j*temp + 48);
                    move[3] = (char)(c+k*temp + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    if(c==0)
                    {
                        movesList[strlen(movesList)-1] = '\0';
                    }else
                    {
                        movesList[strlen(movesList)-1] = '\0';
                        movesList[strlen(movesList)-1] = '\0';
                    }
                }
                board[r][c] = 'R';
                board[r+j*temp][c+k*temp] = capturedPiece;
                temp++;
            }
            if((board[r+j*temp][c+k*temp] == 'a' || board[r+j*temp][c+k*temp] == 'q' ||
                board[r+j*temp][c+k*temp] == 'r' || board[r+j*temp][c+k*temp] == 'b' ||
                board[r+j*temp][c+k*temp] == 'k' || board[r+j*temp][c+k*temp] == 'p') &&
               (r+j*temp)>=0 && (c+k*temp)>=0 && (r+j*temp)<8 && (c+k*temp)<8 && (j == 0 || k == 0))
            {
                capturedPiece = board[r+j*temp][c+k*temp];
                board[r][c]=' ';
                board[r+j*temp][c+k*temp] = 'R';
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r+j*temp + 48);
                    move[3] = (char)(c+k*temp + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    if(c==0)
                    {
                        movesList[strlen(movesList)-1] = '\0';
                    }else
                    {
                        movesList[strlen(movesList)-1] = '\0';
                        movesList[strlen(movesList)-1] = '\0';
                    }
                }
                board[r][c] = 'R';
                board[r+j*temp][c+k*temp] = capturedPiece;
            }
        }
    }
    return movesList;
}
char* queenMoves(char* movesList, int i)
{
    int j=0, k=0, r=i/8, c=i%8, temp=1;
    char capturedPiece, move[5];
    for(j=-1; j<2; j++)
    {
        for(k=-1; k<2; k++)
        {
            temp = 1;
            while(board[r+j*temp][c+k*temp] == ' ' && (r+j*temp)>=0 && (c+k*temp)>=0 &&
                  (r+j*temp)<8 && (c+k*temp)<8 && (j != 0 || k != 0))
            {
                capturedPiece = ' ';
                board[r][c]=' ';
                board[r+j*temp][c+k*temp] = 'Q';
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r+j*temp + 48);
                    move[3] = (char)(c+k*temp + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    if(c==0)
                    {
                        movesList[strlen(movesList)-1] = '\0';
                    }else
                    {
                        movesList[strlen(movesList)-1] = '\0';
                        movesList[strlen(movesList)-1] = '\0';
                    }
                }
                board[r][c] = 'Q';
                board[r+j*temp][c+k*temp] = capturedPiece;
                temp++;
            }
            if((board[r+j*temp][c+k*temp] == 'a' || board[r+j*temp][c+k*temp] == 'q' ||
                board[r+j*temp][c+k*temp] == 'r' || board[r+j*temp][c+k*temp] == 'b' ||
                board[r+j*temp][c+k*temp] == 'k' || board[r+j*temp][c+k*temp] == 'p') &&
               (r+j*temp)>=0 && (c+k*temp)>=0 && (r+j*temp)<8 && (c+k*temp)<8 && (j != 0 || k != 0))
            {
                capturedPiece = board[r+j*temp][c+k*temp];
                board[r][c]=' ';
                board[r+j*temp][c+k*temp] = 'Q';
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r+j*temp + 48);
                    move[3] = (char)(c+k*temp + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    if(c==0)
                    {
                        movesList[strlen(movesList)-1] = '\0';
                    }else
                    {
                        movesList[strlen(movesList)-1] = '\0';
                        movesList[strlen(movesList)-1] = '\0';
                    }
                }
                board[r][c] = 'Q';
                board[r+j*temp][c+k*temp] = capturedPiece;
            }
        }
    }
    return movesList;
}
char* kingMoves(char* movesList, int i)
{
    int j=0, r=i/8, c=i%8;
    char capturedPiece, move[5];
    for(j=0; j<9; j++)
    {
        if(j!=4)
        {
            if((board[r-1+j/3][c-1+j%3] == 'a' || board[r-1+j/3][c-1+j%3] == 'q' ||
                board[r-1+j/3][c-1+j%3] == 'r' || board[r-1+j/3][c-1+j%3] == 'b' ||
                board[r-1+j/3][c-1+j%3] == 'k' || board[r-1+j/3][c-1+j%3] == 'p' ||
                board[r-1+j/3][c-1+j%3] == ' ') && (r-1+j/3)>=0 && (c-1+j%3)>=0 && (r-1+j/3)<8 && (c-1+j%3)<8)
            {
                capturedPiece = board[r-1+j/3][c-1+j%3];
                board[r][c]=' ';
                board[r-1+j/3][c-1+j%3] = 'A';
                findKing();
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r-1+j/3 + 48);
                    move[3] = (char)(c-1+j%3 + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    if(c==0)
                    {
                        movesList[strlen(movesList)-1] = '\0';
                    }else
                    {
                        movesList[strlen(movesList)-1] = '\0';
                        movesList[strlen(movesList)-1] = '\0';
                    }
                }
                board[r][c] = 'A';
                board[r-1+j/3][c-1+j%3] = capturedPiece;
                findKing();
            }
        }
    }
    return movesList;
}

char* bishopMoves(char* movesList, int i)
{
    int j=0, k=0, r=i/8, c=i%8, temp=1;
    char capturedPiece, move[5];
    for(j=-1; j<2; j+=2)
    {
        for(k=-1; k<2; k+=2)
        {
            temp = 1;
            while(board[r+j*temp][c+k*temp] == ' ' && (r+j*temp)>=0 && (c+k*temp)>=0 &&
                  (r+j*temp)<8 && (c+k*temp)<8)
            {
                capturedPiece = ' ';
                board[r][c]=' ';
                board[r+j*temp][c+k*temp] = 'B';
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r+j*temp + 48);
                    move[3] = (char)(c+k*temp + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    if(c==0)
                    {
                        movesList[strlen(movesList)-1] = '\0';
                    }else
                    {
                        movesList[strlen(movesList)-1] = '\0';
                        movesList[strlen(movesList)-1] = '\0';
                    }
                }
                board[r][c] = 'B';
                board[r+j*temp][c+k*temp] = capturedPiece;
                temp++;
            }
            if((board[r+j*temp][c+k*temp] == 'a' || board[r+j*temp][c+k*temp] == 'q' ||
                board[r+j*temp][c+k*temp] == 'r' || board[r+j*temp][c+k*temp] == 'b' ||
                board[r+j*temp][c+k*temp] == 'k' || board[r+j*temp][c+k*temp] == 'p') &&
               (r+j*temp)>=0 && (c+k*temp)>=0 && (r+j*temp)<8)
            {
                capturedPiece = board[r+j*temp][c+k*temp];
                board[r][c]=' ';
                board[r+j*temp][c+k*temp] = 'B';
                if(kingNotChecked() == 1)
                {
                    move[0] = (char)(r + 48);
                    move[1] = (char)(c + 48);
                    move[2] = (char)(r+j*temp + 48);
                    move[3] = (char)(c+k*temp + 48);
                    move[4] = capturedPiece;
                    strcat(movesList, move);
                    if(c==0)
                    {
                        movesList[strlen(movesList)-1] = '\0';
                    }else
                    {
                        movesList[strlen(movesList)-1] = '\0';
                        movesList[strlen(movesList)-1] = '\0';
                    }
                }
                board[r][c] = 'B';
                board[r+j*temp][c+k*temp] = capturedPiece;
            }
        }
    }
    return movesList;
}

void findKing()
{
    int i=-1;
    while(board[i/8][i%8] != 'a'){i++;}
    kingPositionBlack = i;
    i = -1;
    while(board[i/8][i%8] != 'A'){i++;}
    kingPositionWhite = i;
}

int kingNotChecked()
{
    int i=0, j=0, temp=1;
    // Bishop and Queen
    for(i=-1; i<2; i+=2)
    {
        for(j=-1; j<2; j+=2)
        {
            temp=1;
            while(board[kingPositionWhite/8+i*temp][kingPositionWhite%8+j*temp] == ' '){temp++;}
            if(board[kingPositionWhite/8+i*temp][kingPositionWhite%8+j*temp] == 'b' ||
                  board[kingPositionWhite/8+i*temp][kingPositionWhite%8+j*temp] == 'q')
            {
                return 0;
            }
        }
    }

    // Rook and Queen
    for(i=-1; i<2; i++)
    {
        for(j=-1; j<2; j++)
        {
            temp=1;
            if(i==0 || j==0)
            {
                while(board[kingPositionWhite/8+i*temp][kingPositionWhite%8+j*temp] == ' '){temp++;}
                if(board[kingPositionWhite/8+i*temp][kingPositionWhite%8+j*temp] == 'r' ||
                    board[kingPositionWhite/8+i*temp][kingPositionWhite%8+j*temp] == 'q')
                {
                    return 0;
                }
            }
        }
    }

    // King
    for(i=0; i<9; i++)
    {
        if(i!=4 && board[kingPositionWhite/8+i/3][kingPositionWhite%8+i%3] == 'k')
        {
            return 0;
        }
    }

    // Knight
    for(i=-1; i<=1; i+=2)
    {
        for(j=-1; j<=1; j+=2)
        {
            if(board[kingPositionWhite/8+i][kingPositionWhite%8+j*2] == 'k' &&
               (kingPositionWhite/8+i)>=0 && (kingPositionWhite%8+j*2)>=0 &&
               (kingPositionWhite/8+i)<8 && (kingPositionWhite%8+j*2)<8)
            {
                return 0;
            }
        }
    }


    // Pawn
    if(kingPositionWhite > 15)
    {
        if(board[kingPositionWhite/8-1][kingPositionWhite%8-1] == 'p' || board[kingPositionWhite/8-1][kingPositionWhite%8+1] == 'p')
        {
            return 0;
        }
    }

    // NO check condition
    return 1;
}

void makeMove(int x1, int y1, int x2, int y2, char piece)
{
    if((board[x1][y1] = 'P' && x2 == 0) || (board[x1][y1] = 'p' && x2 == 0))      // Pawn Promotion
    {
        board[x1][y1] = ' ';
        if(piece == 'P'){board[x2][y2] = 'Q';}else{board[x2][y2] = 'q';}
    }else
    {
        board[x1][y1] = ' ';
        board[x2][y2] = piece;
        findKing();
    }
}

void undoMove(int x1, int y1, int x2, int y2, char piece, char capture)
{
    board[x1][y1] = piece;
    board[x2][y2] = capture;
    findKing();
}

int AlphaBeta(int depth, int beta, int alpha, char move[20], int player)
{
    int temp=0, i=0, j=0, value=0, noofmoves;
    char list[1000], tempString[20], tempCapture = ' ', returnString[20];
    list[0] = '\0';
    returnString[0] = '\0';
    tempString[0] = '\0';
    allMoves();
    strcpy(list, globalString);
    if(depth == 0 || strlen(list) == 0)
    {
        temp = strlen(list);
        temp = ratingTheMove(temp, depth)*(player*2-1);
        tempString[0] = '\0';
        sprintf(tempString, "%d", temp);
        if(depth == globalDepth){strcpy(move, globalMove4);}
        strcat(move, tempString);
        strcpy(globalString, move);
        return 0;
    }
    //list = sortMoves(list);
    player = 1-player; // either 1 or 0
    for(i=0; i<strlen(list); i+=5)
    {
        tempCapture = board[(int)list[i+2]][(int)list[i+3]];
        makeMove((int)list[i+0], (int)list[i+1], (int)list[i+2], (int)list[i+3], board[(int)list[i+0]][(int)list[i+1]]);
        flipBoard();
        tempString[0] = '\0';
        for(j=0; j<5; j++)
        {
            tempString[0+j] = list[i+j];
        }
        tempString[5] = '\0';
        AlphaBeta(depth-1, beta, alpha, tempString, player);
        strcpy(returnString, globalString);
        j = 5;
        strcpy(tempString, " ");
        while(returnString[j]!='\0')
        {
            tempString[j-5] = returnString[j];
            j++;
        }
        value = atoi(tempString);
        flipBoard();
        undoMove((int)list[i+0], (int)list[i+1], (int)list[i+2], (int)list[i+3], board[(int)list[i+2]][(int)list[i+3]], tempCapture);
        if(player == 0)
        {
            if(value <= beta)
            {
                beta = value;
                if(depth == globalDepth)
                {
                    globalMove4[0] = '\0';
                    for(i=0; i<5; i++)
                    {
                        globalMove4[i] = returnString[i];
                    }
                    globalMove4[5] = '\0';
                }
            }
        }else
        {
            if(value > alpha)
            {
                alpha = value;
                if(depth == globalDepth)
                {
                    globalMove4[0] = '\0';
                    for(i=0; i<5; i++)
                    {
                        globalMove4[i] = returnString[i];
                    }
                    globalMove4[5] = '\0';
                }
            }
        }
        if(alpha>=beta)
        {
            if(player == 0)
            {
                tempString[0] = '\0';
                sprintf(tempString, "%d", beta);
                if(depth == globalDepth){strcpy(move, globalMove4);}
                strcat(move, tempString);
                strcpy(globalString, move);
                return 0;
            }else
            {
                tempString[0] = '\0';
                sprintf(tempString, "%d", alpha);
                if(depth == globalDepth){strcpy(move, globalMove4);}
                strcat(move, tempString);
                strcpy(globalString, move);
                return 0;
            }
        }
    }
    if(player == 0)
    {
        tempString[0] = '\0';
        sprintf(tempString, "%d", beta);
        if(depth == globalDepth)
        {
            strcat(globalMove4, tempString);
            strcpy(globalString, globalMove4);
            return 0;
        }
        strcat(move, tempString);
        strcpy(globalString, move);
        return 0;
    }else
    {
        tempString[0] = '\0';
        sprintf(tempString, "%d", alpha);
        if(depth == globalDepth)
        {
            strcat(globalMove4, tempString);
            strcpy(globalString, globalMove4);
            return 0;
        }
        strcat(move, tempString);
        strcpy(globalString, move);
        return 0;
    }
}

void flipBoard()
{
    int i=0, r=0, c=0;
    char temp = ' ';
    for(i=0; i<32; i++)
    {
        r = i/8;
        c = i%8;
        temp = board[r][c];
        board[r][c] = board[7-r][7-c];
        board[7-r][7-c] = temp;
    }
    for(i=0; i<64; i++)
    {
        r = i/8;
        c = i%8;
        temp = board[r][c];
        switch(temp)
        {
        case 'a' : board[r][c] = 'A';
            break;
        case 'q' : board[r][c] = 'Q';
            break;
        case 'r' : board[r][c] = 'R';
            break;
        case 'b' : board[r][c] = 'B';
            break;
        case 'k' : board[r][c] = 'K';
            break;
        case 'p' : board[r][c] = 'P';
            break;
        case 'A' : board[r][c] = 'a';
            break;
        case 'Q' : board[r][c] = 'q';
            break;
        case 'R' : board[r][c] = 'r';
            break;
        case 'B' : board[r][c] = 'b';
            break;
        case 'K' : board[r][c] = 'k';
            break;
        case 'P' : board[r][c] = 'p';
            break;
        }
    }
    findKing();
}


int ratingTheMove(int list, int depth)
{
    int rate=0, material = rateMaterial();
    rate += rateAttack();
    rate += material;
    rate += rateMoveability(list, depth);
    rate += ratePositional(material);
    flipBoard();
    material = rateMaterial();
    rate -= rateAttack();
    rate -= material;
    rate -= rateMoveability(list, depth);
    rate -= ratePositional(material);
    flipBoard();
    return rate;
}

int rateAttack()
{
    int rate=0, i=0;
    int tempPositionKing=kingPositionWhite;
    for(i=0; i<64; i++)
    {
        switch(board[i/8][i%8])
        {
            case 'P':   kingPositionWhite=i;
                        if(kingNotChecked() != 1){rate-=64;}
                        break;
            case 'R':   kingPositionWhite=i;
                        if(kingNotChecked() != 1){rate-=500;}
                        break;
            case 'K':   kingPositionWhite=i;
                        if(kingNotChecked() != 1){rate-=300;}
                        break;
            case 'B':   kingPositionWhite=i;
                        if(kingNotChecked() != 1){rate-=300;}
                        break;
            case 'Q':   kingPositionWhite=i;
                        if(kingNotChecked() != 1){rate-=900;}
                        break;
        }
    }
    kingPositionWhite=tempPositionKing;
    if(kingNotChecked() != 1){rate-=200;}
    return rate/2;
}

int rateMaterial()
{
    int rate=0, bishopCounter=0, i=0;
    for(i=0;i<64;i++)
    {
        switch(board[i/8][i%8])
        {
            case 'P': rate+=100;
                break;
            case 'R': rate+=500;
                break;
            case 'K': rate+=300;
                break;
            case 'B': bishopCounter+=1;
                break;
            case 'Q': rate+=900;
                break;
        }
    }
    if(bishopCounter>=2)
    {
        rate+=300*bishopCounter;
    }else
    {
        if(bishopCounter==1){rate+=250;}
    }
    return rate;
}

int rateMoveability(int list, int depth)
{
    int rate=0;
    rate+=list;     //5 pointer per valid move
    if (list==0)  //current side is in checkmate or stalemate
    {
        if(kingNotChecked() != 1)  //if checkmate
        {
            rate+=-200000*depth;
        }else   //if stalemate
        {
            rate+=-150000*depth;
        }
    }
    return rate;
}

int ratePositional(int material)
{
    int rate=0, i=0;
    for(i=0; i<64; i++)
    {
        switch(board[i/8][i%8])
        {
            case 'P':   rate+=pawnBoard[i/8][i%8];
                        break;
            case 'R':   rate+=rookBoard[i/8][i%8];
                        break;
            case 'K':   rate+=knightBoard[i/8][i%8];
                        break;
            case 'B':   rate+=bishopBoard[i/8][i%8];
                        break;
            case 'Q':   rate+=queenBoard[i/8][i%8];
                        break;
            case 'A':   if(material>=1750)
                        {
                            rate+=kingMidBoard[i/8][i%8];
                        }else
                        {
                            rate+=kingEndBoard[i/8][i%8];
                        }
                        break;
        }
    }
    return rate;
}

void sortList(char* list)
{
    int value[200], i = 0, max = 0, j = 0, index = 0;
    char sortedList[1000], tempCapture, temp[5];
    printf("\nThe List is : %s\n", list);
    strcpy(sortedList, "");
    for(i=0; i<strlen(list); i+=5)
    {
        tempCapture = board[(int)list[i+2]][(int)list[i+3]];
        makeMove((int)list[i+0], (int)list[i+1], (int)list[i+2], (int)list[i+3], board[(int)list[i+0]][(int)list[i+1]]);
        value[i/5] = ratingTheMove(0, 0);
        undoMove((int)list[i+0], (int)list[i+1], (int)list[i+2], (int)list[i+3], board[(int)list[i+2]][(int)list[i+3]], tempCapture);
        printf("\nvalue[%d] = %d", i, value[i]);
    }
    for(i=0; i<strlen(list); i+=5)
    {
        for(j=0; j<strlen(list); j++)
        {
            if(max < value[j])
            {
                max = value[j];
                index = j;
            }
        }
        temp[0] = list[index*5 + 0];
        temp[1] = list[index*5 + 1];
        temp[2] = list[index*5 + 2];
        temp[3] = list[index*5 + 3];
        temp[4] = list[index*5 + 4];
        strcat(sortedList, temp);
    }
    printf("\nThe Sorted List is : %s\n", sortedList);
    //strcpy(globalString; sortedList);
}

//main
int main()
{
    sortList("3436q"); // "6065 3110p3112p3414p3436q"
    char move[50];
    int x1=0, x2=0, y1=0, y2=0;
    printf("SETTING BOARD...\n");
    while(kingPositionBlack != -1 || kingPositionWhite != -1)
    {
        printf("\n\n");
        printBoard();
        printf("\n\n");
        printf("Enter Your Move : \n");
        printf("From(x1, y1) : ");
        scanf("%d%d", &x1, &y1);
        printf("To(x2, y2) : ");
        scanf("%d%d", &x2, &y2);
        makeMove(x1, y1, x2, y2, board[x1][y1]);
        printf("\n\nBlack Move...\n");
        //
        printBoard();
        findKing();
        AlphaBeta(globalDepth, 1000000, -1000000, "", 0);
        printf("\n\nWhites Move...");
        strcpy(move, globalString);
        makeMove((int)move[0]-48, (int)move[1]-48, (int)move[2]-48, (int)move[3]-48, board[(int)move[0]-48][(int)move[1]-48]);
        /*printf("\n\n");
        printBoard();
        printf("\n\n");
        printf("Enter Your Move : \n");
        printf("From(x1, y1) : ");
        scanf("%d%d", &x1, &y1);
        printf("To(x2, y2) : ");
        scanf("%d%d", &x2, &y2);
        makeMove(x1, y1, x2, y2, board[x1][y1]);
        printf("\n\nBlack Move...\n");*/
    }
    if(kingPositionBlack == -1){printf("\n\nYOU LOSE...");}else{printf("\n\nYOU WIN...");}
    return 0;
}
