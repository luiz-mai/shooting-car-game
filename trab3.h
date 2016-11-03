/*****************************************************************************************
**																						**
**						UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO							**
**							   Luiz Felipe Ferreira Mai                                 **
**																						**
**						   Trabalho 2 de Computação Gráfica								**
**																						**
*****************************************************************************************/
#ifndef TRAB3_H
#define TRAB3_H

#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <GL/freeglut.h>
#include "tinyxml2.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Car.h"
#include "Shot.h"
using namespace std;
using namespace tinyxml2;

class Trab3 {

public:
Trab3();
string getArenaPath(int, char**);
vector<Circle> arenaReading(Trab3, string, vector<Circle>);
Rectangle* rectangleReading(XMLElement*);
vector<Circle> circleReading(XMLElement*, vector<Circle>);
void drawPlayerShots();
void printCronometer(GLfloat x, GLfloat y);
void printEndMessage(GLfloat x, GLfloat y);
};

void display(void);
void idle(void);
void mouseMotion(int, int);
void mouseClick(int, int, int, int);
void keyPressed(unsigned char, int, int);
void keyUp(unsigned char, int, int);
bool outOfScreen(Shot);
bool detectEnemyShotColision(Car);

#endif //TRAB3_H
