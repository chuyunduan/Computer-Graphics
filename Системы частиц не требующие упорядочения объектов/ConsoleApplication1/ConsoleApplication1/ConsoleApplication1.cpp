#define _CRT_SECURE_NO_WARNINGS    

#include <stdlib.h>     
#include<time.h>  
#include"particle.h"    
#include"texture.h"

emitter* e1;
emitter* e2;
emitter* e3;


float whRatio;
int wHeight = 0;
int wWidth = 0;

 
float center[] = { 0, 0, 0 };
float eye[] = { 0, 0, 5 };

particle* init_particle1()
{
	float size = rand() % 15 * 0.02f;
	unsigned char color[] = { 1.0f,0.0f,0.0f };
	particle* p = new particle(size, size, float(rand() % 10 - 4) / 80, float(rand() % 10 - 4) / 80,
		0, -4.9 / 40000, rand() % 80, 0, color, false);
	return p;
}

particle* init_particle2()
{
	float size = rand() % 15 * 0.02f;
	unsigned char color[] = { 0.0f,1.0f,0.0f };
	particle* p = new particle(size, size, float(rand() % 10 - 4) / 80, float(rand() % 10 - 4) / 80,
		0, -4.9 / 40000, rand() % 50, 0, color, false);
	return p;
}
particle* init_particle3()
{
	float size = rand() % 15 * 0.02f;
	unsigned char color[] = { 0.0f,0.0f,1.0f };
	particle* p = new particle(size, size, float(rand() % 10 - 4) / 80, float(rand() % 10 - 4) / 80,
		0, -4.9 / 40000, rand() % 40, 0, color, false);
	return p;
}

void drawScene()
{
	e1->update();
	e2->update();
	e3->update();

}

void updateView(int height, int width)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);        
	glLoadIdentity();               
	whRatio = (GLfloat)width / (GLfloat)height;  
	glOrtho(-30, 30, -30, 30, -100, 100); 
	glMatrixMode(GL_MODELVIEW);      
}

void reshape(int width, int height)
{
	if (height == 0) {
		height = 1;       
	}
	wHeight = height;
	wWidth = width;
	updateView(wHeight, wWidth);         
}

void idle()
{
	glutPostRedisplay();
}

void init(void)
{
	srand(unsigned(time(nullptr)));
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	e1 = new emitter(1000, 0, 0, 0, 0);
	e1->emit(init_particle1);
	e2 = new emitter(1000, 10, 10, 10, 10);
	e2->emit(init_particle2);
	e3 = new emitter(1000, -20, -20, 13, 13);
	e3->emit(init_particle3);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();      
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
	drawScene();    
	glutSwapBuffers();  
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);         
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);            
	glutInitWindowSize(800, 600);           
	int windowHandle = glutCreateWindow("Simple GLUT App");
	glutDisplayFunc(redraw);     
	glutReshapeFunc(reshape);             
	glutIdleFunc(idle);        
	init();
	glutMainLoop();   
	return 0;
}