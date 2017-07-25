package chess_2017_1_27;

import java.io.IOException;
import java.util.Scanner;
import javax.swing.text.AbstractDocument.LeafElement;

public class chess extends Evaluation
{
	// FUNCTIONS LIST
//	void findKing();
//	void flipBoard();
//	String posibleMoves();
//	String posibleP(int i);
//	String posibleR(int i);
//	String posibleK(int i);
//	String posibleB(int i);
//	String posibleQ(int i);
//	String posibleA(int i);
//	boolean kingSafe();
//	void makeMove(String move);
//	void undoMove(String move);
//	String alphaBeta(int depth, int beta, int alpha, String move, int player);
//	int StringLength(String list);
//	String sortMoves(String list);
//	void printBoard();
	
	// VARIABLES
	// small are black and capital are white
	static char chessBoard[][] = 
  {{'r', 'k', 'b', 'q', 'a', 'b', ' ', 'r'},
   {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
   {' ', ' ', ' ', ' ', ' ', 'k', ' ', ' '},
   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
   {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
   {'R', 'K', 'B', 'Q', 'A', 'B', 'K', 'R'}};
	
	static int currentArduinoBoard[][] = {
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0}};

	static int kingPositionC, kingPositionL;
	static int humanAsWhite=-1;
	final static int globalDepth=6;
	public static int countofmoves = 0;
	public static void countzero()
	{
		countofmoves = 0;
	}
	//FUNCTIONS
	static void findKing()
	{
	    kingPositionC = 0;
	    kingPositionL = 0;
	    while('A' != chessBoard[kingPositionC/8][kingPositionC%8] && kingPositionC<64){kingPositionC++;}      //get White King's location
	    while('a' != chessBoard[kingPositionL/8][kingPositionL%8] && kingPositionL<64){kingPositionL++;}      //get Black king's location
	}

	static void flipBoard()
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

	static String posibleMoves()
	{
	    String list="";
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

	static String posibleP(int i)
	{
	    String list = "";
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
	        }catch (Exception e) {}
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
	    } catch (Exception e) {}

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
	    } catch (Exception e) {}
	    return list;
	}

	static String posibleR(int i)
	{
	    String list="";
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
	        } catch (Exception e) {}
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
	        } catch (Exception e) {}
	        temp=1;
	    }
	    return list;
	}

	static String posibleK(int i)
	{
	    String list = "";
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
	            } catch (Exception e) {}

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
	            } catch (Exception e) {}
	        }
	    }
	    return list;
	}

	static String posibleB(int i)
	{
	    String list="";
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
	            } catch (Exception e) {}
	            temp=1;
	        }
	    }
	    return list;
	}

	static String posibleQ(int i)
	{
	    String list="";
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
	                } catch (Exception e) {}
	                temp=1;
	            }
	        }
	    }
	    return list;
	}

	static String posibleA(int i)
	{
	    String list="";
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
	            } catch (Exception e) {}
	        }
	    }
	    //need to add casting later
	    return list;
	}

	static boolean kingSafe()
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
	                if (('b' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8+temp*j] ||
	                    'q' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8+temp*j]) &&
	                    ((kingPositionC/8+temp*i) >= 0 && (kingPositionC/8+temp*i)<8 &&
	                    (kingPositionC%8+temp*j) >= 0 && (kingPositionC%8+temp*j) < 8))
	                {
	                    return false;
	                }
	            } catch (Exception e) {}
	            temp=1;
	        }
	    }
	    //rook/queen
	    for (int i=-1; i<=1; i+=2)
	    {
	        try
	        {
	            while(' ' == chessBoard[kingPositionC/8][kingPositionC%8+temp*i]) {temp++;}
	            if (('r' == chessBoard[kingPositionC/8][kingPositionC%8+temp*i] ||
	                'q' == chessBoard[kingPositionC/8][kingPositionC%8+temp*i]) &&
	                    ((kingPositionC/8) >= 0 && (kingPositionC/8)<8 &&
	                    (kingPositionC%8+temp*i) >= 0 && (kingPositionC%8+temp*i) < 8))
	            {
	                return false;
	            }
	        } catch (Exception e) {}
	        temp=1;
	        try
	        {
	            while(' ' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8]) {temp++;}
	            if (('r' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8] ||
	                'q' == chessBoard[kingPositionC/8+temp*i][kingPositionC%8]) &&
	                    ((kingPositionC/8+temp*i) >= 0 && (kingPositionC/8+temp*i)<8 &&
	                    (kingPositionC%8) >= 0 && (kingPositionC%8) < 8))
	            {
	                return false;
	            }
	        } catch (Exception e) {}
	        temp=1;
	    }
	    //knight
	    for (int i=-1; i<=1; i+=2)
	    {
	        for (int j=-1; j<=1; j+=2)
	        {
	            try
	            {
	                if (('k' == chessBoard[kingPositionC/8+i][kingPositionC%8+j*2]) &&
	                    ((kingPositionC/8+i) >= 0 && (kingPositionC/8+i)<8 &&
	                    (kingPositionC%8+j*2) >= 0 && (kingPositionC%8+j*2) < 8))
	                {
	                    return false;
	                }
	            } catch (Exception e) {}
	            try
	            {
	                if (('k' == chessBoard[kingPositionC/8+i*2][kingPositionC%8+j]) &&
	                    ((kingPositionC/8+i*2) >= 0 && (kingPositionC/8+i*2)<8 &&
	                    (kingPositionC%8+j) >= 0 && (kingPositionC%8+j) < 8)) 
	                {
	                    return false;
	                }
	            } catch (Exception e) {}
	        }
	    }
	    //pawn
	    if (kingPositionC>=16)
	    {
	        try
	        {
	            if (('p' == chessBoard[kingPositionC/8-1][kingPositionC%8-1]) &&
	                    ((kingPositionC/8-1) >= 0 && (kingPositionC/8-1)<8 &&
	                    (kingPositionC%8-1) >= 0 && (kingPositionC%8-1) < 8)) 
	            {
	                return false;
	            }
	        } catch (Exception e) {}
	        try
	        {
	            if (('p' == chessBoard[kingPositionC/8-1][kingPositionC%8+1]) &&
	                    ((kingPositionC/8-1) >= 0 && (kingPositionC/8-1)<8 &&
	                    (kingPositionC%8+1) >= 0 && (kingPositionC%8+1) < 8)) 
	            {
	                return false;
	            }
	        } catch (Exception e) {}
	        //king
	        for (int i=-1; i<=1; i++)
	        {
	            for (int j=-1; j<=1; j++)
	            {
	                if (i!=0 || j!=0)
	                {
	                    try
	                    {
	                        if (('a' == chessBoard[kingPositionC/8+i][kingPositionC%8+j]) &&
	                            ((kingPositionC/8+i) >= 0 && (kingPositionC/8+i)<8 &&
	                            (kingPositionC%8+j) >= 0 && (kingPositionC%8+j) < 8)) 
	                        {
	                            return false;
	                        }
	                    } catch (Exception e) {}
	                }
	            }
	        }
	    }
	    return true;
	}

	static void makeMove(String move)
	{
	    //if(StringLength(move) < 5)
		if(move.length() < 5)
	    {
	        chessBoard[kingPositionC/8][kingPositionC%8] = ' ';
	    }else
	    {
	        if ((chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48] == 'P' &&
	             chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48] != 'p') && (move.charAt(0)-48) <=1)
	        {
	            //if pawn promotion of WHITE
	            chessBoard[(int)(move.charAt(2))-48][(int)(move.charAt(3))-48]= 'Q';
	            chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48] = ' ';
	        }else if ((chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48] != 'P' &&
	             chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48] == 'p') && (move.charAt(1)-48) >=6)
	        {
	            //if pawn promotion of BLACK
	            chessBoard[(int)(move.charAt(2))-48][(int)(move.charAt(3))-48]= 'q';
	            chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48] = ' ';
	        }else
	        {
	            chessBoard[(int)(move.charAt(2))-48][(int)(move.charAt(3))-48] = chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48];
	            chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48]= ' ';
	            if ('A' == chessBoard[(int)(move.charAt(2))-48][(int)(move.charAt(3))-48])
	            {
	                kingPositionC = 8*((int)(move.charAt(2))-48)+((int)(move.charAt(3))-48);
	            }
	            if ('a' == chessBoard[(int)(move.charAt(2))-48][(int)(move.charAt(3))-48])
	            {
	                kingPositionL = 8*((int)(move.charAt(2))-48)+((int)(move.charAt(3))-48);
	            }
	        }
	    }
	}

	static void undoMove(String move)
	{
	    if (chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48] == 'P' && (move.charAt(0)-48) <=1)
	    {
	        //if pawn promotion
	        chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48] = 'P';
	        chessBoard[(int)(move.charAt(2))-48][(int)(move.charAt(3))-48] = (char)(move.charAt(4));
	    }else
	    {
	        chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48]=chessBoard[(int)(move.charAt(2))-48][(int)(move.charAt(3))-48];
	        chessBoard[(int)(move.charAt(2))-48][(int)(move.charAt(3))-48]=(char)(move.charAt(4));
	        if ('A' == chessBoard[(int)(move.charAt(0))-48][(int)(move.charAt(1))-48])
	        {
	            kingPositionC = 8*((int)(move.charAt(0))-48)+((int)(move.charAt(1))-48);
	        }
	    }
	}

	static String alphaBeta(int depth, int beta, int alpha, String move, int player)
	{
	    //return in the form of 1234b##########
	    String list = posibleMoves();
	    countofmoves += list.length()/5;
//	    System.out.println(list);
	    //if (depth==0 || StringLength(list)==0)
	    if (depth==0 || list.length()==0)
	    {
	        String temp;
	        int temp1;
	        //temp1 = rating(StringLength(list), depth)*(player*2-1);
	        temp1 = rating(list.length(), depth)*(player*2-1);
	        temp = Integer.toString(temp1);
//	        if(StringLength(move) == 0){return move;}else{return move.substring(0, 5)+temp;}
	        if(move.length() == 0){return move;}else{return move.substring(0, 5)+temp;}
	    }
//	    list = sortMoves(list);
	    player = 1-player;  //either 1 or 0
	    //for(int i=0; i<StringLength(list); i+=5)
	    for(int i=0; i<list.length(); i+=5)
	    {
	        makeMove(list.substring(i,i+5));
	        flipBoard();
	        String returnString = alphaBeta(depth-1, beta, alpha, list.substring(i,i+5), player);

	        int value = Integer.parseInt(returnString.substring(5));
	        flipBoard();
	        undoMove(list.substring(i,i+5));
	        if (player==0)
	        {
	            if (value<=beta) {beta=value; if (depth==globalDepth) {move=returnString.substring(0,5);}}
	        }else
	        {
	            if (value>alpha) {alpha=value; if (depth==globalDepth) {move=returnString.substring(0,5);}}
	        }
	        if (alpha>=beta)
	        {
	            if (player==0)
	            {
	                String temp;
	                temp = Integer.toString(beta);
	                return move.substring(0, 5)+temp;
	            }else
	            {
	                String temp;
	                temp = Integer.toString(alpha);
	                return move.substring(0, 5)+temp;
	            }
	        }
	    }
	    if(player==0)
	    {
	        String temp;
	        temp = Integer.toString(beta);
	        return move.substring(0, 5)+temp;
	    } else
	    {
	        String temp;
	        temp = Integer.toString(alpha);
	        return move.substring(0, 5)+temp;

	    }
	}

	static String sortMoves(String list)
	{
	    int score[] = new int[list.length()/5];
	    for(int i=0; i<list.length(); i+=5)
	    {
	        makeMove(list.substring(i, i+5));
	        score[i/5]=-rating(-1, 0);
	        undoMove(list.substring(i, i+5));
	    }
	    String newListA = "", newListB = list;
	    int iteration = 6;
	    if(newListB.length()/5 < 6){iteration = newListB.length()/5;}
    	for(int i=0; i<iteration; i++)
	    {//first few moves only
	        int max=-1000000, maxLocation=0;
	        for(int j=0; j<newListB.length()/5; j++)
	        {
	            if (score[j]>max){max=score[j]; maxLocation=j;}
	        }
	        score[maxLocation]=-1000000;
//	        System.out.println("newListB : " + newListB);
//	        System.out.println("index : " + i + "List : " + list);
	        newListA += newListB.substring(maxLocation*5,maxLocation*5+5);
//	        System.out.print(newListB.length());
//	        System.out.println("\t" + newListB);
	        newListB = newListB.substring(0, maxLocation*5) + newListB.substring(maxLocation*5+5, newListB.length());
	    }
	    return newListA+newListB;
	}

	static void printBoard()
	{
	    System.out.println("\n       0  1  2  3  4  5  6  7\n\n");
	    for(int i=0; i<8; i++)
	    {
	        System.out.print(" "+i+"    ");
	        for(int j=0; j<8; j++)
	        {
	            if(chessBoard[i][j] != ' ')
	                System.out.print(" "+chessBoard[i][j]+" ");
	            else
	                System.out.print(" . ");
	        }
	        System.out.println("");
	    }
	}
	
	static void longToArray(long n)
	{
		for(int i = 7; i > -1; i--)
		{
			for(int j = 7; j > -1; j--)
			{
				currentArduinoBoard[i][j] = 0;
			}
		}
	  for(int i = 7; i > -1; i--)
	  {
	    for(int j = 7; j > -1; j--)
	    {
	      currentArduinoBoard[i][j] = (int) (n & 1);
	      n = n >> 1;
	    }
	  }
	}
	
	static long arrayToLong(int Board[][])
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
	
	static long[] movesToLong(String moves)
	{
		long temp[] = new long[100];
		for(int i = 0; i < moves.length(); i += 5)
		{
			int tempBoard[][] = {
				    {0, 0, 0, 0, 0, 0, 0, 0},
				    {0, 0, 0, 0, 0, 0, 0, 0},
				    {0, 0, 0, 0, 0, 0, 0, 0},
				    {0, 0, 0, 0, 0, 0, 0, 0},
				    {0, 0, 0, 0, 0, 0, 0, 0},
				    {0, 0, 0, 0, 0, 0, 0, 0},
				    {0, 0, 0, 0, 0, 0, 0, 0},
				    {0, 0, 0, 0, 0, 0, 0, 0}};
			String move = moves.substring(i, i+5);
			makeMove(move);
			for(int j = 0; j < 8; j++)
			{
				for(int k = 0; k < 8; k++)
				{
					if(chessBoard[j][k] == 'Q' || chessBoard[j][k] == 'R' ||
						chessBoard[j][k] == 'P' || chessBoard[j][k] == 'A' ||
						chessBoard[j][k] == 'K' || chessBoard[j][k] == 'B')
					{
						tempBoard[j][k] = 1;	// contains so 1 else 0
					}
				}
			}
			undoMove(move);
			temp[i/5] = arrayToLong(tempBoard);
		}
		return temp;
	}
	
	static int[][] charBoardtoIntArray()
	{
		int tempBoard[][] = {
			    {0, 0, 0, 0, 0, 0, 0, 0},
			    {0, 0, 0, 0, 0, 0, 0, 0},
			    {0, 0, 0, 0, 0, 0, 0, 0},
			    {0, 0, 0, 0, 0, 0, 0, 0},
			    {0, 0, 0, 0, 0, 0, 0, 0},
			    {0, 0, 0, 0, 0, 0, 0, 0},
			    {0, 0, 0, 0, 0, 0, 0, 0},
			    {0, 0, 0, 0, 0, 0, 0, 0}};
		for(int j = 0; j < 8; j++)
		{
			for(int k = 0; k < 8; k++)
			{
				if(chessBoard[j][k] == 'Q' || chessBoard[j][k] == 'R' ||
					chessBoard[j][k] == 'P' || chessBoard[j][k] == 'A' ||
					chessBoard[j][k] == 'K' || chessBoard[j][k] == 'B')
				{
					tempBoard[j][k] = 1;	// contains so 1 else 0
				}
			}
		}
		return tempBoard;
	}
	
//	static String arrayToMove()		// no need for this bcoz move pehle hi calculate kiye the
//	{
//		String move = "";
//		int changes[] = {};
//		int tempBoard[][] = {
//			    {0, 0, 0, 0, 0, 0, 0, 0},
//			    {0, 0, 0, 0, 0, 0, 0, 0},
//			    {0, 0, 0, 0, 0, 0, 0, 0},
//			    {0, 0, 0, 0, 0, 0, 0, 0},
//			    {0, 0, 0, 0, 0, 0, 0, 0},
//			    {0, 0, 0, 0, 0, 0, 0, 0},
//			    {0, 0, 0, 0, 0, 0, 0, 0},
//			    {0, 0, 0, 0, 0, 0, 0, 0}};
//		tempBoard = charBoardtoIntArray();
//		int index = 0;
//		for(int i = 0; i < 8; i++)
//		{
//			for(int j = 0; j < 8; j++)
//			{
//				if(currentArduinoBoard[i][j] != tempBoard[i][j])
//				{
//					changes[index++] = i*8 + j;
//				}
//			}
//		}
//		int flag = 0; x1, x2, y1, y2;
//		for(int i = 0; i < index; i++)
//		{
//			if(chessBoard[changes[i]/8][changes[i]%8] == ('q' | 'r' | 'p' | 'a' | 'k' | 'b' | ' '))
//			{
//				flag += 1;
//				x2 = changes[i]/8;
//				y2 = changes[i]%8;
//			}
//		}
//		return move;
//	}
	
	static public void main(String[] args) throws Exception
	{
		
		while(true)
		{
////			int flag = 0;	// 1 correct 0 wrong move by arduino
////			String red = Communication.read();
//			long arduinoMoveInLong = Long.parseLong(red);		// read move in form of long
//			System.out.println("pyread : " +  arduinoMoveInLong);
//			longToArray(arduinoMoveInLong);
//			for(int i = 0; i< 8; i++)
//			{
//				for(int j = 0; j< 8; j++)
//				{
//					System.out.print(currentArduinoBoard[i][j] + "\t");
//				}
//				System.out.println("");
//			}
//			String possibleArduinoMoves = posibleMoves();
//			long possibleArduinoMovesInLong[] = movesToLong(possibleArduinoMoves);
			// check if right move
//			int index=0;
//			for(index = 0; index<possibleArduinoMovesInLong.length; index++)
//			{
//				System.out.println(possibleArduinoMovesInLong[index]);
//				if(arduinoMoveInLong == possibleArduinoMovesInLong[index])
//				{
//					flag = 1;
//					break;
//				}
//			}
//			System.out.println("flag : " + flag);
			int flag = 1;
			if(flag == 1)
			{
				System.out.println("started");
				String move;
	            findKing();
	            flipBoard();
	            long starttime = System.currentTimeMillis();
	            countofmoves = 0;
	            move = alphaBeta(globalDepth, 1000000, -1000000, "", 0);
	            makeMove(move);
//	            Communication.write(move);
	            System.out.println("\n\nBLACK MOVES...");
	            flipBoard();
	            printBoard();	
	            System.out.print("time tacken : ");
	            long endtime = System.currentTimeMillis();
	            System.out.println(endtime - starttime);
	            System.out.print("moves calculated : ");
	            System.out.println(countofmoves);
//				Communication.write("1");
//				System.out.println("possibleArduinoMoves : " + possibleArduinoMoves);
//				System.out.println("index : " + index);
				Scanner s = new Scanner(System.in);
				System.out.print("Enter a move : ");
//				move = possibleArduinoMoves.substring(index*5, index*5+5);
				move = s.nextLine();
//				System.out.println("arduino generated move is : " + move);
				makeMove(move);
	            System.out.println("\n\nWHITE MOVES...");
	            printBoard();
			}else
			{
				Communication.write("0");
				System.out.println("send to py is 0");
			}
		}
	}
}