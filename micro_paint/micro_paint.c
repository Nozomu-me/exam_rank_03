#include "micro_paint.h"

void ft_putstr(char *s)
{
    int i=0;
    while(s[i]!='\0')
    {
        write(1,&s[i],1);
        i++;
    }
}

int error(char *s,FILE *file)
{
    if(file!=NULL)
        fclose(file);
    ft_putstr(s);
    return 1;
}

int ft_check(int i,int j,rect rect)
{
    if (((i < rect.x || (rect.x + rect.rect_width < i))
		|| (j < rect.y)) || (rect.y + rect.rect_height < j))
		return (0);
	if (((i - rect.x < 1.00000000) || ((rect.x + rect.rect_width) - i < 1.00000000)) ||
	((j - rect.y < 1.00000000 || ((rect.y + rect.rect_height) - j < 1.00000000))))
		return (2);
    if((i<=(rect.x + rect.rect_width) && i>=rect.x) && (j<=(rect.y + rect.rect_height) && (j>=rect.y)))
        return 1;
	return (3);
}
void ft_draw(rect rect,char *draw)
{
    int i=0;
    while(i<rect.height)
    {
        int j=0;
        while(j<rect.width)
        {
            int check=ft_check((float)j,(float)i,rect);
            if(check==2 && rect.type=='r')
                draw[i*rect.width + j]=rect.c;
            else if(( check==2 || check==1) && rect.type=='R')
                draw[i*rect.width + j]=rect.c;
            j++;
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    if(argc!=2)
        return error("Error: argument\n",NULL);
    FILE *file;
    file = fopen(argv[1],"r");
    if(file == NULL)
        return error("Error: Operation file corrupted\n",file);
    int ret;
    rect rect;
    ret = fscanf(file,"%d %d %c ",&rect.width,&rect.height,&rect.background);
    if(ret!=3 || rect.width<0 || rect.width>300 || rect.height<0 || rect.width>300)
        return error("Error: Operation file corrupted\n",file);
    char draw[rect.width*rect.height];
    int i=0;
    while(i<rect.width*rect.height)
    {
        draw[i]=rect.background;
        i++;
    }
    while((ret=fscanf(file,"%c %f %f %f %f %c ",&rect.type,&rect.x,&rect.y,&rect.rect_width,&rect.rect_height,&rect.c))==6)
    {
        if(rect.rect_width<=0 || rect.rect_height<=0)
            return error("Error: Operation file corrupted\n",file);
        ft_draw(rect,draw);
    }
    if(ret!=-1)
        return error("Error: Operation file corrupted\n",file);
    i=0;
    while(i<rect.height)
    {
        write(1,&draw[i*rect.width],rect.width);
        write(1,"\n",1);
        i++;
    }
}