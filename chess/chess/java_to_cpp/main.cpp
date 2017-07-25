#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;

// FUNCTIONS INITIALISATION
void findKing();
void flipBoard();
string posibleMoves();
string posibleP(int i);
string posibleR(int i);
string posibleK(int i);
string posibleB(int i);
string posibleQ(int i);
string posibleA(int i);
bool kingSafe();
void makeMove(string move);
void undoMove(string move);
string alphaBeta(int depth, int beta, int alpha, string move, int player);
int stringLength(string list);
int rating(int list, int depth);
string sortMoves(string list);
int rateMaterial();
int rateAttack();
int rateMoveablitly(int list, int depth, int material);
int ratePositional(int material);
void printBoard();

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

static int kingPositionC, kingPositionL;
static int humanAsWhite=-1;
static int globalDepth=4;
const int pawnBoard[8][8]={
    { 0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    { 5,  5, 10, 25, 25, 10,  5,  5},
    { 0,  0,  0, 20, 20,  0,  0,  0},
    { 5, -5,-10,  0,  0,-10, -5,  5},
    { 5, 10, 10,-20,-20, 10, 10,  5},
    { 0,  0,  0,  0,  0,  0,  0,  0}};
const int rookBoard[8][8]={
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 5, 10, 10, 10, 10, 10, 10,  5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    { 0,  0,  0,  5,  5,  0,  0,  0}};
const int knightBoard[8][8]={
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}};
const int bishopBoard[8][8]={
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}};
const int queenBoard[8][8]={
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {  0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}};
const int kingMidBoard[8][8]={
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    { 20, 20,  0,  0,  0,  0, 20, 20},
    { 20, 30, 10,  0,  0, 10, 30, 20}};
const int kingEndBoard[8][8]={
    {-50,-40,-30,-20,-20,-30,-40,-50},
    {-30,-20,-10,  0,  0,-10,-20,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-30,  0,  0,  0,  0,-30,-30},
    {-50,-30,-30,-30,-30,-30,-30,-50}};

//FUNCTIONS
void findKing()
{
    kingPositionC = 0;
    kingPositionL = 0;
    while('A' != chessBoard[kingPositionC/8][kingPositionC%8] && kingPositionC<64){kingPositionC++;}//get White King's location
    while('a' != chessBoard[kingPositionL/8][kingPositionL%8] && kingPositionL<64){kingPositionL++;}//get Black king's location
}

void flipBoard()
{
    int i=0, r=0, c=0;
    char temp;
    for(i=0; i<32; i++)
    {
        r = i/8;
        c = i%8;
        temp = chessBoard[r][c];
        chessBoard[r][c] = chessBoard[7-r][7-c];
        chessBoard[7-r][7-c] = temp;
    }
    for(i=0; i<64; i++)
    {
        r = i/8;
        c = i%8;
        temp = chessBoard[r][c];
        switch(temp)
        {
        case 'a' : chessBoard[r][c] = 'A';
            break;
        case 'q' : chessBoard[r][c] = 'Q';
            break;
        case 'r' : chessBoard[r][c] = 'R';
            break;
        case 'b' : chessBoard[r][c] = 'B';
            break;
        case 'k' : chessBoard[r][c] = 'K';
            break;
        case 'p' : chessBoard[r][c] = 'P';
            break;
        case 'A' : chessBoard[r][c] = 'a';
            break;
        case 'Q' : chessBoard[r][c] = 'q';
            break;
        case 'R' : chessBoard[r][c] = 'r';
            break;
        case 'B' : chessBoard[r][c] = 'b';
            break;
        case 'K' : chessBoard[r][c] = 'k';
            break;
        case 'P' : chessBoard[r][c] = 'p';
            break;
        }
    }
    findKing();
}

string posibleMoves()
{
    string list="";
    for(int i=0; i<64; i++)
    {
        switch (chessBoard[i/8][i%8])
        {
            case 'P': list+=posibleP(i);
                break;
            case 'R': list+=posibleR(i);
                break;
            case 'K': list+=posibleK(i);
                break;
            case 'B': list+=posibleB(i);
                break;
            case 'Q': list+=posibleQ(i);
                break;
            case 'A': list+=posibleA(i);
                break;
        }
    }
    return list;//x1,y1,x2,y2,captured piece
}

string posibleP(int i)
{
    string list = "";
    char oldPiece;
    int r=i/8, c=i%8;
    for(int j=-1; j<=1; j+=2)
    {
        try //capture
        {
            if  ((chessBoard[r-1][c+j] == 'a' || chessBoard[r-1][c+j] == 'q' ||
                chessBoard[r-1][c+j] == 'r' || chessBoard[r-1][c+j] == 'b' ||
                chessBoard[r-1][c+j] == 'k' || chessBoard[r-1][c+j] == 'p') &&
                 ((r-1)>=0 && (r-1)<8 && (c+j)>=0 && (c+j)<8))
            {
                oldPiece = chessBoard[r-1][c+j];
                chessBoard[r][c] = ' ';
                chessBoard[r-1][c+j] = 'P';
                if (kingSafe())
                {
                    list = list + (char)(r+48) + (char)(c+48) + (char)(r-1+48) + (char)(c+j+48) + oldPiece;
                }
                chessBoard[r][c] = 'P';
                chessBoard[r-1][c+j] = oldPiece;
            }
        }catch (exception e) {}
    }

    try //move one up
    {
        if((chessBoard[r-1][c] == ' ') && ((r-1)>=0 && (r-1)<8 && (c)>=0 && (c)<8))
        {
            oldPiece = chessBoard[r-1][c];
            chessBoard[r][c] = ' ';
            chessBoard[r-1][c] = 'P';
            if (kingSafe())
            {
                list = list + (char)(r+48) + (char)(c+48) + (char)(r-1+48) + (char)(c+48) + oldPiece;
            }
            chessBoard[r][c] = 'P';
            chessBoard[r-1][c] = oldPiece;
        }
    } catch (exception e) {}

    try //move two up
    {
        if (chessBoard[r-1][c] == ' ' && chessBoard[r-2][c] == ' ' && i>=48 &&
            ((r-1)>=0 && (r-1)<8 && (c)>=0 && (c)<8 && (r-2)>=0 && (r-2)<8))
        {
            oldPiece = chessBoard[r-2][c];
            chessBoard[r][c] = ' ';
            chessBoard[r-2][c] = 'P';
            if (kingSafe())
            {
                list = list + (char)(r+48) + (char)(c+48) + (char)(r-2+48) + (char)(c+48) + oldPiece;
            }
            chessBoard[r][c] = 'P';
            chessBoard[r-2][c] = oldPiece;
        }
    } catch (exception e) {}
    return list;
}

string posibleR(int i)
{
    string list="";
    char oldPiece;
    int r=i/8, c=i%8;
    int temp=1;
    for (int j=-1; j<=1; j+=2)
    {
        try
        {
            while(chessBoard[r][c+temp*j] == ' ' && ((r)>=0 && (r)<8 && (c+temp*j)>=0 && (c+temp*j)<8))
            {
                oldPiece = chessBoard[r][c+temp*j];
                chessBoard[r][c] = ' ';
                chessBoard[r][c+temp*j] = 'R';
                if (kingSafe())
                {
                    list = list + (char)(r+48) + (char)(c+48) + (char)(r+48) + (char)(c+temp*j+48) + oldPiece;
                }
                chessBoard[r][c]= 'R';
                chessBoard[r][c+temp*j] = oldPiece;
                temp++;
            }
            if ((chessBoard[r][c+temp*j] == 'a' || chessBoard[r][c+temp*j] == 'q' ||
                chessBoard[r][c+temp*j] == 'r' || chessBoard[r][c+temp*j] == 'b' ||
                chessBoard[r][c+temp*j] == 'k' || chessBoard[r][c+temp*j] == 'p') &&
                ((r)>=0 && (r)<8 && (c+temp*j)>=0 && (c+temp*j)<8))
            {
                oldPiece = chessBoard[r][c+temp*j];
                chessBoard[r][c] = ' ';
                chessBoard[r][c+temp*j] = 'R';
                if (kingSafe())
                {
                    list = list + (char)(r+48) + (char)(c+48) + (char)(r+48) + (char)(c+j*temp+48) + oldPiece;
                }
                chessBoard[r][c] = 'R';
                chessBoard[r][c+temp*j] = oldPiece;
            }
        } catch (exception e) {}
        temp=1;
        try
        {
            while(chessBoard[r+temp*j][c] == ' ' && ((r+temp*j)>=0 && (r+temp*j)<8 && (c)>=0 && (c)<8))
            {
                oldPiece = chessBoard[r+temp*j][c];
                chessBoard[r][c] = ' ';
                chessBoard[r+temp*j][c] = 'R';
                if (kingSafe())
                {
                    list = list + (char)(r+48) + (char)(c+48) + (char)(r+temp*j+48) + (char)(c+48) + oldPiece;
                }
                chessBoard[r][c] = 'R';
                chessBoard[r+temp*j][c] = oldPiece;
                temp++;
            }
            if ((chessBoard[r+temp*j][c] == 'a' || chessBoard[r+temp*j][c] == 'q' ||
                chessBoard[r+temp*j][c] == 'r' || chessBoard[r+temp*j][c] == 'b' ||
                chessBoard[r+temp*j][c] == 'k' || chessBoard[r+temp*j][c] == 'p') &&
                ((r+temp*j)>=0 && (r+temp*j)<8 && (c)>=0 && (c)<8))
            {
                oldPiece = chessBoard[r+temp*j][c];
                chessBoard[r][c] = ' ';
                chessBoard[r+temp*j][c] = 'R';
                if (kingSafe())
                {
                    list = list + (char)(r+48) + (char)(c+48) + (char)(r+temp*j+48) + (char)(c+48) + oldPiece;
                }
                chessBoard[r][c] = 'R';
                chessBoard[r+temp*j][c] = oldPiece;
            }
        } catch (exception e) {}
        temp=1;
    }
    return list;
}

string posibleK(int i)
{
    string list = "";
    char oldPiece;
    int r=i/8, c=i%8;
    for (int j=-1; j<=1; j+=2)
    {
        for (int k=-1; k<=1; k+=2)
        {
            try
            {
                if ((chessBoard[r+j][c+k*2] == 'a' || chessBoard[r+j][c+k*2] == ' ' ||
                    chessBoard[r+j][c+k*2] == 'q' || chessBoard[r+j][c+k*2] == 'r' ||
                    chessBoard[r+j][c+k*2] == 'b' || chessBoard[r+j][c+k*2] == 'k' ||
                    chessBoard[r+j][c+k*2] == 'p') && ((r+j)>=0 && (r+j)<8 && (c+k*2)>=0 && (c+k*2)<8))
                {
                    oldPiece = chessBoard[r+j][c+k*2];
                    chessBoard[r+j][c+k*2] = 'K';
                    chessBoard[r][c] = ' ';
                    if (kingSafe())
                    {
                        list = list + (char)(r+48) + (char)(c+48) + (char)(r+j+48) + (char)(c+k*2+48) + oldPiece;
                    }
                    chessBoard[r][c] = 'K';
                    chessBoard[r+j][c+k*2] = oldPiece;
                }
            } catch (exception e) {}

            try
            {
                if ((chessBoard[r+j*2][c+k] == 'a' || chessBoard[r+j*2][c+k] == ' ' ||
                    chessBoard[r+j*2][c+k] == 'q' || chessBoard[r+j*2][c+k] == 'r' ||
                    chessBoard[r+j*2][c+k] == 'b' || chessBoard[r+j*2][c+k] == 'k' ||
                    chessBoard[r+j*2][c+k] == 'p') && ((r+j*2)>=0 && (r+j*2)<8 && (c+k)>=0 && (c+k)<8))
                {
                    oldPiece = chessBoard[r+j*2][c+k];
                    chessBoard[r][c] = ' ';
                    if (kingSafe())
                    {
                        list = list + (char)(r+48) + (char)(c+48) + (char)(r+j*2+48) + (char)(c+k+48) + oldPiece;
                    }
                    chessBoard[r][c] = 'K';
                    chessBoard[r+j*2][c+k] = oldPiece;
                }
            } catch (exception e) {}
        }
    }
    return list;
}

string posibleB(int i)
{
    string list="";
    char oldPiece;
    int r=i/8, c=i%8;
    int temp=1;
    for (int j=-1; j<=1; j+=2)
    {
        for (int k=-1; k<=1; k+=2)
        {
            try
            {
                while(chessBoard[r+temp*j][c+temp*k] == ' ' && ((r+temp*j)>=0 && (r+temp*j)<8 && (c+temp*k)>=0 && (c+temp*k)<8))
                {
                    oldPiece = chessBoard[r+temp*j][c+temp*k];
                    chessBoard[r][c] = ' ';
                    chessBoard[r+temp*j][c+temp*k] = 'B';
                    if (kingSafe())
                    {
                        list = list + (char)(r+48) + (char)(c+48) + (char)(r+temp*j+48) + (char)(c+temp*k+48) + oldPiece;
                    }
                    chessBoard[r][c] = 'B';
                    chessBoard[r+temp*j][c+temp*k] = oldPiece;
                    temp++;
                }
                if ((chessBoard[r+temp*j][c+temp*k] == 'a' || chessBoard[r+temp*j][c+temp*k] == 'p' ||
                    chessBoard[r+temp*j][c+temp*k] == 'q' || chessBoard[r+temp*j][c+temp*k] == 'r' ||
                    chessBoard[r+temp*j][c+temp*k] == 'b' || chessBoard[r+temp*j][c+temp*k] == 'k') &&
                    ((r+temp*j)>=0 && (r+temp*j)<8 && (c+temp*k)>=0 && (c+temp*k)<8))
                {
                    oldPiece = chessBoard[r+temp*j][c+temp*k];
                    chessBoard[r][c] = ' ';
                    chessBoard[r+temp*j][c+temp*k] = 'B';
                    if (kingSafe())
                    {
                        list = list + (char)(r+48) + (char)(c+48) + (char)(r+temp*j+48) + (char)(c+temp*k+48) + oldPiece;
                    }
                    chessBoard[r][c] = 'B';
                    chessBoard[r+temp*j][c+temp*k] = oldPiece;
                }
            } catch (exception e) {}
            temp=1;
        }
    }
    return list;
}

string posibleQ(int i)
{
    string list="";
    char oldPiece;
    int r=i/8, c=i%8;
    int temp=1;
    for (int j=-1; j<=1; j++)
    {
        for (int k=-1; k<=1; k++)
        {
            if (j!=0 || k!=0)
            {
                try
                {
                    while(chessBoard[r+temp*j][c+temp*k] == ' ' && ((r+temp*j)>=0 && (r+temp*j)<8 && (c+temp*k)>=0 && (c+temp*k)<8))
                    {
                        oldPiece = chessBoard[r+temp*j][c+temp*k];
                        chessBoard[r][c] = ' ';
                        chessBoard[r+temp*j][c+temp*k] = 'Q';
                        if (kingSafe())
                        {
                            list = list + (char)(r+48) + (char)(c+48) + (char)(r+temp*j+48) + (char)(c+temp*k+48) + oldPiece;
                        }
                        chessBoard[r][c] = 'Q';
                        chessBoard[r+temp*j][c+temp*k] = oldPiece;
                        temp++;
                    }
                    if ((chessBoard[r+temp*j][c+temp*k] == 'a' || chessBoard[r+temp*j][c+temp*k] == 'p' ||
                        chessBoard[r+temp*j][c+temp*k] == 'q' || chessBoard[r+temp*j][c+temp*k] == 'r' ||
                        chessBoard[r+temp*j][c+temp*k] == 'b' || chessBoard[r+temp*j][c+temp*k] == 'k') &&
                        ((r+temp*j)>=0 && (r+temp*j)<8 && (c+temp*k)>=0 && (c+temp*k)<8))
                    {
                        oldPiece = chessBoard[r+temp*j][c+temp*k];
                        chessBoard[r][c] = ' ';
                        chessBoard[r+temp*j][c+temp*k] = 'Q';
                        if (kingSafe())
                        {
                            list = list + (char)(r+48) + (char)(c+48) + (char)(r+temp*j+48) + (char)(c+temp*k+48) + oldPiece;
                        }
                        chessBoard[r][c] = 'Q';
                        chessBoard[r+temp*j][c+temp*k] = oldPiece;
                    }
                } catch (exception e) {}
                temp=1;
            }
        }
    }
    return list;
}

string posibleA(int i)
{
    string list="";
    char oldPiece;
    int r=i/8, c=i%8;
    for (int j=0;j<9;j++)
    {
        if (j!=4)
        {
            try
            {
                if ((chessBoard[r-1+j/3][c-1+j%3] == 'a' || chessBoard[r-1+j/3][c-1+j%3] == 'p' ||
                    chessBoard[r-1+j/3][c-1+j%3] == 'q' || chessBoard[r-1+j/3][c-1+j%3] == 'r' ||
                    chessBoard[r-1+j/3][c-1+j%3] == 'b' || chessBoard[r-1+j/3][c-1+j%3] == 'k' ||
                    chessBoard[r-1+j/3][c-1+j%3] == ' ') && ((r-1+j/3)>=0 && (r-1+j/3)<8 && (c-1+j%3)>=0 && (c-1+j%3)<8))
                    {
                    oldPiece = chessBoard[r-1+j/3][c-1+j%3];
                    chessBoard[r][c] = ' ';
                    chessBoard[r-1+j/3][c-1+j%3] = 'A';
                    int kingTemp = kingPositionC;
                    kingPositionC = i+(j/3)*8+j%3-9;
                    if (kingSafe())
                    {
                        list = list + (char)(r+48) + (char)(c+48) + (char)(r-1+j/3+48) + (char)(c+-1+j%3+48) + oldPiece;
                    }
                    chessBoard[r][c] = 'A';
                    chessBoard[r-1+j/3][c-1+j%3] = oldPiece;
                    kingPositionC = kingTemp;
                }
            } catch (exception e) {}
        }
    }
    //need to add casting later
    return list;
}

bool kingSafe()
{
    //bishop/queen
    int temp=1;
    for (int i=-1; i<=1; i+=2)
    {
        for (int j=-1; j<=1; j+=2)
        {
            try
            {
                while(' ' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8+temp*j]) {temp++;}
                if ('b' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8+temp*j] ||
                    'q' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8+temp*j])
                {
                    return false;
                }
            } catch (exception e) {}
            temp=1;
        }
    }
    //rook/queen
    for (int i=-1; i<=1; i+=2)
    {
        try
        {
            while(' ' == chessBoard[kingPositionC/8][kingPositionC%8+temp*i]) {temp++;}
            if ('r' == chessBoard[kingPositionC/8][kingPositionC%8+temp*i] ||
                'q' == chessBoard[kingPositionC/8][kingPositionC%8+temp*i])
            {
                return false;
            }
        } catch (exception e) {}
        temp=1;
        try
        {
            while(' ' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8]) {temp++;}
            if ('r' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8] ||
                'q' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8])
            {
                return false;
            }
        } catch (exception e) {}
        temp=1;
    }
    //knight
    for (int i=-1; i<=1; i+=2)
    {
        for (int j=-1; j<=1; j+=2)
        {
            try
            {
                if ('k' == chessBoard[kingPositionC/8+i][kingPositionC%8+j*2])
                {
                    return false;
                }
            } catch (exception e) {}
            try
            {
                if ('k' == chessBoard[kingPositionC/8+i*2][kingPositionC%8+j])
                {
                    return false;
                }
            } catch (exception e) {}
        }
    }
    //pawn
    if (kingPositionC>=16)
    {
        try
        {
            if ('p' == chessBoard[kingPositionC/8-1][kingPositionC%8-1])
            {
                return false;
            }
        } catch (exception e) {}
        try
        {
            if ('p' == chessBoard[kingPositionC/8-1][kingPositionC%8+1])
            {
                return false;
            }
        } catch (exception e) {}
        //king
        for (int i=-1; i<=1; i++)
        {
            for (int j=-1; j<=1; j++)
            {
                if (i!=0 || j!=0)
                {
                    try
                    {
                        if ('a' == chessBoard[kingPositionC/8+i][kingPositionC%8+j])
                        {
                            return false;
                        }
                    } catch (exception e) {}
                }
            }
        }
    }
    return true;
}

void makeMove(string move)
{
    if(stringLength(move) < 5)
    {
        chessBoard[kingPositionC/8][kingPositionC%8] = ' ';
    }else
    {
        if ((chessBoard[(int)(move[0])-48][(int)(move[1])-48] == 'P' &&
             chessBoard[(int)(move[0])-48][(int)(move[1])-48] != 'p') && (move[0]-48) <=1)
        {
            //if pawn promotion of WHITE
            chessBoard[(int)(move[2])-48][(int)(move[3])-48]= 'Q';
            chessBoard[(int)(move[0])-48][(int)(move[1])-48] = ' ';
        }else if ((chessBoard[(int)(move[0])-48][(int)(move[1])-48] != 'P' &&
             chessBoard[(int)(move[0])-48][(int)(move[1])-48] == 'p') && (move[0]-48) >=6)
        {
            //if pawn promotion of BLACK
            chessBoard[(int)(move[2])-48][(int)(move[3])-48]= 'q';
            chessBoard[(int)(move[0])-48][(int)(move[1])-48] = ' ';
        }else
        {
            chessBoard[(int)(move[2])-48][(int)(move[3])-48] = chessBoard[(int)(move[0])-48][(int)(move[1])-48];
            chessBoard[(int)(move[0])-48][(int)(move[1])-48]= ' ';
            if ('A' == chessBoard[(int)(move[2])-48][(int)(move[3])-48])
            {
                kingPositionC = 8*((int)(move[2])-48)+((int)(move[3])-48);
            }
            if ('a' == chessBoard[(int)(move[2])-48][(int)(move[3])-48])
            {
                kingPositionL = 8*((int)(move[2])-48)+((int)(move[3])-48);
            }
        }
    }
}

void undoMove(string move)
{
    if (chessBoard[(int)(move[0])-48][(int)(move[1])-48] == 'P' && (move[0]-48) <=1)
    {
        //if pawn promotion
        chessBoard[(int)(move[0])-48][(int)(move[1])-48] = 'P';
        chessBoard[(int)(move[2])-48][(int)(move[3])-48] = (char)(move[4]);
    }else
    {
        chessBoard[(int)(move[0])-48][(int)(move[1])-48]=chessBoard[(int)(move[2])-48][(int)(move[3])-48];
        chessBoard[(int)(move[2])-48][(int)(move[3])-48]=(char)(move[4]);
        if ('A' == chessBoard[(int)(move[0])-48][(int)(move[1])-48])
        {
            kingPositionC = 8*((int)(move[0])-48)+((int)(move[1])-48);
        }
    }
}

string alphaBeta(int depth, int beta, int alpha, string move, int player)
{
    //return in the form of 1234b##########
    string list = posibleMoves();
    if (depth==0 || stringLength(list)==0)
    {
        char temp[100];
        int temp1;
        temp1 = rating(stringLength(list), depth)*(player*2-1);
        sprintf(temp, "%d", temp1);
        if(stringLength(move) == 0){return move;}else{return move.substr(0, 5)+temp;}
    }
    //list = sortMoves(list);
    player = 1-player;  //either 1 or 0
    for(int i=0; i<stringLength(list); i+=5)
    {
        makeMove(list.substr(i,i+5));
        flipBoard();
        string returnString = alphaBeta(depth-1, beta, alpha, list.substr(i,i+5), player);
        char temp2[20];
        int j = 0;
        while(returnString[j+5] != '\0'){temp2[j] = returnString[j+5]; j++;}
        int value = atoi(temp2);
        flipBoard();
        undoMove(list.substr(i,i+5));
        if (player==0)
        {
            if (value<=beta) {beta=value; if (depth==globalDepth) {move=returnString.substr(0,5);}}
        }else
        {
            if (value>alpha) {alpha=value; if (depth==globalDepth) {move=returnString.substr(0,5);}}
        }
        if (alpha>=beta)
        {
            if (player==0)
            {
                char temp[20];
                sprintf(temp, "%d", beta);
                return move.substr(0, 5)+temp;
            }else
            {
                char temp[20];
                sprintf(temp, "%d", alpha);
                return move.substr(0, 5)+temp;
            }
        }
    }
    if(player==0)
    {
        char temp[20];
        sprintf(temp, "%d", beta);
        return move.substr(0, 5)+temp;
    } else
    {
        char temp[20];
        sprintf(temp, "%d", alpha);
        return move.substr(0, 5)+temp;

    }
}

int stringLength(string list)
{
    int i=0;
    while(list[i] != '\0'){i++;}
    return i;
}

int rating(int list, int depth)
{
    int counter=0, material=rateMaterial();
    counter+=rateAttack();
    counter+=material;
    counter+=rateMoveablitly(list, depth, material);
    counter+=ratePositional(material);
    flipBoard();
    material=rateMaterial();
    counter-=rateAttack();
    counter-=material;
    counter-=rateMoveablitly(list, depth, material);
    counter-=ratePositional(material);
    flipBoard();
    return -(counter+depth*50);
}

int rateAttack()
{
    int rate=0, i=0;
    int tempPositionKing = kingPositionC;
    for(i=0; i<64; i++)
    {
        switch(chessBoard[i/8][i%8])
        {
            case 'P':   kingPositionC=i;
                        if(!kingSafe()){rate-=64;}
                        break;
            case 'R':   kingPositionC=i;
                        if(!kingSafe()){rate-=500;}
                        break;
            case 'K':   kingPositionC=i;
                        if(!kingSafe()){rate-=300;}
                        break;
            case 'B':   kingPositionC=i;
                        if(!kingSafe()){rate-=300;}
                        break;
            case 'Q':   kingPositionC=i;
                        if(!kingSafe()){rate-=900;}
                        break;
        }
    }
    kingPositionC=tempPositionKing;
    if(!kingSafe()){rate-=200;}
    return rate/2;
}

int rateMaterial()
{
    int rate=0, bishopCounter=0, i=0;
    for(i=0;i<64;i++)
    {
        switch(chessBoard[i/8][i%8])
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

int rateMoveablitly(int list, int depth, int material)
{
    int rate=0;
    rate+=list;     //5 pointer per valid move
    if (list==0)  //current side is in checkmate or stalemate
    {
        if (list==0)
        {//current side is in checkmate or stalemate
            if (!kingSafe())
            {//if checkmate
                rate+=-200000*(depth+1);
            } else
            {//if stalemate
                rate+=-150000*(depth+1);
            }
        }
    }
    return rate;
}

int ratePositional(int material)
{
    int rate=0, i=0;
    for(i=0; i<64; i++)
    {
        switch(chessBoard[i/8][i%8])
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
                            rate+=stringLength(posibleA(kingPositionC))*10;
                        }else
                        {
                            rate+=kingEndBoard[i/8][i%8];
                            rate+=stringLength(posibleA(kingPositionC))*30;
                        }
                        break;
        }
    }
    return rate;
}

string sortMoves(string list)
{
    cout<<"\nLIST = "<<list<<endl;
    int score[stringLength(list)/5];
    for(int i=0; i<stringLength(list); i+=5)
    {
        makeMove(list.substr(i, i+5));
        score[i/5]=-rating(-1, 0);
        undoMove(list.substr(i, i+5));
    }
    string newListA = "", newListB = list;
    for(int i=0; i<6, i<stringLength(list)/5; i++)
    {//first few moves only
        int max=-1000000, maxLocation=0;
        cout<<"\nerror\n";
        for(int j=0; j<stringLength(list)/5; j++)
        {
            if (score[j]>max){max=score[j]; maxLocation=j;}
        }
        cout<<"\nerror\n";
        score[maxLocation]=-1000000;
        newListA += list.substr(maxLocation*5,maxLocation*5+5);
        newListB = newListB.substr(0, maxLocation*5) + newListB.substr(maxLocation*5+5, stringLength(newListB)-1);
        cout<<"\nerror\n";
    }
    return newListA+newListB;
}

void printBoard()
{
    cout<<endl<<"       0  1  2  3  4  5  6  7"<<endl<<endl<<endl;
    for(int i=0; i<8; i++)
    {
        cout<<" "<<i<<"    ";
        for(int j=0; j<8; j++)
        {
            if(chessBoard[i][j] != ' ')
                cout<<" "<<chessBoard[i][j]<<" ";
            else
                cout<<" . ";
        }
        cout<<endl<<endl;
    }
}

// MAIN
int main()
{
    int choice = 1, flag=1;
    char a;
    while(choice == 1)
    {
        int x1, y1, x2, y2;
        cout<<"INSTRUCTIONS"<<endl;
        cout<<"1)   Lowercase Case Characters are BLACK"<<endl;
        cout<<"2)   Uppercase Case Characters are WHITE"<<endl;
        cout<<"3)   You are playing as BLACK"<<endl;
        cout<<"4)   First Turn WHITE"<<endl;
        cout<<"5)   enjoy..."<<endl<<endl;
        cout<<"SETING BOARD..."<<endl<<endl;
        printBoard();
        findKing();
        if(flag == 1){cout<<endl<<"Enter 's' to start the game... "; cin>>a;}
        while(kingPositionC != 64 && kingPositionL != 64)
        {
            string move = alphaBeta(globalDepth, 1000000, -1000000, "", 0);
            makeMove(move);
            cout<<"\n\nWHITE MOVES..."<<endl;
            printBoard();
            cout<<"Enter your move : \nFrom(X1, Y1) : ";
            cin>>x1>>y1;
            cout<<"To(X2, Y2) : ";
            cin>>x2>>y2;
            move = "";
            move = move + (char)(x1+48) + (char)(y1+48) + (char)(x2+48) + (char)(y2+48) + chessBoard[x2][y2];
            makeMove(move);
            cout<<"\n\nBLACK MOVES..."<<endl;
            printBoard();
            findKing();
        }
        if(kingPositionL == 64)
        {
            cout<<endl<<"WHITE WINS!!!"<<endl;
        }else
        {
            cout<<endl<<"BLACK WINS!!!"<<endl;
        }
        cout<<"Enter 0 to Exit."<<endl;
        cout<<"Enter 1 to Play Another Game."<<endl;
        cout<<"Enter Your Choice : "<<endl;
        cin>>choice;
        flag = 1;
    }
    return 0;
}
