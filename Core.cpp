#include <iostream>
#include <string>
#include <fstream>
#define maxDepth 3
int** modifyBoard(int** board,int yIndex,std::string playerMode);
bool evaluateBoard(int** board,std::string& winner,std::string& how);
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
void StartNewGame();
int check_input();
void Game(int** board);
int minMaxWithAlphaBeta(int** currentState,int depth,int childIndex,int alpha,int beta);
void showBoard(int** board);
bool validModification(int** board,int y);
int** InitiateBoard();
void SaveGame(int** board);
int** LoadGame();

int main()
{
    //interface
    std::cout<<"Welcome To Connect 4 Game"<<std::endl;
	StartNewGame();
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
bool evaluateBoard(int** board,std::string& winner,std::string& how)
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
    if(winner == "")
    {
        return false;
    }else
    {
        return true;
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
                    score += 10000;
                }
                if(vert == 2)
                {
                    score += 25;
                }else if(vert == 3)
                {
                    score += 50;
                }else if(vert == 4)
                {
                    score += 10000;
                }
                if(dia_45 == 2)
                {
                    score += 25;
                }else if(dia_45 == 3)
                {
                    score += 50;
                }else if(dia_45 == 4)
                {
                    score += 10000;
                }
                if(dia45 == 2)
                {
                    score += 25;
                }else if(dia45 == 3)
                {
                    score += 50;
                }else if(dia45 == 4)
                {
                    score += 10000;
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

int check_input()
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
		else if(inp == -1)
		{
			return inp;
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
	return inp-1;

}

void StartNewGame()
{
	while (true)
	{
		std::cout<<"press N to start new game or L to load last game or Q to quit"<<std::endl;
		std::string np;
		std::cin>>np;
		if (np=="N" || np=="n")
		{
			int** board = InitiateBoard();
			while (true)
			{
				std::cout<<"Would you like to start first ? y/n"<<std::endl;
				std::string yn;
				std::cin>>yn;
				if (yn=="Y"|| yn=="y")
				{
					std::cout<<"Your move : ";
					int y1 = check_input();
					board=modifyBoard(board,y1,"them");
					showBoard(board);
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
		else if (np=="L" || np=="l")
		{
			std::cout<<"Loading" << std::endl;
			int** lastboard=LoadGame();
			showBoard(lastboard);
			std::cout<<"Your move : ";
			int y1 = check_input();
			lastboard=modifyBoard(lastboard,y1,"them");
			showBoard(lastboard);
			Game(lastboard);
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
	std::string winner,method;
    bool flag = false;
	while (true)
	{
		std::cout<<"My move : ";
		int x1 = minMaxWithAlphaBeta(board,maxDepth,0,-100000000,100000000);
		std::cout<<x1+1<<std::endl;
		board=modifyBoard(board,x1,"us");
		showBoard(board);
		// Check Winning state
        if(evaluateBoard(board,winner,method))
        {
            flag = true; 
            break;
        } 
		std::cout<<"Your move : ";
		int y1 = check_input();
		if(y1==-1)
		{
			SaveGame(board);
			std::cout<<"Game has been saved"<<std::endl;
			break;
		}
		board=modifyBoard(board,y1,"them");
		showBoard(board);
		// Check Winning State
        if(evaluateBoard(board,winner,method))
        {
            flag = true; 
            break;
        } 
	}
    if(flag)
    {
        std::cout<<"Winner is "+winner+" by connecting 4 "+method<<std::endl;
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
        //std::cout<<depth<<"  0"<<std::endl;
        if(alpha < beta && validModification(currentState,0))
        {
            score1 = minMaxWithAlphaBeta(modifyBoard(currentState,0,"us"),depth-1,0,alpha,beta);
            if(depth > 1)
            {
                if(score1 > alpha)
                {
                    if(depth == maxDepth)
                    {
                        nextStateIndex = 0;
                    }
                    alpha = score1;
                }
                //std::cout<<alpha<<" "<<beta<<std::endl;
            }else
            {
                if(score1 > alpha)
                {
                    alpha = score1;
                }
            }
        }
        //std::cout<<depth<<"  1"<<std::endl;
        if(alpha < beta && validModification(currentState,1))
        {
            score2 = minMaxWithAlphaBeta(modifyBoard(currentState,1,"us"),depth-1,1,alpha,beta);
            if(depth > 1)
            {
                if(score2 > alpha)
                {
                    if(depth == maxDepth)
                    {
                        nextStateIndex = 1;
                    }
                    alpha = score2;
                }
                //std::cout<<alpha<<" "<<beta<<std::endl;
            }else
            {
                if(score2 > alpha)
                {
                    alpha = score2;
                }
            }
        }
        //std::cout<<depth<<"  2"<<std::endl;
        if(alpha < beta && validModification(currentState,2))
        {
            score3 = minMaxWithAlphaBeta(modifyBoard(currentState,2,"us"),depth-1,2,alpha,beta);
            if(depth > 1)
            {
                if(score3 > maxDepth)
                {
                    if(depth == 3)
                    {
                        nextStateIndex = 2;
                    }
                    alpha = score3;
                }
                //std::cout<<alpha<<" "<<beta<<std::endl;
            }else
            {
                if(score3 > alpha)
                {
                    alpha = score3;
                }
            }
        }
        //std::cout<<depth<<"  3"<<std::endl;
        if(alpha < beta && validModification(currentState,3))
        {
            score4 = minMaxWithAlphaBeta(modifyBoard(currentState,3,"us"),depth-1,3,alpha,beta);
            if(depth > 1)
            {
                if(score4 > alpha)
                {
                    if(depth == maxDepth)
                    {
                        nextStateIndex = 3;
                    }
                    alpha = score4;
                }
                //std::cout<<alpha<<" "<<beta<<std::endl;
            }else
            {
                if(score4 > alpha)
                {
                    alpha = score4;
                }
            }
        }
        //std::cout<<depth<<"  4"<<std::endl;
        if(alpha < beta && validModification(currentState,4))
        {
            score5 = minMaxWithAlphaBeta(modifyBoard(currentState,4,"us"),depth-1,4,alpha,beta);
            if(depth > 1)
            {
                if(score5 > alpha)
                {
                    if(depth == maxDepth)
                    {
                        nextStateIndex = 4;
                    }
                    alpha = score5;
                }
                //std::cout<<alpha<<" "<<beta<<std::endl;
            }else
            {
                if(score5 > alpha)
                {
                    alpha = score5;
                }
            }
        }
        //std::cout<<depth<<"  5"<<std::endl;
        if(alpha < beta && validModification(currentState,5))
        {
            score6 = minMaxWithAlphaBeta(modifyBoard(currentState,5,"us"),depth-1,5,alpha,beta);
            if(depth > 1)
            {
                if(score6 > alpha)
                {
                    if(depth == maxDepth)
                    {
                        nextStateIndex = 5;
                    }
                    alpha = score6;
                }
                //std::cout<<alpha<<" "<<beta<<std::endl;
            }else
            {
                if(score6 > alpha)
                {
                    alpha = score6;
                }
            }
        }
        //std::cout<<depth<<"  6"<<std::endl;
        if(alpha < beta && validModification(currentState,6))
        {
            score7 = minMaxWithAlphaBeta(modifyBoard(currentState,6,"us"),depth-1,6,alpha,beta);
            if(depth > 1)
            {
                if(score7 > alpha)
                {
                    if(depth == maxDepth)
                    {
                        nextStateIndex = 6;
                    }
                    alpha = score7;
                }
                //std::cout<<alpha<<" "<<beta<<std::endl;
            }else
            {
                if(score7 > alpha)
                {
                    alpha = score7;
                }
            }
        }
        if(depth == maxDepth)
        {
            return nextStateIndex;
        }else
        {
            return std::min(alpha,beta);
        }
    }
    else
    {
        if(alpha < beta && validModification(currentState,0))
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
        if(alpha < beta && validModification(currentState,1))
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
        if(alpha < beta && validModification(currentState,2))
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
        if(alpha < beta && validModification(currentState,3))
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
        if(alpha < beta && validModification(currentState,4))
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
        if(alpha < beta && validModification(currentState,5))
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
        if(alpha < beta && validModification(currentState,6))
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

void showBoard(int** board)
{
	for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(board[i][j] == -1)
            {
                 std::cout<<"o ";
            }
            else if(board[i][j] == 1)
            {
                std::cout<<"x ";   
            }
            else
            {
                std::cout<<"- ";
            }
        }
        std::cout<<std::endl;
    }
}

bool validModification(int** board,int y)
{
    for(int i=5;i>=0;i--)
    {
        if(board[i][y] == 0)
        {
            return true;
        }
    }  
    return false;
}

int** InitiateBoard()
{
	//board is arranged top down from row 0 to row 5
    int** connect4Board = new int* [6];
    for(int i=0;i<6;i++)
	{
		connect4Board[i] = new int[7];
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			connect4Board[i][j]=0;
		}
	}

	return connect4Board;
}

void SaveGame(int** board)
{
	std::ofstream outfile;
	outfile.open("LastGame.txt");
	for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
		{
			outfile << board[i][j] << std::endl;
		}
	}
	outfile.close();
}

int** LoadGame()
{
	int** board=InitiateBoard();
	std::ifstream infile;
	infile.open("LastGame.txt");
	for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
		{
			infile >> board[i][j];
		}
	}
	infile.close();
	return board;
}
