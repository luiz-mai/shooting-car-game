#include "Rectangle.h"


Rectangle::Rectangle(){
}

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

void Rectangle::drawRectangle(GLuint texture){
	GLfloat beginX = this->beginX;
	GLfloat beginY = this->beginY;
	GLfloat width = this->width;
	GLfloat height = this->height;


	GLfloat materialEmission[] = { 1.0, 1.0, 1.0, 1};
	GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
	GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
	GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1};
	GLfloat mat_shininess[] = { 100.0 };
	glColor3f(1,1,1);

	glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glBindTexture(GL_TEXTURE_2D, texture);
	double textureS = 1;

	glBegin(GL_POLYGON);
		glNormal3f(0,1,0);
		glTexCoord2f (0, 0);
		glVertex3f(beginX,beginY,0);
		glNormal3f(0,1,0);
		glTexCoord2f (0, textureS);
		glVertex3f(beginX+width,beginY,0);
		glNormal3f(0,1,0);
		glTexCoord2f (textureS, textureS);
		glVertex3f(beginX+width,beginY+height,0);
		glNormal3f(0,1,0);
		glTexCoord2f (textureS, 0);
		glVertex3f(beginX,beginY+height,0);
	glEnd();
}
