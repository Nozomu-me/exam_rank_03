#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
typedef struct zone
{
    int width;
    int height;
    char background;
}               t_zone;

typedef struct circle
{
    char type;
    float  x;
    float  y;
    float radius;
    char  c;

}              t_circle;
void ft_putstr(char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		write(1,&str[i],1);
		i++;
	}
}
int  check_in_circle(float x, float y, t_circle *circle)
{
	float	distance;

	distance = sqrtf(powf(x - circle->x, 2.) + powf(y - circle->y, 2.));
	if (distance - circle->radius<=0)
	{
		if ((circle->radius - distance) < 1.00000000)
			return (2);
		return (1);
	}
	return (0);
}

void draw_circle(t_zone *zone, char *drawing, t_circle *circle)
{
	int	y;
	int	x;
	int	in_circle;

	y = 0;
	while (y < zone->height)
	{
		x = 0;
		while (x < zone->width)
		{
			in_circle = check_in_circle((float)x, (float)y, circle);
			if (circle->type == 'C' && in_circle != 0)
				drawing[(y * zone->width) + x] = circle->c;
            if (circle->type == 'c' && in_circle==2)
				drawing[(y * zone->width) + x] = circle->c;
			x++;
		}
		y++;
	}
}
int  error(FILE *file,char *str)
{
	if(file)
		fclose(file);
	ft_putstr(str);
	return 1;
}
int main(int argc, char **argv)
{
    t_circle circle;
    t_zone zone;
    FILE *file;
	int ret;
	if (argc != 2)
		error(NULL,"Error: argument\n");
    file=fopen(argv[1],"r");
    fscanf(file,"%d %d %c",&zone.width,&zone.height,&zone.background);
    if ((zone.width<0 && zone.width>300) || (zone.height<0 && zone.height>300))
        error(file,"Error: Operation file corrupted\n");
    char drawing_zone[zone.width*zone.height];
    int i=0;
    while(i<zone.width*zone.height)
        drawing_zone[i++]=zone.background;
    while(fscanf(file," %c %f %f %f %c",&circle.type,&circle.x,&circle.y,&circle.radius,&circle.c)==5)
    {
        if (circle.radius <= 0.00000000 || (circle.type != 'c' && circle.type != 'C'))
			error(file,"Error: Operation file corrupted\n");
		draw_circle(&zone, drawing_zone, &circle);
    }
    i = 0;
	while (i < zone.height)
	{
		write(1, &drawing_zone[i*zone.width], zone.width);
		write(1, "\n", 1);
		i++;
	}
	fclose(file);
}