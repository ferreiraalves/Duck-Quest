#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
#include <GL/freeglut.h> // Facilita a criação de código e portabilidade do código OpenGL
#include<time.h>


GLuint loadWall() {
    int aux=SOIL_load_OGL_texture(
        "floor.jpg", // Textura da mira
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (aux==0){
        printf("Erro do SOIL: %s\n",SOIL_last_result());
    }
    return aux;
}

GLuint loadChar() {
    int aux=SOIL_load_OGL_texture(
        "metal.jpeg", // Textura da mira
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (aux==0){
        printf("Erro do SOIL: %s\n",SOIL_last_result());
    }
    return aux;
}

GLuint loadFloor() {
    int aux=SOIL_load_OGL_texture(
        "truefloor2.jpg", // Textura da mira
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (aux==0){
        printf("Erro do SOIL: %s\n",SOIL_last_result());
    }
    return aux;
}