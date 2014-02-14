#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 3
#define WIDTH 3

char field[HEIGHT][WIDTH];

void set_default_values(void) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = ' ';
        }
    }
}

void show_field(void) {
    for (int i = 0; i < HEIGHT; i++) {
        printf("-------------\n");
        for (int j = 0; j < WIDTH; j++) {
            printf("| %c ", field[i][j]);
            if (j == WIDTH - 1) 
                printf("|\n"); // Никогда не пиши if в одну строку
        }
    }
    printf("-------------\n");
}

int check_win_conditions(char symb) {
    bool is_horiz_win = false;  
    bool is_vert_win = false;
    bool is_diag_win = false;

    // условие победы по горизонатли
    for (int i = 0; i < HEIGHT; i++) {
        is_horiz_win = true;
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] != symb) {
                is_horiz_win = false;
                break;
            }   
        }
        if (is_horiz_win) {
            return 1;
        }
    }

    // условие победы по вертикали
    for (int i = 0; i < WIDTH; i++) {
        is_vert_win = true;
        for (int j = 0; j < HEIGHT; j++) {
            if (field[j][i] != symb) {
                is_vert_win = false;
                break;
            }   
        }
        if (is_vert_win) {
            return 2;
        }
    }

    // условие победы по диагонали слева-направо
    for (int i = 0; i < WIDTH; i++) {
        is_diag_win = true;
        if (field[i][i] != symb) {
            is_diag_win = false;
            break;
        }
    }
    if (is_diag_win) {
        return 3;
    }

    // условие победы по диагонали справо-налево
    int j = WIDTH;
    for (int i = 0; i < WIDTH; i++) {
        j--;
        is_diag_win = true;
        if (field[i][j] != symb) {
            is_diag_win = false;
            break;
        }
    }
    if (is_diag_win) {
        return 3;
    }

    return 0;
}

int check_input(int x, int y, bool show_message = false) {
    int error_code = 0;

    if (field[x][y] == 'x') {
        error_code = 1;
    } 

    if (field[x][y] == 'o') {
        error_code = 2;
    }


    if (show_message) {
        printf("Incorrect user input. Try again.\n");    
    }
    return error_code;
}

void computer_turn(int ai_type) {
    int x, y;
    printf ("Computer turn:\n");
    if (ai_type == 1) {
        do {
            x = rand() % HEIGHT;
            y = rand() % WIDTH;
            
        } while (check_input(x, y));

        field[x][y] = 'o'; 
    } else if (ai_type == 2) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
               if (field[i][j] == ' ') {
                    field[i][j] = 'o';
                    return;
               }
            }
        }
    }
    // else... ?
}

void human_turn(int x, int y) {
    printf ("Human turn.\n");

    do {
        printf ("Enter x coord: ");
        scanf ("%d", &x);

        printf ("Enter y coord: ");
        scanf ("%d", &y);
    } while (check_input(x, y, true));

    field[x][y] = 'x';
}

int main() {
    int x, y;
    int game_state = 0;
    int ai_type;
    
    srand(time(NULL)); // Нужно выполнить 1 раз

    set_default_values();

    do {
        printf("Choose ai type (1 or 2): \n");
        scanf ("%d", &ai_type);    
    }  while (ai_type != 1 && ai_type != 2);
    
    while (!game_state) {
        human_turn(x, y);        
        show_field();
        if (check_win_conditions('x')) {
            game_state = 1;   
        }
        computer_turn(ai_type);
        show_field();
        if (check_win_conditions('o')) {
            game_state = 2;  
        }
    }

    if (game_state == 1) {
        printf("Game ended human win\n");
    }
    if (game_state == 2) {
        printf("Game ended human loose\n");
    }

    return 0;
}
