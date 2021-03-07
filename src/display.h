#define GL_SILENCE_DEPRECATION
#include "GL/glut.h"
#include "KissFFT/kiss_fft.h"
#include <iostream>

// controls keyboard inputs
void keyboard(unsigned char c, int x, int y);

// controls mouse inputs
void mouse(int button, int state, int x, int y);

// prints text to window
void text(void);

// controls what happens on the window in this function
void render(void);
