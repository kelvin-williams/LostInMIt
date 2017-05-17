/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include <stdlib.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <assimp/vector3.h>

#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;

#include "BasicFunctions.h"

float camx=0.0f;
float camy=0.0f;
float camz=5.0f;
float viewx=0.0f;
float viewy=0.0f;
float viewz=0.0f;
GLboolean pressed[4] = {false, false, false, false};

/* GLUT callback Handlers */

static void resize(int width, int height){
    const float ar = (float) width / (float) height;

    //gluLookAt(	0.0f, 0.0f, 5.0f, 
	//			0.0f, 0.0f, 0.0f, 
	//			0.0f, 1.0f, 0.0f);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //DRAWING TRIANGLES

    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

    gluLookAt(	camx, camy, camz, 
				viewx, viewy, viewz, 
				0.0f, 1.0f, 0.0f);
    
    glPushMatrix();
      glTranslated(0,0,-6);
      glRotated(a,0,1,0);
      glRotated(90,0,0,1);
      LoadObject("2box.obj");
      
      //DrawTriangle(glm::vec3{-1,1,0}, glm::vec3{1,1,0}, glm::vec3{0,-1,0});
    glPopMatrix();

    glutSwapBuffers();
}


static void idle(void)
{
    if (pressed[0]){
        camz -= 0.1f;
    } 
    if(pressed[1]){
        camx -= 0.1f;
        viewx -= 0.1f;
    }
    if(pressed[2]){
        camz += 0.1f;
    }
    if(pressed[3]){
        camx += 0.1f;
        viewx += 0.1f;
    }
    glutPostRedisplay();
}

static void key(unsigned char k, int x, int y)
{
    switch(k){
        case 'w':
            pressed[0] = true;          
            break;
        case 'a':
            pressed[1] = true;
            break;
        case 's':
            pressed[2] = true;
            break;
        case 'd':
            pressed[3] = true;
            break;
    }              
}

static void key2(unsigned char k, int x, int y)
{
    switch(k){
        case 'w':
            pressed[0] = false;          
             break;
        case 'a':
            pressed[1] = false;
            break;
        case 's':
            pressed[2] = false;
            break;
        case 'd':
            pressed[3] = false;
            break;
    }              
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Lost In MIT");

    init2();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(key);
    glutKeyboardUpFunc(key2);

    glClearColor(0,0,0,0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);


    glutMainLoop();

    return EXIT_SUCCESS;
}
