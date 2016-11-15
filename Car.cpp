#include "Car.h"

GLuint LoadTextureRAW(const char *filename);

Car::Car(){
        XMLDocument car;

        vector<Rectangle> wheels;
        vector<Rectangle> bodyRectangles;
        vector<Triangle> bodyTriangles;
        vector<Circle> bodyCircles;
        Rectangle cannon;

        //Loads the car' SVG
        car.LoadFile("car.svg");
        XMLElement* svgElement = car.FirstChildElement("svg");

        //Loads all the rectangular parts (Body, Wheels and Cannon)
        for(XMLElement* rectElement = svgElement->FirstChildElement("rect"); rectElement != NULL; rectElement = rectElement->NextSiblingElement("rect"))
        {
                Rectangle* rect = new Rectangle(
                        rectElement->Attribute("id"),
                        rectElement->FloatAttribute("x"),
                        rectElement->FloatAttribute("y"),
                        rectElement->FloatAttribute("width"),
                        rectElement->FloatAttribute("height"),
                        rectElement->Attribute("fill")
                        );

                if(rect->getID() == "FrontWheels") {
                        vector<Rectangle>::iterator it;
                        it = wheels.begin();
                        wheels.insert(it, *rect);
                } else if(rect->getID() == "BackHeels") {
                        wheels.push_back(*rect);
                } else if(rect->getID() == "Cannon") {
                        this->setCannon(*rect);
                } else{
                        bodyRectangles.push_back(*rect);
                }
        }
        this->setBodyRectangles(bodyRectangles);
        this->setWheels(wheels);

        //Loads all the circular parts (Body)
        for(XMLElement* circleElement = svgElement->FirstChildElement("circle"); circleElement != NULL; circleElement = circleElement->NextSiblingElement("circle"))
        {
                Circle* circle = new Circle(
                        circleElement->Attribute("id"),
                        circleElement->IntAttribute("r"),
                        circleElement->IntAttribute("cx"),
                        circleElement->IntAttribute("cy"),
                        circleElement->Attribute("fill")
                        );

                bodyCircles.push_back(*circle);
        }
        this->setBodyCircles(bodyCircles);

        //Loads all the triangular parts (Body)
        for(XMLElement* triangleElement = svgElement->FirstChildElement("polygon"); triangleElement != NULL; triangleElement = triangleElement->NextSiblingElement("polygon"))
        {
                float pointsArray[6];
                int pointPos = 0;
                string s = triangleElement->Attribute("points");
                string delim = " ";

                int i = 0;
                int pos = s.find(delim);
                while (pos != string::npos) {
                        string s2 = s.substr(i, pos-i);
                        string delim2 = ",";

                        int i2 = 0;
                        int pos2 = s2.find(delim2);
                        while (pos2 != string::npos) {
                                pointsArray[pointPos++] = atof(s2.substr(i2, pos2-i2).c_str());
                                i2 = ++pos2;
                                pos2 = s2.find(delim2, pos2);

                                if (pos2 == string::npos)
                                        pointsArray[pointPos++] = atof(s2.substr(i2, s2.length()).c_str());
                        }
                        i = ++pos;
                        pos = s.find(delim, pos);

                        if (pos == string::npos) {
                                string s2 =  s.substr(i, s.length());
                                string delim2 = ",";

                                int i2 = 0;
                                int pos2 = s2.find(delim2);
                                while (pos2 != string::npos) {
                                        pointsArray[pointPos++] = atof(s2.substr(i2, pos2-i2).c_str());
                                        i2 = ++pos2;
                                        pos2 = s2.find(delim2, pos2);

                                        if (pos2 == string::npos)
                                                pointsArray[pointPos++] = atof(s2.substr(i2, s2.length()).c_str());
                                }
                        }

                }
                Triangle* triangle = new Triangle(
                        triangleElement->Attribute("id"),
                        pointsArray[0],
                        pointsArray[1],
                        pointsArray[2],
                        pointsArray[3],
                        pointsArray[4],
                        pointsArray[5],
                        triangleElement->Attribute("fill")
                        );
                bodyTriangles.push_back(*triangle);
        }

        //Sets the initial values to the car
        this->setBodyTriangles(bodyTriangles);
        this->setWidth(200);
        this->setHeight(200);
        this->setZHeight(100);
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

        vector<Circle> bodyCircles = this->getBodyCircles();
        vector<Rectangle> bodyRectangles = this->getBodyRectangles();
        vector<Rectangle> wheels = this->getWheels();

        float randomAngle = this->getIncrementalNumber();
        if(moving) {
                //Does the moving effect to the wheels.
                if(this->getDirection() == 1)
                        this->setIncrementalNumber(randomAngle + 2);
                else
                        this->setIncrementalNumber(randomAngle - 2);
        }

        //Does the positioning transformations
        glPushMatrix();
        glTranslatef(
                this->getCenterX(),
                this->getCenterY(),
                0
                );
        glRotatef(this->getTheta(), 0, 0, 1);
        glScalef(
                2*playerRadius/this->getWidth(),
                2*playerRadius/this->getHeight(),
                2*playerRadius/this->getZHeight()
                );

        glTranslatef(
                -this->getWidth()/2,
                -this->getHeight()/2,
                0
                );

        this->drawFrontWheels();
        this->drawBackWheels();
        this->drawCarAxis();
        this->drawCarBody();
        this->drawCarCannon();

        glPopMatrix();
        return;
}

// static void drawBox(GLfloat size, GLenum type, const char* texture)
// {
//  GLuint carro = LoadTextureRAW(texture);
//
//  GLfloat materialEmission[] = { 1.0, 1.0, 1.0, 1};
//  GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
//  GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
//  GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1};
//  GLfloat mat_shininess[] = { 100.0 };
//  // if(textura_ligada==0)glColor3f(1,0,0);
//
//  glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
//  glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
//  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
//  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//
//  glColor3f(1,1,1);
//  glBindTexture (GL_TEXTURE_2D, carro);
//  double textureS = 1;
//
//
//   static GLfloat n[6][3] =
//   {
//     {-1.0, 0.0, 0.0},
//     {0.0, 1.0, 0.0},
//     {1.0, 0.0, 0.0},
//     {0.0, -1.0, 0.0},
//     {0.0, 0.0, 1.0},
//     {0.0, 0.0, -1.0}
//   };
//   static GLint faces[6][4] =
//   {
//     {0, 1, 2, 3},
//     {3, 2, 6, 7},
//     {7, 6, 5, 4},
//     {4, 5, 1, 0},
//     {5, 6, 2, 1},
//     {7, 4, 0, 3}
//   };
//   GLfloat v[8][3];
//   GLint i;
//
//   v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
//   v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
//   v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
//   v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
//   v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
//   v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;
//
//   for (i = 5; i >= 0; i--) {
//     glBegin(type);
//     glNormal3fv(&n[i][0]);
//     glVertex3fv(&v[faces[i][0]][0]);
//     glVertex3fv(&v[faces[i][1]][0]);
//     glVertex3fv(&v[faces[i][2]][0]);
//     glVertex3fv(&v[faces[i][3]][0]);
//     glEnd();
//   }
// }


void Car::drawCarBody(){
        GLuint texture;

        glPushMatrix();
        glTranslatef(100,118, 20);

        glColor3f(1,1,1);
        texture = LoadTextureRAW("car_top.bmp");
        glBindTexture(GL_TEXTURE_2D, texture);
        glScalef(30, 75, 15);

        glBegin(GL_QUADS);
        // Front Face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);      // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);      // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);      // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);      // Top Left Of The Texture and Quad
        // Back Face
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);      // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);      // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);      // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);      // Bottom Left Of The Texture and Quad
        glEnd();

        texture = LoadTextureRAW("car_back.bmp");
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        // Top Face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);      // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);      // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);      // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);      // Top Right Of The Texture and Quad
        glEnd();


        texture = LoadTextureRAW("car_front.bmp");
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        // Bottom Face
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);      // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);      // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);      // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);      // Bottom Right Of The Texture and Quad
        glEnd();

        texture = LoadTextureRAW("car_side.bmp");
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        // Right face
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);      // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);      // Top Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);      // Top Left Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);      // Bottom Left Of The Texture and Quad
        // Left Face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);      // Bottom Left Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);      // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);      // Top Right Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);      // Top Left Of The Texture and Quad
        glEnd();

        // drawBox(1, GL_QUADS, "carro.bmp");
        glPopMatrix();
}

void Car::drawCarAxis(){
        //Front axis
        glPushMatrix();
        glTranslatef(70, 70, 0);
        glRotatef(90, 0, 1, 0);
        GLUquadricObj *quadObj = gluNewQuadric();
        gluQuadricNormals(quadObj, GLU_SMOOTH);
        gluCylinder(quadObj, 3, 3, 60, 10, 100);
        glPopMatrix();

        //Back Axis
        glPushMatrix();
        glTranslatef(70, 160, 0);
        glRotatef(90, 0, 1, 0);
        GLUquadricObj *quadObj2 = gluNewQuadric();
        gluQuadricNormals(quadObj2, GLU_SMOOTH);
        gluCylinder(quadObj2, 3, 3, 60, 10, 100);
        glPopMatrix();

        //Center axis
        glPushMatrix();
        glTranslatef(100, 70, 0);
        glRotatef(90, 0, 0, 1);
        glRotatef(90, 0, 1, 0);
        GLUquadricObj *quadObj3 = gluNewQuadric();
        gluQuadricNormals(quadObj3, GLU_SMOOTH);
        gluCylinder(quadObj3, 3, 3, 100, 10, 100);
        glPopMatrix();
}

void Car::drawFrontWheels(){

        glPushMatrix();
        glTranslatef(70,70,0);
        glRotatef(this->getWheelsAngle(), 0, 0, 1);
        glTranslatef(-5, 0, 0);
        glRotatef(this->getIncrementalNumber(), 1, 0, 0);
        glRotatef(90, 0, 1, 0);
        this->drawSingleWheel();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(130,70,0);
        glRotatef(this->getWheelsAngle(), 0, 0, 1);
        glTranslatef(-5, 0, 0);
        glRotatef(this->getIncrementalNumber(), 1, 0, 0);
        glRotatef(90, 0, 1, 0);
        this->drawSingleWheel();
        glPopMatrix();
}

void Car::drawBackWheels(){
        glPushMatrix();
        glTranslatef(70,160,0);
        glTranslatef(-5, 0, 0);
        glRotatef(90, 0, 1, 0);
        this->drawSingleWheel();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(130,160,0);
        glTranslatef(-5, 0, 0);
        glRotatef(90, 0, 1, 0);
        this->drawSingleWheel();
        glPopMatrix();
}

void Car::drawSingleWheel(){
        glColor3f(0,0,0);
        GLUquadricObj *quadObj = gluNewQuadric();
        gluQuadricNormals(quadObj, GLU_SMOOTH);
        gluDisk(quadObj, 0, 10, 10, 100);
        glPushMatrix();
        glTranslatef(0, 0, 10);
        gluDisk(quadObj, 0, 10, 10, 100);
        glPopMatrix();
        gluCylinder(quadObj, 10, 10, 10, 10, 100);
}

void Car::drawCarCannon(){
        glPushMatrix();
        glColor3f(0,0,0);
        glTranslatef(100,50,15);
        glRotatef(this->getCannonAngle(), 0, 0, 1);
        glRotatef(90, 1, 0, 0);
        GLUquadricObj *quadObj = gluNewQuadric();
        gluQuadricNormals(quadObj, GLU_SMOOTH);
        gluCylinder(quadObj, 10, 10, 35, 10, 100);

        glPushMatrix();
        glTranslatef(0,0,30);
        gluSphere(quadObj, 10, 50, 100);
        glPopMatrix();

        glPopMatrix();
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
                        10
                        );
                glRotatef((*it).getCarAngle(), 0, 0, 1);
                glScalef(
                        2*this->getCircleRadius()/this->getWidth(),
                        2*this->getCircleRadius()/this->getHeight(),
                        1
                        );

                glTranslatef(
                        -this->getWidth()/2,
                        -this->getHeight()/2,
                        0
                        );
                glTranslatef(
                        this->getCannon().getBeginX() + this->getCannon().getWidth()/2,
                        this->getCannon().getBeginY() + this->getCannon().getHeight(),
                        0
                        );
                glRotatef((*it).getCannonAngle(), 0, 0, 1);
                glTranslatef(
                        0,
                        -this->getCannon().getHeight(),
                        0
                        );
                GLUquadricObj *quadObj = gluNewQuadric();
                gluQuadricNormals(quadObj, GLU_SMOOTH);
                gluSphere(quadObj, 5, 50, 100);

                glPopMatrix();
        }
        glPopMatrix();
        return;

}

void Car::addShot(){
        Circle shotCircle = Circle("Shot", 12, 0, 0, "yellow");
        Shot shot = Shot(shotCircle,this->getCenterX(),this->getCenterY(),this->getTheta(),this->getCannonAngle());
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
                (*it).setCenterX((*it).getCenterX() + t*this->getShotSpeed()*cos((angle-90)*M_PI/180));
                (*it).setCenterY((*it).getCenterY() + t*this->getShotSpeed()*sin((angle-90)*M_PI/180));
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
