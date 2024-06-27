#include <stdio.h>
/*
By:
Matthew Ryan Carandang
Ponj Elazegui
Nigel Nograles
*/

void DisplayGrid(int Grid[][3]);
void GetUserInput(int num[], int Grid[][3]);
void CheckWinCondition(int Grid[][3],int *win, int*over);
int rowtotal(int Grid[][3],int *win, int*over, int ncol);
int coltotal(int Grid[][3],int *win, int*over, int nrow);

int main (void)
{
    int turn=1,over=0,win=0;
    int Grid[3][3] = {0};
    int Numbers[9]={1,2,3,4,5,6,7,8,9};

    while(over==0)
    {   
        DisplayGrid(Grid);
        if(turn==1)
        {
            fprintf(stdout,"\n\033[0;34mPlayer 1's turn\033[0m\n\n");
            GetUserInput(Numbers,Grid);
        }
        else
        {
            fprintf(stdout,"\n\033[0;31mPlayer 2's turn\033[0m\n\n");
            GetUserInput(Numbers,Grid);
        }

        CheckWinCondition(Grid,&win,&over);

        if(turn==1)
        {
            turn=0;
        }
        else
        {
            turn=1;
        }
    }

    DisplayGrid(Grid);

    if (turn == 1)
    {
        if (win == 1)
        {
            printf("\n\n\033[0;31mPlayer 2 WON!\033[0m");
        }
        else
        {
            printf("\n\n\033[0;34mPlayer 1 WON!\033[0m");
        }
    }

    if (turn == 0)
    {
        if (win == 1)
        {
            printf("\n\n\033[0;34mPlayer 1 WON!\033[0m");
        }
        else
        {
            printf("\n\n\033[0;31mPlayer 2 WON!\033[0m");
        }
    }


}
/*
void DisplayGrid displays the current grid of the game that both
players are currently playing. This updates everytime a change
is made to the grid values
@param Grid[][3] - gets information about the current state of the grids.
@no return value.
*/
void DisplayGrid(int Grid[][3])
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(Grid[i][j]==0)
            {
                fprintf(stdout," [_] ");
            }
            else
            {
                fprintf(stdout," [%d] ",Grid[i][j]);
            }
        }
        fprintf(stdout,"\n");
    }
}

/*
void GetUserInput Prompts players to input the desired number to put to a
cell on the grid. It also holds which numbers that are already played.
@param Grid[][3] - gets information about the current state of the grids.
@param num[] - holds the numbers that were already used/played.
*/
void GetUserInput(int num[], int Grid[][3])
{
    int xcoord=-1,ycoord=-1,occ=1;
    int number,used;

    while(xcoord<0 || xcoord>2 || ycoord<0 || ycoord>2 || occ == 1)
    {
        fprintf(stdout,"Please enter VALID Coordinates (e.g. 1 1, 2 2, etc.): ");
        fscanf(stdin,"%d %d",&xcoord,&ycoord);

        xcoord--;ycoord--;

        if(Grid[xcoord][ycoord]==0)
        {
            occ = 0;
        }
        else
        {
            occ = 1;
        }

    }

    while(number<1 || number > 9 || used == 1)
    {
        fprintf(stdout,"Please Input a Number between 1 to 9: ");
        fscanf(stdin,"%d",&number);
        if(num[number-1]==0)
        {
            used = 1;
        }
        else
        {
            used = 0;
            Grid[xcoord][ycoord]=num[number-1];
            num[number-1]=0;
        }
    }
}

/*
void CheckWinCondition checks if the situation of the Grid will yield 
a win, a lose, or the game will continue. And updates the variable
in doing so.
@param Grid[][3] - gets information about the current state of the grids.
@param *win - A pointer that gets updated if a players wins.
@param *over - terminates the program whenever a player wins.
*/
void CheckWinCondition(int Grid[][3],int *win, int*over)
{
    int row[3];
    int col[3];
    int i;

    for(i=0;i<3;i++)
    {
        row[i]=rowtotal(Grid,&*win,&*over,i);
        col[i]=coltotal(Grid,&*win,&*over,i);
    }

    if((row[0]==15) && (row[1]==15) && (row[2]==15) && (col[0]==15) && (col[1]==15) && (col[2]==15))
    {
        *win = 1;
        *over = 1;
    }

}

/*
void CheckWinConditionrow checks if the row may have a possible winner or 
loser.
@param Grid[][3] - gets information about the current state of the grids.
@param *win - A pointer that gets updated if a players wins.
@param *over - terminates the program whenever a player wins.
@param nrow - Determines which row of the grid will be checked.
*/
int rowtotal(int grid[][3],int *win, int*over, int nrow)
{
    if((grid[nrow][0] !=0)&&(grid[nrow][1] !=0)&&(grid[nrow][2] !=0))
    {
        if((grid[nrow][0] + grid[nrow][1] + grid[nrow][2]<15))
        {
            *win=0;
            *over=1;
        }

    return grid[nrow][0] + grid[nrow][1] + grid[nrow][2];
    }
}

/*
void CheckWinConditioncol checks if the column may have a possible winner or 
loser.
@param Grid[][3] - gets information about the current state of the grids.
@param *win - A pointer that gets updated if a players wins.
@param *over - terminates the program whenever a player wins.
@param ncol - Determines which column of the grid will be checked.
*/
int coltotal(int grid[][3],int *win, int*over, int ncol)
{
    if((grid[0][ncol]!=0)&&(grid[1][ncol]!=0)&&(grid[2][ncol]!=0))
    {
        if((grid[0][ncol] + grid[1][ncol] + grid[2][ncol]<15))
        {
            *win=0;
            *over=1;
        }
        return grid[0][ncol] + grid[1][ncol] + grid[2][ncol];
    }
}