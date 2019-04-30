#include <iostream>
#include <string>
void modifyBoard(int** board,int xIndex,int yIndex,std::string playerMode);
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
int main()
{
    //board is arranged top down from row 0 to row 5
    int** connect4Board = new int* [6];
    for(int i=0;i<6;i++)
    {
        connect4Board[i] = new int[7];
    }
    //modifyBoard(connect4Board,5,3,"user");
    //std::cout<<connect4Board[5][3]<<std::endl;
    //modifyBoard(connect4Board,0,7,"user");
    //std::cout<<connect4Board[0][7]<<std::endl;
    connect4Board[0] = new int[7] {0,0,0,0,0,0,0};
    connect4Board[1] = new int[7] {0,0,0,1,0,0,0};
    connect4Board[2] = new int[7] {0,0,-1,-1,0,0,0};
    connect4Board[3] = new int[7] {0,0,-1,-1,0,0,0};
    connect4Board[4] = new int[7] {1,1,1,-1,-1,1,0};
    connect4Board[5] = new int[7] {-1,-1,1,1,1,-1,0};
    /*for(int i=0;i<6;i++)
    {
        std::cout<<"index "<<i<<std::endl;
        for(int j=0;j<7;j++)
        {
            std::cout<<connect4Board[i][j]<<std::endl;
        }
    }*/
    //std::cout<<countDiagonally_45(connect4Board,2,2,-1)<<std::endl;
    std::string winner,method;
    evaluateBoard(connect4Board,winner,method);
    std::cout<<"winner is "<<winner<<std::endl;
    std::cout<<"by connecting four "<<method<<std::endl;
    return 0;
}

//i will assume that player's game will be 1 in his chosen position and -1 for our algorithm
void modifyBoard(int** board,int xIndex,int yIndex,std::string playerMode)
{
    if(playerMode == "user")
    {
        if(xIndex >= 0&&xIndex <=5&&yIndex>=0&&yIndex<=6)
        {
            board[xIndex][yIndex] = 1;
        }else
        {
            std::cout<<"invalid index"<<std::endl;
        }
        
    }else if(playerMode == "Computer")
    {
        board[xIndex][yIndex] = -1;
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
                    winner = "user";
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
                    winner = "Computer";
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