#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
#include <GL/freeglut.h>

// AMBIENTE / ILUMINAÇAO / VISAO

void init_setup(){

  GLfloat mat_ambient[]={0.7f,0.7f,0.7f,0.1f};
  GLfloat mat_diffuse[]={0.5f,0.5f,0.5f,1.0f};
  GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
  GLfloat mat_shininess[]={50.0f};
  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
  GLfloat light_Intensity[]={0.7f,0.7f,0.7f,1.0f};
  GLfloat light_Position[]={2.0f,6.0f,3.0f,0.0f};
  glLightfv(GL_LIGHT0,GL_POSITION,light_Position);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light_Intensity);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double winlet=4.0;
  glOrtho(-winlet*64/48,winlet*64/48.0,-winlet*64/48,winlet*64/48,0.6,100.0);

  //glFrustum(-1.0,1.0,-1.0,1.0,2.0,100.0);

  //gluPerspective(60.0,winlet*64/48.0, 2.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

}
