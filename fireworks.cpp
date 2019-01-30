#include <iostream>
#include <cstdlib>
#include "stdio.h"
#include <string>
#include <array>
using namespace std;

class Coordinate {
public:
	float x, y, z;
	Coordinate() {
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

class Color {
public:
	float R, G, B;
	Color() {
		R = getRandomColor();
		G = getRandomColor();
		B = getRandomColor();
	}
	static float getRandomColor()
	{
		return rand() / (float)RAND_MAX;
	}
};

void makeStartingPointArray(Coordinate *array, int count) {
	for (int i = 0; i < count; i++) {
		array[i] = Coordinate();
	}
}

void makeColorArray(Color *colorArray, int count) {
	for (int i = 0; i < count; i++) {
		colorArray[i] = Color();
	}
}


int main()
{
	const int NUMBER_OF_FIREWORKS = 3;
	Coordinate coordinates[NUMBER_OF_FIREWORKS] = {};
	makeStartingPointArray(coordinates, NUMBER_OF_FIREWORKS);

	Color colors[NUMBER_OF_FIREWORKS] = {};
	makeColorArray(colors, NUMBER_OF_FIREWORKS);

	getchar();
	return 0;
}