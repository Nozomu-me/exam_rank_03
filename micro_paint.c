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

typedef struct rect
{
    char type;
    float x;
    float y;
    float width;
    float height;
    char caract;
}               t_rect;
void ft_putstr(char *str)
{
    int i=0;
    while(str[i]!='\0')
    {
        write(1,&str[i],1);
        i++;
    }
}
int error(FILE *file,char *str)
{
    if(file!=NULL)
        fclose(file);
    ft_putstr(str);
    return 1;
}
int in_rect(float x,float y,t_rect rect)
{
    if ((((x < rect.x) || (rect.x + rect.width < x)) || (y < rect.y)) || (rect.y + rect.height < y))
		return (0);
	if (((x - rect.x < 1.00000000) || ((rect.x + rect.width) - x < 1.00000000)) ||
		((y - rect.y < 1.00000000 || ((rect.y + rect.height) - y < 1.00000000))))
		return (2);
	return (1);
}
void draw_rect(t_zone zone, char *draw_zone,t_rect rect)
{
    int i,j,in;
    i=0;
    while(i<zone.width)
    {
        j=0;
        while(j<zone.height)
        {
            in=in_rect((float)i,(float)j,rect);
            if(in==2 || (in==1 && rect.type=='R'))
            j++;
        }
        i++;
    }

}
int main(int argc, char **argv)
{
    FILE *file;
    t_zone zone;
    t_rect rect;
    int ret,i,j;
    if (argc != 2)
        return (error(NULL,"Error: argument\n"));
    file = fopen(argv[1],"r");
    if(file==NULL)
        return (error(file,"Error: Operation file corrupted\n"));
    ret = fscanf(file,"%d %d %c",&zone.width,&zone.height,&zone.background);
    if(ret!=3)
        return (error(file,"Error: Operation file corrupted\n"));
    if((zone.width<0||zone.width>300) || (zone.height<0||zone.height>300))
        return (error(file,"Error: Operation file corrupted\n"));
    char draw_zone[zone.width*zone.height];
    i=0;
    while(i<zone.width*zone.height)
        draw_zone[i++]=zone.background;
    while((ret=fscanf(file," %c %f %f %f %f %c",&rect.type,&rect.x,&rect.y,&rect.width,&rect.height,&rect.caract))==6)
    {
        if (rect.width <= 0.0 || rect.height <= 0.0|| (rect.type != 'r' && rect.type != 'R'))
			return(error(file,"Error: Operation file corrupted\n"));
	    draw_rect(zone, draw_zone, rect);
    }
    if (ret!=-1)
        return(error(file,"Error: Operation file corrupted\n"));
    i = 0;
	while (i < zone.height)
	{
		write(1, &draw_zone[i*zone.width], zone.width);
		write(1, "\n", 1);
		i++;
	}
	fclose(file);
}