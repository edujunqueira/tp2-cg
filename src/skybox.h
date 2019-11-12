#ifndef _SKYBOX_CLASS
#define _SKYBOX_CLASS

#include "global.h"

class skybox
{

private:
    GLuint textures[SKYBOX_DOWN+1];

public:
    skybox();
    void loadSkybox(int id);
    void draw(float x, float y, float z, float width, float height, float length);

};

#endif /* _SKYBOX_CLASS */
