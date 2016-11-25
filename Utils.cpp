#include "Utils.h"

void Utils::checkColor(string fill, GLfloat opacity){
								if(fill == "blue")
																glColor4f(0.0, 0.0, 1.0, opacity);
								else if(fill == "darkblue")
																glColor4f(0.0, 0.0, 0.5, opacity);
								else if(fill == "red")
																glColor4f(1.0, 0.0, 0.0, opacity);
								else if(fill == "darkred")
																glColor4f(0.5, 0.0, 0.0, opacity);
								else if(fill == "green")
																glColor4f(0.0, 1.0, 0.0, opacity);
								else if(fill == "darkgreen")
																glColor4f(0.0, 0.5, 0.0, opacity);
								else if(fill == "cyan")
																glColor4f(0.0, 1.0, 1.0, opacity);
								else if(fill == "darkcyan")
																glColor4f(0.0, 0.5, 0.5, opacity);
								else if(fill == "magenta")
																glColor4f(1.0, 0.0, 1.0, opacity);
								else if(fill == "darkmagenta")
																glColor4f(0.5, 0.0, 0.5, opacity);
								else if(fill == "yellow")
																glColor4f(1.0, 1.0, 0.0, opacity);
								else if(fill == "darkyellow")
																glColor4f(0.5, 0.5, 0.0, opacity);
								else if(fill == "white")
																glColor4f(1.0, 1.0, 1.0, opacity);
								else if(fill == "black")
																glColor4f(0.0, 0.0, 0.0, opacity);
								return;
}

int Utils::randomInt(int min, int max){
								srand(clock());
								return min + (rand() % (max - min + 1));
}

GLfloat Utils::distance2P(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){
								return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

}
