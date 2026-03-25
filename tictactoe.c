#include <stdio.h>  
void main(){
    printf("Welcome to Tic Tac Toe Game\n");
    printf("Player 1: X\n");
    printf("Player 2: O\n");
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int row, col, player = 1, moves = 0;  
    char game='n'; 

    while(game != 'w') {
        printf("Player %d, enter your move (row and column):\n ", player);
        scanf("%d %d", &row, &col);
        if (board[row][col] == ' ') {
            board[row][col] = (player == 1) ? 'X' : 'O';
            moves++;
            for (int i = 0; i < 3; i++) {
                if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
                    printf("Player %d wins!\n", player);
                    game='w';
                    break;
                }
                if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
                    printf("Player %d wins!\n", player);
                    game='w';
                    break;
                }
            }
            if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
                printf("Player %d wins!\n", player);
                game='w';
                break;
            }
            if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
                printf("Player %d wins!\n", player);
                game='w';
                break;
            }
            if (moves == 9) {
                printf("It's a draw!\n");
                break;
            }
            player = (player == 1) ? 2 : 1;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}   
    