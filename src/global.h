#ifndef GLOBAL_
#define GLOBAL_


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <cmath>
#include <iostream>
#include <vector>

GLuint loadTexture(const char* file);

enum KEYS {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT
};

enum SKYBOX_DIR {
    SKYBOX_FRONT,
    SKYBOX_BACK,
    SKYBOX_LEFT,
    SKYBOX_RIGHT,
    SKYBOX_UP,
    SKYBOX_DOWN
};

#endif /* GLOBAL_ */
