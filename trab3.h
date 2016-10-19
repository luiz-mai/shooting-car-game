/*****************************************************************************************
**																						**
**						UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO							**
**							   Luiz Felipe Ferreira Mai 								**
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
#include <cmath>
#include <GL/freeglut.h>
#include "tinyxml2.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Car.h"
using namespace std;
using namespace tinyxml2;

class Trab3{

public:
  Trab3();
  string getArenaPath(int, char**);
  vector<Circle> arenaReading(Trab3, string, vector<Circle>);
  Rectangle* rectangleReading(XMLElement*);
  vector<Circle> circleReading(XMLElement*, vector<Circle>);
};

void display(void);
void idle(void);
void mouseMotion(int, int);
void mouseClick(int, int, int, int);
void keyPressed(unsigned char, int, int);
void keyUp(unsigned char, int, int);

#endif //TRAB3_H
