#ifndef BASICFUNCTIONS_H_INCLUDED
#define BASICFUNCTIONS_H_INCLUDED

typedef struct point{
    float x, y, z;
}Point;



void DrawTriangle( glm::vec3 p1, glm::vec3 p2, glm::vec3 p3){

	
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex3f( p3.x, p3.y, p3.z);
    glVertex3f( p2.x, p2.y, p2.z);
    glVertex3f( p1.x, p1.y, p1.z);
    
    glColor3f(0.0f,1.0f,0.0f);

    
 //   glVertex3f( p2.x, p2.y, p2.z);
   // glVertex3f( p3.x, p3.y, p3.z);
   // glVertex3f( p1.x, p1.y, p1.z);

    //glColor3f(3.0f , 3.0f, 3.0f);

    
    

    glEnd();
    
    


}

#endif // BASICFUNCTIONS_H_INCLUDED
