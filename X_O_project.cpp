// X O game 

#include <iostream>
using namespace std;

void displayBoard(char board[3][3])
{
    cout << "  1   2   3" << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j)
        {
            cout << " " << board[i][j] << " ";
            if (j < 2) cout << "|";


        }
        cout << endl;
        if (i < 2) cout << " ---+---+---" << endl;
    }
    cout << endl;
}

bool checkWin(char board[3][3], char player)
{
    for (int i = 0; i < 3; ++i)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                (board[0][i] == player && board[1][i] == player && board[2][i] == player))
        {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
            (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return true;
    }
    return false;
}

bool isBoardFull(char board[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    int row, col;
    char currentPlayer = 'X';

    while (true)
    {
        displayBoard(board);

        cout << "Player " << currentPlayer << ", enter row (1-3) and column (1-3): ";
        cin >> row >> col;

        row--; // Convert to 0-based index
        col--; // Convert to 0-based index

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ')
        {
            cout << "Invalid input! Try again." << endl;
            continue;
        }

        board[row][col] = currentPlayer;

        if (checkWin(board, currentPlayer))
        {
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }

        if (isBoardFull(board))
        {
            displayBoard(board);
            break;
        }

        // Switch players
        if (currentPlayer == 'X')
        {
            currentPlayer = 'O';
        }
        else
        {
            currentPlayer = 'X';
        }
    }

    return 0;
}