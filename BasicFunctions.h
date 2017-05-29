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
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z};
            t.p1n = {(float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[0]].z};
            t.p1t = {(float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[0]].x,
                     (float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[0]].y};


            t.p2p = {  (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z};
            t.p2n = {(float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[1]].z};
            t.p2t = {(float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[1]].x,
                     (float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[1]].y};


            t.p3p = {  (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                       (float) scene->mMeshes[mesh]->mVertices[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z};
            t.p3n = {(float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y,
                     (float) scene->mMeshes[mesh]->mNormals[scene->mMeshes[mesh]->mFaces[face].mIndices[2]].z};
            t.p3t = {(float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[2]].x,
                     (float)scene->mMeshes[mesh]->mTextureCoords[0][scene->mMeshes[mesh]->mFaces[face].mIndices[2]].y};


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

    texName[6] = SOIL_load_OGL_texture
        (
        "chairbb.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[7] = SOIL_load_OGL_texture
        (
        "portas/105.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[8] = SOIL_load_OGL_texture
        (
        "portas/101.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[9] = SOIL_load_OGL_texture
        (
        "portas/102.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[10] = SOIL_load_OGL_texture
        (
        "portas/103.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[11] = SOIL_load_OGL_texture
        (
        "portas/104.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[12] = SOIL_load_OGL_texture
        (
        "portas/106.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[13] = SOIL_load_OGL_texture
        (
        "portas/r1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[14] = SOIL_load_OGL_texture
        (
        "portas/r2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[15] = SOIL_load_OGL_texture
        (
        "portas/r3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[16] = SOIL_load_OGL_texture
        (
        "portas/r4.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[17] = SOIL_load_OGL_texture
        (
        "portas/r5.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[18] = SOIL_load_OGL_texture
        (
        "portas/r6.png",
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
    LoadObject2("texchair.obj", &trianglelist[0]);

    init_list(&trianglelist[1]);
    LoadObject2("2box.obj", &trianglelist[1]);

    init_list(&trianglelist[2]);
    LoadObject2("table.obj", &trianglelist[2]);

    init_list(&trianglelist[3]);
    LoadObject2("2box.obj", &trianglelist[3]);

    init_list(&trianglelist[4]);
    LoadObject2("pc2.obj", &trianglelist[4]);


    ////SKYBOX////////////////////////////////////////////////////
    texName[19] = SOIL_load_OGL_texture
        (
        "skybox.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[20] = SOIL_load_OGL_texture
        (
        "door.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[21] = SOIL_load_OGL_texture
        (
        "gray.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[22] = SOIL_load_OGL_texture
        (
        "bege.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    texName[23] = SOIL_load_OGL_texture
        (
        "black.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|
        SOIL_FLAG_MIPMAPS
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);


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

            glColor3f(0.0f, 0.0f, 0.0f);
            
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

        glColor3f(0.2f, 0.2f, 0.2f);
        

        glm::vec3 n = glm::normalize(aux->t.p1n);
        glNormal3f(n.x, n.y, n.z );
        glTexCoord2f(aux->t.p1t.x, aux->t.p1t.y);
        glVertex3f(aux->t.p1p.x, aux->t.p1p.y, aux->t.p1p.z );
        
        n = glm::normalize(aux->t.p2n);
        glNormal3f(n.x, n.y, n.z );
        glTexCoord2f(aux->t.p2t.x, aux->t.p2t.y);
        glVertex3f(aux->t.p2p.x, aux->t.p2p.y, aux->t.p2p.z );

        n = glm::normalize(aux->t.p3n);
        glNormal3f(n.x, n.y, n.z );
        glTexCoord2f(aux->t.p3t.x, aux->t.p3t.y);
        glVertex3f(aux->t.p3p.x, aux->t.p3p.y, aux->t.p3p.z );

        
        
        if (aux->next == NULL) break;
        aux = aux->next;

    }

    glEnd();

}


#endif // BASICFUNCTIONS_H_INCLUDED