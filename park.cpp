#include "src/global.h"
#include "src/point.h"
#include "src/skybox.h"

bool keys[4];
float xSpeed = 0.00f, ySpeed = 0.00f, zSpeed = 0.00f;
float xAngle = 0.00f, yAngle = 0.00f;
int width = 0, height = 0, pressedX = 0, pressedY = 0;
GLuint floorTexture;
bool lookAt = false;

int floorDisplayList;
float floorHeight = -1;
float tileSize = 0.20f;
int gridSize = 20;

skybox* box = nullptr;

void doFloor() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    //int texWidth, texHeight;
    //glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texWidth);
    //glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texHeight);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) teste);
    glBindTexture(GL_TEXTURE_2D, 0);



    floorDisplayList = glGenLists(1);
    glNewList(floorDisplayList, GL_COMPILE);
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

void projection() {
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, razaoAspecto, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw() {
    projection();
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(lookAt){
        glRotatef(yAngle, 1, 0, 0);
        glRotatef(xAngle, 0, 1, 0);
    }else
        glRotatef(0, 0, 0, 0);

    glTranslatef(xSpeed, ySpeed, zSpeed);


    glColor4d(1,1,1,1);

    box->draw(0,0,0,2,2,2);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
        glCallList(floorDisplayList);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glBindTexture(GL_TEXTURE_2D, 0);

    glutSwapBuffers();
}


void setup(){

    floorTexture = loadTexture("img/grass.png");
    doFloor();

    float cor[] = {.5f, .5f, .5f };
    //glClearColor(cor[0], cor[1], cor[2], 1.0f);
    /*
    glFogi(GL_FOG_MODE, GL_EXP);        // Linear, exp. ou exp²
    glFogfv(GL_FOG_COLOR, cor);         // Cor
    glFogf(GL_FOG_DENSITY, 0.1f);      // Densidade
    glHint(GL_FOG_HINT, GL_DONT_CARE);  // Não aplicar se não puder
    glFogf(GL_FOG_START, 10.0f);         // Profundidade inicial
    glFogf(GL_FOG_END, 12.0f);           // Profundidade final
    glEnable(GL_FOG);                   // Liga GL_FOG
    */
    box = new skybox();
}

void mousePress(int button, int state, int x, int y) // funcao para receber o clique do mouse; usada para verificar o clique sobre botoes
{
    if(button == 3 && state == GLUT_DOWN)
        zSpeed += 0.3f;
    else if(button == 4 && state == GLUT_DOWN)
        zSpeed -= 0.3f;
    else{
        pressedX = x;
        pressedY = y;
    }

}

void mouseMotion(int x, int y) // funcao para receber o clique do mouse; usada para verificar o clique sobre botoes
{
    //xSpeed += ( (float) x / (float) width - (float) pressedX / (float) width)  / 10.0;
    //ySpeed -= ( (float) y / (float) height - (float) pressedY / (float) height)  / 10.0;
    xAngle -= ( (float) x / (float) width - (float) pressedX / (float) width)  / 2.0;
    yAngle -= ( (float) y / (float) height - (float) pressedY / (float) height)  / 2.0;
}

void keyboardPress(unsigned char key, int x, int y)
{
    switch(key) {
        // Tecla ESC
        case 27:
            exit(0);
            break;
        case 'c':
            if (lookAt)
                lookAt = false;
            else
                lookAt = true;
            break;
    }
    glutPostRedisplay();
}

void arrowPress(int key, int x, int y) // funcao para receber clique de setas do teclado
{
    switch(key)
    {
        case GLUT_KEY_UP:
            keys[KEY_UP] = true;
            break;
        case GLUT_KEY_DOWN:
            keys[KEY_DOWN] = true;
            break;
        case GLUT_KEY_LEFT:
            keys[KEY_LEFT] = true;
            break;
        case GLUT_KEY_RIGHT:
            keys[KEY_RIGHT] = true;
            break;
    }
}

/*
void keyboardRelease(unsigned char key, int x, int y) // funcao para receber o release da tecla do teclado
{
    switch(key)
    {
    case 'w':
        keys[LEFT_UP] = false;
        break;
    case 's':
        keys[LEFT_DOWN] = false;
        break;
    default:
        break;
    }
}
*/

void arrowRelease(int key, int x, int y) // funcao para receber o release das setas do teclado
{
    switch(key)
    {
    case GLUT_KEY_UP:
        keys[KEY_UP] = false;
        break;
    case GLUT_KEY_DOWN:
        keys[KEY_DOWN] = false;
        break;
    case GLUT_KEY_LEFT:
        keys[KEY_LEFT] = false;
        break;
    case GLUT_KEY_RIGHT:
        keys[KEY_RIGHT] = false;
        break;
    default:
        break;
    }
}

void reshape(int width, int height)
{
    projection();
    glLoadIdentity();
}

static void refresh(void)
{
    if(keys[KEY_UP])
        zSpeed += 0.005f;
    else if(keys[KEY_DOWN])
        zSpeed -= 0.005f;
    else if(keys[KEY_RIGHT])
        xSpeed -= 0.005f;
    else if(keys[KEY_LEFT])
        xSpeed += 0.005f;

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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Amusement Park");

    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);
    glutIdleFunc(refresh);
    glutMouseFunc(mousePress);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboardPress);
    glutSpecialFunc(arrowPress);
    //glutKeyboardUpFunc(keyboardRelease);
    glutSpecialUpFunc(arrowRelease);

    glClearColor(1,1,1,0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
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

    setup();

    glutMainLoop();

   return 0;
}
