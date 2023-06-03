#include <stdio.h>
#include <stdlib.h>
#include "pr1.h"


int main()
{
    int x_from = 0, y_from = 0, x_to = 0, y_to = 0;
    int color = 1; // 1 = red, 2 = green
    int x_prev, y_prev;
    print_board();

    while (x_from != -1 && y_from != -1 && x_to != -1 && y_to != -1){
        if (color == 1){ // RED'S MOVE
            printf("RED's move: ");
            scanf("%d %d %d %d", &x_from, &y_from, &x_to, &y_to);
            if (check_move(1, x_from, y_from, x_to, y_to) == VALID_MOVE){
                x_prev = x_from;
                y_prev = y_from;
                if (check_jump(x_from, y_from, x_to, y_to) == VALID_MOVE){
                    helper(1, x_from, y_from, x_to, y_to);
                    if (is_jumper(x_prev, y_prev, x_to, y_to) == TRUE) {
                        printf("RED's move: ");
                        scanf("%d %d %d %d", &x_from, &y_from, &x_to, &y_to);
                        while (check_move(1, x_from, y_from, x_to, y_to) == INVALID_MOVE) {
                            printf("RED's move: ");
                            scanf("%d %d %d %d", &x_from, &y_from, &x_to, &y_to);
                        }
                        helper(1, x_from, y_from, x_to, y_to);
                        x_prev = x_from;
                        y_prev = y_from;
                        if (check_jump(x_from, y_from, x_to, y_to) == TRUE && is_jumper(x_prev, y_prev, x_to, y_to) == TRUE){
                            color = 1;
                        } else { color = 2;}
                    } else {
                        color = 2;
                    }

                } else {
                    helper(1, x_from, y_from, x_to, y_to);
                    color = 2;
                }

            } else if (x_from == -1 && y_from == -1 && x_to == -1 && y_to == -1){
                exit(0);
            } else {
                color = 1;
                printf("INVALID MOVE.  TRY AGAIN!!\n");
            }

        } else if (color == 2){ // GREEN'S MOVE
            printf("GREEN's move: ");
            scanf("%d %d %d %d", &x_from, &y_from, &x_to, &y_to);
            if (check_move(2, x_from, y_from, x_to, y_to) == VALID_MOVE){
                x_prev = x_from;
                y_prev = y_from;
                if (check_jump(x_from, y_from, x_to, y_to) == VALID_MOVE){
                    helper(2, x_from, y_from, x_to, y_to);
                    if (is_jumper(x_prev, y_prev, x_to, y_to) == TRUE) {
                        printf("GREEN's move: ");
                        scanf("%d %d %d %d", &x_from, &y_from, &x_to, &y_to);
                        while (check_move(2, x_from, y_from, x_to, y_to) == INVALID_MOVE) {
                            printf("RED's move: ");
                            scanf("%d %d %d %d", &x_from, &y_from, &x_to, &y_to);
                        }
                        helper(2, x_from, y_from, x_to, y_to);
                        x_prev = x_from;
                        y_prev = y_from;
                        if (check_jump(x_from, y_from, x_to, y_to) == TRUE && is_jumper(x_prev, y_prev, x_to, y_to) == TRUE){
                            color = 2;
                        } else { color = 1;}
                    }  else {
                        color = 1;
                    }

                } else {
                    helper(2, x_from, y_from, x_to, y_to);
                    color = 1;
                }
            } else if (x_from == -1 && y_from == -1 && x_to == -1 && y_to == -1){
                exit(0);
            } else {
                color = 2;
                printf("INVALID MOVE.  TRY AGAIN!!\n");
            }
        }

    }

}

int // checks 1 unit around piece
check_neighbor(int x_from, int y_from, int x_to, int y_to){
    int x_distance = abs(x_from-x_to);
    int y_distance = abs(y_from-y_to);

    if (x_to != x_from && x_distance <= 2 && y_distance == 1 && the_board[y_to][x_to] == 7){
        return VALID_MOVE;
    } else {
        return INVALID_MOVE;
    }
}

int
check_jump(int x_from, int y_from, int x_to, int y_to){
    int x_distance = abs(x_from-x_to);
    int y_distance = abs(y_from-y_to);

    if (x_distance <= 4 && y_distance <= 2 && x_from != x_to && the_board[y_to][x_to] == 7){
        if (the_board[y_from-1][x_from-1] != 7 && x_to == x_from-2 && y_to == y_from-2 && the_board[y_to][x_to] == 7){ // NW
            return VALID_MOVE;
        } else if (the_board[y_from][x_from-2] != 7 && x_to == x_from-4 && y_to == y_from && the_board[y_to][x_to] == 7){ // W
            return VALID_MOVE;
        } else if (the_board[y_from+1][x_from-1] != 7 && x_to == x_from-2 && y_to == y_from+2 && the_board[y_to][x_to] == 7){ // SW
            return VALID_MOVE;
        } else if (the_board[y_from+1][x_from+1] != 7 && x_to == x_from+2 && y_to == y_from+2 && the_board[y_to][x_to] == 7){ // SE
            return VALID_MOVE;
        } else if (the_board[y_from][x_from+2] != 7 && x_to == x_from+4 && y_to == y_from && the_board[y_to][x_to] == 7){ // E
            return VALID_MOVE;
        } else if (the_board[y_from-1][x_from+1] != 7 && x_to == x_from+2 && y_to == y_from-2 && the_board[y_to][x_to] == 7){ // NE
            return VALID_MOVE;
        } else {
            return INVALID_MOVE;
        }
    } else {
        return INVALID_MOVE;
    }
}

// Checks validity of move
int
check_move(int color, int x_from, int y_from, int x_to, int y_to){
    if (check_jump(x_from, y_from, x_to, y_to) == VALID_MOVE && the_board[y_from][x_from] == color){
        // jump move
    } else if (check_neighbor(x_from, y_from, x_to, y_to) == VALID_MOVE && the_board[y_from][x_from] == color){
        // neighbor move
    } else {
        return INVALID_MOVE;
    }
    return VALID_MOVE;


}

// Checks the 6 neighboring spaces
int
is_jumper(int x_from, int y_from, int x_to, int y_to){
    if (check_jump(x_to, y_to, x_to-2, y_to-2) == VALID_MOVE && x_to-2 != x_from && y_to-2 != y_from){ // NW
    } else if (check_jump(x_to, y_to, x_to-4, y_to) == VALID_MOVE && x_to-4 != x_from && y_to != y_from){ // W
    } else if (check_jump(x_to, y_to, x_to-2, y_to+2) == VALID_MOVE && x_to-2 != x_from && y_to+2 != y_from){ // SW
    } else if (check_jump(x_to, y_to, x_to+2, y_to+2) == VALID_MOVE && x_to+2 != x_from && y_to+2 != y_from){ // SE
    } else if (check_jump(x_to, y_to, x_to+4, y_to) == VALID_MOVE && x_to+4 != x_from && y_to != y_from){ // E
    } else if (check_jump(x_to, y_to, x_to+2, y_to-2) == VALID_MOVE && x_to+2 != x_from && y_to-2 != y_from){ // NE
    } else {
        return FALSE;
    }
    return TRUE;

}

int helper(int color, int x_from, int y_from, int x_to, int y_to){
    if (color == 1){
        the_board[y_from][x_from] = 7;
        the_board[y_to][x_to] = 1;
        print_board();
    } else if (color == 2){
        the_board[y_from][x_from] = 7;
        the_board[y_to][x_to] = 2;
        print_board();
    }
    return VALID_MOVE;

}

void
print_board()
{
    int i, j, k = 0;
    for (i = 0; i < BOARD_SIZE_Y; i++) {
        if (i == 0){
            for (k = 0; k < BOARD_SIZE_X; k++){
                printf("\t%d", k);
            }
            printf("\n");
        }
        printf("%d\t", i);
        for (j = 0; j < BOARD_SIZE_X; j++) {
            if (the_board[i][j] == 1){
                printf("R\t");
            } else if (the_board[i][j] == 2){
                printf("G\t");
            } else if (the_board[i][j] == 7){
                printf("-\t");
            } else if (the_board[i][j] == 0){
                printf("\t");
            }
        }
        printf("\n");
    }
}
