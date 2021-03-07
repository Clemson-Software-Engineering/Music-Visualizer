#include "display.h"

using namespace std;

string filename;
kiss_fft_cpx in[10], out[10];

// void getFFT(const kiss_fft_cpx* in, kiss_fft_cpx* out){
//   kiss_fft_cfg cfg;
//   kiss_fft(cfg, in, out);
//   free(cfg);
// }


// Controls keyboard inputs
void keyboard(unsigned char c, int x, int y) {
  // Exit application on space bar press
  if (c == 32) {
    exit(0);
  }
}

// Controls mouse inputs
void mouse(int button, int state, int x, int y) {
  // exit application on right click
  if(button == GLUT_RIGHT_BUTTON) {
    exit(0);
  }
}

// Prints text to window
void text(int x, int y, float r, float g, float b, char* string) {
  int j = strlen(string);
  glColor3f(r, g, b);
  glRasterPos2f(x, y);
  
  // Load string one char at a time
  for(int i = 0; i < j; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
  }
}

// Controls what happens on the window in this function
void render(void) {
  // Window sizes for x,y coordinates
  int const w = glutGet(GLUT_WINDOW_WIDTH);
  int const h = glutGet(GLUT_WINDOW_HEIGHT);
  
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT);
  
  // Prepare screen for loading of text
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, h, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // Load text
  char string[] = {"Hello, World!"};
  text(100.0, 100.0, 255.0, 255.0, 255.0, string);
  glutSwapBuffers();
}

// Main creates the window and calls render()
int main(int argc, char** argv) {

  if (argc < 2){
    printf("Usage: wave_iteration <FILENAME>\n");
    return 1;
  } 

  filename = argv[1];

  // Creates window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Music Visualizer");
  
  // Renders function for window
  glutDisplayFunc(render);
  
  // Add keyboard and mouse functionality
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  
  // Initiates the GLUT code, opens window
  glutMainLoop();
  return 0;
}