﻿#include "GLTools.h"
#include "GLShaderManager.h"

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

static GLint fogMode;

static void init(void)
{
    GLfloat position[] = { 0.5, 0.5, 3.0, 0.0 };

    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    {   //{}使模块划分更加清楚
        GLfloat mat[3] = { 0.1745, 0.01175, 0.01175 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
        mat[0] = 0.61424; mat[1] = 0.04136; mat[2] = 0.04136;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
        mat[0] = 0.727811; mat[1] = 0.626959; mat[2] = 0.626959;
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.6 * 128.0);
    }

    glEnable(GL_FOG);//激活雾效果
    {
        GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };
        /*雾方程式模式，有三种形式，根据物体距离观察点的距离能
        够算得一个雾因子(默认是计算机自动算出的，但我们也可以自
        己控制雾因子)，雾就是通过雾因子把雾颜色与源片段的颜色进
        行混合得到的*/
        fogMode = GL_EXP;
        glFogi(GL_FOG_MODE, fogMode);
        glFogfv(GL_FOG_COLOR, fogColor);//雾颜色
        glFogf(GL_FOG_DENSITY, 0.35);//雾密度
        glHint(GL_FOG_HINT, GL_DONT_CARE);//在渲染质量与速度上没有偏向
        glFogf(GL_FOG_START, 1.0);//雾开始值(距离观察点开始距离)
        glFogf(GL_FOG_END, 5.0);//雾结束值
    }
    glClearColor(0.5, 0.5, 0.5, 1.0);
}

static void renderSphere(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(0.4, 16, 16);
    glPopMatrix();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderSphere(-2., -0.5, -1.0);
    renderSphere(-1., -0.5, -2.0);
    renderSphere(0., -0.5, -3.0);
    renderSphere(1., -0.5, -4.0);
    renderSphere(2., -0.5, -5.0);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.5, 2.5, -2.5 * (GLfloat)h / (GLfloat)w,
            2.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.5 * (GLfloat)w / (GLfloat)h,
            2.5 * (GLfloat)w / (GLfloat)h, -2.5, 2.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    //雾效果逼真程度:GL_EXP < GL_EXP2 < GL_LINEAR
    switch (key) {
    case 'f':
    case 'F':
        if (fogMode == GL_EXP) {
            fogMode = GL_EXP2;
            printf("Fog mode is GL_EXP2\n");
        }
        else if (fogMode == GL_EXP2) {
            fogMode = GL_LINEAR;
            printf("Fog mode is GL_LINEAR\n");
        }
        else if (fogMode == GL_LINEAR) {
            fogMode = GL_EXP;
            printf("Fog mode is GL_EXP\n");
        }
        glFogi(GL_FOG_MODE, fogMode);
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;

}