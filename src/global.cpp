#include "global.h"

GLuint loadTexture(const char* file)
{
    GLuint idTextura = SOIL_load_OGL_texture(
                           file,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (idTextura == 0)
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());

    return idTextura;
}
