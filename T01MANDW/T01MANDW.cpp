#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#include "Compl.h"

#define H 720
#define W 1280
#define x0 (-2.)
#define x1 2.
#define y0 (-2.)
#define y1 2.

typedef unsigned char byte;

compl Const(0.36, 0.36);

struct frame
{
	byte Image[H][W][4];

	frame(void)
	{
		int n;
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				compl Z(x0 + ((x1 - x0) * j) / W, y0 + ((y1 - y0) * i) / H);
				n = Z.Julia(Const);

				PutPixel(j, i, n, n, n);
			}	
	}

	void PutPixel(int x, int y, byte R, byte G, byte B)
	{
		Image[y][x][0] = B;
		Image[y][x][1] = G;
		Image[y][x][2] = R;
		Image[y][x][3] = 255;
	}

	void Draw(void)
	{
		glDrawPixels(W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Image);
	}
};

void Display( void )
{
	static frame MyFrame;
	
	glClear(GL_COLOR_BUFFER_BIT);

	MyFrame.Draw();

	glFinish();          
	glutSwapBuffers();   
	glutPostRedisplay();
}

void Keyboard(unsigned char Key, int X, int Y)
{
	if (Key == 27)
		exit(0);
}

int main( int argc, char *argv[] )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(W, H);
	glutCreateWindow("MANDW");

	glutDisplayFunc(Display);       
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return 0;
}