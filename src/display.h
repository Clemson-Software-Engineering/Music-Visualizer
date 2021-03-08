#ifndef DISPLAY_H
#define DISPLAY_H

#define GL_SILENCE_DEPRECATION
#include "GL/glut.h"
#include "KissFFT/kiss_fft.h"
#include <iostream>
#include <vector>
//#include <SFML/Audio.hpp>
#include <sys/time.h>

using namespace std;

#define N 1024

//Externs
extern vector<int> amps;
extern vector<int> freq;
extern kiss_fft_cpx in[N], out[N];

// controls keyboard inputs
void keyboard(unsigned char c, int x, int y);

// controls mouse inputs
void mouse(int button, int state, int x, int y);

// prints text to window
void text(void);

// controls what happens on the window in this function
void render(void);

#endif
