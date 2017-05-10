#ifndef BASICFUNCTIONS_H_INCLUDED
#define BASICFUNCTIONS_H_INCLUDED

typedef struct point{
    float x, y, z;
}Point;



void DrawTriangle( glm::vec3 p1, glm::vec3 p2, glm::vec3 p3){

	
    glBegin(GL_TRIANGLES);

    glColor3f(0.6f, 0.6f, 0.6f);

    glVertex3f( p3.x, p3.y, p3.z);
    glVertex3f( p2.x, p2.y, p2.z);
    glVertex3f( p1.x, p1.y, p1.z);
    
   // glColor3f(0.0f,1.0f,0.0f);

    
 //   glVertex3f( p2.x, p2.y, p2.z);
   // glVertex3f( p3.x, p3.y, p3.z);
   // glVertex3f( p1.x, p1.y, p1.z);

    //glColor3f(3.0f , 3.0f, 3.0f);

    
    

    glEnd();
    
    


}


void LoadObject(const char * obj){


    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(obj, aiProcess_Triangulate | 
                                                  aiProcess_GenSmoothNormals);
    unsigned int mesh, face;

    for (mesh = 0 ; mesh < scene->mNumMeshes; mesh++) 
    {

        for(face = 0; face < scene->mMeshes[mesh]->mNumFaces; face++) 
        {

            glBegin(GL_TRIANGLES);

            glColor3f(0.6f, 0.6f, 0.6f);
            

            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z);
                                   
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z);
                                   
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z);


// Back
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z);
                                   
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z);
                                   
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z);
            



       glEnd();
        }
    }
}


#endif // BASICFUNCTIONS_H_INCLUDED
