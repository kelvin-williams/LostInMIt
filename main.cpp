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

typedef struct triangle{

    glm::vec3 p1p, p2p, p3p;//Vértices do triângulo
    glm::vec3 p1n, p2n, p3n;//Normais dos Três vértices
    glm::vec2 p1t, p2t, p3t;//Coordenadas de Textura
    
}Triangle;

typedef struct node{

    Triangle t;
    struct node * next;

}Node;

typedef struct list{

    Node * head;

}List;

void init_list(List * list){

    list->head = NULL;
}

void list_add(List * list, Triangle t){

    if(list->head == NULL){
        list->head = new(Node);
        list->head->t = t;
        list->head->next = NULL;
    }
    else{
        Node * aux;
        aux = new(Node);
        aux->t = t;
        aux->next = list->head;
        list->head = aux;
    }
    
}

void list_free(List * trianglelist){

    Node * aux = trianglelist->head;

    while(aux!=NULL){
	    Node* aux2 = aux->next;
	    free(aux);
	    aux = aux2;

 }
}

GLuint texName[30];
List trianglelist[10];

#include "BasicFunctions.h"

using namespace sowi;

Camera camera;
bool close = false;
bool inside = false;

tAABB p1 = {2.2f, -18.8f, -2.2f, -22.0f};
tAABB p2 = {13.2f, 20.8f, -2.2f, 18.8f};
tAABB p3 = {-0.3f, 20.8f, -4.2f, -20.0f};
tAABB p4 = {11.2f, 10.8f, 0.3f, -21.0f};
tAABB p5 = {11.2f, 20.8f, 0.3f, 12.0f};
tAABB p6 = {14.2f, 20.8f, 11.8f, -20.0f};
tAABB p7 = {11.2f, -20.0f, 1.3f, -26.0f};
tAABB p8 = {26.3f, -24.0f, 10.2f, -30.0f};
tAABB p9 = {30.0f, -8.0f, 23.5f, -30.0f};
tAABB p10 = {30.2f, -5.0f, 11.5f, -10.8f};
tAABB p11 = {13.2f, -18.8f, 9.5f, -21.0f};
tAABB p12 = {30.0f, -21.8f, 17.6f, -30.0f};
tAABB p13 = {30.0f, -18.4f, 17.6f, -22.0f};
tAABB p14 = {30.0f, -15.0f, 17.6f, -18.7f};
tAABB p15 = {30.0f, -11.6f, 17.6f, -15.2f};
tAABB p16 = {17.6f, -12.8f, 12.2f, -19.1f};
tAABB p17 = {16.6f, -8.8f, 12.2f, -13.1f};

tAABB stairs = {4.8f, 6.8f, -0.2f, -0.5f};
tAABB door = {13.2f, -18.5f, 9.5f, -22.5f};

tAABB in[17] = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17};

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

void free_mem(void)
{
	printf("Finalizando programa...\n\n");
}

void enter(Camera *p, tAABB sala){
    if(p->action == true){
        if(AABBtoAABB(p->futplayer,sala)){
            if(p->futposz > -19.50f){
                if(camera.camz < -20.0f){
                    inside = true;
                    p->move = true;
                    p->futposx = 11.0f;
                    p->futposz = -21.5f;
                }
            } 
            else{
                if(camera.camz > -20.2f){
                    inside = false;
                    p->move = true;
                    p->futposx = 11.0f;
                    p->futposz = -18.8f;
                }
            }
        }
    }
}


void fim(Camera *p, tAABB sala){
    if(p->action == true){
        if(AABBtoAABB(p->futplayer,sala)){
            if(p->camx > 1.1f){
                glutDestroyWindow(1);
                close = true;
            }
        }
    }
}

GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_specular[] = { 20.0f, 20.0f, 20.0f, 1.0f };
GLfloat light_specularpc[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition1[]= { 5.7f, 12.7f, -25.0f, 1.0f };
GLfloat LightAmbient2[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse2[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition2[]= { 18.7, 2.6f, -17.5f, 1.0f };
GLfloat LightPosition3[]= { (2), 9.9f, 0.0f, 1.0f };

 GLfloat mat_ambient[]    = { 0.2f, 0.2f, 0.2f, 1.0f };
 GLfloat mat_diffuse[]    = { 0.2f, 0.2f, 0.2f, 1.0f };
 GLfloat mat_specular[]   = { 20.0f, 20.0f, 20.0f, 1.0f };
 GLfloat mat_specularpc[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
 GLfloat high_shininess[] = { 128.0f };
 GLfloat light_specularoff[] = { 0.0f, 0.0f, 0.0f, 1.0f };
 GLfloat mat_specularoff[]   = { 0.0f, 0.0f, 0.0f, 1.0f };



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

    if (camera.full == true){
        resize (1366, 768);
        glutFullScreen();
    }
    else{
        resize(800, 600);
        glutReshapeWindow(800, 600);
    }

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0f, 1.0f, 0.001f, 100.0f);


    camera.mover();
	
     enter(&camera, door);

	for(int i = 0; i < 17; i++){
		outofBox(&camera, in[i]);
	}
	
	camera.attAABB();
    
    fim(&camera, stairs);

    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

    gluLookAt(	camera.posx, camera.posy, camera.posz, //posição da camera
				camera.camx, camera.camy, camera.camz,	//look at da camera
				0.0f, 1.0f, 0.0f);  //vetor UP da camera
    
       glPushMatrix();
            glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
        glPopMatrix();

        glPushMatrix();
        glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);
        glPopMatrix();
    ///NO TEXTURE

    ///////////////OBJECTS///////////////////////
    

/////YES TEXTURE/////////////////

 glEnable(GL_TEXTURE_2D);
 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


      glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
      glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
      glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
      //Bebedouro
      glBindTexture(GL_TEXTURE_2D, texName[21]);
      glPushMatrix();
      glTranslated(1.0,-1.0,14.0);
      //glRotated(-90,0,1,0);
      glScaled(0.2,0.65,0.2);
      PrintObj(&trianglelist[1]);
      glPopMatrix();

      //Quadro
      glBindTexture(GL_TEXTURE_2D, texName[24]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,-1.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(22.55f, 1.4f, -10.05f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(22.55f, -0.5f, -10.05f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(16.31f, -0.5f, -10.05f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(16.31f, 1.4f, -10.05f);
      glEnd();


      //mesa1
      glBindTexture(GL_TEXTURE_2D, texName[22]);
      glPushMatrix();
      glTranslated(21.5,-1.7,-23.3);
      //glRotated(-90,0,1,0);
      glScaled(0.7,0.5,0.3);
      PrintObj(&trianglelist[2]);
      glPopMatrix();

      //mesa2
      glBindTexture(GL_TEXTURE_2D, texName[22]);
      glPushMatrix();
      glTranslated(21.5,-1.7,-19.96);
      //glRotated(-90,0,1,0);
      glScaled(0.7,0.5,0.3);
      PrintObj(&trianglelist[2]);
      glPopMatrix();

      //mesa3
      glBindTexture(GL_TEXTURE_2D, texName[22]);
      glPushMatrix();
      glTranslated(21.5,-1.7,-16.62);
      //glRotated(-90,0,1,0);
      glScaled(0.7,0.5,0.3);
      PrintObj(&trianglelist[2]);
      glPopMatrix();

      //mesa4
      glBindTexture(GL_TEXTURE_2D, texName[22]);
      glPushMatrix();
      glTranslated(21.5,-1.7,-13.28);
      //glRotated(-90,0,1,0);
      glScaled(0.7,0.5,0.3);
      PrintObj(&trianglelist[2]);
      glPopMatrix();

      //mesa professor
      glBindTexture(GL_TEXTURE_2D, texName[22]);
      glPushMatrix();
      glTranslated(14.5,-1.7,-12.28);
      //glRotated(-90,0,1,0);
      glScaled(0.3,0.5,0.2);
      PrintObj(&trianglelist[2]);
      glPopMatrix();


      glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specularpc);
      glLightfv(GL_LIGHT1, GL_SPECULAR, light_specularpc);
      glLightfv(GL_LIGHT2, GL_SPECULAR, light_specularpc);
      if(inside){
      ///////PCS/////////////////
      ///////PRIMEIRA FILA//////////
      //pc11
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(23.58,-0.3,-23.0);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc12
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(24.2,-0.6,-23.0);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc21
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(22.36,-0.3,-23.0);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc22
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(22.98,-0.6,-23.0);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc31
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(21.14,-0.3,-23.0);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc32
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(21.76,-0.6,-23.0);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc41
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(19.92,-0.3,-23.0);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc42
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(20.54,-0.6,-23.0);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc51
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(18.7,-0.3,-23.0);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc52
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(19.32,-0.6,-23.0);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      ///////SEGUNDA FILA//////////
      //pc11
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(23.58,-0.3,-19.66);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc12
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(24.2,-0.6,-19.66);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc21
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(22.36,-0.3,-19.66);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc22
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(22.98,-0.6,-19.66);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc31
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(21.14,-0.3,-19.66);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc32
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(21.76,-0.6,-19.66);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc41
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(19.92,-0.3,-19.66);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc42
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(20.54,-0.6,-19.66);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc51
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(18.7,-0.3,-19.66);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc52
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(19.32,-0.6,-19.66);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      ///////TERCEIRA FILA//////////
      //pc11
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(23.58,-0.3,-16.32);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc12
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(24.2,-0.6,-16.32);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc21
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(22.36,-0.3,-16.32);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc22
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(22.98,-0.6,-16.32);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc31
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(21.14,-0.3,-16.32);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc32
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(21.76,-0.6,-16.32);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc41
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(19.92,-0.3,-16.32);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc42
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(20.54,-0.6,-16.32);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc51
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(18.7,-0.3,-16.32);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc52
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(19.32,-0.6,-16.32);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      ///////SEGUNDA FILA//////////
      //pc11
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(23.58,-0.3,-12.98);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc12
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(24.2,-0.6,-12.98);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc21
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(22.36,-0.3,-12.98);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc22
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(22.98,-0.6,-12.98);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc31
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(21.14,-0.3,-12.98);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc32
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(21.76,-0.6,-12.98);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc41
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(19.92,-0.3,-12.98);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc42
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(20.54,-0.6,-12.98);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();

      //pc51
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(18.7,-0.3,-12.98);
      glRotated(180,0,1,0);
      glScaled(0.1,0.3,0.3);
      PrintObj(&trianglelist[3]);
      glPopMatrix();

      //pc52
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glPushMatrix();
      glTranslated(19.32,-0.6,-12.98);
      glRotated(180,0,1,0);
      glScaled(0.7,0.7,0.7);
      PrintObj(&trianglelist[4]);
      glPopMatrix();


    /////////CHAIRS/////////////////////////////////////
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specularoff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specularoff);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specularoff);
      
      //Primeira fila
      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(24.19,-1.7,-23.97);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(22.97,-1.7,-23.97);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(21.75,-1.7,-23.97);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(20.53,-1.7,-23.97);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(19.31,-1.7,-23.97);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      //Segunda fila
      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(24.19,-1.7,-20.825);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(22.97,-1.7,-20.825);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(21.75,-1.7,-20.825);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(20.53,-1.7,-20.825);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(19.31,-1.7,-20.825);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      //Terceira fila
      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(24.19,-1.7,-17.48);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(22.97,-1.7,-17.48);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(21.75,-1.7,-17.48);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(20.53,-1.7,-17.48);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(19.31,-1.7,-17.48);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      //Quarta fila
      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(24.19,-1.7,-14.14);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(22.97,-1.7,-14.14);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(21.75,-1.7,-14.14);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(20.53,-1.7,-14.14);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(19.31,-1.7,-14.14);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      //////////////////CADEIRAS DA DIREITA////////////////

      //Segunda fila

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(13.21,-1.7,-15.815);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(14.43,-1.7,-15.815);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(15.65,-1.7,-15.815);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(16.87,-1.7,-15.815);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      //Terceira fila

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(13.21,-1.7,-17.48);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(14.43,-1.7,-17.48);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(15.65,-1.7,-17.48);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(16.87,-1.7,-17.48);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      //Quarta fila

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(13.21,-1.7,-14.14);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(14.43,-1.7,-14.14);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(15.65,-1.7,-14.14);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(16.87,-1.7,-14.14);
      glRotated(-90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

      //cadeira do professor
      glBindTexture(GL_TEXTURE_2D, texName[6]);
      glPushMatrix();
      glTranslated(14.87,-1.7,-11.14);
      glRotated(90,0,1,0);
      glScaled(0.03,0.03,0.03);
      PrintObj(&trianglelist[0]);
      glPopMatrix();

}

      /////////////////WALLS/////////////////////////////////////////
  
      glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specularoff);
      glLightfv(GL_LIGHT1, GL_SPECULAR, light_specularoff);
      glLightfv(GL_LIGHT2, GL_SPECULAR, light_specularoff);
      
      //Left Hall Floor
      glBindTexture(GL_TEXTURE_2D, texName[1]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,1.0f,0.0f);
      glTexCoord2f(1.0f,20.0f); glVertex3f(1.2f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,20.0f); glVertex3f(-1.2f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.2f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f);
      glEnd();

      //Left Hall Left Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(1.0f,20.0f); glVertex3f(-1.2f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,20.0f); glVertex3f(-1.2f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.2f, 2.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(-1.2f, -1.7f, 20.0f);
      glEnd();

      //Left Hall Front Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(1.6f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(-1.2f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.2f, -1.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.6f, -1.7f, -20.0f);
      glEnd();

      //Left Hall Ceiling
      glBindTexture(GL_TEXTURE_2D, texName[3]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,-1.0f,0.0f);
      glTexCoord2f(1.0f,10.0f); glVertex3f(1.6f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,10.0f); glVertex3f(-1.2f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.2f, 2.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.6f, 2.7f, -20.0f);
      glEnd();

      //Left Hall Right (Half) Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,10.0f); glVertex3f(1.2f, -0.5f, -20.0f);
      glTexCoord2f(0.5f,10.0f); glVertex3f(1.2f, -1.7f, -20.0f);
      glTexCoord2f(0.5f,0.0f); glVertex3f(1.2f, -1.7f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -0.5f, 0.0f);
      glEnd();

      //Left Hall Right (Half) Wall top
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,1.0f,0.0f);
      glTexCoord2f(1.0f/3.0f,18.0f); glVertex3f(1.6f, -0.5f, -20.0f);
      glTexCoord2f(0.0f,18.0f); glVertex3f(1.2f, -0.5f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -0.5f, 0.0f);
      glTexCoord2f(1.0f/3.0f,0.0f); glVertex3f(1.6f, -0.5f, 0.0f);
      glEnd();

      //Left Hall Right (Half) Wall (other side)
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,9.0f); glVertex3f(1.6f, -0.5f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.6f, -10.7f, 0.0f);
      glTexCoord2f(18.0f,0.0f); glVertex3f(1.6f, -10.7f, -20.0f);
      glTexCoord2f(18.0f,9.0f); glVertex3f(1.6f, -0.5f, -20.0f);
      glEnd();

      //Left Hall Right ("Elevator Shaft") Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f/3.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      
      glEnd();

      //Left Hall Right (Final) Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f);
      glEnd();

      //Left Hall Back Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,-1.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(-1.2f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(-1.2f, -1.7f, 20.0f);
      glEnd();

      //Middle Corridor Left Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(10.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glEnd();

      //Stairs Right Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,-1.0f);
      glTexCoord2f(1.0f,5.0f); glVertex3f(10.2f, 12.7f, 20.0f/3.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -10.7f, 20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -10.7f, 20.0f/3.0f);
      glTexCoord2f(0.0f,5.0f); glVertex3f(1.2f, 12.7f, 20.0f/3.0f);
      glEnd();

      //Middle Corridor Floor
      glBindTexture(GL_TEXTURE_2D, texName[1]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,1.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(3.0f,0.0f); glVertex3f(10.2f, -1.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(3.0f,1.0f); glVertex3f(10.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glEnd();

      //Middle Corridor Ceiling
      glBindTexture(GL_TEXTURE_2D, texName[3]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,-1.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.6f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(3.0f,1.0f); glVertex3f(10.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(3.0f,0.0f); glVertex3f(10.2f, 2.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.6f, 2.7f, 2.0f*20.0f/3.0f);
      glEnd();

      //Middle Corridor Right Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,-1.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.2f, -1.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(1.2f, 2.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(10.2f, 2.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, -1.7f, 2.0f*20.0f/3.0f);
      glEnd();

      //Right Hall Floor
      glBindTexture(GL_TEXTURE_2D, texName[1]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,1.0f,0.0f);
      glNormal3f(0.0f,1.0f,0.0f);glTexCoord2f(1.0f,20.0f); glVertex3f(12.6f, -1.7f, -20.0f);
      glNormal3f(0.0f,1.0f,0.0f);glTexCoord2f(0.0f,20.0f); glVertex3f(10.2f, -1.7f, -20.0f);
      glNormal3f(0.0f,1.0f,0.0f);glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f);
      glNormal3f(0.0f,1.0f,0.0f);glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, -1.7f, 20.0f);
      glEnd();

      //Right Hall Left (Final) Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 2.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,3.0f); glVertex3f(10.2f, -1.7f, 2.0f*20.0f/3.0f);
      glTexCoord2f(0.0f,3.0f); glVertex3f(10.2f, 2.7f, 2.0f*20.0f/3.0f);
      glEnd();

      //Right Hall Back Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,-1.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(10.2f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(12.6f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.6f, -1.7f, 20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f);
      glEnd();

      //Right Hall Right Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,20.0f); glVertex3f(12.6f, 2.7f, -20.0f);
      glTexCoord2f(1.0f,20.0f); glVertex3f(12.6f, -1.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, -1.7f, 20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.6f, 2.7f, 20.0f);
      glEnd();

      //Right Hall Ceiling 1
      glBindTexture(GL_TEXTURE_2D, texName[3]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,-1.0f,0.0f);
      glTexCoord2f(1.0f,5.0f); glVertex3f(12.6f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,5.0f); glVertex3f(10.2f, 2.7f, 20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 2.7f, 0.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, 2.7f, 0.0f);
      glEnd();

      //Right Hall Ceiling 2
      glBindTexture(GL_TEXTURE_2D, texName[3]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,-1.0f,0.0f);
      glTexCoord2f(1.0f,5.0f); glVertex3f(12.6f, 2.7f, 0.0f);
      glTexCoord2f(0.0f,5.0f); glVertex3f(9.8f, 2.7f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, 2.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, 2.7f, -20.0f);
      glEnd();
      
      //Right Hall Front Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.6f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(9.8f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, -1.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, -1.7f, -20.0f);
      glEnd();

      //Right Hall Front Wall (Other side (CI106))
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,-1.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(9.8f, 2.7f, -20.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.6f, 2.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, -1.7f, -20.0f);
      glEnd();

      //Right Hall Left (Half) Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, -0.5f, 0.0f);
      glTexCoord2f(0.5f,0.0f); glVertex3f(10.2f, -1.7f, 0.0f);
      glTexCoord2f(0.5f,10.0f); glVertex3f(10.2f, -1.7f, -20.0f);
      glTexCoord2f(0.0f,10.0f); glVertex3f(10.2f, -0.5f, -20.0f);
      glEnd();

      //Right Hall Left (Half) Wall top
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,1.0f,0.0f);
      glTexCoord2f(1.0f/3.0f,18.0f); glVertex3f(10.2f, -0.5f, -20.0f);
      glTexCoord2f(0.0f,18.0f); glVertex3f(9.8f, -0.5f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, -0.5f, 0.0f);
      glTexCoord2f(1.0f/3.0f,0.0f); glVertex3f(10.2f, -0.5f, 0.0f);
      glEnd();

      //Right Hall Left (half) Wall (Other side)
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,9.0f); glVertex3f(9.8f, -0.5f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, -10.7f, -20.0f);
      glTexCoord2f(18.0f,0.0f); glVertex3f(9.8f, -10.7f, 0.0f);
      glTexCoord2f(18.0f,9.0f); glVertex3f(9.8f, -0.5f, 0.0f);
      glEnd();

      //Right Hall Left Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 2.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, -1.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(1.0f,3.0f); glVertex3f(10.2f, -1.7f, 0.0f);
      glTexCoord2f(0.0f,3.0f); glVertex3f(10.2f, 2.7f, 0.0f);
      glEnd();

      //Right Hall Left Wall (Other Side (stairs))
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,3.0f); glVertex3f(10.2f, 12.7f, 0.0f);
      glTexCoord2f(4.0f,3.0f); glVertex3f(10.2f, -10.7f, 0.0f);
      glTexCoord2f(4.0f,0.0f); glVertex3f(10.2f, -10.7f, 20.0f/3.0f + 20.0f/6.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 12.7f, 20.0f/3.0f + 20.0f/6.0f);
      glEnd();

      //Middle Wall
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,-1.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 12.7f, 0.0f);
      glTexCoord2f(18.0f,0.0f); glVertex3f(10.2f, -10.7f, 0.0f);
      glTexCoord2f(18.0f,9.0f); glVertex3f(1.2f, -10.7f, 0.0f);
      glTexCoord2f(0.0f,9.0f); glVertex3f(1.2f, 12.7f, 0.0f);
      glEnd();

      //Right Hall Top Outer Wall
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,10.0f); glVertex3f(9.8f, 12.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, 2.7f, -20.0f);
      glTexCoord2f(18.0f,0.0f); glVertex3f(9.8f, 2.7f, 0.0f);
      glTexCoord2f(18.0f,10.0f); glVertex3f(9.8f, 12.7f, 0.0f);
      glEnd();

      //Middle Wall (Other Side)
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(0.0f,3.0f); glVertex3f(1.2f, 12.7f, 0.0f);
      glTexCoord2f(4.0f,3.0f); glVertex3f(1.2f, -10.7f, 0.0f);
      glTexCoord2f(4.0f,0.0f); glVertex3f(10.2f, -10.7f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 12.7f, 0.0f);
      glEnd();

      //Broken Stairs
      glBindTexture(GL_TEXTURE_2D, texName[5]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,1.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(10.2f, -10.7f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -10.7f, 0.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.2f, -10.7f, 20.0f/3.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(10.2f, -10.7f, 20.0f/3.0f);
      glEnd();

      //Stair Ceiling
      glBindTexture(GL_TEXTURE_2D, texName[3]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,-1.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 12.7f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.2f, 12.7f, 0.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(10.2f, 12.7f, 20.0f/3.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(1.2f, 12.7f, 20.0f/3.0f);
      glEnd();

      //Left Hall Outer Wall
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(4.0f,22.0f); glVertex3f(1.6f, 12.7f, -25.0f);
      glTexCoord2f(0.0f,22.0f); glVertex3f(1.6f, 12.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.6f, -10.7f, -20.0f);
      glTexCoord2f(4.0f,0.0f); glVertex3f(1.6f, -10.7f, -25.0f);
      glEnd();

      //Right Hall Outer Wall
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(4.0f,22.0f); glVertex3f(9.8f, 12.7f, -20.0f);
      glTexCoord2f(0.0f,22.0f); glVertex3f(9.8f, 12.7f, -25.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, -10.7f, -25.0f);
      glTexCoord2f(4.0f,0.0f); glVertex3f(9.8f, -10.7f, -20.0f);
      glEnd();

      //Left Hall Outer Top Wall
      glBindTexture(GL_TEXTURE_2D, texName[4]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,10.0f); glVertex3f(1.6f, 12.7f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.6f, 2.7f, 0.0f);
      glTexCoord2f(18.0f,0.0f); glVertex3f(1.6f, 2.7f, -20.0f);
      glTexCoord2f(18.0f,10.0f); glVertex3f(1.6f, 12.7f, -20.0f);
      glEnd();

      //Parada Preta do meio front
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.6f, -1.2f, -21.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.6f, -3.2f, -21.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(9.8f, -3.2f, -21.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(9.8f, -1.2f, -21.0f);
      glEnd();

      //Parada Preta do meio top
      glBindTexture(GL_TEXTURE_2D, texName[23]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,1.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.6f, -1.2f, -21.5f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.6f, -1.2f, -21.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(9.8f, -1.2f, -21.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(9.8f, -1.2f, -21.5f);
      glEnd();

      
      

      //Bloqueio da escada
      glBindTexture(GL_TEXTURE_2D, texName[25]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(1.2f, 2.7f, 0.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(1.2f, -1.7f, 0.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(1.2f, -1.7f, 20.0f/3.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(1.2f, 2.7f, 20.0f/3.0f);
      glEnd();


      /////////////////Sala 106////////////////

      //Left Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(9.8f, 2.7f, -25.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(9.8f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, -1.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(9.8f, -1.7f, -25.0f);
      glEnd();

      //Floor
      glBindTexture(GL_TEXTURE_2D, texName[1]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,1.0f,0.0f);
      glTexCoord2f(0.0f,5.0f); glVertex3f(12.6f, -1.7f, -25.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.6f, -1.7f, -10.0f);
      glTexCoord2f(5.0f,0.0f); glVertex3f(24.8f, -1.7f, -10.0f);
      glTexCoord2f(5.0f,5.0f); glVertex3f(24.8f, -1.7f, -25.0f);
      glEnd();

      //Other Floor
      glBindTexture(GL_TEXTURE_2D, texName[1]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,1.0f,0.0f);
      glTexCoord2f(0.0f,2.0f); glVertex3f(9.8f, -1.7f, -25.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, -1.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, -1.7f, -20.0f);
      glTexCoord2f(1.0f,2.0f); glVertex3f(12.6f, -1.7f, -25.0f);
      glEnd();

      //Front Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(9.8f, 2.7f, -25.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(9.8f, -1.7f, -25.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(24.8f, -1.7f, -25.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(24.8f, 2.7f, -25.0f);
      glEnd();


      //Back Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,-1.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(24.8f, 2.7f, -10.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(24.8f, -1.7f, -10.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.601f, -1.7f, -10.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.601f, 2.7f, -10.0f);
      glEnd();

      //Other Left Wall
      glBindTexture(GL_TEXTURE_2D, texName[2]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.6f, 2.7f, -10.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(12.6f, -1.7f, -10.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.6f, -1.7f, -20.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, 2.7f, -20.0f);
      glEnd();

      //Ceiling1
      glBindTexture(GL_TEXTURE_2D, texName[3]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,-1.0f,0.0f);
      glTexCoord2f(0.0f,2.0f); glVertex3f(9.8f, 2.7f, -20.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(9.8f, 2.7f, -25.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.6f, 2.7f, -25.0f);
      glTexCoord2f(1.0f,2.0f); glVertex3f(12.6f, 2.7f, -20.0f);
      glEnd();

      //Ceiling2
      glBindTexture(GL_TEXTURE_2D, texName[3]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,-1.0f,0.0f);
      glTexCoord2f(0.0f,5.0f); glVertex3f(12.6f, 2.7f, -10.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.6f, 2.7f, -25.0f);
      glTexCoord2f(5.0f,0.0f); glVertex3f(24.8f, 2.7f, -25.0f);
      glTexCoord2f(5.0f,5.0f); glVertex3f(24.8f, 2.7f, -10.0f);
      glEnd();

      /////////////THEDOORS///////////////////////////////////

      //CI101
      glBindTexture(GL_TEXTURE_2D, texName[8]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(-1.19f, 1.0f, 19.5f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.19f, -1.7f, 19.5f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(-1.19f, -1.7f, 18.1f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(-1.19f, 1.0f, 18.1f);
      glEnd();

      //CI102
      glBindTexture(GL_TEXTURE_2D, texName[9]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(-1.15f, 1.0f, 1.9f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.15f, -1.7f, 1.9f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(-1.15f, -1.7f, 0.5f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(-1.15f, 1.0f, 0.5f);
      glEnd();

      //CI103
      glBindTexture(GL_TEXTURE_2D, texName[10]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(-1.15f, 1.0f, -8.1f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.15f, -1.7f, -8.1f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(-1.15f, -1.7f, -9.5f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(-1.15f, 1.0f, -9.5f);
      glEnd();

      //CI104
      glBindTexture(GL_TEXTURE_2D, texName[11]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(-1.15f, 1.0f, -10.5f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-1.15f, -1.7f, -10.5f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(-1.15f, -1.7f, -11.9f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(-1.15f, 1.0f, -11.9f);
      glEnd();

      //CI105
      glBindTexture(GL_TEXTURE_2D, texName[7]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(0.7f, 1.0f, -19.85f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(-0.7f, 1.0f, -19.85f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-0.7f, -1.7f, -19.85f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(0.7f, -1.7f, -19.85f);
      glEnd();

      //CI106
      glBindTexture(GL_TEXTURE_2D, texName[12]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.1f, 1.0f, -19.85f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(10.7f, 1.0f, -19.85f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.7f, -1.7f, -19.85f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.1f, -1.7f, -19.85f);
      glEnd();

      //R1
      glBindTexture(GL_TEXTURE_2D, texName[13]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(12.55f, 1.0f, -11.9f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.55f, -1.7f, -11.9f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.55f, -1.7f, -10.5f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.55f, 1.0f, -10.5f);
      glEnd();
    
      //R2
      glBindTexture(GL_TEXTURE_2D, texName[14]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(12.55f, 1.0f, -9.5f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.55f, -1.7f, -9.6f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.55f, -1.7f, -8.1f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.55f, 1.0f, -8.1f);
      glEnd();

      //R3
      glBindTexture(GL_TEXTURE_2D, texName[15]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(12.55f, 1.0f, -1.9f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.55f, -1.7f, -1.9f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.55f, -1.7f, -0.5f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.55f, 1.0f, -0.5f);
      glEnd();

      //R4
      glBindTexture(GL_TEXTURE_2D, texName[16]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(12.55f, 1.0f, 0.5f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.55f, -1.7f, 0.5f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.55f, -1.7f, 1.9f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.55f, 1.0f, 1.9f);
      glEnd();

      //R5
      glBindTexture(GL_TEXTURE_2D, texName[17]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(12.55f, 1.0f, 20.0f/3.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.55f, -1.7f, 20.0f/3.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.55f, -1.7f, 20.0f/3.0f + 1.4f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.55f, 1.0f, 20.0f/3.0f + 1.4f);
      glEnd();

      //R6
      glBindTexture(GL_TEXTURE_2D, texName[18]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(12.55f, 1.0f, 2.0f*20.0f/3.0 + 0.5f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(12.55f, -1.7f, 2.0f*20.0f/3.0 + 0.5f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.55f, -1.7f, 2.0f*20.0f/3.0 + 1.9f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.55f, 1.0f, 2.0f*20.0f/3.0 + 1.9f);
      glEnd();

      //106 Inside
      glBindTexture(GL_TEXTURE_2D, texName[20]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f(12.1f, 1.0f, -20.01f);
      glTexCoord2f(1.0f,0.0f); glVertex3f(12.1f, -1.7f, -20.01f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(10.7f, -1.7f, -20.01f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(10.7f, 1.0f, -20.01f);
      glEnd();


      ////////SKYBOX////////////////////////////
      //Front
      glBindTexture(GL_TEXTURE_2D, texName[19]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(0.25f,2.0/3.0f); glVertex3f(-2.0f, 15.0f, -30.0f);
      glTexCoord2f(0.25f,1.0/3.0f); glVertex3f(-2.0f, -15.0f, -30.0f);
      glTexCoord2f(0.5f,1.0f/3.0f); glVertex3f(30.0f, -15.0f, -30.0f);
      glTexCoord2f(0.5f,2.0/3.0f); glVertex3f(30.0f, 15.0f, -30.0f);
      glEnd();

      //Left
      glBindTexture(GL_TEXTURE_2D, texName[19]);
      glBegin(GL_QUADS);
      glNormal3f(1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,2.0/3.0f); glVertex3f(-2.0f, 15.0f, 30.0f);
      glTexCoord2f(0.0f,1.0/3.0f); glVertex3f(-2.0f, -15.0f, 30.0f);
      glTexCoord2f(0.25f,1.0f/3.0f); glVertex3f(-2.0f, -15.0f, -30.0f);
      glTexCoord2f(0.25f,2.0f/3.0f); glVertex3f(-2.0f, 15.0f, -30.0f);
      glEnd();

      //Right
      glBindTexture(GL_TEXTURE_2D, texName[19]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.5f,2.0/3.0f); glVertex3f(30.0f, 15.0f, -30.0f);
      glTexCoord2f(0.5f,1.0/3.0f); glVertex3f(30.0f, -30.0f, -30.0f);
      glTexCoord2f(0.75f,1.0f/3.0f); glVertex3f(30.0f, -30.0f, 30.0f);
      glTexCoord2f(0.75f,2.0f/3.0f); glVertex3f(30.0f, 15.0f, 30.0f);
      glEnd();

      //Up
      glBindTexture(GL_TEXTURE_2D, texName[19]);
      glBegin(GL_QUADS);
      glNormal3f(0.0f,-1.0f,0.0f);
      glTexCoord2f(0.25f,1.0f); glVertex3f(-2.0f, 15.0f, 30.0f);
      glTexCoord2f(0.25f,2.0/3.0f); glVertex3f(-2.0f, 15.0f, -30.0f);
      glTexCoord2f(0.5f,2.0f/3.0f); glVertex3f(30.0f, 15.0f, -30.0f);
      glTexCoord2f(0.5f,1.0f); glVertex3f(30.0f, 15.0f, 30.0f);
      glEnd();

      //Right Wall
      glBindTexture(GL_TEXTURE_2D, texName[26]);
      glBegin(GL_QUADS);
      glNormal3f(-1.0f,0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(24.8f, 2.7f, -25.0f);
      glTexCoord2f(0.0f,0.0f); glVertex3f(24.8f, -1.7f, -25.0f);
      glTexCoord2f(2.0f,0.0f); glVertex3f(24.8f, -1.7f, -10.0f);
      glTexCoord2f(2.0f,1.0f); glVertex3f(24.8f, 2.7f, -10.0f);
      glEnd();
      

     glDisable(GL_TEXTURE_2D);
     

    if(!close){
		glutSwapBuffers();
    }
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


/* Program entry point */

int main(int argc, char *argv[])
{
    printf("\nInicializando Lost in Mit...\n");

    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Lost In MIT");
    glutSetCursor(GLUT_CURSOR_NONE);

    printf("\nLista de comandos:\n\n'f' para entrar/sair no modo fullscreen\n'e' para entrar/sair da sala 106\n'e' para finalizar o programa em frente as escadas\n\n");

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


    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT3, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, LightPosition3);
//	glEnable(GL_LIGHT3);
	
	glEnable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    atexit(free_mem);

    glutMainLoop();

    return EXIT_SUCCESS;
}
