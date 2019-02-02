#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include "GL\glew.h"
#include "GL\freeglut.h"
#else
#include <GL/glut.h>
#endif
#endif
using namespace std;

#define SIZE 32
float X[SIZE + 1];
float Y[SIZE + 1];


class Color {
public:
	float R, G, B;
	Color() {
		R = getRandomColor();
		G = getRandomColor();
		B = getRandomColor();
	}
	Color(float _R, float _G, float _B) {
		R = _R;
		G = _G;
		B = _B;
	}
	static float getRandomColor()
	{
		return rand() / (float)RAND_MAX;
	}
};

class Coordinate {
public:
	float x, y, z;
	Coordinate() {

	}
	Coordinate(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	void randomizeCoordinates() {
		x = getRandomStartingPoint();
		y = getRandomStartingPoint();
		z = getRandomStartingPoint();
	}
	static float getRandomStartingPoint()
	{
		const int MAX = 2;
		const int MIN = 1;
		return (rand() / (float)RAND_MAX * MAX) - MIN;
	}
};

class LineSegment {
public: Coordinate to, from;
		LineSegment(Coordinate _from, Coordinate _to) {
			to = _to;
			from = _from;
		}
		void draw(Color color) {
			glLineWidth(2);
			glColor3f(color.R, color.G, color.B);
			glBegin(GL_LINES);
			glVertex3f(from.x, from.y, from.z);
			glVertex3f(to.x, to.y, to.z);
			glEnd();
			glFlush();
		}
};

void makeFireWorkStartingPointArray(Coordinate *array, int count) {
	const double SCREEN_WIDTH = 2.0;
	const float START = -1.0;
	for (int i = 0; i < count; i++) {
		float width = (SCREEN_WIDTH - count / SCREEN_WIDTH);
		if (width < 0) {
			width = width * START;
		}
		array[i] = Coordinate(width*i - width, 0, 0);
	}
}

void makeColorArray(Color *colorArray, int count) {
	for (int i = 0; i < count; i++) {
		colorArray[i] = Color();
	}
}

//---------------------------------------
// Calculate random value between [-R..R]
//---------------------------------------
float myrand(float R)
{
	return (2 * R * rand()) / RAND_MAX - R;
}

//---------------------------------------
// Recursive function to split lines
//---------------------------------------
void split(int low, int high, float radius)
{
	// Check terminating condition
	if ((high - low) > 1)
	{
		// Calculate length of line segment
		float dx = X[high] - X[low];
		float dy = Y[high] - Y[low];
		float length = sqrt(dx * dx + dy * dy) / radius;

		// Generate midpoint with random displacement
		int mid = (high + low) / 2;
		X[mid] = (X[high] + X[low]) / 2 + myrand(length);
		Y[mid] = (Y[high] + Y[low]) / 2 + myrand(length);

		// Perform recursive calls
		split(low, mid, radius);
		split(mid, high, radius);
	}
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
	// Initialize OpenGL
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	const int NUMBER_OF_FIREWORKS = 3;
	Coordinate coordinates[NUMBER_OF_FIREWORKS] = {};
	makeFireWorkStartingPointArray(coordinates, NUMBER_OF_FIREWORKS);

	Color colors[NUMBER_OF_FIREWORKS] = {};
	makeColorArray(colors, NUMBER_OF_FIREWORKS);

	for (int i = 0; i < NUMBER_OF_FIREWORKS; i++) {
		Color tempColor = Color();
		Coordinate tempTo = Coordinate(1, 1, 1);
		LineSegment *tempLineSegment = new LineSegment(coordinates[i], tempTo);
		tempLineSegment->draw(tempColor);
		delete tempLineSegment;
	}

	// foreach firework starting point, make line segments from the center to many directions with a specified length.
	// compute the to position coordinate.
	// draw. 

	//// Draw red line
	//glBegin(GL_LINE_STRIP);
	//glColor3f(1.0, 0.0, 0.0);
	//X[0] = -0.5;
	//Y[0] = -0.5;
	//X[SIZE] = 0.5;
	//Y[SIZE] = 0.5;
	//split(0, SIZE, 1);
	//for (i = 0; i <= SIZE; i++)
	//	glVertex2f(X[i], Y[i]);
	//glEnd();

	// Draw green line
	/*glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	X[0] = 0.5;
	Y[0] = -0.5;
	X[SIZE] = -0.5;
	Y[SIZE] = 0.5;
	split(0, SIZE, 5);
	glVertex2f(X[2], Y[2]);
	glVertex2f(X[30], Y[30]);*/
	// for (i = 0; i <= SIZE; i

	/*glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(15, 0, 0);
	glEnd();
	glFlush();*/
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 250);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Line");
	glutDisplayFunc(display);
	glutMainLoop();

	getchar();
	return 0;
}