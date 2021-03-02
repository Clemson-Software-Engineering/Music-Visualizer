#include "display.h"

// main creates the window and calls render()
int main(int argc, char** argv) {
  // creates window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Music Visualizer");
  // renders function for window
  glutDisplayFunc(render);
  // add keyboard and mouse functionality
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  // initiates the GLUT code, opens window
  glutMainLoop();
}

// controls keyboard inputs
void keyboard(unsigned char c, int x, int y) {
  // exit application on space bar press
  if (c == 32) {
    exit(0);
  }
}

// controls mouse inputs
void mouse(int button, int state, int x, int y) {
  // exit application on right click
  if(button == GLUT_RIGHT_BUTTON) {
    exit(0);
  }
}

// prints text to window
void text(int x, int y, float r, float g, float b, char* string) {
  int j = strlen(string);
  glColor3f(r, g, b);
  glRasterPos2f(x, y);
  // load string one char at a time
  for(int i = 0; i < j; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
  }
}

// controls what happens on the window in this function
void render(void) {
  // window sizes for x,y coordinates
  int const w = glutGet(GLUT_WINDOW_WIDTH);
  int const h = glutGet(GLUT_WINDOW_HEIGHT);
  // clear screen
  glClear(GL_COLOR_BUFFER_BIT);
  // prepare screen for loading of text
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, h, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // load text
  char string[] = {"hello world"};
  text(100.0, 100.0, 255.0, 255.0, 255.0, string);
  glutSwapBuffers();
}
