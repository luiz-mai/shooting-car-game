#ifndef MODELOBJ_H
#define MODELOBJ_H

#include <string>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#endif

using namespace std;

class ModelObj {
public:
ModelObj();
float* calculateNormal(float* coord1,float* coord2,float* coord3 );
int Load(char *filename);         // Loads the model
void Draw();         // Draws the model on the screen
void Release();         // Release the model

float* normals;         // Stores the normals
float* Faces_Triangles;         // Stores the triangles
float* vertexBuffer;         // Stores the points which make the object
long TotalConnectedPoints;         // Stores the total number of connected verteces
long TotalConnectedTriangles;         // Stores the total number of connected triangles

};

#endif //MODELOBJ_H
