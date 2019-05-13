#include <iostream>
#include <string>
#include <list>
int** modifyBoard(int** board,int yIndex,std::string playerMode);
void evaluateBoard(int** board,std::string& winner,std::string& how);
int countHorizontally(int** board,int xIndex,int yIndex,int val);
int countVertically(int** board,int xIndex,int yIndex,int val);
int countDiagonally45(int** board,int xIndex,int yIndex,int val);
int countDiagonally_45(int** board,int xIndex,int yIndex,int val);
int countHorizontallyBef(int** board,int xIndex,int yIndex,int val);
int countHorizontallyAft(int** board,int xIndex,int yIndex,int val);
int countVerticallyBef(int** board,int xIndex,int yIndex,int val);
int countVerticallyAft(int** board,int xIndex,int yIndex,int val);
int countDiagonally_45Bef(int** board,int xIndex,int yIndex,int val);
int countDiagonally_45Aft(int** board,int xIndex,int yIndex,int val);
int countDiagonally45Bef(int** board,int xIndex,int yIndex,int val);
int countDiagonally45Aft(int** board,int xIndex,int yIndex,int val);
int heurstic(int** board);
void Start_New_Game(int** board);
void check_input();
void Game(int** board);
int minMaxWithAlphaBeta(int** currentState,int depth,int childIndex,int alpha,int beta);
int main()
{
    //board is arranged top down from row 0 to row 5
    int** connect4Board = new int* [6];
    for(int i=0;i<6;i++)
    {
        connect4Board[i] = new int[7];
    }
    connect4Board[0] = new int[7] {0,0,0,0,0,0,0};
    connect4Board[1] = new int[7] {0,0,0,0,0,0,0};
    connect4Board[2] = new int[7] {0,0,0,0,0,0,0};
    connect4Board[3] = new int[7] {0,0,0,0,0,0,0};
    connect4Board[4] = new int[7] {0,0,0,-1,-1,0,0};
    connect4Board[5] = new int[7] {0,0,-1,1,1,1,0};
    int** result;
    int i = minMaxWithAlphaBeta(connect4Board,3,0,-100000000,100000000);
    std::cout<<"out is "<<i<<std::endl;
    result = modifyBoard(connect4Board,i,"us");
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            std::cout<<result[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::string winner,method;
    evaluateBoard(result,winner,method);
    std::cout<<"winner is "<<winner<<std::endl;
    std::cout<<"by connecting four "<<method<<std::endl;
    //std::cout<<"output of our utility function : "<<heurstic(connect4Board)<<std::endl;
    /*
    //interface
    std::cout<<"Welcome To Connect 4 Game"<<std::endl;
	Start_New_Game(connect4Board);*/
    return 0;
}

//i will assume that player's game will be -1 in his chosen position and 1 for our algorithm yIndex is column number
int** modifyBoard(int** board,int yIndex,std::string playerMode)
{
    int** result = new int* [6];
    for(int i=0;i<6;i++)
    {
        result[i] = new int[7];
    }
    //board is arranged top down from row 0 to row 5
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            result[i][j] = board[i][j];
        }
    }
    if(playerMode == "us")
    {
        if(yIndex >= 0&&yIndex < 7)
        {
            for(int i=5;i>=0;i--)
            {
                if(result[i][yIndex] == 0)
                {
                    result[i][yIndex] = 1;
                    return result;
                }
            }  
        }
        
    }else if(playerMode == "them")
    {
        if(yIndex >= 0&&yIndex < 7)
        {
            for(int i=5;i>=0;i--)
            {
                if(result[i][yIndex] == 0)
                {
                    result[i][yIndex] = -1;
                    return result;
                }
            }  
        }
    }
}
//it will evaluate board and tell us who wins and how he won method (connecting 4 horizontally,...etc)
void evaluateBoard(int** board,std::string& winner,std::string& how)
{
    winner = "";
    how = "";
    bool flag = false;
    for(int i=0;i<6;i++)
    {
        if(flag)
        {
            break;
        }
        for(int j=0;j<7;j++)
        {
            if(board[i][j] == 1)
            {
                if(countHorizontally(board,i,j,1) >= 4)
                {
                    how += " Horizontally";   
                }
                if(countVertically(board,i,j,1) >= 4)
                {
                    how +=" Vertically";
                }
                if(countDiagonally45(board,i,j,1) >= 4)
                {
                    how +=" diagonally+45";
                }
                if(countDiagonally_45(board,i,j,1) >= 4)
                {
                    how +=" diagonally-45";
                }
                if(how != "")
                {
                    winner = "computer";
                    flag = true;
                    break;
                }
            }
            else if(board[i][j] == -1)
            {
                if(countHorizontally(board,i,j,-1) >= 4)
                {
                    how += " Horizontally";   
                }
                if(countVertically(board,i,j,-1) >= 4)
                {
                    how +=" Vertically";
                }
                if(countDiagonally45(board,i,j,-1) >= 4)
                {
                    how +=" diagonally+45";
                }
                if(countDiagonally_45(board,i,j,-1) >= 4)
                {
                    how +=" diagonally-45";
                }
                if(how != "")
                {
                    winner = "user";
                    flag = true;
                    break;
                }
            }        
        }
    }
}

int countHorizontally(int** board,int xIndex,int yIndex,int val)
{
    return -1 + countHorizontallyBef(board,xIndex,yIndex,val) + countHorizontallyAft(board,xIndex,yIndex,val);
}

int countHorizontallyBef(int** board,int xIndex,int yIndex,int val)
{
    if(yIndex < 0 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countHorizontallyBef(board,xIndex,yIndex-1,val);
}

int countHorizontallyAft(int** board,int xIndex,int yIndex,int val)
{
    if(yIndex > 6 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countHorizontallyAft(board,xIndex,yIndex+1,val);
}

int countVertically(int** board,int xIndex,int yIndex,int val)
{
    return -1 + countVerticallyBef(board,xIndex,yIndex,val) + countVerticallyAft(board,xIndex,yIndex,val);
}

int countVerticallyBef(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex < 0 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countVerticallyBef(board,xIndex-1,yIndex,val);
}

int countVerticallyAft(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex > 5 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countVerticallyAft(board,xIndex+1,yIndex,val);
}

int countDiagonally45(int** board,int xIndex,int yIndex,int val)
{
    return -1 + countDiagonally45Bef(board,xIndex,yIndex,val) + countDiagonally45Aft(board,xIndex,yIndex,val);
}

int countDiagonally45Bef(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex < 0 || yIndex < 0 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countDiagonally45Bef(board,xIndex-1,yIndex+1,val);
}

int countDiagonally45Aft(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex > 5 || yIndex > 6 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countDiagonally45Aft(board,xIndex+1,yIndex-1,val);
}

int countDiagonally_45(int** board,int xIndex,int yIndex,int val)
{
    return -1 + countDiagonally_45Bef(board,xIndex,yIndex,val) + countDiagonally_45Aft(board,xIndex,yIndex,val);
}

int countDiagonally_45Bef(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex < 0 || yIndex < 0 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countDiagonally_45Bef(board,xIndex-1,yIndex-1,val);
}

int countDiagonally_45Aft(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex > 5 || yIndex > 6 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countDiagonally_45Aft(board,xIndex+1,yIndex+1,val);
}

int heurstic(int** board)
{
    int score = 0;
    int horz , vert , dia45 , dia_45;
    for(int i = 5;i >= 0;i--)
    {
        for(int j = 0;j < 7;j++)
        {
            horz = 0 , vert = 0 , dia45 = 0 , dia_45 = 0;
            if(board[i][j] == 1)
            {
                horz = countHorizontally(board,i,j,1);
                vert = countVertically(board,i,j,1);
                dia45 = countDiagonally45(board,i,j,1);
                dia_45 = countDiagonally_45(board,i,j,1);
                if(horz == 2)
                {
                    score += 25;
                }else if(horz == 3)
                {
                    score += 50;
                }else if(horz == 4)
                {
                    score += 1000000;
                }
                if(vert == 2)
                {
                    score += 25;
                }else if(vert == 3)
                {
                    score += 50;
                }else if(vert == 4)
                {
                    score += 1000000;
                }
                if(dia_45 == 2)
                {
                    score += 25;
                }else if(dia_45 == 3)
                {
                    score += 50;
                }else if(dia_45 == 4)
                {
                    score += 1000000;
                }
                if(dia45 == 2)
                {
                    score += 25;
                }else if(dia45 == 3)
                {
                    score += 50;
                }else if(dia45 == 4)
                {
                    score += 1000000;
                }

            }else if(board[i][j] == -1)
            {
                horz = countHorizontally(board,i,j,-1);
                vert = countVertically(board,i,j,-1);
                dia45 = countDiagonally45(board,i,j,-1);
                dia_45 = countDiagonally_45(board,i,j,-1);
                if(horz == 2)
                {
                    score -= 25;
                }else if(horz == 3)
                {
                    score -= 50;
                }else if(horz == 4)
                {
                    score -= 1000000;
                }
                if(vert == 2)
                {
                    score -= 25;
                }else if(vert == 3)
                {
                    score -= 50;
                }else if(vert == 4)
                {
                    score -= 1000000;
                }
                if(dia_45 == 2)
                {
                    score -= 25;
                }else if(dia_45 == 3)
                {
                    score -= 50;
                }else if(dia_45 == 4)
                {
                    score -= 1000000;
                }
                if(dia45 == 2)
                {
                    score -= 25;
                }else if(dia45 == 3)
                {
                    score -= 50;
                }else if(dia45 == 4)
                {
                    score -= 1000000;
                }
            }
        }
    }
    return score;
}



void check_input()
{
	int inp;
	std::cin>>inp;
	while (true)
	{
		if(std::cin.fail())
		{
			std::cout << "Wrong value,Enter a number between 1 and 7, Try again" << std::endl << "Your move : ";
			std::cin.clear();
			std::cin.ignore(256,'\n');
			std::cin >> inp;
		}
		else if (inp<1 || inp>7)
		{
			std::cout << "Wrong value,Enter a number between 1 and 7, Try again" << std::endl << "Your move : ";
			std::cin.clear();
			std::cin.ignore(256,'\n');
			std::cin >> inp;
		}
		else
		{
			break;
		}
	}

}

void Start_New_Game(int** board)
{
	while (true)
	{
		std::cout<<"press N to start new game or Q to quit"<<std::endl;
		std::string np;
		std::cin>>np;
		if (np=="N" || np=="n")
		{
			while (true)
			{
				std::cout<<"Would you like to start first ? y/n"<<std::endl;
				std::string yn;
				std::cin>>yn;
				if (yn=="Y"|| yn=="y")
				{
					std::cout<<"Your move : ";
					check_input();
					// Modify Board
					break;
				}
				else if (yn=="N" || yn=="n")
				{
					break;
				}
				else
				{
					std::cout<<"Wrong input, Try again"<<std::endl;
				}
			}
			//Start game here
			Game(board);
		}
		else if (np=="Q" || np=="q")
		{
			std::cout<<"Thank you for Playing" << std::endl;
			break;
		}
		else
		{
			std::cout<<"Wrong value, Try again" << std::endl;
		}
	}
}

void Game(int** board)
{
	while (true)
	{
		std::cout<<"My move : ";
		// Call Algorithm
		// Modify Board
		// Check Winning state 
		std::cout<<"Your move : ";
		check_input();
		// Modify Board
		// Check Winning State
	}
}

int minMaxWithAlphaBeta(int** currentState,int depth,int childIndex,int alpha,int beta)
{
    int score1,score2,score3,score4,score5,score6,score7;
    int nextStateIndex;
    if(depth == 0)
    {
        return heurstic(currentState);
    }
    if(depth%2 == 1)
    {
        if(alpha < beta)
        {
            score1 = minMaxWithAlphaBeta(modifyBoard(currentState,0,"us"),depth-1,0,alpha,beta);
            if(depth > 1)
            {
                if(score1 > alpha)
                {
                    if(depth == 3)
                    {
                        nextStateIndex = 0;
                    }
                    alpha = score1;
                }
            }else
            {
                if(score1 > alpha)
                {
                    alpha = score1;
                }
            }
        }
        if(alpha < beta)
        {
            score2 = minMaxWithAlphaBeta(modifyBoard(currentState,1,"us"),depth-1,1,alpha,beta);
            if(depth > 1)
            {
                if(score2 > alpha)
                {
                    if(depth == 3)
                    {
                        nextStateIndex = 1;
                    }
                    alpha = score2;
                }
            }else
            {
                if(score2 > alpha)
                {
                    alpha = score2;
                }
            }
        }
        if(alpha < beta)
        {
            score3 = minMaxWithAlphaBeta(modifyBoard(currentState,2,"us"),depth-1,2,alpha,beta);
            if(depth > 1)
            {
                if(score3 > alpha)
                {
                    if(depth == 3)
                    {
                        nextStateIndex = 2;
                    }
                    alpha = score3;
                }
            }else
            {
                if(score3 > alpha)
                {
                    alpha = score3;
                }
            }
        }
        if(alpha < beta)
        {
            score4 = minMaxWithAlphaBeta(modifyBoard(currentState,3,"us"),depth-1,3,alpha,beta);
            if(depth > 1)
            {
                if(score4 > alpha)
                {
                    if(depth == 3)
                    {
                        nextStateIndex = 3;
                    }
                    alpha = score4;
                }
            }else
            {
                if(score4 > alpha)
                {
                    alpha = score4;
                }
            }
        }
        if(alpha < beta)
        {
            score5 = minMaxWithAlphaBeta(modifyBoard(currentState,4,"us"),depth-1,4,alpha,beta);
            if(depth > 1)
            {
                if(score5 > alpha)
                {
                    if(depth == 3)
                    {
                        nextStateIndex = 4;
                    }
                    alpha = score5;
                }
            }else
            {
                if(score5 > alpha)
                {
                    alpha = score5;
                }
            }
        }
        if(alpha < beta)
        {
            score6 = minMaxWithAlphaBeta(modifyBoard(currentState,5,"us"),depth-1,5,alpha,beta);
            if(depth > 1)
            {
                if(score6 > alpha)
                {
                    if(depth == 3)
                    {
                        nextStateIndex = 5;
                    }
                    alpha = score6;
                }
            }else
            {
                if(score6 > alpha)
                {
                    alpha = score6;
                }
            }
        }
        if(alpha < beta)
        {
            score7 = minMaxWithAlphaBeta(modifyBoard(currentState,6,"us"),depth-1,6,alpha,beta);
            if(depth > 1)
            {
                if(score7 > alpha)
                {
                    if(depth == 3)
                    {
                        nextStateIndex = 6;
                    }
                    alpha = score7;
                }
            }else
            {
                if(score7 > alpha)
                {
                    alpha = score7;
                }
            }
        }
        if(depth == 3)
        {
            return nextStateIndex;
        }else
        {
            return std::min(alpha,beta);
        }
    }
    else
    {
        if(alpha < beta)
        {
            score1 = minMaxWithAlphaBeta(modifyBoard(currentState,0,"them"),depth-1,0,alpha,beta);
            if(depth > 1)
            {
                if(score1 < beta)
                {
                    beta = score1;
                }
            }
        }
        if(alpha < beta)
        {
            score2 = minMaxWithAlphaBeta(modifyBoard(currentState,1,"them"),depth-1,1,alpha,beta);
            if(depth > 1)
            {
                if(score2 < beta)
                {
                    beta = score2;
                }
            }
        }
        if(alpha < beta)
        {
            score3 = minMaxWithAlphaBeta(modifyBoard(currentState,2,"them"),depth-1,2,alpha,beta);
            if(depth > 1)
            {
                if(score3 < beta)
                {
                    beta = score3;
                }
            }
        }
        if(alpha < beta)
        {
            score4 = minMaxWithAlphaBeta(modifyBoard(currentState,3,"them"),depth-1,3,alpha,beta);
            if(depth > 1)
            {
                if(score4 < beta)
                {
                    beta = score4;
                }
            }
        }
        if(alpha < beta)
        {
            score5 = minMaxWithAlphaBeta(modifyBoard(currentState,4,"them"),depth-1,4,alpha,beta);
            if(depth > 1)
            {
                if(score5 < beta)
                {
                    beta = score5;
                }
            }
        }
        if(alpha < beta)
        {
            score6 = minMaxWithAlphaBeta(modifyBoard(currentState,5,"them"),depth-1,5,alpha,beta);
            if(depth > 1)
            {
                if(score6 < beta)
                {
                    beta = score6;
                }
            }
        }
        if(alpha < beta)
        {
            score7 = minMaxWithAlphaBeta(modifyBoard(currentState,6,"them"),depth-1,6,alpha,beta);
            if(depth > 1)
            {
                if(score7 < beta)
                {
                    beta = score7;
                }
            }
        }
        return std::max(alpha,beta);
    }
}
