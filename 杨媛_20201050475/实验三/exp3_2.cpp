//改进的Bresenham算法
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include<iostream>
using namespace std;
void ProBresenham(int x0, int y0, int x1, int y1){
	int x, y, dx, dy, e;
	dx = x1 - x0;
	dy = y1 - y0;
	e = -dx;
	x = x0;
	y = y0;
	while (x <= x1) {
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		x++;
		e = e + 2 * dy;
		if (e > 0) {
			y++;
			e = e - 2 * dx;
		}
	}
}
void Display(){//显示函数
	glClear(GL_COLOR_BUFFER_BIT);    //清空颜色堆栈
	ProBresenham(100,100,400,400);//画直线
	glFlush();    //清空缓冲区指令
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //初始化显示模式
	glutInitWindowSize(600, 600);    //设置窗口尺寸
	glutInitWindowPosition(200, 100);    //设置窗口位置
	glutCreateWindow("改进Bresenham算法");    //创建窗口
	glutDisplayFunc(Display);    //注册显示函数
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    //设置背景颜色，完全不透明
	glColor3f(1.0f, 0.0f, 0.0f);    //设置画笔颜色
	glMatrixMode(GL_PROJECTION);            //设置投影
	gluOrtho2D(0.0, 600, 0.0, 600);    //设置投影区域
	glutMainLoop();    //进入程序循环
	return 0;
}
