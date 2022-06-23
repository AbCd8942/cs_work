#include <windows.h>
#include <GL/glut.h>
float fTranslate;//平移因子
float fRotate;//旋转因子
float fScale=1.0f;//缩放因子
void Draw_Cube(GLfloat x1, GLfloat x2, GLfloat y1,GLfloat y2,GLfloat z1,GLfloat z2)
{	//桌子由立方体组成，已知六个参数即可构造八个顶点
	int i, j;
	GLfloat vertex[8][3] = {
		//八个顶点，从v1-v8
		x1,y1,z2,
		x2,y1,z2,
		x1,y2,z2,
		x2,y2,z2,
		x1,y1,z1,
		x2,y1,z1,
		x1,y2,z1,
		x2,y2,z1
	};
	GLint surface[6][4] = {
		//v1对应0,以此类推
		0,1,3,2,
		4,5,7,6,
		2,3,7,6,
		0,1,5,4,
		0,2,6,4,
		1,3,7,5
	};
	glBegin(GL_QUADS);//指定绘制方式
	//将每个立方体分成六个面绘制
	for (i = 0; i < 6; i++)
		for (j = 0; j < 4; j++)
			glVertex3fv(vertex[surface[i][j]]);
	glEnd();
}
void Draw_Table(){
	//将桌子拆分成5个立方体绘制
	Draw_Cube(0.0, 1.0, 0.0, 0.8, 0.6, 0.8);//桌面
	Draw_Cube(0.1, 0.3, 0.1, 0.3, 0.0, 0.6);//四条腿
	Draw_Cube(0.7, 0.9, 0.1, 0.3, 0.0, 0.6);
	Draw_Cube(0.1, 0.3, 0.5, 0.7, 0.0, 0.6);
	Draw_Cube(0.7, 0.9, 0.5, 0.7, 0.0, 0.6);
}
void reshape(int width, int height){
	//当窗口尺寸改变时改变尺寸
	if (height==0){
		height=1;
	}
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void idle(){
	glutPostRedisplay();
}
void redraw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT);//清除窗口
	glLoadIdentity();
	//三维变换——移动
	glPushMatrix();//glpushmatrix与glpopmatrix配合使用可以消除上一次变换对本次变换的影响
	glTranslatef(-2.5f, 0.0f,-6.0f);//放在左边
	glTranslatef(0.0f, fTranslate, 0.0f);
	Draw_Table();
	glPopMatrix();
	//三维变换——旋转
	glPushMatrix();
	glTranslatef(0.0f, 0.0f,-6.0f);//放在中间
	glRotatef(fRotate, 0, 1.0f, 0);
	Draw_Table();
	glPopMatrix();
	//三维变换——缩放
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, -6.0f);//放在右边
	glScalef(fScale, fScale,fScale);
	Draw_Table();
	glPopMatrix();
	//更新因子
	fTranslate += 0.5f;
	fRotate += 0.5f;
	fScale -= 0.5f;
	if(fTranslate > 0.5f)
		fTranslate = 0.0f;
	if (fScale < 0.5f)//缩小到一定程度之后变回原来大小
		fScale = 1.0f;
	glutSwapBuffers();
}
int main (int argc,  char *argv[]){
	glutInit(&argc, argv);//对glut函数库进行初始化
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//指定glutCreateWindow函数将要创建的窗口显示模式 RGB 双缓冲
	glutInitWindowSize(640,480);//窗口大小
	glutCreateWindow("三维变换");//打开设置好的窗口，进入glutMainLoop之前这个窗口不会显示
	glutDisplayFunc(redraw);//指定当前窗口需要重绘时调用的函数
	glutReshapeFunc(reshape);//注册窗口大小改变时回调函数
	glutIdleFunc(idle);	//可以执行连续动画
	glutMainLoop();//进入glut事件处理循环，永远不会返回
	return 0;
}
