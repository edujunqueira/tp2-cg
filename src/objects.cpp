#include <limits.h>
#include <float.h>

#include "objects.h"



void loadTree(float height, float base)
{
	float angle;
    // cilindro //
    GLUquadric *obj = gluNewQuadric();
    glColor3f(0.41f, 0.32f, 0.27f);
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, base, base - (0.2 * base), height, 5,5);
    glPopMatrix();
    // -- - -- //
	glTranslatef(0.0, height, 0.0);
	height -= height * .2;
    base -= base * 0.3;
	for(int a = 0; a < 3; a++){
		angle = rand() % 50 + 20;
		if(angle > 48)
			angle = -(rand() % 50 + 20);
		if (height > 1){
			glPushMatrix();
			glRotatef(angle, 1, 0.0, 1);
			loadTree(height, base);
			glPopMatrix();
		}
        else{
            glColor3f(0.0, 1.0/a, 0.0);
            glutSolidSphere(.2,10,10);
        }
	}
}

void loadFloor(int list, GLuint texture) {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glNewList(list, GL_COMPILE);
        int gridSize = 50;
        float floorHeight = -1, tileSize = 0.20f;
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(-gridSize, floorHeight, -gridSize);
            glTexCoord2f(0, gridSize * 10 * tileSize);
            glVertex3f(-gridSize, floorHeight, gridSize);
            glTexCoord2f(gridSize * 10 * tileSize, gridSize * 10 * tileSize);
            glVertex3f(gridSize, floorHeight, gridSize);
            glTexCoord2f(gridSize * 10 * tileSize, 0);
            glVertex3f(gridSize, floorHeight, -gridSize);
        glEnd();
    glEndList();
}

objects::objects()
{
    listCount = 1;
}

int objects::newObject(int type, GLuint texture, float height, float base)
{
    displayLists.push_back(glGenLists(listCount));
    switch(type)
    {
        case(OBJECT_FLOOR):
            loadFloor(displayLists[listCount-1], texture);
            break;
        case(OBJECT_TREE):

            glNewList(displayLists[listCount-1], GL_COMPILE);
                loadTree(height, base);
            glEndList();
            break;
    }
    listCount++;
    return displayLists[listCount-2];
}
