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

#define NUMBER_OF_FIREWORKS 3
float getRandomFloat()
{
	return rand() / (float)RAND_MAX;
}

class Color {
public:
	float R, G, B;
	Color() {
		R = getRandomFloat();
		G = getRandomFloat();
		B = getRandomFloat();
	}
	Color(float _R, float _G, float _B) {
		R = _R;
		G = _G;
		B = _B;
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
			glLineWidth(1.0);
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
	const Color color = Color(0.87451, 0.61961, 0.20392);
	float RADIUS = 0.25;
	float PI = acos(-1);
	Firework(Coordinate from) {
		int LINE_SEGMENTS_PER_FIREWORK = 15;
		float phiIncrement = PI / LINE_SEGMENTS_PER_FIREWORK;
		float thetaIncrement = 2 * PI / LINE_SEGMENTS_PER_FIREWORK;
		for (float phi = 0; phi < PI; phi += phiIncrement) {
			for (float theta = 0; theta < 2 * PI; theta += thetaIncrement) {
				float phiRandomIncrement = getRandomFloat();
				float thetaRandomIncrement = getRandomFloat();
				phiRandomIncrement *= rand() % 2 == 0 ? -1 : 1;
				thetaRandomIncrement *= rand() % 2 == 0 ? -1 : 1;
				double x = (from.x + (RADIUS + getRandomFloat() / 10) * sin(phi + phiRandomIncrement) * cos(theta + thetaRandomIncrement));
				double y = (from.y + (RADIUS + getRandomFloat() / 10) * sin(phi + phiRandomIncrement) * sin(theta + thetaRandomIncrement));
				double z = (from.z + (RADIUS + getRandomFloat() / 10) * cos(phi + phiRandomIncrement));
				Coordinate to = Coordinate(x, y, z);
				lineSegments.push_back(LineSegment(from, to));
			}
		}
	}
	void drawFirework() {
		for (auto it = lineSegments.begin(); it != lineSegments.end(); it++) {
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

vector<Firework*> fireworks;
Coordinate coordinates[3] = { Coordinate(-.5, .5, 0), Coordinate(0, -.5, 0), Coordinate(.5, 0, 0) };
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	cout << "update" << endl;
	for (int i = 0; i < 3; i++) {
		fireworks[i]->drawFirework();
	}
	glutSwapBuffers();
}

void cleanUp() {
	for (auto it = fireworks.begin(); it != fireworks.end(); it++) {
		delete &it;
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
	for (int i = 0; i < NUMBER_OF_FIREWORKS; i++) {
		fireworks.push_back(new Firework(coordinates[i]));
	}
	glutMainLoop();
	cleanUp();
	return 0;
}