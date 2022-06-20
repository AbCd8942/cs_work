#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
//DDA算法生成直线段
void DDA_Line(int x1, int y1, int x2, int y2) {
	double dx, dy, e, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	dx /= e;
	dy /= e;
	x = x1;
	y = y1;
	for (int i = 0; i < e; i++) {
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex2i(int(x + 0.5), int(y + 0.5));
		glEnd();
		glFlush();
		x += dx;
		y += dy;
	}
}
void display(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	DDA_Line(100, 400, 250, 300);
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DDA_line");
	glutDisplayFunc(display);
	glColor3f(0.0, 0.0, 0.0);//颜色
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutMainLoop();
	return 0;
}
