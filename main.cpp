#include<stdio.h>
#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
#include <GL/freeglut.h> // Facilita a criação de código e portabilidade do código OpenGL
//#include <iostream.h>




// ---------- TADS MAPA




const int largura = 400;
const int altura = 400;
int map [largura][altura];
int width, height, channels;
unsigned char *ht_map = SOIL_load_image ("mapa.png",
                                          &width, &height, &channels,
                                          SOIL_LOAD_RGB);

void map_init(){
  int i,j;

  for (i=0;i<height;i++){
    for(j=0;j<width;j++){
      if(ht_map[(i*width+j)*3]==0 && ht_map[(i*width+j)*3+1]==0 && ht_map[(i*width+j)*3+2]==0){
        map[i][j]=0;
      }
      else if(ht_map[(i*width+j)*3]==255 && ht_map[(i*width+j)*3+1]==255 && ht_map[(i*width+j)*3+2]==255){
        map[i][j]=1;
      }else if (ht_map[(i*width+j)*3]==255 && ht_map[(i*width+j)*3+1]==0 && ht_map[(i*width+j)*3+2]==0){
        map[i][j]=2;
      }else {
        map[i][j]=3;
      }
    }
  }
}


void map_print(){
  int i,j;
  for (i=0;i<height;i++){
    for(j=0;j<width;j++){
      if (map[i][j]==0)
        printf("x ");
      else
        printf("  ");

      //printf("%d ",map[i][j]);

    }
    printf("\n");
  }
}

// ---------- TADS MAPA







// ---------- TADS GLUT

// NOVIDADE: callback para o evento "reshape"
void redimensionada(int width, int height) {
/*
    if (height == 0) height = 1; //

    double ratio = (double)width / (double)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    bounds = (Bounds){-ratio,ratio,-1.0,1.0};
//   printf("%f ",bounds.left);
//-ratio, ratio, -1, 1, -1, 1);//
    glOrtho(bounds.left,bounds.right, bounds.bottom,bounds.top, -1.0, 1.0);

//  if (width<=height){
//    gluOrtho2D(0.0, janelaw, 0.0, janelah*height/width);
//  }else{
//    gluOrtho2D(0.0, janelaw*width/height/2, 0.0, janelah);
//  }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
*/
}

// NOVIDADE: callback de "keyboard"
void teclaPressionada(unsigned char key, int x, int y) {
/*
    //printf("%d -> %c\n",key,key);
    // vê qual tecla foi pressionada
    switch(key){
        case 27: // Tecla ESC, sai do jogo
            auxiliarEstado = estadojogo;
            estadojogo = 4;
            glutPostRedisplay();
            break;

        default:
            break;
    }
*/
}

void mousePressionado(int botao, int estado, int x, int y) {
/*    if ((botao == GLUT_LEFT_BUTTON) && (estado == GLUT_UP)) {
        printf("%d e %d\n", x, y);
        if (estadojogo == 4) {
            if ((y > 0) && (y < 600)) {
                if ((x > 0) && (x < 400)) {
                    exit(0);
                } else if ((x > 400) && (x < 1000)) {
                    estadojogo = auxiliarEstado;
                }
            }
        }

        if (estadojogo == 6 || estadojogo == 7) {
            if ((y > 0) && (y < 600)) {
                if ((x > 0) && (x < 400)) {
                    estadojogo = 0;
                    setup();
                } else if ((x > 400) && (x < 1000)) {
                    if (estadojogo == 6) estadojogo = auxiliarEstado;
                    if (estadojogo == 7) exit(0);
                }
            }
        }
    }
*/
}





// ----------- TADS GLUT

void configuraProjecao() {
  float razaoAspecto = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-razaoAspecto, razaoAspecto, -1.0, 1.0, 2.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void redimensiona(int width, int height)
{
    glViewport(0, 0, width, height);
    configuraProjecao();
}

void desenhaCubo(int espaco)
{
  configuraProjecao();
  const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  const double a = t*90.0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3d(1,0,0);

  if(espaco == 0){
  // CUBO sólido
  glPushMatrix();
    glTranslated(2.4,1.2,-6);
    //glRotated(a,0,0,1);
    glutSolidCube(1);
  glPopMatrix();
  } else {
  // CUBO em modelo de arame
  glPushMatrix();
    glTranslated(2.4,-1.2,-6);
    //glRotated(a,0,0,1);
    glutWireCube(1);
  glPopMatrix();
  }
  glutSwapBuffers();
}

static void teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :     // Tecla 'ESC
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;

        case 'p':
        case 'o':
            projection = key;
            break;

        case 32:        // tecla 'Espaço'
            projection = (projection == 'p' ? 'o' : 'p' );
            break;
    }

    glutPostRedisplay();
}

static void atoa(void)
{
    glutPostRedisplay();
}


// configura alguns parâmetros do modelo de iluminação: FONTE DE LUZ
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

// configura alguns parâmetros do modelo de iluminação: MATERIAL
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


int main(int argc, char *argv[]) {
  /*
  glutInit(&argc, argv);
  map_init();
  map_print();


  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(600, 400);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("TP2");

  glutReshapeFunc(redimensionada);
  glutKeyboardFunc(teclaPressionada);
  glutMouseFunc(mousePressionado);







  return 0;
  */

  glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Ortho vs Frustum");

    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);
    glutIdleFunc(atoa);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
