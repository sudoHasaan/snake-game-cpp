//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <cmath>
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * */

double startx = 320, starty = 400;
double cirx = 300, ciry = 300, a, b, c, d, e = 0, f = 0;
int x = 2, m = 300, n = 300, num = 4, timer1 = 70, timer2 = 70, timer3 = 70, timer4 = 70, timer5 = 66, timer6 = -195,timerh=130;
int snake[2000][2] = {{290, 300}, {280, 300}};
bool l = true, r = true, up = true, down = true, gen = true, gameover = true, over = true, power = true;
int foodx[6][2] = {};
int hurdlex[1][3] = {};
int score;


// food respawning
void food(int num)
{
    do
    {
        gen = true;
        foodx[num][0] = (rand() % 55 + 4);
        foodx[num][1] = (rand() % 49 + 4);
        for (int i = 0; i < num; i++)
        {
            if (foodx[num][0] == foodx[i][0] || foodx[num][1] == foodx[i][1] || abs(foodx[num][0] - foodx[i][0]) == abs(foodx[num][1] - foodx[i][1]) || (foodx[num][0] + foodx[i][0]) == (foodx[num][1] + foodx[i][1]))
            {
                gen = false;
            }
        }
       
        

    } while (gen == false);
}

// food timer
void foodgen(int m)
{
    timer1 += 1;
    if (timer1 >= 70)
    {
        food(0);
        timer1 = 0;
    }
    timer2 += 1;
    if (timer2 >= 70)
    {
        food(1);
        timer2 = 0;
    }
    timer3 += 1;
    if (timer3 >= 70)
    {
        food(2);
        timer3 = 0;
    }
    timer4 += 1;
    if (timer4 >= 70)
    {
        food(3);
        timer4 = 0;
    }
    timer5 += 1;
    if (timer5 >= 70)
    {
        food(4);
        timer5 = 0;
    }
    timer6 += 1;
    if (timer6 >= 70)
    {
        food(5);
        timer6 = -195;
        power = false;
    }
    if ((cirx == foodx[0][0] * 10 && ciry == foodx[0][1] * 10) || (snake[0][0] == foodx[0][0] * 10 && snake[0][1] == foodx[0][1] * 10))
    {
        food(0);
        timer1 = 0;
        x++;
        score += 5;
    }
    if ((cirx == foodx[1][0] * 10 && ciry == foodx[1][1] * 10) || (snake[0][0] == foodx[1][0] * 10 && snake[0][1] == foodx[1][1] * 10))
    {
        food(1);
        timer2 = 0;
        x++;
        score += 5;
    }
    if ((cirx == foodx[2][0] * 10 && ciry == foodx[2][1] * 10) || (snake[0][0] == foodx[2][0] * 10 && snake[0][1] == foodx[2][1] * 10))
    {
        food(2);
        timer3 = 0;
        x++;
        score += 5;
    }
    if ((cirx == foodx[3][0] * 10 && ciry == foodx[3][1] * 10) || (snake[0][0] == foodx[3][0] * 10 && snake[0][1] == foodx[3][1] * 10))
    {
        food(3);
        timer4 = 0;
        x++;
        score += 5;
        glutPostRedisplay();
    }
    if ((cirx == foodx[4][0] * 10 && ciry == foodx[4][1] * 10) || (snake[0][0] == foodx[4][0] * 10 && snake[0][1] == foodx[4][1] * 10))
    {
        food(4);
        timer5 = 0;
        x++;
        score += 5;
    }
    if ((cirx == foodx[5][0] * 10 && ciry == foodx[5][1] * 10) || (snake[0][0] == foodx[5][0] * 10 && snake[0][1] == foodx[5][1] * 10))
    {
        power = true;
        timer6 = -195;
        x++;
        score += 20;
    }
    // once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, foodgen, 0);
}



void Display()
{
    // set the background color using function glClearColotgr.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

    if (gameover == true)
    {
        glClearColor(0.2 /*Red Component*/, 0.0 /*Green Component*/,
                     0.2 /*Blue Component*/, 0 /*Alpha component*/);             // Red==Green==Blue==1 --> White Colour
        glClear(GL_COLOR_BUFFER_BIT);                                            // Update the colors
        DrawString(500, 610, "Score: " + to_string(score), colors[WHITE_SMOKE]); // this will print given string at x=50 , y=600
        // DrawString( 50, 570, "You will use these to make your game", colors[DARK_RED]); // this will print given string at x=50 , y=570

        // grid display
        for (int x = 0; x < 641; x += 10)
        {
            for (int y = 0; y < 581; y += 10)
            {
                if (x == 0 || x == 630 || x == 10 || x == 640 || y == 0 || y == 10 || y == 580 || y == 570)
                {
                    DrawSquare(x, y, 10, colors[DARK_GRAY]);
                }
                else
                {
                    DrawSquare(x, y, 10, colors[BLACK]);
                }
            }
        }
        //                    v1( x,y )   v2( x,y )  , v3( x,y )
        // DrawTriangle( 300, 50 , 500, 50 , 400 , 250, colors[MISTY_ROSE] );  // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)

        // DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
        // DrawLine( 130 , 50 ,  130 , 80 , 30 , colors[] );

        // snake draw
        DrawCircle(cirx + 5, ciry + 5, 5, colors[LIME_GREEN]);
        for (int i = 0; i < x; i++)
        {
            DrawSquare(snake[i][0], snake[i][1], 10, colors[YELLOW]);
        }

        // food display

        for (int i = 0; i <= 5; i++)
        {
            if (i <= 4)
            {
                DrawCircle(foodx[i][0] * 10 + 5, foodx[i][1] * 10 + 5, 5, colors[ORANGE_RED]);
            }
            else if (i == 5 && power == false)
            {
                DrawCircle(foodx[i][0] * 10 + 5, foodx[i][1] * 10 + 5, 5, colors[PURPLE]);
            }
        }

        // Game over condition
        for (int i = 0; i < x; i++)
        {
            if (cirx == snake[i][0] && ciry == snake[i][1])
            {
                gameover = false;
            }
        }
        
        
    }
    else
    {
        glClearColor(0 /*Red Component*/, 0.0 /*Green Component*/,
                     0.0 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
        glClear(GL_COLOR_BUFFER_BIT);                                // Update the colors
        sleep(1);
        DrawString(250, 300, " GAME OVER \n", colors[YELLOW]);
        DrawString(250, 340, "Your Score: " + to_string(score), colors[YELLOW_GREEN]);
    }

    glutSwapBuffers(); // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
    {
        // Prevent movement if already moving left
        if (l == false)
        {
            return; // Already moving left, ignore key press
        }
        
        if (cirx >= 30)
        {
            if (cirx <= snake[0][0])
            {

                a = cirx;
                b = ciry;
                cirx -= 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
                l = false, r = true, up = true, down = true;
            }
        }
        else
        {
            if (cirx <= snake[0][0])
            {
                cirx = 620;
                a = cirx;
                b = ciry;
                cirx -= 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
                l = false, r = true, up = true, down = true;
            }
        }
    }

    else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
    {
        // Prevent movement if already moving right
        if (r == false)
        {
            return; // Already moving right, ignore key press
        }
        
        if (cirx <= 610)
        {

            if (cirx >= snake[0][0])
            {

                a = cirx;
                b = ciry;
                cirx += 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
                l = true, r = false, up = true, down = true;
            }
        }
        else
        {
            if (cirx >= snake[0][0])
            {
                cirx = 20;
                a = cirx;
                b = ciry;
                cirx += 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
                l = true, r = false, up = true, down = true;
            }
        }
    }

    else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/
    {
        // Prevent movement if already moving up
        if (up == false)
        {
            return; // Already moving up, ignore key press
        }
        
        if (ciry <= 550)
        {

            if (ciry >= snake[0][1])
            {

                b = ciry;
                a = cirx;
                ciry += 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
                l = true, r = true, up = false, down = true;
            }
        }
        else
        {
            if (ciry >= snake[0][1])
            {
                ciry = 20;
                b = ciry;
                a = cirx;
                ciry += 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
                l = true, r = true, up = false, down = true;
            }
        }
    }

    else if (key == GLUT_KEY_DOWN) /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/
    {
        // Prevent movement if already moving down
        if (down == false)
        {
            return; // Already moving down, ignore key press
        }
        
        if (ciry >= 30)
        {

            if (ciry <= snake[0][1])
            {
                b = ciry;
                a = cirx;
                ciry -= 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
                l = true, r = true, up = true, down = false;
            }
        }
        else
        {
            if (ciry <= snake[0][1])
            {
                ciry = 560;
                b = ciry;
                a = cirx;
                ciry -= 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
                l = true, r = true, up = true, down = false;
            }
        }
    }

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
    glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y)
{
    if (key == KEY_ESC /* Escape key ASCII*/)
    {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key == 'r' /* Escape key ASCII*/)
    {
        // exit(1); // exit the program when escape key is pressed.
        // aswangle+=90;
    }

    else if (int(key) == 13)
    {
    }

    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
// continous movement
void Timer(int m)
{
    if (r == false)
    {
        if (cirx <= 610)
        {
            if (cirx >= snake[0][0])
            {
                a = cirx;
                cirx += 10;
                b = ciry;
                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
            }
        }
        else
        {
            if (cirx >= snake[0][0])
            {
                cirx = 20;
                a = cirx;
                b = ciry;
                cirx += 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
            }
        }
    }
    else if (l == false)
    {
        if (cirx >= 30)
        {
            if (cirx <= snake[0][0])
            {
                a = cirx;
                b = ciry;
                cirx -= 10;
                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
            }
        }
        else
        {
            if (cirx <= snake[0][0])
            {
                cirx = 620;
                a = cirx;
                b = ciry;
                cirx -= 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
            }
        }
    }
    else if (up == false)
    {
        if (ciry <= 550)
        {
            if (ciry >= snake[0][1])
            {
                b = ciry;
                a = cirx;
                ciry += 10;
                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
            }
        }
        else
        {
            if (ciry >= snake[0][1])
            {
                ciry = 20;
                b = ciry;
                a = cirx;
                ciry += 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
            }
        }
    }
    else if (down == false)
    {
        if (ciry >= 30)
        {
            if (ciry <= snake[0][1])
            {
                b = ciry;
                ciry -= 10;
                a = cirx;
                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
            }
        }
        else
        {
            if (ciry <= snake[0][1])
            {
                ciry = 560;
                b = ciry;
                a = cirx;
                ciry -= 10;

                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (j == 0)
                        {
                            c = snake[i][j];
                            snake[i][j] = a;
                            a = c;
                        }
                        else
                        {
                            d = snake[i][j];
                            snake[i][j] = b;
                            b = d;
                        }
                    }
                }
            }
        }
    }
    // implement your functionality here
    glutPostRedisplay();
    // once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char *argv[])
{
    srand(time(0));
    int width = 650, height = 650; // i have set my window size to be 800 x 600
    InitRandomizer();              // seed the random number generator...
    glutInit(&argc, argv);         // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50);               // set the initial position of our window
    glutInitWindowSize(width, height);            // set the size of our window
    glutCreateWindow("PF's Snake Game");          // set the title of our game window
    SetCanvasSize(width, height);                 // set the number of pixels...

    // Register your functions to the library,
    // you are telling the library names of function to call for different tasks.
    // glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display);          // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys);   // tell library which function to call for printable ASCII characters
    // This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);
    glutTimerFunc(5.0 / FPS, foodgen, 0);
    
    //  now handle the control to library and it will call our registered functions when
    //  it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */
