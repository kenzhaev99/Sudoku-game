#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>

#define UNASSIGNED 0
#define SIZE 9

using std::cin;
using std::cout;

bool unassignedCell(int grid[SIZE][SIZE], int &row, int &col);
bool allInOneCheck(int grid[SIZE][SIZE], int row, int col, int value);

bool findSolution(int grid[SIZE][SIZE])
{
    int row, col;

    if (!unassignedCell(grid, row, col))
    {
        return true;
    }

    for (int value = 1; value <= 9; value++)
    {
        if (allInOneCheck(grid, row, col, value))
        {
            grid[row][col] = value;
            if (findSolution(grid))
            {
                return true;
            }
            grid[row][col] = UNASSIGNED;
        }
    }

    return false;
}

bool unassignedCell(int grid[SIZE][SIZE], int &row, int &col)
{
    for (row = 0; row < SIZE; row++)
    {
        for (col = 0; col < SIZE; col++)
        {
            if (grid[row][col] == UNASSIGNED)
            {
                return true;
            }
        }
    }

    return false;
}

bool containsRow(int grid[SIZE][SIZE], int row, int value)
{
    for (int col = 0; col < SIZE; col++)
    {
        if (grid[row][col] == value)
        {
            return true;
        }
    }

    return false;
}

bool containsCol(int grid[SIZE][SIZE], int col, int value)
{
    for (int row = 0; row < SIZE; row++)
    {
        if (grid[row][col] == value)
        {
            return true;
        }
    }
    return false;
}

bool containsBox(int grid[SIZE][SIZE], int boxRow, int boxCol, int value)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (grid[row+boxRow][col+boxCol] == value)
            {
                return true;
            }
        }
    }

    return false;
}

bool allInOneCheck(int grid[SIZE][SIZE], int row, int col, int value)
{
    return !containsRow(grid, row, value) && !containsCol(grid, col, value) && !containsBox(grid, row-row%3, col-col%3, value);
}

void draw(int grid[SIZE][SIZE], bool withComments)
{
    if (withComments)
    {
        printf("If you want to exit, insert 9876 (where value)\n");
        printf("if you want to see the solution, insert 1234 (where value)\n");
    }

    printf("----------------------\n");

    for (int row = 0; row < SIZE; row++)
    {
        printf("|");
        for (int col = 0; col < SIZE; col++)
        {
            if (grid[row][col] != 0)
            printf("%d", grid[row][col]);
            else printf("=");
            if ((col+1) % 3 == 0) printf("|");
        }
        printf("\r\n");
        if ((row+1) % 3 == 0)
        {
                printf("----------------------\n");
        }
    }
}

bool isWin(int grid[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j] == 0) return false;
        }
    }
    return true;
}

int main()
{
    SetConsoleTitle("Sudoku game");
    int grid[SIZE][SIZE] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    srand(time(NULL));

    for (int i = 0; i < 30; i++)
    {
        int row = rand() % 10;
        int col = rand() % 10;
        int val = rand() % 10;
        printf("%d", val);
        if (allInOneCheck(grid, row, col, val))
            grid[row][col] = val;
    }

    int row, column, curNumber;

    while(true)
    {
        if (isWin(grid))
        {
            printf("You win!\nInsert any key to exit!");
            system("pause");
            break;
        }

        system("cls");
        draw(grid, true);
        printf("Insert row:");
        cin >> row;
        printf("Insert column:");
        cin >> column;
        printf("Insert value for this coordinates:");
        cin >> curNumber;

        if (curNumber == 9876) break;

        else if (curNumber == 1234)
        {

            if (findSolution(grid) == true)
            {
                draw(grid, false);
            }

            else
            {
                printf("No solution found");
            }

            printf("You lose!\nInsert any key to exit!");
            system("pause");
            break;
        }

        if (allInOneCheck(grid, row - 1, column - 1, curNumber))
        {
            grid[row - 1][column - 1] = curNumber;
        }

        else
        {
            printf("Incorrect value, try one more please!\n");
            system("pause");
            continue;
        }
    }
    return 0;
}
