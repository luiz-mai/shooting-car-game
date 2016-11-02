#include "Utils.h"

void Utils::checkColor(string fill){
								if(fill == "blue")
																glColor3f(0.0, 0.0, 1.0);
								else if(fill == "darkblue")
																glColor3f(0.0, 0.0, 0.3647);
								else if(fill == "red")
																glColor3f(1.0, 0.0, 0.0);
								else if(fill == "darkred")
																glColor3f(0.3647, 0.0, 0.0);
								else if(fill == "green")
																glColor3f(0.0, 1.0, 0.0);
								else if(fill == "darkgreen")
																glColor3f(0.0, 0.3647, 0.0);
								else if(fill == "cyan")
																glColor3f(0.0, 1.0, 1.0);
								else if(fill == "darkcyan")
																glColor3f(0.0, 0.3647, 0.3647);
								else if(fill == "magenta")
																glColor3f(1.0, 0.0, 1.0);
								else if(fill == "darkmagenta")
																glColor3f(0.3647, 0.0, 0.3647);
								else if(fill == "yellow")
																glColor3f(1.0, 1.0, 0.0);
								else if(fill == "darkyellow")
																glColor3f(0.3647, 0.3647, 0.0);
								else if(fill == "white")
																glColor3f(1.0, 1.0, 1.0);
								else if(fill == "black")
																glColor3f(0.0, 0.0, 0.0);
								return;
}

int Utils::randomInt(int min, int max){
								srand(clock());
								return min + (rand() % (max - min + 1));
}
