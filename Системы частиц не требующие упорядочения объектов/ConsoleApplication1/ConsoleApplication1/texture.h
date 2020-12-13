
#pragma once
#include <gl/glut.h>
#include<stdio.h>
struct TextureTga
{
	GLubyte* imageData;
	GLuint bpp;
	GLuint width;
	GLuint height;
	GLuint texID;
};


bool BuildTexture(char* szPathName, GLuint& texid);


