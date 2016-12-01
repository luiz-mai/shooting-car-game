#include "Car.h"
#include "carBody.h"
#include "carCannon.h"
#include "carWheel.h"

GLuint LoadTextureRAW(const char *filename);

Car::Car(string id){
        this->ID = id;
        this->setCenterZ(25);
        this->setTheta(0);
        this->setCannonAngle(0);
        this->setWheelsAngle(0);
        this->setMoving(false);
        this->setAxisWidth(58.5);
        this->setBackwardCount(0);
        this->setDirection(1);
        return;
}

vector<Rectangle> Car::getWheels(){
        return this->wheels;
}

vector<Rectangle> Car::getBodyRectangles(){
        return this->bodyRectangles;
}

vector<Triangle> Car::getBodyTriangles(){
        return this->bodyTriangles;
}

vector<Circle> Car::getBodyCircles(){
        return this->bodyCircles;
}

Rectangle Car::getCannon(){
        return this->cannon;
}

vector<Shot> Car::getShotsVector(){
        return this->shotsVector;
}

GLfloat Car::getCircleRadius(){
        return this->circleRadius;
}

GLfloat Car::getWidth(){
        return this->width;
}

GLfloat Car::getHeight(){
        return this->height;
}

GLfloat Car::getZHeight(){
        return this->zHeight;
}

GLfloat Car::getTheta(){
        return this->theta;
}

GLfloat Car::getCenterX(){
        return this->centerX;
}

GLfloat Car::getCenterY(){
        return this->centerY;
}

GLfloat Car::getCenterZ(){
        return this->centerZ;
}

GLfloat Car::getSpeed(){
        return this->speed;
}

GLfloat Car::getShotSpeed(){
        return this->shotSpeed;
}

GLfloat Car::getWheelsAngle(){
        return this->wheelsAngle;
}

GLfloat Car::getCannonAngle(){
        return this->cannonAngle;
}

GLfloat Car::getCannonZAngle(){
        return this->cannonZAngle;
}

GLfloat Car::getAxisWidth(){
        return this->axisWidth;
}

int Car::getBackwardCount(){
        return this->backwardCount;
}

int Car::getDirection(){
        return this->direction;
}

GLfloat Car::getIncrementalNumber(){
        return this->incrementalNumber;
}

bool Car::getMoving(){
        return this->moving;
}

string Car::getColor(){
        return this->color;
}

void Car::setWheels(vector<Rectangle> wheels){
        this->wheels = wheels;
        return;
}

void Car::setBodyRectangles(vector<Rectangle> bodyRectangles){
        this->bodyRectangles = bodyRectangles;
        return;
}

void Car::setBodyTriangles(vector<Triangle> bodyTriangles){
        this->bodyTriangles = bodyTriangles;
        return;
}


void Car::setBodyCircles(vector<Circle> bodyCircles){
        this->bodyCircles = bodyCircles;
        return;
}

void Car::setCannon(Rectangle cannon){
        this->cannon = cannon;
        return;
}

void Car::setShotsVector(vector<Shot> shotsVector){
        this->shotsVector = shotsVector;
        return;
}

void Car::setCircleRadius(GLfloat circleRadius){
        this->circleRadius = circleRadius;
        return;
}


void Car::setWidth(GLfloat width){
        this->width = width;
        return;
}

void Car::setHeight(GLfloat height){
        this->height = height;
        return;
}

void Car::setZHeight(GLfloat zHeight){
        this->zHeight = zHeight;
        return;
}

void Car::setTheta(GLfloat theta){
        this->theta = theta;
        return;
}

void Car::setCenterX(GLfloat centerX){
        this->centerX = centerX;
        return;
}

void Car::setCenterY(GLfloat centerY){
        this->centerY = centerY;
        return;
}

void Car::setCenterZ(GLfloat centerZ){
        this->centerZ = centerZ;
        return;
}

void Car::setSpeed(GLfloat speed){
        this->speed = speed;
        return;
}

void Car::setShotSpeed(GLfloat shotSpeed){
        this->shotSpeed = shotSpeed;
        return;
}

void Car::setWheelsAngle(GLfloat wheelsAngle){
        if(abs(wheelsAngle) < 45)
                this->wheelsAngle = wheelsAngle;
        return;
}

void Car::setCannonAngle(GLfloat cannonAngle){
        if(abs(cannonAngle) < 45)
                this->cannonAngle = cannonAngle;
        return;
}

void Car::setCannonZAngle(GLfloat cannonZAngle){
        if(cannonZAngle >= 0 && cannonZAngle <= 45)
                this->cannonZAngle = cannonZAngle;
        return;
}

void Car::setAxisWidth(GLfloat axisWidth){
        this->axisWidth = axisWidth;
        return;
}

void Car::setIncrementalNumber(float incrementalNumber){
        this->incrementalNumber = incrementalNumber;
        return;
}

void Car::setBackwardCount(int backwardCount){
        this->backwardCount = backwardCount;
        return;
}

void Car::setDirection(int direction){
        this->direction = direction;
        return;
}

void Car::setMoving(bool moving){
        this->moving = moving;
        return;
}

void Car::setColor(string color){
        this->color = color;
        return;
}

void Car::drawCar(){

        bool moving = this->getMoving();
        GLfloat playerRadius = this->getCircleRadius();

        float randomAngle = this->getIncrementalNumber();
        if(moving) {
                //Does the moving effect to the wheels.
                if(this->getDirection() == 1)
                        this->setIncrementalNumber(randomAngle + 10);
                else
                        this->setIncrementalNumber(randomAngle - 10);
        }

        //Does the positioning transformations
        glPushMatrix();
        glTranslatef(
                this->getCenterX(),
                this->getCenterY(),
                0
                );
        glRotatef(this->getTheta(), 0, 0, 1);


        glTranslatef(
                -this->getWidth()/2,
                -this->getHeight()/2,
                0
                );

        glPushMatrix();
        glTranslatef(0,0,15);
        this->drawFrontWheels();
        this->drawBackWheels();
        this->drawCarBody();
        this->drawCarCannon();
        glPopMatrix();


        glPopMatrix();

        return;
}



void Car::drawCarBody(){


        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);


        glPushMatrix();
        glTranslatef(15, 15, 0);
        glScalef(55, 55, 55);
        glRotatef(180, 0, 0, 1);
        GLuint carTex = LoadTextureRAW("car.bmp");
        glBindTexture (GL_TEXTURE_2D, carTex);
        glVertexPointer(3, GL_FLOAT, 0, carBodyVerts);
        glNormalPointer(GL_FLOAT, 0, carBodyNormals);
        glTexCoordPointer(2, GL_FLOAT, 0, carBodyTexCoords);
        glDrawArrays(GL_TRIANGLES, 0, carBodyNumVerts);

        glPopMatrix();

        glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
}

void Car::drawCarAxis(){

}

void Car::drawFrontWheels(){

        glPushMatrix();
        glTranslatef(7,-3,-6);
        glRotatef(this->getWheelsAngle(), 0, 0, 1);
        glTranslatef(-5, 0, 0);
        glRotatef(this->getIncrementalNumber(), 1, 0, 0);
        glScalef(14,14,14);
        this->drawSingleWheel();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(28,-3,-6);
        glRotatef(this->getWheelsAngle(), 0, 0, 1);
        glRotatef(this->getIncrementalNumber(), 1, 0, 0);
        glScalef(14,14,14);
        this->drawSingleWheel();
        glPopMatrix();
}

void Car::drawBackWheels(){
        glPushMatrix();
        glTranslatef(2,30,-4);
        glRotatef(this->getIncrementalNumber(), 1, 0, 0);
        glScalef(18,18,18);
        this->drawSingleWheel();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(28,30,-4);
        glRotatef(this->getIncrementalNumber(), 1, 0, 0);
        glScalef(18,18,18);
        this->drawSingleWheel();
        glPopMatrix();
}

void Car::drawSingleWheel(){
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);

        glPushMatrix();

        GLuint carTex = LoadTextureRAW("car.bmp");
        glBindTexture (GL_TEXTURE_2D, carTex);
        glVertexPointer(3, GL_FLOAT, 0, carWheelVerts);
        glNormalPointer(GL_FLOAT, 0, carWheelNormals);
        glTexCoordPointer(2, GL_FLOAT, 0, carWheelTexCoords);
        glDrawArrays(GL_TRIANGLES, 0, carWheelNumVerts);

        glPopMatrix();

        glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
}

void Car::drawWheelCircle(GLfloat radius){

}

void Car::drawCarCannon(){
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);

        glPushMatrix();

        glTranslatef(15,20,15);
        glRotatef(-(this->getCannonZAngle()-10), 1, 0, 0);
        glRotatef(this->getCannonAngle(), 0, 0, 1);
        glScalef(20,20,20);
        glRotatef(180,0,0,1);
        GLuint carTex = LoadTextureRAW("car.bmp");
        glBindTexture (GL_TEXTURE_2D, carTex);
        glVertexPointer(3, GL_FLOAT, 0, carCannonVerts);
        glNormalPointer(GL_FLOAT, 0, carCannonNormals);
        glTexCoordPointer(2, GL_FLOAT, 0, carCannonTexCoords);
        glDrawArrays(GL_TRIANGLES, 0, carCannonNumVerts);

        glPopMatrix();

        glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
}


void Car::drawShots(){
        glPushMatrix();
        vector<Shot> carShots = this->getShotsVector();
        //Applies the positioning transformations to all the shots.
        for(vector<Shot>::iterator it = carShots.begin(); it != carShots.end(); ++it) {
                glPushMatrix();
                glTranslatef(
                        (*it).getCenterX(),
                        (*it).getCenterY(),
                        (*it).getCenterZ()
                        );
                glRotatef(-(*it).getCannonZAngle(), 1, 0, 0);
                glRotatef((*it).getCannonAngle() + (*it).getCarAngle(), 0, 0, 1);
                GLUquadricObj *quadObj = gluNewQuadric();
                gluQuadricNormals(quadObj, GLU_SMOOTH);
                glColor3f(1, 0, 1);
                gluSphere(quadObj, 1.5, 50, 100);

                glPopMatrix();
        }
        glPopMatrix();
        return;

}

void Car::addShot(){
        Circle shotCircle = Circle("Shot", 12, 0, 0, "yellow");
        GLfloat angulo = this->getTheta() + this->getCannonAngle();
        GLfloat shotX = this->getCenterX()-(sin(this->getTheta()*M_PI/180)*4)+(sin(angulo*M_PI/180));
        GLfloat shotY = this->getCenterY()+(cos(this->getTheta()*M_PI/180)*4)-(cos(angulo*M_PI/180));
        Shot shot = Shot(shotCircle,shotX,shotY, 28+sin(this->getCannonZAngle()*M_PI/180)*10, this->getTheta(),this->getCannonAngle(), this->getCannonZAngle());
        this->shotsVector.push_back(shot);
        return;
}

bool Car::detectTrackColision(vector<Circle> trackVector, GLfloat biggestRadius){
        for(vector<Circle>::iterator it = trackVector.begin(); it != trackVector.end(); ++it) {
                //Can't go inside the inner track
                if((*it).getRadius() != biggestRadius ) {
                        if(sqrt(pow(((*it).getCenterX() - this->getCenterX()),2) + pow(((*it).getCenterY() - this->getCenterY()),2))
                           < (*it).getRadius() + this->getCircleRadius()) {
                                return true;
                        }
                }
                //Can't go outside the outer track
                else {
                        if(sqrt(pow(((*it).getCenterX() - this->getCenterX()),2)+pow((*it).getCenterY() - this->getCenterY(),2)) + this->getCircleRadius()
                           > biggestRadius) {
                                return true;
                        }
                }
        }
        return false;
}

bool Car::detectFoeColision(vector<Car> foesVector){
        for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
                if(sqrt(pow(((*it).getCenterX() - this->getCenterX()),2) + pow(((*it).getCenterY() - this->getCenterY()),2))
                   < (*it).getCircleRadius() + this->getCircleRadius()) {
                        return true;
                }
        }
        return false;
}

bool Car::detectCarColision(Car car){
        if(sqrt(pow((car.getCenterX() - this->getCenterX()),2) + pow((car.getCenterY() - this->getCenterY()),2))
           < car.getCircleRadius() + this->getCircleRadius()) {
                return true;
        }

        return false;
}

void Car::updateShots(GLdouble t){
        vector<Shot> playerShotsVector = this->getShotsVector();
        for(vector<Shot>::iterator it = playerShotsVector.begin(); it != playerShotsVector.end(); ++it) {
                GLfloat angle = (*it).getCarAngle() + (*it).getCannonAngle();
                GLfloat angleZ = (*it).getCannonZAngle() - 10;
                (*it).setCenterX((*it).getCenterX() + t*this->getShotSpeed()*cos((angle-90)*M_PI/180));
                (*it).setCenterY((*it).getCenterY() + t*this->getShotSpeed()*sin((angle-90)*M_PI/180));
                (*it).setCenterZ((*it).getCenterZ() + t*this->getShotSpeed()*cos((angleZ-90)*M_PI/180));
        }
        this->setShotsVector(playerShotsVector);
        return;
}

void Car::moveForward(GLdouble t){
        this->setCenterX(this->getCenterX() + t*(this->getSpeed()*cos((this->getTheta()-90)*M_PI/180)));
        this->setCenterY(this->getCenterY() + t*(this->getSpeed()*sin((this->getTheta()-90)*M_PI/180)));
        this->setTheta(this->getTheta() + t*(this->getSpeed()*tan((this->getWheelsAngle())*M_PI/180)));
}

void Car::moveBackward(GLdouble t){
        this->setCenterX(this->getCenterX() - t*(this->getSpeed()*cos((this->getTheta()-90)*M_PI/180)));
        this->setCenterY(this->getCenterY() - t*(this->getSpeed()*sin((this->getTheta()-90)*M_PI/180)));
        this->setTheta(this->getTheta() - t*(this->getSpeed()*tan((this->getWheelsAngle())*M_PI/180)));
}
void Car::foeMove(GLdouble t, GLfloat threshold){
        //Sets the cannon at a random position
        Utils utils;
        if(utils.randomInt(0,20) == 19)       //Don't change too often
                this->setCannonAngle(utils.randomInt(-45,45));

        //Sets the position of the wheels to keep tracking the threshold's radius
        this->setWheelsAngle((-1)*asin(this->getAxisWidth()/threshold)*180/M_PI);
        if(this->getDirection() == 1) {
                this->moveForward(t);
        } else {
                this->moveBackward(t);
        }


}
