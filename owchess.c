#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8

// Chess board representation ('.' = empty, uppercase = white, lowercase = black)
char board[BOARD_SIZE][BOARD_SIZE];

// Player colors
#define WHITE_PLAYER 1
#define BLACK_PLAYER 2
#define COMPUTER 3

int current_player = WHITE_PLAYER;
int game_mode = 0; // 1 = vs Computer, 2 = 2 Player

// Function prototypes
void initialize_board();
void print_board();
void setup_initial_positions();
void setup_intermediate_position();
int parse_move(char* move, int* from_row, int* from_col, int* to_row, int* to_col);
int is_valid_move(int from_row, int from_col, int to_row, int to_col);
void make_move(int from_row, int from_col, int to_row, int to_col);
void suggest_best_move();
void computer_move();
int is_in_check(int player);
void undo_move(int fr, int fc, int tr, int tc, char captured);
int hass_legal_moves(int player);
int check_game_status();
void show_possible_moves(int row, int col);

int main() {
    int choice, position_choice;
    
    printf("\n=== CHESS GAME ===\n");
    
    // Choose starting position
    printf("\nChoose starting position:\n");
    printf("1. Initial Position\n");
    printf("2. Intermediate Position\n");
    printf("Enter choice (1-2): ");
    scanf("%d", &position_choice);
    
    // Initialize empty board
    initialize_board();
    
    if (position_choice == 1) {
        setup_initial_positions();
    } else {
        setup_intermediate_position();
    }
    
    // Choose game mode
    printf("\nChoose game mode:\n");
    printf("1. Play with Computer\n");
    printf("2. 2 Player\n");
    printf("Enter choice (1-2): ");
    scanf("%d", &game_mode);
    
    printf("\nGame Started! White moves first.\n");
    
    while (1) {
        
        print_board();
        
        // Check for winner
        if (check_game_status()) {
    break;
}
        if (current_player == WHITE_PLAYER) {
            printf("enter single address to show moves or ");
            printf("type exit for end the game\nWHITE's turn. Enter move (e.g., e2e4) or 'best' for suggestion: ");
        

        } else {
            printf("type exit for end the game\nBLACK's turn. Enter move (e.g., e7e5) or 'best' for suggestion: ");
        }
        
        char move[10];
        scanf("%s", move);

// Show moves command
if (strlen(move) == 2) {
    int col = tolower(move[0]) - 'a';
    int row = 8 - (move[1] - '0');

    if (col >= 0 && col < 8 && row >= 0 && row < 8) {
        show_possible_moves(row, col);
    } else {
        printf("Invalid position!\n");
    }
    continue;
}
        
        if (strcmp(move, "best") == 0 || strcmp(move, "Best") == 0) {
            suggest_best_move();
            continue;
        }
        if (strcmp(move, "exit") == 0) break;
        
        int from_row, from_col, to_row, to_col;
        
        if (parse_move(move, &from_row, &from_col, &to_row, &to_col)) {
            if (is_valid_move(from_row, from_col, to_row, to_col)) {
                make_move(from_row, from_col, to_row, to_col);
                current_player = (current_player == WHITE_PLAYER) ? BLACK_PLAYER : WHITE_PLAYER;
            } else {
                printf("Invalid move! Try again.\n");
            }
        } else {
            printf("Invalid move format! Use format like e2e4\n");
        }
        
        // Computer move if playing vs computer
        if (game_mode == 1 && current_player == BLACK_PLAYER) {
            computer_move();
            current_player = WHITE_PLAYER;
        }
    }
    srand(time(0)); // Seed random number generator for computer moves
    return 0;
}

void initialize_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

void print_board() {
    printf("\n  a b c d e f g h\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n\n");
}

void setup_initial_positions() {
    // White pieces (uppercase)
    board[7][0] = 'R'; board[7][1] = 'N'; board[7][2] = 'B'; board[7][3] = 'Q';
    board[7][4] = 'K'; board[7][5] = 'B'; board[7][6] = 'N'; board[7][7] = 'R';
    for (int j = 0; j < 8; j++) board[6][j] = 'P';
    
    // Black pieces (lowercase)
    board[0][0] = 'r'; board[0][1] = 'n'; board[0][2] = 'b'; board[0][3] = 'q';
    board[0][4] = 'k'; board[0][5] = 'b'; board[0][6] = 'n'; board[0][7] = 'r';
    for (int j = 0; j < 8; j++) board[1][j] = 'p';
}


 void setup_intermediate_position() {
    print_board();

    printf("\n=== Setup Custom Board ===\n");
    printf("Enter pieces manually.\n");
    printf("Format: <Piece> <Position> (e.g., K e1, q d8)\n");
    printf("Type 'done' to finish.\n\n");

    while (1) {
        char input[10];
        printf("Enter piece and position: ");
        scanf("%s", input);

        // Stop condition
        if (strcmp(input, "done") == 0) {
            break;
        }

        char piece = input[0];

        char pos[3];
        scanf("%s", pos);

        int col = tolower(pos[0]) - 'a';
        int row = 8 - (pos[1] - '0');

        // Validation
        if (col < 0 || col >= 8 || row < 0 || row >= 8) {
            printf("Invalid position! Try again.\n");
            continue;
        }

        if (!strchr("KQRBNPkqrbnp", piece)) {
            printf("Invalid piece! Try again.\n");
            continue;
        }

        // Place piece
        board[row][col] = piece;

        print_board();
    }

    printf("\nCustom position loaded!\n");
}   
int parse_move(char* move, int* from_row, int* from_col, int* to_row, int* to_col) {
    if (strlen(move) != 4) return 0;
    
    *from_col = tolower(move[0]) - 'a';
    *from_row = 8 - (move[1] - '0');
    *to_col = tolower(move[2]) - 'a';
    *to_row = 8 - (move[3] - '0');
    
    if (*from_col < 0 || *from_col >= 8 || *from_row < 0 || *from_row >= 8 ||
        *to_col < 0 || *to_col >= 8 || *to_row < 0 || *to_row >= 8) {
        return 0;
    }
    return 1;
}

int is_valid_move(int from_row, int from_col, int to_row, int to_col) {
    // Basic validation: piece exists, correct color, not same square
    char piece = board[from_row][from_col];
    if (piece == '.') return 0;

    char dest=board[to_row][to_col];
    if (dest!='.'){
        if(isupper(piece)==isupper(dest) || islower(piece)==islower(dest)){
            return 0;
        }
    }
    int is_black = islower(piece);
    int is_white = isupper(piece);
    
    
    
    if ((current_player == WHITE_PLAYER && !is_white) ||
        (current_player == BLACK_PLAYER && is_white)) {
        return 0;
    }
    
    if (from_row == to_row && from_col == to_col) return 0;
    
    // Simple movement rules (basic validation)
    int row_diff = abs(to_row - from_row);
    int col_diff = abs(to_col - from_col);
    
    // Pawn movement
   // White Pawn
if (piece == 'P') {
    // 1 step forward
    if (from_row - to_row == 1 && col_diff == 0 && board[to_row][to_col] == '.')
        return 1;

    // 2 steps from starting position
    if (from_row == 6 && from_row - to_row == 2 && col_diff == 0 &&
        board[from_row - 1][from_col] == '.' &&
        board[to_row][to_col] == '.')
        return 1;

    // Diagonal capture
    if (from_row - to_row == 1 && col_diff == 1 &&
        board[to_row][to_col] != '.' && islower(board[to_row][to_col]))
        return 1;
}

// Black Pawn
else if (piece == 'p') {
    // 1 step forward
    if (to_row - from_row == 1 && col_diff == 0 && board[to_row][to_col] == '.')
        return 1;

    // 2 steps from starting position
    if (from_row == 1 && to_row - from_row == 2 && col_diff == 0 &&
        board[from_row + 1][from_col] == '.' &&
        board[to_row][to_col] == '.')
        return 1;

    // Diagonal capture
    if (to_row - from_row == 1 && col_diff == 1 &&
        board[to_row][to_col] != '.' && isupper(board[to_row][to_col]))
        return 1;
} 
    
    // Rook movement
    else if (piece == 'R' || piece == 'r') {
        if (row_diff == 0){
            // Check for clear path horizontally
            int step = (to_col > from_col) ? 1 : -1;
            for (int c = from_col + step; c != to_col; c += step) {
                if (board[from_row][c] != '.') return 0;
            }
            return 1;
        }
        if(col_diff == 0){
            // Check for clear path vertically
            int step = (to_row > from_row) ? 1 : -1;
            for (int r = from_row + step; r != to_row; r += step) {
                if (board[r][from_col] != '.') return 0;
            }
            return 1;
        }
    }
    // Bishop movement
    else if (piece == 'B' || piece == 'b') {
    if (row_diff == col_diff) {
        int row_step = (to_row > from_row) ? 1 : -1;
        int col_step = (to_col > from_col) ? 1 : -1;

        int r = from_row + row_step;
        int c = from_col + col_step;

        while (r != to_row && c != to_col) {
            if (board[r][c] != '.') return 0;
            r += row_step;
            c += col_step;
        }
        return 1;
    }
}

else if (piece == 'Q' || piece == 'q') {

    // Horizontal move
    if (row_diff == 0) {
        int step = (to_col > from_col) ? 1 : -1;
        for (int c = from_col + step; c != to_col; c += step) {
            if (board[from_row][c] != '.') return 0;
        }
        return 1;
    }

    // Vertical move
    if (col_diff == 0) {
        int step = (to_row > from_row) ? 1 : -1;
        for (int r = from_row + step; r != to_row; r += step) {
            if (board[r][from_col] != '.') return 0;
        }
        return 1;
    }

    // Diagonal move (like bishop)
    if (row_diff == col_diff) {
        int row_step = (to_row > from_row) ? 1 : -1;
        int col_step = (to_col > from_col) ? 1 : -1;

        int r = from_row + row_step;
        int c = from_col + col_step;

        while (r != to_row && c != to_col) {
            if (board[r][c] != '.') return 0;
            r += row_step;
            c += col_step;
        }
        return 1;
    }
}

    // Knight movement
    else if (piece == 'N' || piece == 'n') {
        if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2))
            return 1;
    }
    
    // King movement
    else if (piece == 'K' || piece == 'k') {
        if (row_diff <= 1 && col_diff <= 1)
            return 1;
    }
    
    return 0; // Invalid move
}

void make_move(int from_row, int from_col, int to_row, int to_col) {
    board[to_row][to_col] = board[from_row][from_col];
    board[from_row][from_col] = '.';
    printf("Move executed: %c%d to %c%d\n", 
           'a' + from_col, 8 - from_row,
           'a' + to_col, 8 - to_row);
}

void suggest_best_move() {
    printf("AI Suggestion:\n");
    if (current_player == WHITE_PLAYER) {
        printf("1. e2e4 (King's Pawn Opening)\n");
        printf("2. d2d4 (Queen's Pawn Opening)\n");
        printf("3. g1f3 (Reti Opening)\n");
    } else {
        printf("1. e7e5 (King's Pawn Defense)\n");
        printf("2. c7c5 (Sicilian Defense)\n");
        printf("3. d7d5 (Queen's Gambit Declined)\n");
    }
}


void computer_move() {
    printf("\nComputer (Black) is thinking...\n");
    
    // Simple computer AI - random valid move
    int valid_moves[64][4]; // from_row, from_col, to_row, to_col
    int move_count = 0;
    
    for (int fr = 0; fr < 8; fr++) {
        for (int fc = 0; fc < 8; fc++) {
            if (islower(board[fr][fc])) {
                for (int tr = 0; tr < 8; tr++) {
                    for (int tc = 0; tc < 8; tc++) {
                        if (is_valid_move(fr, fc, tr, tc)) {
                            valid_moves[move_count][0] = fr;
                            valid_moves[move_count][1] = fc;
                            valid_moves[move_count][2] = tr;
                            valid_moves[move_count][3] = tc;
                            move_count++;
                        }
                    }
                }
            }
        }
    }
    
    if (move_count > 0) {
        int random_move = rand() % move_count;
        int fr = valid_moves[random_move][0];
        int fc = valid_moves[random_move][1];
        int tr = valid_moves[random_move][2];
        int tc = valid_moves[random_move][3];
        
        printf("Computer moves: %c%d to %c%d\n", 
               'a' + fc, 8 - fr, 'a' + tc, 8 - tr);
        make_move(fr, fc, tr, tc);
    }
}


int is_in_check(int player) {
    int king_row, king_col;
    char king = (player == WHITE_PLAYER) ? 'K' : 'k';

    // Find king
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == king) {
                king_row = i;
                king_col = j;
            }
        }
    }

    // Check if any opponent piece can attack king
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char piece = board[i][j];
            if (piece == '.') continue;

            // Opponent piece
            if ((player == WHITE_PLAYER && islower(piece)) ||
                (player == BLACK_PLAYER && isupper(piece))) {

                if (is_valid_move(i, j, king_row, king_col)) {
                    return 1; // King is in check
                }
            }
        }
    }

    return 0;
}


void undo_move(int fr, int fc, int tr, int tc, char captured) {
    board[fr][fc] = board[tr][tc];
    board[tr][tc] = captured;
}

int has_legal_moves(int player) {
    for (int fr = 0; fr < 8; fr++) {
        for (int fc = 0; fc < 8; fc++) {
            char piece = board[fr][fc];
            if (piece == '.') continue;

            if ((player == WHITE_PLAYER && isupper(piece)) ||
                (player == BLACK_PLAYER && islower(piece))) {

                for (int tr = 0; tr < 8; tr++) {
                    for (int tc = 0; tc < 8; tc++) {

                        if (is_valid_move(fr, fc, tr, tc)) {

                            char captured = board[tr][tc];

                            // Make move
                            board[tr][tc] = board[fr][fc];
                            board[fr][fc] = '.';

                            int check = is_in_check(player);

                            // Undo move
                            undo_move(fr, fc, tr, tc, captured);

                            if (!check) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int check_game_status() {

    if (is_in_check(WHITE_PLAYER)) {
        if (!has_legal_moves(WHITE_PLAYER)) {
            printf("\nCHECKMATE! BLACK WINS!\n");
            return 1;
        } else {
            printf("\nWHITE is in CHECK!\n");
        }
    }

    if (is_in_check(BLACK_PLAYER)) {
        if (!has_legal_moves(BLACK_PLAYER)) {
            printf("\nCHECKMATE! WHITE WINS!\n");
            return 1;
        } else {
            printf("\nBLACK is in CHECK!\n");
        }
    }

    return 0;
}

void show_possible_moves(int row, int col) {
    char piece = board[row][col];

    if (piece == '.') {
        printf("No piece at this position!\n");
        return;
    }

    // Check if correct player's piece
    if ((current_player == WHITE_PLAYER && !isupper(piece)) ||
        (current_player == BLACK_PLAYER && !islower(piece))) {
        printf("Not your piece!\n");
        return;
    }

    printf("Possible moves for %c at %c%d:\n",
           piece, 'a' + col, 8 - row);

    int found = 0;

    for (int tr = 0; tr < 8; tr++) {
        for (int tc = 0; tc < 8; tc++) {

            if (is_valid_move(row, col, tr, tc)) {

                char captured = board[tr][tc];

                // Make move temporarily
                board[tr][tc] = board[row][col];
                board[row][col] = '.';

                // Check if king is safe
                if (!is_in_check(current_player)) {
                    printf("-> %c%d\n", 'a' + tc, 8 - tr);
                    found = 1;
                }

                // Undo move
                undo_move(row, col, tr, tc, captured);
            }
        }
    }

    if (!found) {
        printf("No legal moves available.\n");
    }
}