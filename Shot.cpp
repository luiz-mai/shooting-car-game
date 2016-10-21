#include "Shot.h"

Shot::Shot(){
}

Shot::Shot(Circle circle, GLfloat centerX, GLfloat centerY, GLfloat carAngle, GLfloat cannonAngle){
        this->circle = circle;
        this->centerX = centerX;
        this->centerY = centerY;
        this->carAngle = carAngle;
        this->cannonAngle = cannonAngle;
}

Circle Shot::getCircle(){
        return this->circle;
}

GLfloat Shot::getCenterX(){
        return this->centerX;
}

GLfloat Shot::getCenterY(){
        return this->centerY;
}

GLfloat Shot::getCarAngle(){
        return this->carAngle;
}

GLfloat Shot::getCannonAngle(){
        return this->cannonAngle;
}


void Shot::setCircle(Circle circle){
        this->circle = circle;
        return;
}

void Shot::setCenterX(GLfloat centerX){
        this->centerX = centerX;
        return;
}

void Shot::setCenterY(GLfloat centerY){
        this->centerY = centerY;
        return;
}

void Shot::setCarAngle(GLfloat carAngle){
        this->carAngle = carAngle;
        return;
}

void Shot::setCannonAngle(GLfloat cannonAngle){
        this->cannonAngle = cannonAngle;
        return;
}



void Shot::drawShot(GLfloat playerRadius, Car* car){


        glPushMatrix();
        glTranslatef(
                this->getCenterX(),
                this->getCenterY(),
                0
                );


        glRotatef(this->carAngle, 0, 0, 1);
        glScalef(
                2*playerRadius/car->getWidth(),
                2*playerRadius/car->getHeight(),
                1
                );

        glTranslatef(
                -car->getWidth()/2,
                -car->getHeight()/2,
                0
                );

        glTranslatef(
                car->getCannon().getBeginX() + car->getCannon().getWidth()/2,
                car->getCannon().getBeginY() + car->getCannon().getHeight(),
                0
                );

        glRotatef(this->getCannonAngle(), 0, 0, 1);

        glTranslatef(
                0,
                -car->getCannon().getHeight(),
                0
                );
        this->getCircle().drawCircle();

        glPopMatrix();
        return;
}
