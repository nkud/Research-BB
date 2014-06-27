/*
 * =====================================================================================
 *
 *       Filename:  Terminal.h
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU
 *
 * =====================================================================================
 */


#ifndef ___TERMINAL_S
#define ___TERMINAL_S

#include <iostream>

#define ESC             "\033["

#define TERMINAL_CLEAR          std::cout<<"\033[2J";
#define TERMINAL_LOCATION(x,y)  std::cout<<"\033["<<x<<";"<<y<<"H";

#define CLEAR_RIGHT     ESC"0K"
#define REVERSE         "\033[7m"
#define STANDARD        "\033[0m"
#define UNDERLINE       "\033[4m"
#define RED             "\033[31m"
#define GREEN           "\033[32m"
#define BLUE            "\033[34m"
#define CYAN            "\033[36m"
#define WHITE           "\033[37m"
#define WHITE_BG        "\033[47m"
#define BLUE_BG         "\033[44m"
#define RED_BG          "\033[41m"
#define GREEN_BG        "\033[42m"
#define BLACK_BG        "\033[40m"
#define CLR_BG          "\033[49m"
#define CLR_ST          "\033[39m"
#define CURSOR_HIDE     "\033[>5h"
#define CURSOR_CLEAR    std::cout<<CURSOR_HIDE;

#endif
