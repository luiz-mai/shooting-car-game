#include "Rectangle.h"


Rectangle::Rectangle(){}

Rectangle::Rectangle(string ID, GLfloat beginX, GLfloat beginY, GLfloat width, GLfloat height, string fill){
        this->ID = ID;
        this->beginX = beginX;
        this->beginY = beginY;
        this->width = width;
        this->height = height;
        this->fill = fill;
        return;
}

string Rectangle::getID(){
  return this->ID;
}
GLfloat Rectangle::getBeginX(){
  return this->beginX;
}

GLfloat Rectangle::getBeginY(){
  return this->beginY;
}

GLfloat Rectangle::getWidth(){
  return this->width;
}

GLfloat Rectangle::getHeight(){
  return this->height;
}

string Rectangle::getFill(){
  return this->fill;
}

void Rectangle::setID(string ID){
  this->ID = ID;
  return;
}

void Rectangle::setBeginX(GLfloat beginX){
  this->beginX = beginX;
  return;
}

void Rectangle::setBeginY(GLfloat beginY){
  this->beginY = beginY;
  return;
}

void Rectangle::setWidth(GLfloat width){
  this->width = width;
  return;
}

void Rectangle::setHeight(GLfloat height){
  this->height = height;
  return;
}

void Rectangle::setFill(string fill){
  this->fill = fill;
  return;
}

void Rectangle::drawRectangle(){
        GLfloat beginX = this->beginX;
        GLfloat beginY = this->beginY;
        GLfloat width = this->width;
        GLfloat height = this->height;

        Utils utils;
        utils.checkColor(this->fill);

        glBegin(GL_POLYGON);
        glVertex3f(beginX,beginY,0);
        glVertex3f(beginX+width,beginY,0);
        glVertex3f(beginX+width,beginY+height,0);
        glVertex3f(beginX,beginY+height,0);
        glEnd();
}
