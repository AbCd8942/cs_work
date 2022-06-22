//中点Bresenham算法生成直线
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include<iostream>
#define WIDTH    500        //窗口宽度
#define HEIGHT    500        //窗口高度
void Init(){//初始化
    glClearColor(1.0f,1.0f,1.0f,1.0f);    //设置背景颜色，完全不透明
    glColor3f(1.0f,0.0f,0.0f);    //设置画笔颜色
    glMatrixMode(GL_PROJECTION);            //设置投影
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);    //设置投影区域
    }
 void MidpointBresenham(int x0,int y0,int x1,int y1) {  //中点Bresenham算法画线
    int dx,dy,d,UpIncre,DownIncre,x,y;
    if(x0>x1){
        x=x1;x1=x0;x0=x;
        y=y1;y1=y0;y0=y;
    }
    x = x0,y = y0;
    dx = x1-x0;
    dy = y1-y0;
    if(dy>0&&dy<=dx){    //0<k<=1
        d = dx-2*dy;
        UpIncre = 2*dx-2*dy;
        DownIncre = -2*dy;
        while(x<=x1){
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
            x++;
            if(d<0){
                y++;
                d+=UpIncre;
            }
            else
                d+=DownIncre;
        }
    }
    else if((dy>=(-dx))&&dy<=0) //-1<=k<=0
    {
        d=dx-2*dy;
        UpIncre=-2*dy;
        DownIncre=-2*dx-2*dy;
        while(x<=x1)
        {
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
            x++;
            if(d>0)
             {
                 y--;
                 d+=DownIncre;
             }
             else d+=UpIncre;
        }
    }
     else if(dy<(-dx)) //k<-1
     {
        d=-dy-2*dx;
        UpIncre=2*dx+2*dy;
         DownIncre=2*dx;
         while(y>=y1)
        {
             glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
            y--;
             if(d<0)
            {
               x++;
                d-=UpIncre;
             }
             else d-=DownIncre;
        }
    }
    else //k>1和k不存在
    {
        d=dy-2*dx;
         UpIncre=2*dy-2*dx;
        DownIncre=-2*dx;
        while(y<=y1)
         {
             glBegin(GL_POINTS);
           glVertex2i(x,y);
            glEnd();
             y++;
            if(d<0)
            {
                 x++;
                d+=UpIncre;
            }
             else d+=DownIncre;
        }
    }
}
 void Display()    //显示函数
{
     glClear(GL_COLOR_BUFFER_BIT);    //清空颜色堆栈
    MidpointBresenham(100,200,200,100);    //画直线
     glFlush();    //清空缓冲区指令
 }
 int main(int argc,char** argv)
 {
    glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //初始化显示模式
    glutInitWindowSize(WIDTH,HEIGHT);    //设置窗口尺寸
     glutInitWindowPosition(200,100);    //设置窗口位置
    glutCreateWindow("Bresenham画直线");    //创建窗口
    glutDisplayFunc(Display);    //注册显示函数
     Init();        //初始化
     glutMainLoop();    //进入程序循环
     return 0;
}
