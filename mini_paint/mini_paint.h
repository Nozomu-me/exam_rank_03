#ifndef MINI_PAINT_H
#define MINI_PAINT_H

#include<unistd.h>
#include<stdio.h>
#include<math.h>

typedef struct cercle
{
    int width;
    int height;
    char bachground;
    char type;
    float x;
    float y;
    float radius;
    char c;
}cercle;

#endif