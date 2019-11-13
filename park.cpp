#include "src/camera.h"
#include "src/objects.h"
#include "src/point.h"
#include "src/skybox.h"

bool keys[4];
int width = 0, height = 0;
GLuint floorTexture;
float rotation = 0.00f;

int floorDisplayList, treeDisplayList[5], wheelDisplayList, standDisplayList, benchDisplayList;

bool cursor = true, lightOn = true;

skybox* box = nullptr;
objects* obj = nullptr;
camera cam;

void projection() {
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, razaoAspecto, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw() {

    projection();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gluLookAt(cam.mPos.x,  cam.mPos.y,  cam.mPos.z,
			  cam.mView.x, cam.mView.y, cam.mView.z,
			  cam.mUp.x,   cam.mUp.y,   cam.mUp.z);

    // SkyBox
    glColor4d(1,1,1,1);
    box->draw(0, 0, 0, 1000, 1000, 1000);
    //

    // Grass
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
        glCallList(floorDisplayList);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Ferris wheel
    glPushMatrix();
        glTranslatef(5.0f, 0.0f, -5.0f);
        glCallList(standDisplayList);
        glPushMatrix();
		    glTranslatef(0.2f, 1.0f, 0.0f);
            glRotatef(rotation, 1.0f, 0.0f, 0.0f);
            glCallList(wheelDisplayList);
        glPopMatrix();
    glPopMatrix();
    rotation += 0.01f;

    /*glCallList(treeDisplayList[0]);
    glPushMatrix();
    glTranslatef(1.5f, -1.5f, 0.0f);
    glCallList(treeDisplayList[1]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0f, -1.5f, 0.0f);
    glCallList(treeDisplayList[2]);
    glPopMatrix();*/

    glutSwapBuffers();
}


void setup(){

    floorTexture = loadTexture("img/grass3.jpg");
    obj = new objects();
    floorDisplayList = obj->newObject(OBJECT_FLOOR, floorTexture, 0);
    /*for(int i = 0; i < 5; i++)
        treeDisplayList[i] = obj->newObject(OBJECT_TREE, 0, 1.5, 0.2);*/
    standDisplayList = obj->newObject(OBJECT_STAND, 0, 0);
    benchDisplayList = obj->newObject(OBJECT_BENCH, 0, 0);
    wheelDisplayList = obj->newObject(OBJECT_WHEEL, 0, 0);

    box = new skybox();
    ShowCursor(false);
}

void mousePress(int button, int state, int x, int y) // funcao para receber o clique do mouse; usada para verificar o clique sobre botoes
{
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        if(cursor == TRUE){
            ShowCursor(FALSE);
            cursor = FALSE;
        }else{
            ShowCursor(TRUE);
            cursor = TRUE;
        }
    }
}

void keyboardPress(unsigned char key, int x, int y)
{
    switch(key) {
        // Tecla ESC
        case 27:
            exit(0);
            break;

        case 'l':
            if(lightOn){
                lightOn = false;
                glDisable(GL_LIGHT0);
                glDisable(GL_NORMALIZE);
                glDisable(GL_COLOR_MATERIAL);
                glDisable(GL_LIGHTING);
            } else {
                lightOn = true;
                glEnable(GL_LIGHT0);
                glEnable(GL_NORMALIZE);
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_LIGHTING);
            }
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

    cam.mWindowWidth  = width;
	cam.mWindowHeight = height;
}

static void refresh(void)
{

    if(keys[KEY_UP])
        cam.moveCamera(CAMERA_SPEED);
    else if(keys[KEY_DOWN])
        cam.moveCamera(-CAMERA_SPEED);
    else if(keys[KEY_RIGHT])
        cam.rotateView(0, -CAMERA_SPEED, 0);
    else if(keys[KEY_LEFT])
        cam.rotateView(0, CAMERA_SPEED, 0);

    if(!cursor)
        cam.moveMouse();

    glutPostRedisplay();
}

// configura alguns parâmetros do modelo de iluminação: FONTE DE LUZ
const GLfloat light_ambient[]  = { 0.5f, 0.5f, 0.5f, 0.1f }; // 0 0 0 1
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
    glutKeyboardFunc(keyboardPress);
    glutSpecialFunc(arrowPress);
    //glutKeyboardUpFunc(keyboardRelease);
    glutSpecialUpFunc(arrowRelease);

    glShadeModel(GL_SMOOTH);

    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); // GL_LESS
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_TEXTURE_2D);

	cam.positionCamera(0, 2.5f, 5,	0, 2.5f, 0,   0, 1, 0);

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
