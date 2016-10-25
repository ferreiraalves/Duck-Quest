#ifndef __MAPA__H_
#define __MAPA__H_


void map_init();
void map_print();
void wall();
void draw_room();
void desenhaLabirinto();
void sobeCameraZ();
void desceCameraZ();
void sobeCameraX();
void desceCameraX();
int check_inbouds(int i, int j);
GLuint loadwall();
void generate_random();

void inicializa ();
void imprime ();

void pushpilha();

void poppilha();

void imprimePilha();

int validaXY();

void verifica();

void duck();

void changefloor();

void switch_frame();

void universo();

float getHeight();

float getWidth();


#endif
