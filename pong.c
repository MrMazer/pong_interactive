// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>

#define kWIDTH 80
#define kHEIGHT 25

void print_winner(int score_1, int score_2);
void print_game_zone(int ball_position_x, int ball_position_y, int rocket_right_position,
                     int rocket_left_position);
int user_input_a(int rocket_right_position);
int user_input_z(int rocket_right_position);
int user_input_k(int rocket_left_position);
int user_input_m(int rocket_left_position);
int ball_reverse_by_rocket(int ball_position_x, int ball_position_y, int rocket_right_position,
                           int rocket_left_position, int ball_move_x);
int ball_reverse_by_wall(int ball_position_y, int ball_move_y);
int main() {
    int player_score_1 = 0, player_score_2 = 0;
    int ball_position_x = 40, ball_position_y = 13;
    int ball_move_x = 2, ball_move_y = 1;
    int rocket_left_position = 13, rocket_right_position = 13;

    while (player_score_1 != 21 && player_score_2 != 21) {  // Добавил остановку программы с помощью буквы "q"

        // render

        printf("\033[H\033[J");

        print_game_zone(ball_position_x, ball_position_y, rocket_right_position, rocket_left_position);

        printf("Players score: %02d : %02d", player_score_1, player_score_2);

        char input = getchar();
        if (input == 'q')
            break;
        else if (input == 'a' || input == 'A' || input == 'z' || input == 'Z' || input == 'k' ||
                 input == 'K' || input == 'm' || input == 'M') {
            if ((input == 'a' || input == 'A'))
                rocket_left_position = user_input_a(rocket_left_position);
            else if ((input == 'z' || input == 'Z'))
                rocket_left_position = user_input_z(rocket_left_position);
            else if ((input == 'k' || input == 'K'))
                rocket_right_position = user_input_k(rocket_right_position);
            else if ((input == 'm' || input == 'M'))
                rocket_right_position = user_input_m(rocket_right_position);
            ball_position_x += ball_move_x;
            ball_position_y += ball_move_y;

            if (ball_position_x == 0 || ball_position_x == 80) {
                // counting_score
                if (ball_position_x == 0) {
                    (player_score_2)++;

                } else if (ball_position_x == 80) {
                    (player_score_1)++;
                }
                ball_move_x = -ball_move_x;

                ball_position_x = 40;
                ball_position_y = 13;
            }
            ball_move_y = ball_reverse_by_wall(ball_position_y, ball_move_y);
            ball_move_x = ball_reverse_by_rocket(ball_position_x, ball_position_y, rocket_right_position,
                                                 rocket_left_position, ball_move_x);
        }

        else if (input == ' ') {
            //  move_ball()
            ball_position_x += ball_move_x;
            ball_position_y += ball_move_y;

            if (ball_position_x == 0 || ball_position_x == 80) {
                // counting_score
                if (ball_position_x == 0) {
                    (player_score_2)++;

                } else if (ball_position_x == 80) {
                    (player_score_1)++;
                }
                ball_move_x = -ball_move_x;

                ball_position_x = 40;
                ball_position_y = 13;
            }
            ball_move_y = ball_reverse_by_wall(ball_position_y, ball_move_y);
            ball_move_x = ball_reverse_by_rocket(ball_position_x, ball_position_y, rocket_right_position,
                                                 rocket_left_position, ball_move_x);
        }

    }  // конец while
    print_winner(player_score_1, player_score_2);
    return 0;
}

int user_input_a(int rocket_left_position) {
    if (rocket_left_position == 3)
        return rocket_left_position + 2;
    else
        return rocket_left_position - 2;
}

int user_input_z(int rocket_left_position) {
    if (rocket_left_position == 23)
        return rocket_left_position - 2;
    else
        return rocket_left_position + 2;
}

int user_input_k(int rocket_right_position) {
    if (rocket_right_position == 3)
        return rocket_right_position + 2;
    else
        return rocket_right_position - 2;
}

int user_input_m(int rocket_right_position) {
    if (rocket_right_position == 23)
        return rocket_right_position - 2;
    else
        return rocket_right_position + 2;
}

int ball_reverse_by_rocket(int ball_position_x, int ball_position_y, int rocket_right_position,
                           int rocket_left_position, int ball_move_x) {
    if ((ball_position_x == 4 || ball_position_x == 3 || ball_position_x == 5 || ball_position_x == 6) &&
        (ball_position_y == rocket_left_position - 1 || ball_position_y == rocket_left_position ||
         ball_position_y == rocket_left_position + 1)) {
        return -ball_move_x;
    } else if ((ball_position_x == 76 || ball_position_x == 77 || ball_position_x == 75 ||
                ball_position_x == 74) &&
               (ball_position_y == rocket_right_position - 1 || ball_position_y == rocket_right_position ||
                ball_position_y == rocket_right_position + 1)) {
        return -ball_move_x;
    } else
        return ball_move_x;
}
int ball_reverse_by_wall(int ball_position_y, int ball_move_y) {
    if (ball_position_y == 24 || ball_position_y == 2 || ball_position_y == 1 || ball_position_y == 25)
        return -ball_move_y;
    else
        return ball_move_y;
}
void print_game_zone(int ball_position_x, int ball_position_y, int rocket_right_position,
                     int rocket_left_position) {
    char field_boreder = '|';
    char field_top_n_bottom = '-';
    char space = ' ';
    char rocket_part = '#';
    char ball = '*';
    for (int index_y = 1; index_y <= kHEIGHT; ++index_y) {
        for (int index_x = 1; index_x < kWIDTH; ++index_x) {
            if ((index_y == 1) || (index_y == kHEIGHT)) {  // верх низ
                printf("%c", field_top_n_bottom);
            } else if (index_x == kWIDTH / 2 && index_y == 13) {
                printf("+");
            } else if ((index_x == 1) || (index_x == kWIDTH / 2) ||
                       (index_x == kWIDTH - 1)) {  // бока и середина
                printf("%c", field_boreder);
            } else if (index_x == 4) {  // rocetka 1
                if ((index_y == rocket_left_position - 1) || (index_y == rocket_left_position) ||
                    (index_y == rocket_left_position + 1)) {
                    printf("%c", rocket_part);
                } else {
                    printf("%c", space);
                }
            } else if (index_x == 76) {  // rocetka 2
                if ((index_y == rocket_right_position - 1) || (index_y == rocket_right_position) ||
                    (index_y == rocket_right_position + 1)) {
                    printf("%c", rocket_part);
                } else {
                    printf("%c", space);
                }

            } else if ((index_x == ball_position_x) && (index_y == ball_position_y)) {  // мяч
                printf("%c", ball);
            } else {
                printf("%c", space);
            }
        }
        printf("\n");
    }
}

void print_winner(int player_score_1, int player_score_2) {
    if (player_score_1 == 21 || player_score_2 == 21) {
        if (player_score_1 == 21) {
            printf("PLAYER 1 WINNER! \nRESULT - %02d:%02d", player_score_1, player_score_2);
        } else {
            printf("PLAYER 2 WINNER! \nRESULT - %02d:%02d", player_score_1, player_score_2);
        }
    } else {
        printf("GAME OVER \nRESULT - %02d:%02d", player_score_1, player_score_2);
    }
}
