/*
  Autor: Anderson Altair Tomkelski
  E-mail: ander.tomkelski@gmail.com

  O seguinte programa tem como objetivo desenhar um braço robótico, formado por 4 cubos que, rotaciona
  suas partes para direita e para a esquerda
*/

#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

// Constants to define the width/height of the window
const int WIDTH = 800;
const int HEIGHT = 800;

// Define how many frames per seconds we want our
// applications to run.
const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;

float angleY = 0;
float positionX = 0;

class Cube {
public:
  float x, y, z, angle;
  float scaleX, scaleY, scaleZ;
  int r, g, b;
  float size;

  Cube(float x, float y, float z, float angle, int r, int g, int b, int size){
    this->x = x;
    this->y = y;
    this->z = z;
    this->angle = angle;
    this->r = r;
    this->g = g;
    this->b = b;
    this->size = size;
  }

  void display(Cube *downCube, float scaleY){
    glColor3f(this->r, this->g, this->b);
    glTranslatef(0, downCube->size / 2, 0);
    glRotatef(this->angle, 0, 0, 1);
    glTranslatef(0, scaleY * this->size / 2, 0);
    glScalef(1, scaleY, 1);
    glutWireCube(this->size);
  }
};

Cube black(0, 1, 0, 0, 0, 0, 0, 1);
Cube red(0, 2, 0, 0, 1, 0, 0, 1);
Cube green(0, 3, 0, 0, 0, 1, 0, 1);
Cube blue(0, 4.5, 0, 0, 0, 0, 1, 1);

void renderCoordinateAxis()
{
	// X axis - green color
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
		// Left side, negative X
		glVertex2f(-10.0, 0.0);
		glVertex2f(0.0, 0.0);

		// Right side, positive X
		glVertex2f(0.0, 0.0);
		glVertex2f(10.0, 0.0);
	glEnd();

	// Y axis - blue color
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		// Top side, positive Y
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 10.0);

		// Bottom side, negative Y
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, -10.0);
	glEnd();
}

void display()
{
	// Clear the screen painting it with the white color
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Inform we want to make changes to the modelview matrix, starting
	// with no transformation at all.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move the camera away from the origin along the Z axis by 10 pixels.
	glTranslatef(0, 0, -10.0f);

  // Rotate under Y axis
  glRotatef(angleY, 0, 1, 0);

	// Render the X and Y axis to guide ourselves.
	renderCoordinateAxis();

  glTranslatef(positionX, 0, 0);

  black.display(&black, 1);

  red.display(&black, 1);

  green.display(&red, 1);

  blue.display(&green, 2);

	// Start the rendering on a new frame
	glutSwapBuffers();
}


void update(int value)
{
	// Update the angle of rotation
	//angle += 3;

	// Request a new frame rendering
	glutPostRedisplay();

	// Re-schedule the update() function to be called after a few
	// milliseconds again.
	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
}


void keyboard(unsigned char key, int x, int y)
{
  if (key == 'Q'){
    // Move red block to right
    if(red.angle >= -70)
      red.angle -= 1;
  }
  if (key == 'A'){
    // Move red block to left
    if(red.angle <= 70)
      red.angle += 1;
  }
  if (key == 'W'){
    // Move green block to right
    if(green.angle >= -70)
      green.angle -= 1;
  }
  if (key == 'S'){
    // Move green block to left
    if(green.angle <= 70)
      green.angle += 1;
    
  }
  if (key == 'E'){
    // Move blue block to right
    if(blue.angle >= -70)
      blue.angle -= 1;
  }
  if (key == 'D'){
    // Move blue block to left
    if(blue.angle <= 70)
      blue.angle += 1;
  }
  if (key == 'Z') {
    // Move arm to left
    positionX -= 1;
  }
  if (key == 'X') {
    // Move arm to right
    positionX += 1;
  }


	if (key == 27) {
		// ESC key
		exit(0);
	}
}

void arrows(int key, int x, int y){
  if(key == 100){
    // Left arrow
    angleY -= 1;
  }
  if(key == 102){
    // Right arrow
    angleY += 1;
  }
}

void mouse(int button, int state, int x, int y)
{
	std::cout << "Mouse pressed: button=" << button << ", state=" << state << ", x=" << x << " y=" << y << std::endl;
}

void initView()
{
	// We want a window to the world that is a rectangle starting at (0,0)
	// and ending at (WIDTH, HEIGHT).
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
	
	// Adjust the global projection (camera)
	glMatrixMode(GL_PROJECTION);
	
	// Reset any existing projection settings and adjust the field-of-view (FOV)
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);
	
	// From now on, every transformation is to be applied on each object, e.g. modelview.
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Transformation - Simple");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
  glutSpecialFunc(arrows);
	glutMouseFunc(mouse);

  glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);

	initView();

	glutMainLoop();
	return 0;
}