#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
#include <GL/freeglut.h> // Facilita a criação de código e portabilidade do código OpenGL
#include<time.h>


GLuint loadWall() {
    int aux=SOIL_load_OGL_texture(
        "floor.jpg", // Textura da parede
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (aux==0){
        printf("Erro do SOIL: %s\n",SOIL_last_result());
    }
    return aux;
}


GLuint loadPinto() {
    int aux=SOIL_load_OGL_texture(
        "pintobody.jpg", // Textura do pinto
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (aux==0){
        printf("Erro do SOIL: %s\n",SOIL_last_result());
    }
    return aux;
}

GLuint loadPe() {
    int aux=SOIL_load_OGL_texture(
        "pe.jpg", // Textura do pinto
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (aux==0){
        printf("Erro do SOIL: %s\n",SOIL_last_result());
    }
    return aux;
}

GLuint loadUniverso() {
    int aux=SOIL_load_OGL_texture(
        "universo.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (aux==0){
        printf("Erro do SOIL: %s\n",SOIL_last_result());
    }
    return aux;
}



GLuint loadMetal() {
    int aux=SOIL_load_OGL_texture(
        "metal.jpeg", // Textura do bule
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
