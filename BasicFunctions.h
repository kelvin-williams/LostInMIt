#ifndef BASICFUNCTIONS_H_INCLUDED
#define BASICFUNCTIONS_H_INCLUDED

typedef struct point{
    float x, y, z;
}Point;



void DrawTriangle( float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z){

  //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0);

    glVertex3f( p2x, p2y, p2z);
    glVertex3f( p1x, p1y, p1z);
    glVertex3f( p3x, p3y, p3z);

    glEnd();


}

#endif // BASICFUNCTIONS_H_INCLUDED
