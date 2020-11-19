#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct rect
{
    int width;
    int height;
    char background;
    char type;
    float x;
    float y;
    float rect_width;
    float rect_height;
    char c;
}rect;