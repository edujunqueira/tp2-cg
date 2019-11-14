#include "src/camera.h"
#include "src/objects.h"
#include "src/point.h"
#include "src/skybox.h"

bool keys[4];
int width = 0, height = 0, camPos = 0;
GLuint floorTexture;

// rotação dos brinquedos
float rotation = 0.00f, kamikazeRotation = 0.00f, carouselRotation = 0.00f;

// listas dos objetos a serem desenhados
int floorDisplayList, treeDisplayList[8], wheelDisplayList, standDisplayList,
    benchDisplayList, kamikazeDisplayList, kamikazeStandDisplayList,
    carouselDisplayList, carouselStandDisplayList;

// mudança de luz e cameras pelas teclas (l e 1/2, respectivamente)
bool lightOn = true, cursor = true;


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


    /////// Desenhar a cena ///////

    // ---- Skybox ----- //
    glColor4d(1,1,1,1);
    box->draw(0, 0, 0, 1000, 1000, 1000);

    // ---- Grass ----- //
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
        glCallList(floorDisplayList);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glBindTexture(GL_TEXTURE_2D, 0);

    // ---- Ferris wheel ----- //
    glPushMatrix();
        glTranslatef(5.0f, 0.0f, -20.0f);
        glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
        glCallList(standDisplayList);
        glPushMatrix();
		    glTranslatef(0.2f, 1.0f, 0.0f);
            glRotatef(rotation, 1.0f, 0.0f, 0.0f);
            glCallList(wheelDisplayList);
        glPopMatrix();
    glPopMatrix();
    rotation += 0.01f;

    // ---- Trees ----- //
    glPushMatrix();
        glTranslatef(-10.0f, -1.5f, -10.0f);
        glCallList(treeDisplayList[0]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(10.0f, -1.5f, -10.0f);
		glRotatef(15, 0.0f, 1.0f, 0.0f);
        glCallList(treeDisplayList[1]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(15.0f, -1.5f, -8.0f);
		glRotatef(30, 0.0f, 1.0f, 0.0f);
        glCallList(treeDisplayList[2]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-10.0, -1.5f, -20.0f);
		glRotatef(45, 0.0f, 1.0f, 0.0f);
        glCallList(treeDisplayList[3]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5f, -1.5f, -30.0f);
		glRotatef(60, 0.0f, 1.0f, 0.0f);
        glCallList(treeDisplayList[4]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-3.0f, -1.5f, -25.0f);
		glRotatef(75, 0.0f, 1.0f, 0.0f);
        glCallList(treeDisplayList[5]);
    glPopMatrix();

    // ---- Benches ----- //
    glPushMatrix();
        glColor3f(0.31f, 0.18f, 0.03f);
        glTranslatef(9.0f, 0.0f, -10.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        for(int b = 0; b <= 4; b++){
            glCallList(benchDisplayList);
            glTranslatef(0.5f, 0.0f, 0.0f);
        }
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.31f, 0.18f, 0.03f);
        glTranslatef(6.0f, 0.0f, -8.0f);
        for(int b = 0; b <= 4; b++){
            glCallList(benchDisplayList);
            glTranslatef(0.5f, 0.0f, 0.0f);
        }
    glPopMatrix();

    // ---- Kamikaze ----- //
    glPushMatrix();
        glTranslatef(-5.0f, 0.0f, -15.0f);
        glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
        glCallList(kamikazeStandDisplayList);
        glPushMatrix();
            glRotatef(kamikazeRotation, 1.0f, 0.0f, 0.0f);
            glCallList(kamikazeDisplayList);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-3.0f, 0.0f, 0.0f);
            glRotatef(-kamikazeRotation, 1.0f, 0.0f, 0.0f);
            glCallList(kamikazeDisplayList);
        glPopMatrix();
    glPopMatrix();
    if((kamikazeRotation/360) >= (floor(kamikazeRotation/360) + 0.47f) && (kamikazeRotation/360) <= (floor(kamikazeRotation/360) + 0.53f))
        kamikazeRotation += 0.006f;
    else
        kamikazeRotation += 0.05f;

    // ---- Carousel ---- //
    glPushMatrix();
        glTranslatef(-15.0f, 0.0f, -5.0f);
        glCallList(carouselStandDisplayList);
        glPushMatrix();
            glRotatef(carouselRotation, 0.0f, 1.0f, 0.0f);
            glCallList(carouselDisplayList);
        glPopMatrix();
    glPopMatrix();
    carouselRotation += 0.05f;

    /////// - ///////

    glutSwapBuffers();

}

/*
    -- Classe "objects" serve para guardar as listas de display em uma forma mais orientada a objetos
    -- Quando o objeto é criado (na função setup), ele é carregado na memória do openGL (com glNewList)
    -- Então, quando necessário, ele é criado no cenário
*/
void setup(){

    floorTexture = loadTexture("img/grass3.jpg");
    obj = new objects();
    // -- Criação de objetos -- //
    floorDisplayList = obj->newObject(OBJECT_FLOOR, floorTexture, 0);
    for(int i = 0; i < 8; i++)
        treeDisplayList[i] = obj->newObject(OBJECT_TREE, 0, 0);
    standDisplayList = obj->newObject(OBJECT_STAND, 0, 0);
    benchDisplayList = obj->newObject(OBJECT_BENCH, 0, 0);
    wheelDisplayList = obj->newObject(OBJECT_WHEEL, 0, 0);
    kamikazeStandDisplayList = obj->newObject(OBJECT_KAMIKAZE_STAND, 0, 0);
    kamikazeDisplayList = obj->newObject(OBJECT_KAMIKAZE, 0, 0);
    carouselDisplayList = obj->newObject(OBJECT_CAROUSEL, 0, 0);
    carouselStandDisplayList = obj->newObject(OBJECT_CAROUSEL_STAND, 0, 0);
    box = new skybox();
    // -- -- //
    ShowCursor(false);
}

void mousePress(int button, int state, int x, int y)
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
        case '1':
            if(cursor)
            {
                ShowCursor(FALSE);
                cursor = FALSE;
            }
            break;
        case '2':
            if(!cursor)
            {
                ShowCursor(TRUE);
                cursor = TRUE;
            }
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
            if(cursor)
                camPos--;
            if(camPos < 0)
                camPos = 3;
            break;
        case GLUT_KEY_RIGHT:
            if(cursor)
                camPos++;
            if(camPos >= 4)
                camPos = 0;
            break;
    }

    if((key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) && cursor == TRUE){
        switch(camPos){
            case (CAMERA_POS_DEFAULT):
                cam.positionCamera(0, 2.5f, 5,	0, 2.5f, 0,   0, 1, 0);
                break;
            // wheel
            case (CAMERA_POS_WHEEL):
                cam.positionCamera(0.0f, 2.5f, -10.0f, 5.0f, 0.0f, -20.0f, 0.0f, 1.0f, 0.0f);
                break;
            // kamikaze
            case (CAMERA_POS_KAMIKAZE):
                cam.positionCamera(0.0f, 2.5f, -5.0f, -5.0f, 0.0f, -15.0f, 0.0f, 1.0f, 0.0f);
                break;
            // carousel
            case (CAMERA_POS_CAROUSEL):
                cam.positionCamera(-10.0f, 2.5f, 5.0f, -15.0f, 0.0f, -5.0f, 0.0f, 1.0f, 0.0f);
                break;
        }
    }
}

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

// iluminação, fonte de luz
const GLfloat light_ambient[]  = { 0.f, 0.f, 0.f, 1.f }; // 0 0 0 1
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

// iluminação, material
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
    glutSpecialUpFunc(arrowRelease);

    glShadeModel(GL_SMOOTH);

    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
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
