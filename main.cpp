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
#include <Camera.h>

#include <stdlib.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <assimp/vector3.h>

GLuint texName[10];

#include "BasicFunctions.h"

using namespace sowi;

Camera camera;

tAABB p1 = {2.2f, -18.8f, -2.2f, -20.0f};
tAABB p2 = {13.2f, 20.8f, -2.2f, 18.8f};
tAABB p3 = {-0.3f, 20.8f, -4.2f, -20.0f};
tAABB p4 = {11.2f, 10.8f, 0.3f, -20.0f};
tAABB p5 = {11.2f, 20.8f, 0.3f, 12.0f};
tAABB p6 = {15.2f, 20.8f, 11.8f, -20.0f};

tAABB in[6] = {p1, p2, p3, p4, p5, p6};


/* GLUT callback Handlers */

bool AABBtoAABB(const tAABB& tBox1, const tAABB& tBox2){
		return(tBox1.MaxX < tBox2.MaxX &&
			   tBox1.MinX > tBox2.MinX &&
			   tBox1.MaxZ < tBox2.MaxZ &&
			   tBox1.MinZ > tBox2.MinZ);
}
void outofBox(Camera *p, tAABB sala){
		if((AABBtoAABB(p->futplayer, sala))){
			p->move = false;
		}
}

void inBoxF(Camera *p, tAABB sala){
		if((AABBtoAABB(p->futplayer, sala))){
			p->futposx = -15.0f;
			p->futposz = 8.5f;
		}
}

static void resize(int width, int height){
    const float ar = (float) width / (float) height;

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
    
    glViewport(0, 0, camera.width, camera.height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0f, 1.0f, 0.001f, 100.0f);

    //DRAWING TRIANGLES

    camera.mover();
	
	for(int i = 0; i < 6; i++){
		outofBox(&camera, in[i]);
	}
	
	camera.attAABB();
	
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

    gluLookAt(	camera.posx, camera.posy, camera.posz, //posição da camera
				camera.camx, camera.camy, camera.camz,	//look at da camera
				0.0f, 1.0f, 0.0f);  //vetor UP da camera
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    
    ///////////////OBJECTS///////////////////////
    /*glPushMatrix();
      glTranslated(0,0,-6);
      glRotated(a,0,1,0);
      glRotated(90,0,0,1);
      glBindTexture(GL_TEXTURE_2D, texName[0]);
      LoadObject("2box.obj");
      //DrawTriangle(glm::vec3{-1,1,0}, glm::vec3{1,1,0}, glm::vec3{0,-1,0});
    glPopMatrix();*/


    /////////////////QUADS/////////////////////////////////////////
    
    
      //Left Hall Floor
      glBindTexture(GL_TEXTURE_2D, texName[1]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,20.0f); glVertex3f(1.2f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,20.0f); glVertex3f(-1.2f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.2f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f);
      glEnd();

      //Left Hall Left Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,20.0f); glVertex3f(-1.2f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,20.0f); glVertex3f(-1.2f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.2f, 2.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(-1.2f, -1.7f, 20.0f);
      glEnd();

      //Left Hall Front Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,1.0f); glVertex3f(1.6f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(-1.2f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.2f, -1.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.6f, -1.7f, -20.0f);
      glEnd();

      //Left Hall Ceiling
      glBindTexture(GL_TEXTURE_2D, texName[3]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,10.0f); glVertex3f(1.6f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,10.0f); glVertex3f(-1.2f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.2f, 2.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.6f, 2.7f, -20.0f);
      glEnd();

      //Left Hall Right (Half) Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,10.0f); glVertex3f(1.2f, -0.5f, -20.0f);
      glTexCoord2f(0.5f,10.0f); glVertex3f(1.2f, -1.7f, -20.0f);
      glTexCoord2f(0.5f,0.0f); glVertex3f(1.2f, -1.7f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -0.5f, 0.0f);
      glEnd();

      //Left Hall Right (Half) Wall top
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f/3.0f,18.0f); glVertex3f(1.6f, -0.5f, -20.0f);
      glTexCoord2f(0.0f,18.0f); glVertex3f(1.2f, -0.5f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -0.5f, 0.0f);
      glTexCoord2f(1.0f/3.0f,0.0f); glVertex3f(1.6f, -0.5f, 0.0f);
      glEnd();

      //Left Hall Right (Half) Wall (other side)
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.6f, -0.5f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.6f, -1.7f, 0.0f);
      glTexCoord2f(18.0f,0.0f); glVertex3f(1.6f, -1.7f, -20.0f);
      glTexCoord2f(18.0f,1.0f); glVertex3f(1.6f, -0.5f, -20.0f);
      glEnd();

      //Left Hall Right ("Elevator Shaft") Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f/3.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      
      glEnd();

      //Left Hall Right (Final) Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f);
      glEnd();

      //Left Hall Back Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,1.0f); glVertex3f(-1.2f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(-1.2f, -1.7f, 20.0f);
      glEnd();

      //Middle Corridor Left Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(10.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glEnd();

      //Stairs Right Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,1.0f); glVertex3f(10.2f, 2.7f, 20.0f/3.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f/3.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f/3.0f);
      glEnd();

      //Middle Corridor Floor
      glBindTexture(GL_TEXTURE_2D, texName[1]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(3.0f,0.0f); glVertex3f(10.2f, -1.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(3.0f,1.0f); glVertex3f(10.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glEnd();

      //Middle Corridor Ceiling
      glBindTexture(GL_TEXTURE_2D, texName[3]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(3.0f,1.0f); glVertex3f(10.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(3.0f,0.0f); glVertex3f(10.2f, 2.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, 2.7f, 2.0f*20.0f/3.0f);
      glEnd();

      //Middle Corridor Right Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.2f, -1.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(1.2f, 2.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(10.2f, 2.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, -1.7f, 2.0f*20.0f/3.0f);
      glEnd();

      //Right Hall Floor
      glBindTexture(GL_TEXTURE_2D, texName[1]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,20.0f); glVertex3f(12.6f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,20.0f); glVertex3f(10.2f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, -1.7f, 20.0f);
      glEnd();

      //Right Hall Left (Final) Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 2.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,3.0f); glVertex3f(10.2f, -1.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(0.0f,3.0f); glVertex3f(10.2f, 2.7f, 2.0f*20.0f/3.0f);
      glEnd();

      //Right Hall Back Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,1.0f); glVertex3f(10.2f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(12.6f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.6f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f);
      glEnd();

      //Right Hall Right Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,20.0f); glVertex3f(12.6f, 2.7f, -20.0f);
      glTexCoord2f(1.0f,20.0f); glVertex3f(12.6f, -1.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, -1.7f, 20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.6f, 2.7f, 20.0f);
      glEnd();

      //Right Hall Ceiling
      glBindTexture(GL_TEXTURE_2D, texName[3]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,10.0f); glVertex3f(12.6f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,10.0f); glVertex3f(9.8f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, 2.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, 2.7f, -20.0f);
      glEnd();
      
      //Right Hall Front Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.6f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(9.8f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, -1.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, -1.7f, -20.0f);
      glEnd();

      //Right Hall Left (Half) Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, -0.5f, 0.0f);
      glTexCoord2f(0.5f,0.0f); glVertex3f(10.2f, -1.7f, 0.0f);
      glTexCoord2f(0.5f,10.0f); glVertex3f(10.2f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,10.0f); glVertex3f(10.2f, -0.5f, -20.0f);
      glEnd();

      //Right Hall Left (Half) Wall top
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f/3.0f,18.0f); glVertex3f(10.2f, -0.5f, -20.0f);
      glTexCoord2f(0.0f,18.0f); glVertex3f(9.8f, -0.5f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, -0.5f, 0.0f);
      glTexCoord2f(1.0f/3.0f,0.0f); glVertex3f(10.2f, -0.5f, 0.0f);
      glEnd();

      //Right Hall Left Wall (Other side)
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,1.0f); glVertex3f(9.8f, -0.5f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, -1.7f, -20.0f);
      glTexCoord2f(18.0f,0.0f); glVertex3f(9.8f, -1.7f, 0.0f);
      glTexCoord2f(18.0f,1.0f); glVertex3f(9.8f, -0.5f, 0.0f);
      glEnd();

      //Right Hall Left Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(1.0f,3.0f); glVertex3f(10.2f, -1.7f, 0.0f);
      glTexCoord2f(0.0f,3.0f); glVertex3f(10.2f, 2.7f, 0.0f);
      glEnd();

      //Right Hall Left Wall (Other Side (stairs))
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,3.0f); glVertex3f(10.2f, 2.7f, 0.0f);
      glTexCoord2f(1.0f,3.0f); glVertex3f(10.2f, -1.7f, 0.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glEnd();

      //Middle Wall
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 2.7f, 0.0f);
      glTexCoord2f(3.0f,0.0f); glVertex3f(10.2f, -1.7f, 0.0f);
      glTexCoord2f(3.0f,9.0f); glVertex3f(1.2f, -1.7f, 0.0f);
      glTexCoord2f(0.0f,9.0f); glVertex3f(1.2f, 2.7f, 0.0f);
      glEnd();

      //Middle Wall (Other Side)
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,3.0f); glVertex3f(1.2f, 2.7f, 0.0f);
      glTexCoord2f(1.0f,3.0f); glVertex3f(1.2f, -1.7f, 0.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 2.7f, 0.0f);
      glEnd();

     glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}


static void idle(void)
{
    glutPostRedisplay();
}

void mexerCamera(int x, int y){
	camera.lookerCamera(x, y);
}
void keyPressed(unsigned char key, int x, int y){
	camera.keyPressed(key, x, y);
}
void keyUp(unsigned char key, int x, int y){
	camera.keyUp(key, x, y);
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
    glutSetCursor(GLUT_CURSOR_NONE);

    init2();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    glutPassiveMotionFunc(mexerCamera);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

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

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    glutMainLoop();

    return EXIT_SUCCESS;
}
