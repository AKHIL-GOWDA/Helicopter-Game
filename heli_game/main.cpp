#include <windows.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<stdio.h>
#include<conio.h>

float bspd=0.15;
float b1x=50.0,b1y=0;//block 1
float b=0.0;//copter moving
int i=0,sci=0;
float scf=1;
char scs[20], c = 'y';
int score = 0;
int wflag=1;
void init(void)
{
	b1y=(rand()%45)+10;
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glLoadIdentity ();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0 , 0.0);
}
void drawcopter()
{
	glColor3f(0.7,1.0,1.0);
	glRectf(10,49.8,19.8,44.8);//body
	glRectf(2,46,10,48);//tail
	glRectf(2,46,4,51);//tail up
	glRectf(14,49.8,15.8,52.2);//propeller stand
	glRectf(7,53.6,22.8,52.2);//propeller
}
void renderBitmapString(float x,float y,float z,void *font,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);
	for (c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void heliup()
{
	b+=0.2;
	i+=2;
	glutPostRedisplay();
}
void helidown()
{
	b-=0.2;
	i-=2;
	glutPostRedisplay();
}

void mouse(int btn,int state,int x,int y)
{
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(heliup);
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
		glutIdleFunc(helidown);
	glutPostRedisplay();
}

void display ()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//Crash condition
	if( (i==370||i==-350) //top and bottom checking
||(((int)b1x==10||(int)b1x==7||(int)b1x==4||(int)b1x==1)   &&(int)b1y<53+(int)b&&(int)b1y+35>53+(int)b)//propeller front checking
||(((int)b1x==9||(int)b1x==3||(int)b1x==6)&&(int)b1y<45+(int)b&&(int)b1y+35>45+(int)b)//lower body checking
||(((int)b1x==0)&&(int)b1y<46+(int)b&&(int)b1y+35>46+(int)b)//lower tail checking
	)
	{
		glColor3f(0.8,0.8,1.0);
		glRectf(0.0,0.0,100.0,100.0);
		glColor3f(0.0,0.0,0.0);
		glutSwapBuffers();
		glFlush();
        printf("GAME OVER\nClose the console window to exit...\n");
        printf("Your score: %d", score);
        exit(0);
	}
	else if(wflag==1)//Welcome Screen
	{
		wflag=0;
		glColor3f(0.3,0.7,0.2);
		printf("CLICK TO START\n");
        printf("CLICK AND HOLD LEFT MOUSE BUTTON TO GO UP\n");
		printf("RELEASE TO GO DOWN\n");
		drawcopter();
		glutSwapBuffers();
		glFlush();
	}
	else {
		glPushMatrix();
		glColor3f(0.3,0.7,0.2);
		glRectf(0.0,0.0,100.0,10.0);//ceil
		glRectf(0.0,100.0,100.0,90.0);//floor
		sci=(int)scf;
		glTranslatef(0.0,b,0.0);
		drawcopter();//code for helicopter
		if(b1x<-10)
		{
			b1x=50;
			b1y=(rand()%25)+20;
			score++;
		}
		else b1x-=bspd;
		glTranslatef(b1x,-b,0.0);
		glColor3f(1.0,0.0,0.0);
		glRectf(b1x,b1y,b1x+5,b1y+35);//block 1
		glPopMatrix();
		glutSwapBuffers();
		glFlush();
	}
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w<=h)
        glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,20.0);
	else
        glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,20.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	score = 0;
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (480, 360);
	glutInitWindowPosition (0,0);
	int win = glutCreateWindow ("Helicopter Game");
	init();
	glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutMouseFunc(mouse);
        glutMainLoop();
        /*glutDestroyWindow(int win);
        printf ("Want to play again? (y/n)\n");
        scanf ("%c", &c);*/
}
