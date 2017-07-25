package chess_2017_1_27;

public class Evaluation 
{
	
	// FUNCTIONS LIST
//	int rating(int list, int depth);
//	int rateMaterial();
//	int rateAttack();
//	int rateMoveablitly(int list, int depth, int material);
//	int ratePositional(int material);
	static final int pawnBoard[][]={
	    { 0,  0,  0,  0,  0,  0,  0,  0},
	    {50, 50, 50, 50, 50, 50, 50, 50},
	    {10, 10, 20, 30, 30, 20, 10, 10},
	    { 5,  5, 10, 25, 25, 10,  5,  5},
	    { 0,  0,  0, 20, 20,  0,  0,  0},
	    { 5, -5,-10,  0,  0,-10, -5,  5},
	    { 5, 10, 10,-20,-20, 10, 10,  5},
	    { 0,  0,  0,  0,  0,  0,  0,  0}};
	static final int rookBoard[][]={
	    { 0,  0,  0,  0,  0,  0,  0,  0},
	    { 5, 10, 10, 10, 10, 10, 10,  5},
	    {-5,  0,  0,  0,  0,  0,  0, -5},
	    {-5,  0,  0,  0,  0,  0,  0, -5},
	    {-5,  0,  0,  0,  0,  0,  0, -5},
	    {-5,  0,  0,  0,  0,  0,  0, -5},
	    {-5,  0,  0,  0,  0,  0,  0, -5},
	    { 0,  0,  0,  5,  5,  0,  0,  0}};
	static final int knightBoard[][]={
	    {-50,-40,-30,-30,-30,-30,-40,-50},
	    {-40,-20,  0,  0,  0,  0,-20,-40},
	    {-30,  0, 10, 15, 15, 10,  0,-30},
	    {-30,  5, 15, 20, 20, 15,  5,-30},
	    {-30,  0, 15, 20, 20, 15,  0,-30},
	    {-30,  5, 10, 15, 15, 10,  5,-30},
	    {-40,-20,  0,  5,  5,  0,-20,-40},
	    {-50,-40,-30,-30,-30,-30,-40,-50}};
	static final int bishopBoard[][]={
	    {-20,-10,-10,-10,-10,-10,-10,-20},
	    {-10,  0,  0,  0,  0,  0,  0,-10},
	    {-10,  0,  5, 10, 10,  5,  0,-10},
	    {-10,  5,  5, 10, 10,  5,  5,-10},
	    {-10,  0, 10, 10, 10, 10,  0,-10},
	    {-10, 10, 10, 10, 10, 10, 10,-10},
	    {-10,  5,  0,  0,  0,  0,  5,-10},
	    {-20,-10,-10,-10,-10,-10,-10,-20}};
	static final int queenBoard[][]={
	    {-20,-10,-10, -5, -5,-10,-10,-20},
	    {-10,  0,  0,  0,  0,  0,  0,-10},
	    {-10,  0,  5,  5,  5,  5,  0,-10},
	    { -5,  0,  5,  5,  5,  5,  0, -5},
	    {  0,  0,  5,  5,  5,  5,  0, -5},
	    {-10,  5,  5,  5,  5,  5,  0,-10},
	    {-10,  0,  5,  0,  0,  0,  0,-10},
	    {-20,-10,-10, -5, -5,-10,-10,-20}};
	static final int kingMidBoard[][]={
	    {-30,-40,-40,-50,-50,-40,-40,-30},
	    {-30,-40,-40,-50,-50,-40,-40,-30},
	    {-30,-40,-40,-50,-50,-40,-40,-30},
	    {-30,-40,-40,-50,-50,-40,-40,-30},
	    {-20,-30,-30,-40,-40,-30,-30,-20},
	    {-10,-20,-20,-20,-20,-20,-20,-10},
	    { 20, 20,  0,  0,  0,  0, 20, 20},
	    { 20, 30, 10,  0,  0, 10, 30, 20}};
	static final int kingEndBoard[][]={
	    {-50,-40,-30,-20,-20,-30,-40,-50},
	    {-30,-20,-10,  0,  0,-10,-20,-30},
	    {-30,-10, 20, 30, 30, 20,-10,-30},
	    {-30,-10, 30, 40, 40, 30,-10,-30},
	    {-30,-10, 30, 40, 40, 30,-10,-30},
	    {-30,-10, 20, 30, 30, 20,-10,-30},
	    {-30,-30,  0,  0,  0,  0,-30,-30},
	    {-50,-30,-30,-30,-30,-30,-30,-50}};	
	
	static int rating(int list, int depth)
	{
	    int counter=0, material=rateMaterial();
	    counter+=rateAttack();
	    counter+=material;
	    counter+=rateMoveablitly(list, depth, material);
	    counter+=ratePositional(material);
	    chess.flipBoard();
	    material=rateMaterial();
	    counter-=rateAttack();
	    counter-=material;
	    counter-=rateMoveablitly(list, depth, material);
	    counter-=ratePositional(material);
	    chess.flipBoard();
	    return -(counter+depth*50);
	}

	static int rateAttack()
	{
	    int rate=0, i=0;
	    int tempPositionKing = chess.kingPositionC;
	    for(i=0; i<64; i++)
	    {
	        switch(chess.chessBoard[i/8][i%8])
	        {
	            case 'P':   chess.kingPositionC=i;
	                        if(!chess.kingSafe()){rate-=64;}
	                        break;
	            case 'R':   chess.kingPositionC=i;
	                        if(!chess.kingSafe()){rate-=500;}
	                        break;
	            case 'K':   chess.kingPositionC=i;
	                        if(!chess.kingSafe()){rate-=300;}
	                        break;
	            case 'B':   chess.kingPositionC=i;
	                        if(!chess.kingSafe()){rate-=300;}
	                        break;
	            case 'Q':   chess.kingPositionC=i;
	                        if(!chess.kingSafe()){rate-=900;}
	                        break;
	        }
	    }
	    chess.kingPositionC=tempPositionKing;
	    if(!chess.kingSafe()){rate-=200;}
	    return rate/2;
	}

	static int rateMaterial()
	{
	    int rate=0, bishopCounter=0, i=0;
	    for(i=0;i<64;i++)
	    {
	        switch(chess.chessBoard[i/8][i%8])
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

	static int rateMoveablitly(int list, int depth, int material)
	{
	    int rate=0;
	    rate+=list;     //5 pointer per valid move
	    if (list==0)  //current side is in checkmate or stalemate
	    {
	        if (list==0)
	        {//current side is in checkmate or stalemate
	            if (!chess.kingSafe())
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

	static int ratePositional(int material)
	{
	    int rate=0, i=0;
	    for(i=0; i<64; i++)
	    {
	        switch(chess.chessBoard[i/8][i%8])
	        {
	            case 'P':   rate+=chess.pawnBoard[i/8][i%8];
	                        break;
	            case 'R':   rate+=chess.rookBoard[i/8][i%8];
	                        break;
	            case 'K':   rate+=chess.knightBoard[i/8][i%8];
	                        break;
	            case 'B':   rate+=chess.bishopBoard[i/8][i%8];
	                        break;
	            case 'Q':   rate+=chess.queenBoard[i/8][i%8];
	                        break;
	            case 'A':   if(material>=1750)
	                        {
	                            rate+=chess.kingMidBoard[i/8][i%8];
//	                            rate+=StringLength(posibleA(kingPositionC))*10;
	                            rate+=chess.posibleA(chess.kingPositionC).length()*10;
	                        }else
	                        {
	                            rate+=chess.kingEndBoard[i/8][i%8];
//	                            rate+=StringLength(posibleA(kingPositionC))*30;
	                            rate+=chess.posibleA(chess.kingPositionC).length()*30;
	                        }
	                        break;
	        }
	    }
	    return rate;
	}
}
