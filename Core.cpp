#include <iostream>
#include <string>
void modifyBoard(int** board,int yIndex,std::string playerMode,int** result);
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
    connect4Board[0] = new int[7] {0,0,0,0,0,0,0};
    connect4Board[1] = new int[7] {0,0,0,1,0,0,0};
    connect4Board[2] = new int[7] {0,0,-1,-1,0,0,0};
    connect4Board[3] = new int[7] {0,0,-1,-1,0,0,0};
    connect4Board[4] = new int[7] {1,1,1,-1,-1,1,0};
    connect4Board[5] = new int[7] {-1,-1,1,1,1,-1,0};
    int** result = new int* [6];
    for(int i=0;i<6;i++)
    {
        result[i] = new int[7];
    }
    modifyBoard(connect4Board,3,"them",result);
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            std::cout<<result[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    /*
    std::string winner,method;
    evaluateBoard(connect4Board,winner,method);
    std::cout<<"winner is "<<winner<<std::endl;
    std::cout<<"by connecting four "<<method<<std::endl;*/
    return 0;
}

//i will assume that player's game will be -1 in his chosen position and 1 for our algorithm yIndex is column number
void modifyBoard(int** board,int yIndex,std::string playerMode,int** result)
{
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
        if(yIndex > 0&&yIndex <7)
        {
            for(int i=5;i>=0;i--)
            {
                if(result[i][yIndex] == 0)
                {
                    result[i][yIndex] = 1;
                    break;
                }
            }  
        }
        
    }else if(playerMode == "them")
    {
        if(yIndex > 0&&yIndex <7)
        {
            for(int i=5;i>=0;i--)
            {
                if(result[i][yIndex] == 0)
                {
                    result[i][yIndex] = -1;
                    break;
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