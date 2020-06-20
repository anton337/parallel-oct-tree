#ifndef DRAW_H
#define DRAW_H

#include "marching_cubes.h"
#include "common.h"

double global_x = 0;
double global_y = 0;
double global_z = -5;
double global_th = 90;
double global_phi = 180;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(global_x,global_y,global_z);
  glRotatef(global_th,1,0,0);
  glRotatef(global_phi,0,1,0);
  float mcolor[] = {0.5f,0.5f,0.0f,1.0f};
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mcolor);
  draw();
  glPopMatrix();
  glutSwapBuffers();
}

void idle() {
  usleep(10000);
  glutPostRedisplay();
}

void init() {
  glClearColor (1.0, 1.0, 1.0, 1.0); 

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  // glEnable(GL_CULL_FACE);

  glMatrixMode(GL_PROJECTION);

  glMatrixMode(GL_PROJECTION);  // Select The Projection Matrix
  glLoadIdentity();             // Reset The Projection Matrix

  gluPerspective(45.0f,1,0.001f,10000.0f);

  glMatrixMode(GL_MODELVIEW);   // Select The Modelview Matrix
  glLoadIdentity();             // Reset The Modelview Matrix


}

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case 'a':
      global_x += .1;
      break;
    case 'd':
      global_x -= .1;
      break;
    case 'w':
      global_z += .1;
      break;
    case 's':
      global_z -= .1;
      break;
    case 'q':
      global_y -= .1;
      break;
    case 'z':
      global_y += .1;
      break;
    case 'i':
      global_th += 1;
      break;
    case 'k':
      global_th -= 1;
      break;
    case 'j':
      global_phi += 1;
      break;
    case 'l':
      global_phi -= 1;
      break;
    case ' ':
      save();
      break;
    case 'v':
      vbo();
      break;
    case 27: exit(0);
  }
}

int main(int argc, char ** argv) {
  initialize();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1000,1000);
  glutCreateWindow(argv[0]);
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  }
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  init();
  glutMainLoop();
  return 0;
}

#endif
