#include <limits.h>
#include <float.h>
#include <math.h>

#include "objects.h"

void loadCarouselStand(int list)
{
	glNewList(list, GL_COMPILE);
		GLUquadric *base = gluNewQuadric();
		glColor3f(0.80f, 0.50f, 0.19f);
		glPushMatrix();
			glRotatef(90, 1.0, 0.0, 0.0);
			gluCylinder(base, 0.2f, 0.35f, 4, 4, 20);
		glPopMatrix();
	glEndList();
}

void loadCarousel(int list)
{
	int sides = 30, linhas = 15;
	glNewList(list, GL_COMPILE);
		glPushMatrix();
			glColor3f(0.80f, 0.50f, 0.19f);
			glBegin(GL_TRIANGLE_FAN);
				glVertex3f(0.0f, 0.0f, 0.0f);
				for(int i = 0; i < (sides + 1); i++){
					float theta = 2.0f * 3.1415926f * i / sides;
					glVertex3f(2.5f * sin(theta), 0.6f, 2.5f * cos(theta));
				}
			glEnd();
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_LINES);
				for(int j = 0; j < linhas; j++){
					float theta = 2.0f * 3.1415926f * j / linhas;
					glVertex3f(2.0f * sin(theta), 0.48f, 2.0f * cos(theta));
					glVertex3f(2.5f * sin(theta), -((rand() % 15 + 15) / 10.0f) , 2.5f * cos(theta));
				}
			glEnd();
		glPopMatrix();
	glEndList();
}

void loadKamikazeStand(int list)
{
	glNewList(list, GL_COMPILE);
		GLUquadric *base = gluNewQuadric();
		GLUquadric *base1 = gluNewQuadric();
		glColor3f(0.6f, 0.6f, 0.6f);
		glPushMatrix();
			glRotatef(90, 1.0, 0.0, 0.0);
			gluCylinder(base, 0.2f, 0.2f, 5, 4, 20);
			glColor3f(0.88f, 0.88f, 0.4f);
			glutSolidSphere(.5, 10, 10);
		glPopMatrix();
		glColor3f(0.6f, 0.6f, 0.6f);
		glPushMatrix();
			glRotatef(90, 0.0, 1.0, 0.0);
			glTranslatef(0.0f, 0.0f, -1.5f);
			gluCylinder(base1, 0.2f, 0.2f, 3, 20, 20);
		glPopMatrix();
	glEndList();
}


void loadKamikaze(int list)
{
	glNewList(list, GL_COMPILE);
	GLUquadric *base = gluNewQuadric();
	GLUquadric *base2 = gluNewQuadric();
	GLUquadric *placa = gluNewQuadric();
	GLUquadric *carro = gluNewQuadric();
	GLUquadric *tampa = gluNewQuadric();
	glColor3f(0.6f, 0.6f, 0.6f);

	// suportes
	glPushMatrix();
		glTranslatef(1.5f, 3.5f, 0.0f);
		glRotatef(90, 1.0, 0.0, 0.0);
		gluCylinder(base, 0.2f, 0.2f, 3.5, 4, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, 0.0f, 0.0f);
		glRotatef(90, 1.0, 0.0, 0.0);
		gluCylinder(base2, 0.2f, 0.2f, 3.5, 4, 20);
	glPopMatrix();

	// placa
	glColor3f(0.28f, 0.38f, 0.81f);
	glPushMatrix();
		glTranslatef(1.5f, 3.5f, -0.2f);
		glRotatef(30, 1.0, 0.0, 0.0);
		gluCylinder(placa, 0.4f, 0.4f, 1.5, 4, 20);
		glTranslatef(0.0f, 0.0f, 1.5f);
		gluDisk(tampa, 0.0f, 0.4f, 4, 4);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.5f, 3.5f, 0.2f);
		glRotatef(-210, 1.0, 0.0, 0.0);
		gluCylinder(placa, 0.4f, 0.4f, 1.5, 4, 20);
		glTranslatef(0.0f, 0.0f, 1.5f);
		gluDisk(tampa, 0.0f, 0.4f, 4, 4);
	glPopMatrix();

	// carro
	glColor3f(0.96f, 0.74f, 0.84f);
	glPushMatrix();
		glTranslatef(1.5f, -3.5f, -1.5f);
		gluCylinder(carro, 0.6f, 0.6f, 3, 4, 20);
		gluDisk(tampa, 0.0f, 0.6f, 4, 4);
		glTranslatef(0.0f, 0.0f, 3.0f);
		gluDisk(tampa, 0.0f, 0.6f, 4, 4);
	glPopMatrix();

	glEndList();
}

void loadStand(int list)
{
	glNewList(list, GL_COMPILE);
		float size = 0.1f;
		GLUquadric *base = gluNewQuadric();
		GLUquadric *baseCentral = gluNewQuadric();
	    glColor3f(0.39f, 0.19f, 0.08f);

	    glPushMatrix();
	    	glTranslatef(0.0f, 1.0f, 0.0f);
		    glRotatef(60, 1.0, 0.0, 0.0);
	    	gluCylinder(base, size, size, 3.5, 4, 20);
	    glPopMatrix();

		glPushMatrix();
	    glTranslatef(0.0f, -2.0f, -1.7f);
		glRotatef(-60, 1.0, 0.0, 0.0);
	    	gluCylinder(base, size, size, 3.5, 4, 20);
	    glPopMatrix();

		glPushMatrix();
		    glTranslatef(1.0f, 1.0f, 0.0f);
		    glRotatef(60, 1.0, 0.0, 0.0);
	    	gluCylinder(base, size, size, 3.5, 4, 20);
	    glPopMatrix();

		glPushMatrix();
	    glTranslatef(1.0f, -2.0f, -1.7f);
		glRotatef(-60, 1.0, 0.0, 0.0);
	    	gluCylinder(base, size, size, 3.5, 4, 20);
	    glPopMatrix();

		glPushMatrix();
	    glTranslatef(-0.2f, 1.0f, 0.0f);
	    glRotatef(90, 0.0, 1.0, 0.0);
	    	gluCylinder(baseCentral, size * 2, size * 2, 1.4f, 20, 20);
	    glPopMatrix();


		glPushMatrix();
	    glTranslatef(-0.2f, 1.0f, 0.0f);
	    glRotatef(90, 0.0, 1.0, 0.0);
	    	gluDisk(baseCentral, 0, size * 2, 20, 20);
		glTranslatef(0.0f, 0.0f, 1.4f);
   	    	gluDisk(baseCentral, 0, size * 2, 20, 20);
	    glPopMatrix();
	glEndList();
}

void loadWheel(int list)
{
	int sides = 12;
	glNewList(list, GL_COMPILE);
		GLUquadric *roda = gluNewQuadric();
		glLineWidth(3);
	    glColor3f(1.0f, 1.0f, 1.0f);
		glPushMatrix();
			// disco 1
		    glRotatef(90, 0.0f, 1.0, 0.0);
		    	gluDisk(roda, 2.0f - 0.1f, 2.0f, sides, sides);
			// disco 2
			glTranslatef(0.0f, 0.0f, 0.6f);
	   	    	gluDisk(roda, 2.0f - 0.1f, 2.0f, sides, sides);
	    glPopMatrix();
		glLineWidth(2);

		// linhas do centro até as rodas
		glColor3f(1.0f, 1.0f, 0.0f);
		glPushMatrix();
			glRotatef(90.0f, 0.5f, 0.0f, 0.0f);
			for(int i = 0; i < sides; i++){
				float theta = 2.0f * 3.1415926f * i / sides;
		        glBegin(GL_LINES);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f(0.0f, 1.9f * sin(theta), 1.9f * cos(theta));
		        glEnd();
		    }
			glTranslatef(0.6f, 0.0f, 0.0f);
			for(int j = 0; j < sides; j++){
				float theta = 2.0f * 3.1415926f * j / sides;
		        glBegin(GL_LINES);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f(0.0f, 1.9f * sin(theta), 1.9f * cos(theta));
		        glEnd();
		    }
			// linhas entre as rodas
			glLineWidth(3);
			glColor3f(1.0f, 1.0f, 1.0f);
			for(int j = 0; j < sides; j++){
				float theta = 2.0f * 3.1415926f * j / sides;
		        glBegin(GL_LINES);
					glVertex3f( 0.0f, 1.9f * sin(theta), 1.9f * cos(theta));
					glVertex3f(-0.6f, 1.9f * sin(theta), 1.9f * cos(theta));
		        glEnd();
		    }
		glPopMatrix();

		glLineWidth(1);
	glEndList();
}

void loadBench(int list)
{
	float size;
	glNewList(list, GL_COMPILE);
	glBegin(GL_QUADS);
        // parte de trás-cima
        glVertex3f(-0.5f,  0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f( 0.0f, -0.5f, 0.0f);
        glVertex3f( 0.0f,  0.0f, 0.0f);

        // parte de cima
        glVertex3f(-0.5f,  0.0f,  0.0f);
        glVertex3f(-0.5f,  0.0f, -0.1f);
        glVertex3f( 0.0f,  0.0f, -0.1f);
        glVertex3f( 0.0f,  0.0f,  0.0f);

        // parte de frente-cima (encosta as costas)
        glVertex3f(-0.5f,   0.0f, -0.1f);
        glVertex3f(-0.5f, -0.35f, -0.1f);
        glVertex3f( 0.0f, -0.35f, -0.1f);
        glVertex3f( 0.0f,   0.0f, -0.1f);

        // parte de sentar-frente
        glVertex3f(-0.5f, -0.35f, -0.1f);
        glVertex3f(-0.5f, -0.35f, -0.4f);
        glVertex3f( 0.0f, -0.35f, -0.4f);
        glVertex3f( 0.0f, -0.35f, -0.1f);

        // parte de frente-baixo (encosta as pernas)
        glVertex3f(-0.5f, -0.75f, -0.4f);
        glVertex3f(-0.5f, -0.35f, -0.4f);
        glVertex3f( 0.0f, -0.35f, -0.4f);
        glVertex3f( 0.0f, -0.75f, -0.4f);

        // parte de baixo
        glVertex3f(-0.5f, -0.75f, -0.4f);
        glVertex3f(-0.5f, -0.75f, -0.3f);
        glVertex3f( 0.0f, -0.75f, -0.3f);
        glVertex3f( 0.0f, -0.75f, -0.4f);

        // parte de tras-baixo
        glVertex3f(-0.5f, -0.5f, -0.3f);
        glVertex3f(-0.5f, -0.75f, -0.3f);
        glVertex3f( 0.0f, -0.75f, -0.3f);
        glVertex3f( 0.0f, -0.5f, -0.3f);

        // parte de sentar-tras
        glVertex3f(-0.5f, -0.5f,  0.0f);
        glVertex3f(-0.5f, -0.5f, -0.3f);
        glVertex3f( 0.0f, -0.5f, -0.3f);
        glVertex3f( 0.0f, -0.5f,  0.0f);

        // tampas
        // esquerda-cima
        glVertex3f(-0.5f,  0.0f,  0.0f);
        glVertex3f(-0.5f, -0.5f,  0.0f);
        glVertex3f(-0.5f, -0.5f, -0.1f);
        glVertex3f(-0.5f,  0.0f, -0.1f);

        // direita-cima
        glVertex3f(0.0f,  0.0f,  0.0f);
        glVertex3f(0.0f, -0.5f,  0.0f);
        glVertex3f(0.0f, -0.5f, -0.1f);
        glVertex3f(0.0f,  0.0f, -0.1f);

        // esquerda-baixo
        glVertex3f(0.0f, -0.35f, -0.4f);
        glVertex3f(0.0f, -0.75f, -0.4f);
        glVertex3f(0.0f, -0.75f, -0.3f);
        glVertex3f(0.0f, -0.35f, -0.3f);

        // direita-baixo
        glVertex3f(-0.5f, -0.35f, -0.4f);
        glVertex3f(-0.5f, -0.75f, -0.4f);
        glVertex3f(-0.5f, -0.75f, -0.3f);
        glVertex3f(-0.5f, -0.35f, -0.3f);

        // esquerda-meio
        glVertex3f(-0.5f, -0.35f, -0.1f);
        glVertex3f(-0.5f,  -0.5f, -0.1f);
        glVertex3f(-0.5f,  -0.5f, -0.3f);
        glVertex3f(-0.5f, -0.35f, -0.3f);

        // direita-meio
        glVertex3f(0.0f, -0.35f, -0.1f);
        glVertex3f(0.0f,  -0.5f, -0.1f);
        glVertex3f(0.0f,  -0.5f, -0.3f);
        glVertex3f(0.0f, -0.35f, -0.3f);

    glEnd();
	glEndList();
}


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
            glutSolidSphere(0.7f, 5, 5);
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

int objects::newObject(int type, GLuint texture, int otherList)
{
    displayLists.push_back(glGenLists(listCount));
    switch(type)
    {
        case(OBJECT_FLOOR):
            loadFloor(displayLists[listCount-1], texture);
            break;

        case(OBJECT_TREE):
            glNewList(displayLists[listCount-1], GL_COMPILE);
                loadTree(1.5, 0.2);
            glEndList();
            break;

		case(OBJECT_STAND):
        	loadStand(displayLists[listCount-1]);
            break;

		case(OBJECT_WHEEL):
        	loadWheel(displayLists[listCount-1]);
            break;

		case(OBJECT_BENCH):
	        loadBench(displayLists[listCount-1]);
            break;

		case(OBJECT_KAMIKAZE):
			loadKamikaze(displayLists[listCount-1]);
			break;

		case(OBJECT_KAMIKAZE_STAND):
			loadKamikazeStand(displayLists[listCount-1]);
			break;

		case(OBJECT_CAROUSEL):
			loadCarousel(displayLists[listCount-1]);
			break;

		case(OBJECT_CAROUSEL_STAND):
			loadCarouselStand(displayLists[listCount-1]);
			break;
    }
    listCount++;
    return displayLists[listCount-2];
}
