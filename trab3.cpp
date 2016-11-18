/*****************************************************************************************
**																						**
**						UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO							**
**							   Luiz Felipe Ferreira Mai               **
**																						**
**						   Trabalho 3 de Computação Gráfica								**
**																						**
*****************************************************************************************/

#include "trab3.h"

GLuint LoadTextureRAW(const char *filename);

using namespace std;

Trab3 trab;
int i_status[1000];
//Arena variables
vector<Circle> trackVector;
Rectangle* startTrack;
Car* player;
int biggestRadius = 0, smallestRadius = 99999;
int width, height;
int arenaCenterX = 0, arenaCenterY = 0;
//Foes variables
vector<Car> foesVector;
GLfloat foeSpeed;
GLfloat foeShootingSpeed;
GLfloat foeShootingFrequency;
GLfloat shootingTime = 0;
GLfloat t;
//Text variables
static char str[2000];
void * timer_font = GLUT_BITMAP_9_BY_15;
void * end_font = GLUT_BITMAP_TIMES_ROMAN_24;
time_t start;
//End of the game variables
int gameState = 0;
bool crossedLine1 = false, crossedLine2 = false;
//Camera variables
int cameraMode = 0;  //0:Cockpit  /  1:Canhão  /  2:Externa
GLfloat cam1x, cam1y, cam1z, cam2x, cam2y, cam2z, centro_x, centro_y, centro_z;
int lastX, lastY;
int buttonDown;
double camDist=10;
double camXYAngle=0;
double camXZAngle=0;

GLuint parede;
GLuint chao;
GLuint teto;
GLuint largada;
bool night_mode;


int main(int argc, char** argv) {
								start = time(0);
								player = new Car("player");

								//Reads the config and arena files.
								string arenaFullPath = trab.getArenaPath(argc, argv);
								trackVector = trab.arenaReading(trab, arenaFullPath, trackVector);
								width = 2*biggestRadius;
								height = 2*biggestRadius;

								//OpenGL initializations
								glutInit(&argc, argv);
								glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
								glutInitWindowSize(500,500);
								glutInitWindowPosition(100,100);
								glutCreateWindow("Trabalho Final de Computacao Grafica");

								glClearColor(0,0,0,0);
								glEnable(GL_DEPTH_TEST);
							    glEnable( GL_TEXTURE_2D );
							    glEnable(GL_LIGHTING);
								glShadeModel (GL_SMOOTH);

							    glDepthFunc(GL_LEQUAL);
								glViewport(0,0,500,500);


								chao = LoadTextureRAW( "floor.bmp" );
								parede = LoadTextureRAW( "parede.bmp" );
								teto = LoadTextureRAW( "sky.bmp" );
								largada = LoadTextureRAW("largada.bmp");

								glClearDepth(1.0f);
								glDepthFunc(GL_LEQUAL);
								glMatrixMode(GL_PROJECTION);
								gluPerspective(60.0f, -1, 1, 1000);
								glMatrixMode(GL_MODELVIEW);
								glLoadIdentity();
								glutIdleFunc(idle);
								glutKeyboardFunc(keyPressed);
								glutKeyboardUpFunc(keyUp);
								glutMouseFunc(mouseClick);
								glutMotionFunc(moveCamera);
								glutPassiveMotionFunc(mouseMotion);

								glEnable(GL_LIGHT0);

								glutDisplayFunc(display);

								glutMainLoop();
								return 0;
}

void drawWalls(){
								GLuint texture = parede;
								GLfloat materialEmission[] = { 1.0, 1.0, 1.0, 1};
								GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
								GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
								GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1};
								GLfloat mat_shininess[] = { 100.0 };
								// if(textura_ligada==0)glColor3f(1,0,0);

								glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
								glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
								glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
								glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
								glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

								// if(textura_ligada){
								glColor3f(1,1,1);
								glBindTexture (GL_TEXTURE_2D, texture);
								double textureS = 15;

								float j = 0, i=0;
								float definition = 0.1;
								Circle pistaOut = trackVector.at(0);
								GLfloat x = pistaOut.getCenterX();
								GLfloat y = pistaOut.getCenterY();
								GLfloat altura = 100;
								// GLfloat altura = 4*player->getZHeight();


								glPushMatrix();
								glTranslatef(x, y, 0);

								//desenha parede externa (cilindro oco)
								for(i = 0; i < 2; i++) {
																GLfloat raio = trackVector.at(i).getRadius();

																glBegin(GL_QUAD_STRIP);
																for(j = 0; j <= 2 * M_PI; j += definition) {
																								const float tc = ( j / (float)( 2 * M_PI ) );
																								glNormal3f(0,1,0);
																								glTexCoord2f( textureS * tc, 0.0 );
																								glVertex3f(raio*cos(j), raio*sin(j), altura);
																								glTexCoord2f( textureS * tc, 1.0 );
																								glVertex3f(raio*cos(j), raio*sin(j), 0);
																}
																glTexCoord2f( 0.0, 0.0 );
																glVertex3f(raio, 0, altura);
																glTexCoord2f( 0.0, 1.0 );
																glVertex3f(raio, 0, 0);
																glEnd();
								}

								glPopMatrix();

}

void drawFloor(){
								GLuint texture = chao;

								GLfloat materialEmission[] = { 1.0, 1.0, 1.0, 1};
								GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
								GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
								GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1};
								GLfloat mat_shininess[] = { 100.0 };
								// if(textura_ligada==0)glColor3f(1,1,0);

								glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
								glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
								glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
								glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
								glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

								// if(textura_ligada){
								glColor3f(1,1,1);
								glBindTexture (GL_TEXTURE_2D, texture);
								double textureS = 10;
								GLfloat height_window = 800; //é mil e quinhentox mas ela só ganha 750, a outra metade ela pegou na bolsa da amiga dela
								GLfloat width_window = 800;
								glBegin (GL_QUADS);
								glNormal3f(0,1,0);
								glTexCoord2f (0, 0);
								glVertex3f (0, 0, 0);
								glNormal3f(0,1,0);
								glTexCoord2f (0, textureS);
								glVertex3f (0, height_window, 0);
								glNormal3f(0,1,0);
								glTexCoord2f (textureS, textureS);
								glVertex3f (width_window, height_window,0);
								glNormal3f(0,1,0);
								glTexCoord2f (textureS, 0);
								glVertex3f (width_window, 0,0);
								glEnd();
}

void drawSky()
{
								GLuint texture = teto;
								GLfloat materialEmission[] = { 1.0, 1.0, 1.0, 1};
								GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
								GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
								GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1};
								GLfloat mat_shininess[] = { 100.0 };
								// if(textura_ligada==0)glColor3f(1,0,0);

								glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
								glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
								glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
								glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
								glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

								// if(textura_ligada){
								glColor3f(1,1,1);
								glBindTexture (GL_TEXTURE_2D, texture);
								double textureS = 10;
								GLfloat height_window = 800;
								GLfloat width_window = 800;
								GLfloat altura = 100;
								glBegin (GL_QUADS);
								glNormal3f(0,1,0);
								glTexCoord2f (0, 0);
								glVertex3f (0,0,altura);
								glNormal3f(0,1,0);
								glTexCoord2f (0, textureS);
								glVertex3f (0, height_window,altura);
								glNormal3f(0,1,0);
								glTexCoord2f (textureS, textureS);
								glVertex3f (width_window, height_window,altura);
								glNormal3f(0,1,0);
								glTexCoord2f (textureS, 0);
								glVertex3f (width_window, 0,altura);
								glEnd();
}


void display(){
								glClearColor (0.0,0.0,0.0,1.0);
								glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
								glLoadIdentity();
								trab.printCronometer(0.88,0.95);


								//If player hasn't won or lost
								if(gameState == 0) {


																GLfloat scale = player->getCircleRadius()/player->getWidth();
																if(cameraMode == 0) {
																								cam1x=player->getCenterX()+t*(player->getSpeed()*cos((player->getTheta()-90)*M_PI/180));
																								cam1y=player->getCenterY()+t*(player->getSpeed()*sin((player->getTheta()-90)*M_PI/180));
																								cam1z=15;
																								centro_x=player->getCenterX()+5000*(player->getSpeed()*cos((player->getTheta()-90)*M_PI/180));
																								centro_y=player->getCenterY()+5000*(player->getSpeed()*sin((player->getTheta()-90)*M_PI/180));
																								centro_z=0;
																								gluLookAt(cam1x, cam1y, cam1z, centro_x, centro_y, centro_z, 0, 0, 1);
																} else if(cameraMode == 1) {
																								GLfloat angulo = player->getTheta() + player->getCannonAngle();
																								GLfloat scale = player->getCircleRadius()/player->getHeight();
																								cam1x = player->getCenterX()+(sin(player->getTheta()*M_PI/180)*player->getCircleRadius())+(sin(angulo*M_PI/180)*player->getCannon().getHeight()*scale);
																								cam1y = player->getCenterY()-(cos(player->getTheta()*M_PI/180)*player->getCircleRadius())-(cos(angulo*M_PI/180)*player->getCannon().getHeight()*scale);
																								cam1z = 25+sin(player->getCannonZAngle()*M_PI/180)*player->getCannon().getHeight()*scale;
																								centro_x = cam1x + sin(angulo*M_PI/180)*200;
																								centro_y = cam1y - cos(angulo*M_PI/180)*200;
																								centro_z = cam1z + sin(player->getCannonZAngle()*M_PI/180)*200;
																								gluLookAt(cam1x,cam1y,cam1z, centro_x,centro_y,centro_z, 0,0,1);
																} else if(cameraMode == 2) {
																								cam1x = player->getCenterX() + 5*(player->getCircleRadius())*sin((camXYAngle)*M_PI/180)*cos((camXZAngle)*M_PI/180);
																								cam1y = player->getCenterY() + 5*(player->getCircleRadius())*cos((camXYAngle)*M_PI/180)*cos((camXZAngle)*M_PI/180);
																								cam1z= 80;
																								gluLookAt(cam1x,cam1y,cam1z, player->getCenterX(),player->getCenterY(),60, 0,0,1);
																}

																GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
															    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

															   glEnable(GL_LIGHT1);
															   GLfloat light_position1[] = { 400.0, 400.0, 0.0, 1.0 };
															   GLfloat light1[] = {1,1,1,1};
															   glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
															   glLightfv(GL_LIGHT1, GL_DIFFUSE, light1);

																//Draw scenario
																drawFloor();
																// drawSky();
																// drawWalls();


																//Draws all the tracks
																vector<Circle>::iterator it = trackVector.begin();
																// for(vector<Circle>::iterator it = trackVector.begin(); it != trackVector.end(); ++it) {
																// (*it).drawCircle();
																// }

																//Draws the start track
																glPushMatrix();
																glTranslatef(0,0,1);
																startTrack->drawRectangle(largada);
																glPopMatrix();

																//Draws the player's car
																Circle* c = new Circle("id", player->getCircleRadius(), player->getCenterX(), player->getCenterY(), "green");
																c->drawCircle();
																player->drawCar();


																//Draws all the foes
																for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
																								(*it).drawCar();
																}

																//Draws all the shots
																player->drawShots();
																for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
																								(*it).drawShots();
																}
																//Renders the cronometer at the corner of the screen
																// Utils utils;
																// utils.checkColor("white");
																// trab.printCronometer(60,70);




								} else{
																//GAME OVER or YOU WIN
																trab.printEndMessage(width/2, height/2);
								}
								glutSwapBuffers();
								glFlush();
								return;
}

void idle(){
								//If player hasn't won or lost
								if(gameState == 0) {
																//Position before moving (used in case of colision)
																float oldCenterX =  player->getCenterX();
																float oldCenterY =  player->getCenterY();

																//Measure of the elapsed time
																static GLdouble previousTime = 0;
																GLdouble currentTime;
																currentTime = glutGet(GLUT_ELAPSED_TIME);
																t = currentTime - previousTime;
																previousTime = currentTime;

																//Player movement
																char c;
																if(i_status['w'] == 1 || i_status['W'] == 1 || i_status['s'] == 1 || i_status['S'] == 1) {
																								player->setMoving(true);
																								//Moves the carroInimigoFileElement
																								if(i_status['w'] == 1 || i_status['W'] == 1) {
																																player->moveForward(t);
																								}
																								if(i_status['s'] == 1 || i_status['S'] == 1) {
																																player->moveBackward(t);
																								}

																								//Check if player won
																								bool betweenStartTrackX = (player->getCenterX() > startTrack->getBeginX())
																																																		&& (player->getCenterX() < startTrack->getBeginX() + startTrack->getWidth());
																								bool betweenStartTrackY = (player->getCenterY() > startTrack->getBeginY() - startTrack->getHeight())
																																																		&& (player->getCenterY() < startTrack->getBeginY() + startTrack->getHeight());
																								bool aboveStartTrack = player->getCenterY() < startTrack->getBeginY() - startTrack->getHeight();
																								bool belowStartTrack = player->getCenterY() > startTrack->getBeginY() + startTrack->getHeight();

																								if( aboveStartTrack && betweenStartTrackX) {
																																crossedLine1 = true;
																																crossedLine2 = false;
																								}

																								if(belowStartTrack && betweenStartTrackX) {
																																crossedLine2 = true;
																								}

																								if(betweenStartTrackY && betweenStartTrackX) {
																																if(crossedLine1 && crossedLine2) {
																																								gameState = 1;
																																} else {
																																								crossedLine1 = false;
																																								crossedLine2 = false;
																																}
																								}
																} else {
																								player->setMoving(false);
																}


																//Sets the angle of the wheels
																c = 'a';
																if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() - 5);
																c = 'A';
																if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() - 5);
																c = 'd';
																if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() + 5);
																c = 'D';
																if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() + 5);

																c = '1';
																if(i_status[c] == 1) cameraMode = 0;
																c = '2';
																if(i_status[c] == 1) cameraMode = 1;
																c = '3';
																if(i_status[c] == 1) cameraMode = 2;

																//ativa/desativa modo noturno
																if(i_status['n'] == 1 || i_status['N'] == 1){
																	night_mode = !night_mode;

																	if(night_mode){
																		teto = LoadTextureRAW("sky_night.bmp");
																	} else {
																		teto = LoadTextureRAW("sky.bmp");
																	}

																}

																//Updates the position of all the shots
																//Erases the shots that are outside the screen.
																vector<Shot> playerShotsVector = player->getShotsVector();
																player->updateShots(t);
																playerShotsVector.erase(
																								remove_if(playerShotsVector.begin(), playerShotsVector.end(), outOfScreen),
																								playerShotsVector.end());
																foesVector.erase(
																								remove_if(foesVector.begin(), foesVector.end(), detectEnemyShotColision),
																								foesVector.end());

																//Adds a shot to the foes every X seg.
																shootingTime += foeShootingFrequency*t;
																// if(shootingTime >= 1) {
																//  for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
																//   (*it).addShot();
																//  }
																//  shootingTime = 0;
																// }

																//Detects colision with the foes and tracks
																if(player->detectFoeColision(foesVector) || player->detectTrackColision(trackVector, biggestRadius)) {
																								player->setCenterX(oldCenterX);
																								player->setCenterY(oldCenterY);
																}

																//Detects colision with the shots
																Utils utils;
																for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
																								vector<Shot> foeShotsVector = (*it).getShotsVector();
																								for(vector<Shot>::iterator it2 = foeShotsVector.begin(); it2 != foeShotsVector.end(); ++it2) {
																																if(utils.distance2P((*it2).getCenterX(), (*it2).getCenterY(), player->getCenterX(),
																																																				player->getCenterY()) < player->getCircleRadius()) {
																																								gameState = -1;
																																}
																								}
																}

																//Gives some AI to the foes
																for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {

																								int index = it - foesVector.begin();
																								vector<Car> otherFoes = foesVector;
																								otherFoes.erase(otherFoes.begin() + index);

																								vector<Shot> foeShotsVector = (*it).getShotsVector();
																								(*it).updateShots(t);

																								foeShotsVector.erase(
																																remove_if(foeShotsVector.begin(), foeShotsVector.end(), outOfScreen),
																																foeShotsVector.end());

																								GLfloat threshold = smallestRadius + (biggestRadius-smallestRadius)/2;

																								if((*it).getBackwardCount() > 0) {
																																(*it).foeMove(t, threshold);
																																(*it).setBackwardCount((*it).getBackwardCount()-1);
																								} else if ((*it).detectTrackColision(trackVector, biggestRadius) || (*it).detectCarColision(*player) || (*it).detectFoeColision(otherFoes)) {
																																Utils utils;
																																(*it).setDirection((*it).getDirection() * (-1));
																																(*it).foeMove(t, threshold);
																																(*it).setBackwardCount(utils.randomInt(10, 50));
																								} else {
																																(*it).setDirection(1);
																																(*it).foeMove(t, threshold);
																								}
																}
								}
								glutPostRedisplay();
								return;
}

bool outOfScreen(Shot shot)
{
								return shot.getCenterX() < arenaCenterX - biggestRadius ||
															shot.getCenterX() > arenaCenterX + biggestRadius ||
															shot.getCenterY() < arenaCenterY - biggestRadius ||
															shot.getCenterY() > arenaCenterY + biggestRadius;
}

bool detectEnemyShotColision(Car car){
								Utils utils;
								vector<Shot> playerShotsVector = player->getShotsVector();
								for(vector<Shot>::iterator it = playerShotsVector.begin(); it != playerShotsVector.end(); ++it) {
																if(utils.distance2P(car.getCenterX(), car.getCenterY(), (*it).getCenterX(), (*it).getCenterY()) < car.getCircleRadius()) {
																								int index = it - playerShotsVector.begin();
																								playerShotsVector.erase(playerShotsVector.begin() + index);
																								player->setShotsVector(playerShotsVector);
																								return true;
																}
								}
								return false;
}

void keyUp(unsigned char key, int x, int y){
								i_status[key] = 0;
								glutPostRedisplay();
								return;
}

void keyPressed(unsigned char key, int x, int y){
								i_status[key] = 1;
								glutPostRedisplay();
								return;
}

void mouseClick(int button, int state, int x, int y){
								if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
																//Cria um novo tiro e insere no vetor
																player->addShot();
								}
								if (button == GLUT_RIGHT_BUTTON) {
																if(state == GLUT_DOWN) {
																								lastX = x;
																								lastY = y;
																								buttonDown = 1;
																} else {
																								buttonDown = 0;
																}
								}
								glutPostRedisplay();
								return;
}

void moveCamera(int x, int y)
{

								if (!buttonDown)
																return;

								if(x-lastX>0) {camXYAngle += 2; }
								else if(x-lastX<0) {camXYAngle -= 2; }

								if(y-lastY>0) {camXZAngle += 2; }
								else if(y-lastY<0) {camXZAngle -= 2; }

								if(camXYAngle>=180) camXYAngle=180;
								if(camXYAngle<=-180) camXYAngle=-180;
								if(camXZAngle>=90) camXZAngle=89;
								if(camXZAngle<=-90) camXZAngle=-89;

								lastX = x;
								lastY = y;

}

void mouseMotion(int x, int y){
								//Determina a angulação do canhão.
								//Canto esquerdo da tela: -45 / Canto direito da tela: +45
								if(x > 250) {
																player->setCannonAngle(45*(x-250)/250);
								} else if (x < 250) {
																player->setCannonAngle(-45*(250-x)/250);
								}

								player->setCannonZAngle(45*(500-y)/500);

								glutPostRedisplay();
								return;
}




//----------------------------MÉTODOS DA CLASSE--------------------------------

Trab3::Trab3(){
}


string Trab3::getArenaPath(int argc, char** argv){
								XMLDocument configs;
								string configFile;
								if(argc == 1) {
																configFile =  "config.xml";
								} else {
																string path = argv[1];
																configFile =  path + "config.xml";
								}
								configs.LoadFile(configFile.c_str());
								XMLElement* aplicationElement = configs.FirstChildElement("aplicacao");
								XMLElement* arenaFileElement = aplicationElement->FirstChildElement("arquivoDaArena");
								XMLElement* carroFileElement = aplicationElement->FirstChildElement("carro");
								player->setSpeed( carroFileElement->FloatAttribute("velCarro"));
								player->setShotSpeed( carroFileElement->FloatAttribute("velTiro"));
								XMLElement* carroInimigoFileElement = aplicationElement->FirstChildElement("carroInimigo");
								foeSpeed = carroInimigoFileElement->FloatAttribute("velCarro");
								foeShootingSpeed = carroInimigoFileElement->FloatAttribute("velTiro");
								foeShootingFrequency = carroInimigoFileElement->FloatAttribute("freqTiro");
								string arenaPath = arenaFileElement->Attribute("caminho");
								string arenaFilename = arenaFileElement->Attribute("nome");
								string arenaExtension = arenaFileElement->Attribute("tipo");
								return arenaPath + arenaFilename + "." + arenaExtension;
}

vector<Circle> Trab3::arenaReading(Trab3 trab, string arenaFullPath, vector<Circle> trackVector){
								XMLDocument arena;
								arena.LoadFile(arenaFullPath.c_str());
								XMLElement* svgElement = arena.FirstChildElement("svg");
								startTrack = trab.rectangleReading(svgElement);
								trackVector = trab.circleReading(svgElement, trackVector);
								return trackVector;
}

Rectangle* Trab3::rectangleReading(XMLElement* svgElement){
								XMLElement* rectElement = svgElement->FirstChildElement("rect");
								Rectangle* rect = new Rectangle(
																rectElement->Attribute("id"),
																rectElement->FloatAttribute("x"),
																rectElement->FloatAttribute("y"),
																rectElement->FloatAttribute("width"),
																rectElement->FloatAttribute("height"),
																rectElement->Attribute("fill")
																);
								return rect;
}

vector<Circle> Trab3::circleReading(XMLElement* svgElement, vector<Circle> trackVector){
								for(XMLElement* circleElement = svgElement->FirstChildElement("circle"); circleElement != NULL; circleElement = circleElement->NextSiblingElement("circle"))
								{
																Circle* circle = new Circle(
																								circleElement->Attribute("id"),
																								circleElement->FloatAttribute("r"),
																								circleElement->FloatAttribute("cx"),
																								circleElement->FloatAttribute("cy"),
																								circleElement->Attribute("fill")
																								);

																if(circle->getID() == "Jogador") {
																								player->setCenterX(circle->getCenterX());
																								player->setCenterY(circle->getCenterY());
																								player->setCircleRadius(circle->getRadius());
																								player->setWidth(circle->getRadius());
																								player->setHeight(circle->getRadius());
																								player->setZHeight(circle->getRadius()/2);
																								player->setColor(circle->getFill());
																} else if(circle->getID() == "Inimigo") {
																								Car* foe = new Car("foe");
																								foe->setCenterX(circle->getCenterX());
																								foe->setCenterY(circle->getCenterY());
																								foe->setCircleRadius(circle->getRadius());
																								foe->setWidth(circle->getRadius());
																								foe->setHeight(circle->getRadius());
																								foe->setZHeight(circle->getRadius()/2);
																								foe->setColor(circle->getFill());
																								foe->setSpeed(foeSpeed);
																								foe->setShotSpeed(foeShootingSpeed);
																								//Put the foes at the right position.
																								GLfloat initialAngle = atan(((arenaCenterY - foe->getCenterY())/(foe->getCenterX() - arenaCenterX)))*180/M_PI;
																								if(foe->getCenterX() < arenaCenterX) {
																																foe->setTheta(180-initialAngle);
																								} else {
																																foe->setTheta(-initialAngle);
																								}
																								foesVector.push_back(*foe);
																} else {
																								trackVector.push_back(*circle);
																								if(circle->getRadius() > biggestRadius) {
																																biggestRadius = circle->getRadius();
																																arenaCenterX = circle->getCenterX();
																																arenaCenterY = circle->getCenterY();
																								}
																								if(circle->getRadius() < smallestRadius) {
																																smallestRadius = circle->getRadius();
																								}
																}
								}
								return trackVector;
}

void Trab3::RasterChars(GLfloat x, GLfloat y, GLfloat z, const char * text, double r, double g, double b)
{
    //Push to recover original attributes
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        //Draw text in the x, y, z position
        glColor3f(0,1,0);
        glRasterPos3f(x, y, z);
        const char* tmpStr;
        tmpStr = text;
        while( *tmpStr ){
            glutBitmapCharacter(timer_font, *tmpStr);
            tmpStr++;
        }
    glPopAttrib();
}

void Trab3::PrintText(GLfloat x, GLfloat y, const char * text, double r, double g, double b)
{
    //Draw text considering a 2D space (disable all 3d features)
    glMatrixMode (GL_PROJECTION);
    //Push to recover original PROJECTION MATRIX
    glPushMatrix();
        glLoadIdentity ();
        glOrtho (0, 1, 0, 1, -1, 1);
        trab.RasterChars(x, y, 0, text, r, g, b);
    glPopMatrix();
    glMatrixMode (GL_MODELVIEW);
}

void Trab3::printCronometer(GLfloat x, GLfloat y){
								char *tmpStr;
								int seconds_since_start = difftime( time(0), start);
								int minutes = seconds_since_start / 60;
								int seconds = seconds_since_start % 60;
								sprintf(str, "%02d:%02d", minutes, seconds);
								trab.PrintText(x, y, str, 0, 1, 0);
}

void Trab3::printEndMessage(GLfloat x, GLfloat y){
								char *tmpStr;
								if(gameState == 1) {
																sprintf(str, "You win!");

								} else if(gameState == -1) {
																sprintf(str, "GAME OVER!");
								}
								this->PrintText(0.48, 0.5, str, 1, 1, 1);
}

void Trab3::drawAxes(double size){
								GLfloat mat_ambient_r[] = { 1.0, 0.0, 0.0, 1.0 };
								GLfloat mat_ambient_g[] = { 0.0, 1.0, 0.0, 1.0 };
								GLfloat mat_ambient_b[] = { 0.0, 0.0, 1.0, 1.0 };
								GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
																					no_mat);
								glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
								glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);

								//x axis
								glPushMatrix();
								glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_r);
								glColor3fv(mat_ambient_r);
								glScalef(size, size*0.1, size*0.1);
								glTranslatef(0.5, 0, 0); // put in one end
								glutSolidCube(1.0);
								glPopMatrix();

								//y axis
								glPushMatrix();
								glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_g);
								glColor3fv(mat_ambient_g);
								glRotatef(90,0,0,1);
								glScalef(size, size*0.1, size*0.1);
								glTranslatef(0.5, 0, 0); // put in one end
								glutSolidCube(1.0);
								glPopMatrix();

								//z axis
								glPushMatrix();
								glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_b);
								glColor3fv(mat_ambient_b);
								glRotatef(-90,0,1,0);
								glScalef(size, size*0.1, size*0.1);
								glTranslatef(0.5, 0, 0); // put in one end
								glutSolidCube(1.0);
								glPopMatrix();

}
