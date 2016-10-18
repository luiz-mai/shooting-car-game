#include "Triangle.h"

Triangle::Triangle(){}

Triangle::Triangle(string ID, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, string fill){
    this->ID = ID;
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->x3 = x3;
    this->y3 = y3;
    this->fill = fill;
    return;
}

string Triangle::getID(){
    return this->ID;
}

GLfloat Triangle::getX1(){
    return this->x1;
}

GLfloat Triangle::getY1(){
    return this->y1;
}

GLfloat Triangle::getX2(){
    return this->x2;
}

GLfloat Triangle::getY2(){
    return this->y2;
}

GLfloat Triangle::getX3(){
    return this->x3;
}

GLfloat Triangle::getY3(){
    return this->y3;
}

string Triangle::getFill(){
    return this->fill;
}

void Triangle::setID(string ID){
    this->ID = ID;
    return;
}

void Triangle::setX1(GLfloat x1){
    this->x1 = x1;
    return;
}

void Triangle::setY1(GLfloat y1){
    this->y1 = y1;
    return;
}

void Triangle::setX2(GLfloat x2){
    this->x2 = x2;
    return;
}

void Triangle::setY2(GLfloat y2){
    this->y2 = y2;
    return;
}

void Triangle::setX3(GLfloat x3){
    this->x3 = x3;
    return;
}

void Triangle::setY3(GLfloat y3){
    this->y3 = y3;
    return;
}

void Triangle::setFill(string fill){
    this->fill = fill;
    return;
}

void Triangle::drawTriangle(){
    Utils utils;
    utils.checkColor(this->getFill());
    glBegin(GL_TRIANGLES); //Begin triangle coordinates
        glVertex3f(this->getX1(), this->getY1(), 1.0f);
        glVertex3f(this->getX2(), this->getY2(), 1.0f);
        glVertex3f(this->getX3(), this->getY3(), 1.0f);
    glEnd(); //End triangle coordinates
}
