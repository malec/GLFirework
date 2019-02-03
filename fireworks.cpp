#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
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
			glLineWidth(3.0);
			glColor3f(color.R, color.G, color.B);
			glBegin(GL_LINES);
			glVertex3f(from.x, from.y, from.z);
			glVertex3f(to.x, to.y, to.z);
			glEnd();
			glFlush();
		}
};

class Firework {
private:
	list<LineSegment> lineSegments;
public:
	const Color color = Color(0.87451, 0.41961, 0.00392);;
	float RADIUS = 0.25;
	float PI = acos(-1);
	Firework(Coordinate from) {
		int LINE_SEGMENTS_PER_FIREWORK = 20;
		float phiIncrement = PI / LINE_SEGMENTS_PER_FIREWORK;
		float thetaIncrement = 2 * PI / LINE_SEGMENTS_PER_FIREWORK;
		for (float phi = 0; phi < PI; phi += phiIncrement) {
			for (float theta = 0; theta < 2 * PI; theta += thetaIncrement) {
				double x = from.x + RADIUS * sin(phi) * cos(theta);
				double y = from.y + RADIUS * sin(phi) * sin(theta);
				double z = from.z + RADIUS * cos(phi);
				Coordinate to = Coordinate(x, y, z);
				lineSegments.push_back(LineSegment(from, to));
			}
		}
	}
	void drawFirework() {
		// iterator<forward_iterator_tag,LineSegment> lineSegmentIterator = lineSegments.begin();
		for (list<LineSegment>::iterator it = lineSegments.begin(); it != lineSegments.end(); ++it) {
			it->draw(color);
		}
	}
};
void makeFireWorkStartingPointArray(Coordinate *array, int count) {
	const double SCREEN_WIDTH = 2.0;
	const float START = -1.0;
	for (int i = 0; i < count; i++) {
		float width = (SCREEN_WIDTH / (count + 1));
		array[i] = Coordinate((i + 1)*width - 1, (i % 2 == 1 ? 1.0 / 3.0 : 2.0 / 3.0), 0);
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

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	const int NUMBER_OF_FIREWORKS = 3;
	vector<Coordinate> origin;
	origin.push_back(Coordinate(-.5, .5, 0));
	origin.push_back(Coordinate(0, -.5, 0));
	origin.push_back(Coordinate(.5, 0, 0));
	vector<Firework> firework;
	for(int i = 0; i < NUMBER_OF_FIREWORKS; i++) {
		Firework *firework = new Firework(origin[i]);
		firework->drawFirework();
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 250);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Fireworks");
	glutDisplayFunc(display);
	glutMainLoop();

	getchar();
	return 0;
}