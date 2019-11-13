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

enum OBJECTS_TYPE {
    OBJECT_NONE,
    OBJECT_FLOOR,
    OBJECT_TREE,
    OBJECT_WHEEL,
    OBJECT_STAND,
    OBJECT_BENCH,
};

#define CAMERA_SPEED 0.001f
#define drand48() (((float) rand())/((float) RAND_MAX))
#define srand48(x) (srand((x)))

#endif /* GLOBAL_ */
