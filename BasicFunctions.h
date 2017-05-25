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

    glEnd();
    
    
}

void init2(){

  texName[0] = SOIL_load_OGL_texture
        (
        "cuco.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0//SOIL_FLAG_INVERT_Y
        );
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


  texName[1] = SOIL_load_OGL_texture
        (
        "floor.jpeg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    texName[2] = SOIL_load_OGL_texture
        (
        "wwall.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    texName[3] = SOIL_load_OGL_texture
        (
        "ceiling.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

}


void LoadObject(const char * obj){


    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(obj, aiProcess_Triangulate | 
                                                  aiProcess_GenSmoothNormals);
    unsigned int mesh, face;

   
   

   
    
    for (mesh = 0 ; mesh < scene->mNumMeshes; mesh++) 
    {
      
      
      if(scene->mMeshes[mesh]->HasTextureCoords(0)){
        ;
        } 
        for(face = 0; face < scene->mMeshes[mesh]->mNumFaces; face++) 
        {


            glBegin(GL_TRIANGLES);

           // glColor3f(0.6f, 0.6f, 0.6f);
            
//front
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z);
            glTexCoord2f((float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
                         (float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y);
            //glTexCoord2f(0.0f,0.0f);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z);
                                   
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z);
            glTexCoord2f((float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                        (float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y);
            //glTexCoord2f(0.0f,1.0f);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z);
                                   
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z);
            glTexCoord2f((float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                         (float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y);
            //glTexCoord2f(1.0f,1.0f);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z);


// Back
/*
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z);
            //glTexCoord2f((float)scene->mMeshes[mesh]->mTextureCoords[scene->mMeshes[mesh]->mFaces[face].mIndices[2]][0].x,
              //           (float)scene->mMeshes[mesh]->mTextureCoords[scene->mMeshes[mesh]->mFaces[face].mIndices[2]][0].y);
            glTexCoord2f(0.0f,0.0f);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z);
                                   
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z);
            //glTexCoord2f((float)scene->mMeshes[mesh]->mTextureCoords[scene->mMeshes[mesh]->mFaces[face].mIndices[1]][0].x,
              //           (float)scene->mMeshes[mesh]->mTextureCoords[scene->mMeshes[mesh]->mFaces[face].mIndices[1]][0].y);
            glTexCoord2f(0.0f,1.0f);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z);
                                   
            glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y,
                       (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z);
            //glTexCoord2f((float)scene->mMeshes[mesh]->mTextureCoords[scene->mMeshes[mesh]->mFaces[face].mIndices[0]][0].x,
              //           (float)scene->mMeshes[mesh]->mTextureCoords[scene->mMeshes[mesh]->mFaces[face].mIndices[0]][0].y);
            glTexCoord2f(1.0f,1.0f);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z);
            
*/


       glEnd();
        }
    }
   
}


#endif // BASICFUNCTIONS_H_INCLUDED