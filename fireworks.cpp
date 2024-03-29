#include <iostream>
#include <cstdlib>
#include <string>
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
};

class LineSegment {
public: Coordinate to, from;
		LineSegment(Coordinate _from, Coordinate _to) {
			to = _to;
			from = _from;
		}
		void drawVertex(Color color) {
			glVertex3f(from.x, from.y, from.z);
			glVertex3f(to.x, to.y, to.z);      
		}
};

class Firework {
private:
	vector<LineSegment> lineSegments;
public:
	const Color color = Color(0.87451, 0.61961, 0.20392);
	const float RADIUS = 0.25;
	const float PI = acos(-1);
	Firework(Coordinate from) {
		int LINE_SEGMENTS_PER_FIREWORK = 12;
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
    glLineWidth(1.0);
    glColor3f(color.R, color.G, color.B);
    glBegin(GL_LINES);
		for (int i = 0; i < lineSegments.size(); i++) {
			lineSegments[i].drawVertex(color);
		}
    glEnd();
    glFlush();
  }
};

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

vector<Firework*> fireworks;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 3; i++) {
		fireworks[i]->drawFirework();
	}
}

void cleanUp() {
	for (int i = 0; i < fireworks.size(); i++) {
		delete fireworks[i];
	}
}

int main(int argc, char *argv[])
{
	srand (time(NULL));
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 250);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Fireworks");
	glutDisplayFunc(display);
	Coordinate coordinates[NUMBER_OF_FIREWORKS] = { Coordinate(-.5, .5, 0), Coordinate(0, -.5, 0), Coordinate(.5, 0, 0) };
	for (int i = 0; i < NUMBER_OF_FIREWORKS; i++) {
		fireworks.push_back(new Firework(coordinates[i]));
	}
	glutMainLoop();
	cleanUp();
	return 0;
}