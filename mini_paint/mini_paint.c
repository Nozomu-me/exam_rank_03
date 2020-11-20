#include "mini_paint.h"

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
int ft_check(float x,float y,cercle cercle)
{
    float dist = sqrt((x-cercle.x)*(x-cercle.x)+(y-cercle.y)*(y-cercle.y));
    if(dist<=cercle.radius)
    {
        if(cercle.radius-dist<1.0)
            return 2;
        return 1;
    }
    return 0;
}
void ft_draw(cercle cercle,char *draw)
{
    int i=0;
    while(i<cercle.height)
    {
        int j=0;
        while(j<cercle.width)
        {
            int check=ft_check((float)j,(float)i,cercle);
            if(check==2 && cercle.type=='c')
                draw[i*cercle.width + j]=cercle.c;
            if(check!=0 && cercle.type=='C')
                draw[i*cercle.width + j]=cercle.c;
            j++;
        }
        i++;
    }
}
int main(int argc,char **argv)
{
    if(argc!=2)
        return error("error:argument\n",NULL);
    FILE *file;
    file = fopen(argv[1],"r");
    if(file == NULL)
        return error("error\n",file);
    cercle cercle;
    int ret;
    ret = fscanf(file,"%d %d %c ",&cercle.width,&cercle.height,&cercle.bachground);
    if (ret!=3)
        return error("error\n",file);
    if(cercle.width<0||cercle.width>300 || cercle.height<0||cercle.height>300)
        return error("error\n",file);
    char draw[cercle.width*cercle.height];
    int i=0;
    while(i<cercle.width*cercle.height)
    {
        draw[i]=cercle.bachground;
        i++;
    }
    while((ret = fscanf(file,"%c %f %f %f %c ",&cercle.type,&cercle.x,&cercle.y,&cercle.radius,&cercle.c))==5)
    {
        if(cercle.radius<=0)
            return error("error\n",file);
        ft_draw(cercle,draw);
    }
    if(ret!=-1)
        return error("error\n",file);
    i=0;
    while(i<cercle.height)
    {
        write(1,&draw[i*cercle.width],cercle.width);
        write(1,"\n",1);
        i++;
    }
    return 0;
}