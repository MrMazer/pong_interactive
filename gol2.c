#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 25

void draw(char field[WIDTH][HEIGHT]);
void evaluate(char field[WIDTH][HEIGHT]);
void getInitialConfiguration(char field[WIDTH][HEIGHT]);
void adjustSpeed(int *speed);

int main()
{
    srand(time(0));
    char field[WIDTH][HEIGHT];
    int sleep_time;

    getInitialConfiguration(field);
    adjustSpeed(&sleep_time);

    struct timespec req;
    req.tv_sec = sleep_time;
    req.tv_nsec = 0;

    while (1)
    {
        draw(field);
        evaluate(field);
        nanosleep(&req, NULL);
    }

    return 0;
}

void getInitialConfiguration(char field[WIDTH][HEIGHT])
{
    printf("Введите начальную конфигурацию поля (0 - пусто, 1 - живая клетка):\n");
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int state;
            if (scanf("%d", &state) != 1 || (state != 0 && state != 1))
            {
                printf("Неверный ввод. Пожалуйста, введите 0 или 1.\n");
                exit(1);
            }
            field[x][y] = state ? 1 : 0;
        }
    }
}

void adjustSpeed(int *speed)
{
    printf("Введите скорость (в секундах) между поколениями: ");
    if (scanf("%d", speed) != 1 || *speed < 0)
    {
        printf("Неверный ввод. Пожалуйста, введите положительное целое число.\n");
        exit(1);
    }
}

void draw(char field[WIDTH][HEIGHT])
{
    printf("\033[H");
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            printf(field[x][y] ? "■" : " ");
        }
        printf("\n");
    }
}

void evaluate(char field[WIDTH][HEIGHT])
{
    char newField[WIDTH][HEIGHT];

    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            int lives = 0;
            for (int xr = x - 1; xr <= x + 1; xr++)
            {
                for (int yr = y - 1; yr <= y + 1; yr++)
                {
                    if (xr == x && yr == y) continue; // Skip the cell itself
                    int nx = (xr + WIDTH) % WIDTH;
                    int ny = (yr + HEIGHT) % HEIGHT;
                    if (field[nx][ny])
                    {
                        lives++;
                    }
                }
            }

            if (field[x][y])
            {
                newField[x][y] = (lives == 2 || lives == 3) ? 1 : 0;
            }
            else
            {
                newField[x][y] = (lives == 3) ? 1 : 0;
            }
        }
    }

    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            field[x][y] = newField[x][y];
        }
    }
}
