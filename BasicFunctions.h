#ifndef BASICFUNCTIONS_H_INCLUDED
#define BASICFUNCTIONS_H_INCLUDED


typedef struct point{
    float x, y, z;
}Point;


void DrawTriangle( glm::vec3 p1, glm::vec3 p2, glm::vec3 p3){

	
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.1f, 0.0f);

    glVertex3f( p3.x, p3.y, p3.z);
    glVertex3f( p2.x, p2.y, p2.z);
    glVertex3f( p1.x, p1.y, p1.z);

    glEnd();
    
    
}

void LoadObject2(const char * obj, List * list){


    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(obj, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
    unsigned int mesh, face;

    for (mesh = 0 ; mesh < scene->mNumMeshes; mesh++) 
    {

        for(face = 0; face < scene->mMeshes[mesh]->mNumFaces; face++) 
        {
            Triangle t;

            t.p1p = {  (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z,};
            t.p1n = {(float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z};


            t.p2p = {  (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z,};
            t.p2n = {(float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z};


            t.p3p = {  (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z,};
            t.p3n = {(float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z};

            list_add(list, t);
           
        }

    }

}




void init2(){

  ////////////////Texturas/////////////////////////////////////////////////////
  texName[0] = SOIL_load_OGL_texture
        (
        "cuco.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        //SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);


  texName[1] = SOIL_load_OGL_texture
        (
        "floor.jpeg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y |
        SOIL_FLAG_MIPMAPS
        );
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[2] = SOIL_load_OGL_texture
        (
        "wwall.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[3] = SOIL_load_OGL_texture
        (
        "ceiling.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[4] = SOIL_load_OGL_texture
        (
        "tiles.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[5] = SOIL_load_OGL_texture
        (
        "stairs.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);


    //////OBJETOS//////////////////////////////////////////////////
    
    init_list(&trianglelist[0]);
    LoadObject2("Chair_01.obj", &trianglelist[0]);

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

            glColor3f(0.0f, 0.0f, 1.0f);
            
//front
        //    glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
          //             (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y,
            //           (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z);
          //  glTexCoord2f((float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
             //            (float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y);
            //glTexCoord2f(0.0f,0.0f);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y, 
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z);
                                   
         //   glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
           //            (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
             //          (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z);
          //  glTexCoord2f((float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
              //          (float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y);
            //glTexCoord2f(0.0f,1.0f);
            glVertex3f((float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z);
                                   
           // glNormal3f((float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
             //          (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
               //        (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z);
          //  glTexCoord2f((float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
               //          (float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y);
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


void PrintObj(List * list){

    Node * aux = list->head;
    glBegin(GL_TRIANGLES);

    

    while(aux!=NULL){

        glColor3f(0.0f, 1.0f, 0.0f);

        glNormal3f(aux->t.p1n.x, aux->t.p1n.y, aux->t.p1n.z );
        glVertex3f(aux->t.p1p.x, aux->t.p1p.y, aux->t.p1p.z );

        glNormal3f(aux->t.p2n.x, aux->t.p2n.y, aux->t.p2n.z );
        glVertex3f(aux->t.p2p.x, aux->t.p2p.y, aux->t.p2p.z );

        glNormal3f(aux->t.p3n.x, aux->t.p3n.y, aux->t.p3n.z );
        glVertex3f(aux->t.p3p.x, aux->t.p3p.y, aux->t.p3p.z );
        
        if (aux->next == NULL) break;
        aux = aux->next;

    }

    glEnd();

}


#endif // BASICFUNCTIONS_H_INCLUDED