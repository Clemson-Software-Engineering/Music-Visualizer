#include "display.h"

using namespace std;

vector<int> amps(0);
vector<int> freq(0);

string filename;

kiss_fft_cpx in[N], out[N];

//Sound buffers from SMFL
// sf::SoundBuffer buffer;
// sf::Sound sound(buffer);

//Get the FFT of the wav
void getFFT(const kiss_fft_cpx in[N], kiss_fft_cpx out[N]){
  kiss_fft_cfg cfg;
  //kiss_fft(cfg, in, out); //returning linker error
  free(cfg);
}

void init_vis(){
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_POLYGON_SMOOTH);
}

void load_data(){

  //  if (!buffer.loadFromFile(filename.c_str())){
  //    exit(0);
  //  } 

  vector<int>::iterator amp_iteration = amps.begin();
  vector<int>::iterator freq_iteration = freq.begin();

  double sampleRate = 1.0;//buffer.getSampleRate();
  double sampleCount = 1.0;//buffer.getSampleCount();
  auto samples = 1.0;//buffer.getSamples();

  vector<double> data;
  for (int i = 0; i < (int)sampleCount; i++){
    //data.push_back((double)samples[i])
  }

  int frameNum = 0;


}

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
    printf("Usage: ./a.out <FILENAME>\n");
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

  //Initalize the vizualizer
  init_vis();
  
  // Initiates the GLUT code, opens window
  glutMainLoop();
  return 0;
}