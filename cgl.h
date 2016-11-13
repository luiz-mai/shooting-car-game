#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

using namespace std;

struct Vertex{
    bool used;
    double x, y, z;
};
struct Position{
    float x, y, z, xrot, yrot, zrot;
};
struct TVertex{
    double x, y;
};
struct Image{
    int   type;
    int   id;
    int   width;
    int   height;
    char *data;
};
struct TriFace{
    int a, b, c;
    bool used;
};
struct Map{
    int vI[3];
    int uvI[3];
    int vnI[3];
};
struct Obj{
    string name;  //header of 'o'
    string mtl;

    int TotalFaceCount;
    int imgIndex;

    vector<Map> fmap;
};
struct ObjLoader{
    int objCount;
    //When multiple objects in the same file, they share verticies.
    vector<TVertex> uv_vert;
    vector<Vertex> vert;
    vector<Vertex> vn_vert;

    vector<Obj> obj;
    string mtllib;
};

typedef enum _types { TYPE_BMP, TYPE_RPI } ImagesType; 

//CLASS DEFINITIONS--------------------------------------------------------------
class cglTexture{
    public:
        cglTexture(){};
        void LoadTexture(char * File, int Type, int PicID, bool mipmap);//Modified
        void SetTexture(Image img, int PicID, bool mipmap);  //NEW
        Image GetTexture(char * bmpFile, int type, int setPID); //NEW
        void SetActiveTexture(int PicID);
        void EnableSphere();
        void DisableSphere();
    private:
        Image LoadRPI(char * filename){};
        void getBitmapImageData(char *pFileName, Image *pImage);
        GLuint g_textureID[50];
};

class CGL{
    public:
        CGL();
        bool StoreRPI(Image img);
        //Obj File Loader --->>> WORKING for multiple objects =)
        ObjLoader* objLoad(const char * filename, ObjLoader* obj);
        void       objDraw(ObjLoader obj);
        ObjLoader* objLoadTex(ObjLoader* obj);

        void EnableHUD();
        void DisableHUD();
        int * GetWindowSize();
    private:

        cglTexture tex;
        int texCount;

        char * strToLower(char * string);
};

CGL::CGL(){
}

char * CGL::strToLower(char * string){
    char* ret = (char*)malloc(strlen(string));
    for(int i = 0; i <= strlen(string); i++){
        ret[i] = tolower(string[i]);
    }
    return ret;
}
void debugDisplayArray(char * str, int sz){
    for(int i = 0; i <= sz; i++){
        cout << str[i];
    }
    cout << endl;
}
ObjLoader* CGL::objLoad(const char* filename, ObjLoader* obj){
    ifstream fin(filename);
    if(!fin){
        obj->objCount = -1;
        return obj;
    }
    //Starting container at 0, not one. adjust accordingly!**************
    //objcount starts at 1;
    string line;
    
   
    
    while(getline(fin, line)){
        stringstream ss(line);
        string lhead;
        getline(ss, lhead, ' ');
        if(lhead.compare("o") == 0){
            string name;
            getline(ss, name, '\n'); //Get the name;
            //Create a new object and assign the name
            Obj object;
            object.name = name;
            object.TotalFaceCount = 0;
            //Add it to the vector and increase the object count
            obj->obj.push_back(object);
            obj->objCount += 1;
        }else if(lhead.compare("v") == 0){
            Vertex tmpVert;

            tmpVert.used = true;

            ss >> tmpVert.z;
            ss >> tmpVert.y;
            ss >> tmpVert.x;

            obj->vert.push_back(tmpVert);
        }else if(lhead.compare("vt") == 0){
            TVertex tmpVert;

            ss >> tmpVert.x;
            ss >> tmpVert.y;

            obj->uv_vert.push_back(tmpVert);
        }else if(lhead.compare("vn") == 0){
            Vertex tmpVert;
            string tmp;
            tmpVert.used = true;

            ss >> tmpVert.x;
            ss >> tmpVert.y;
            ss >> tmpVert.z;

            obj->vn_vert.push_back(tmpVert);

        }else if(lhead.compare("f") == 0){
            Map mtmp;
            obj->obj[obj->objCount-1].TotalFaceCount += 1;
            for(int i = 0; i < 3; i++){ //Currently only supporting triangles.
                string group;
                getline(ss, group, ' ');
                stringstream iss(group);

                string tmp;
                getline(iss, tmp, '/');
                mtmp.vI[i] = atoi(tmp.c_str()) -1; //Index starts at one, conatainer starts at 0;
                tmp.clear();

                getline(iss, tmp, '/');
                mtmp.uvI[i] = atoi(tmp.c_str()) -1;
                tmp.clear();

                getline(iss, tmp, ' ');
                mtmp.vnI[i] = atoi(tmp.c_str()) -1;
                tmp.clear();
            }
            obj->obj[obj->objCount-1].fmap.push_back(mtmp);
        }else if(lhead.compare("mtllib") == 0){
        
       
        	 
        	 	
            getline(ss,obj->mtllib);
            ifstream mtlTest(obj->mtllib.c_str());
            if(!fin){
                cout << "ERROR: Unable able to open mtllib file " << obj->mtllib << endl;
            }
        }else if(lhead.compare("usemtl") == 0){
        
        	
        	
            getline(ss, obj->obj[obj->objCount -1].mtl);
           
            
            
        }

    }
    
    
    objLoadTex(obj);
}
ObjLoader * CGL::objLoadTex(ObjLoader* obj){

    if(obj->objCount <= 0 || obj->mtllib.size() <= 0){
        cout << "Unable to load textures" << endl;
        return obj;
    }
    
    ifstream mtl(obj->mtllib.c_str());
    
    if(!mtl){
        cout << "Unable to open mtl file" << endl;
        return obj;
    }
    
    
    glEnable(GL_TEXTURE_2D);
    string line;
    int picID = 0;
    
    while(getline(mtl, line)){
        string header;
        stringstream ss(line);
        ss >> header;
        if(header.compare("newmtl") == 0){ //First find where the mtl name is declared
            string value;
            ss >> value;
            //Cycle through all of the objects to see which one uses this material
            for(int i = 0; i < obj->objCount; i++){
                if(obj->obj[i].mtl.compare(value) == 0){
                	
                    string subLine;
                    
                    while(getline(mtl, subLine)){
                        stringstream subSS(subLine);
                        string subValue;
                        subSS >> subValue;
                        if(subValue.compare("map_Kd") == 0){
                            string file;
                            //getline(subSS, file);
                            subSS >> file;       //NEED TO CHANGE THIS, WILL FAIL IF WHITESPACE IN FILE PATH
                            tex.LoadTexture((char*)file.c_str(), TYPE_BMP, picID, true);
                            obj->obj[i].imgIndex = picID;
                            picID ++;
                            break;
                        }
                    }
                    
                    break;
                }
            }
        }
    }
    
}
void CGL::objDraw(ObjLoader obj){
    glBegin(GL_TRIANGLES);
    for(int o = 0; o < obj.objCount; o++){
        tex.SetActiveTexture(obj.obj[o].imgIndex);
        for(int f = 0; f < obj.obj[o].TotalFaceCount; f++){
            for(int i = 0; i < 3; i++){
            	glTexCoord2d(obj.uv_vert[obj.obj[o].fmap[f].uvI[i]].x, obj.uv_vert[obj.obj[o].fmap[f].uvI[i]].y);
                glVertex3f(-obj.vert[obj.obj[o].fmap[f].vI[i]].x, obj.vert[obj.obj[o].fmap[f].vI[i]].y, obj.vert[obj.obj[o].fmap[f].vI[i]].z);
            }
        }
    }
    glEnd();
}

void cglTexture::SetActiveTexture(int PicID){
    if(PicID > -1){
        glBindTexture(GL_TEXTURE_2D, g_textureID[PicID]);
    }
}

void cglTexture::LoadTexture(char * File, int type, int PicID, bool mipmap){
    Image textureImage;
    //getBitmapImageData(bmpFile, &textureImage[PicID]);
    if(type == TYPE_RPI){
        textureImage = LoadRPI(File);
    }else if(type == TYPE_BMP){
        getBitmapImageData(File, &textureImage);
    }
    textureImage.id = PicID;
    SetTexture(textureImage, PicID, mipmap);
}

void cglTexture::SetTexture(Image img, int PicID, bool mipmap){
    glGenTextures( 1, &g_textureID[PicID] );
    glBindTexture( GL_TEXTURE_2D, g_textureID[PicID] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    if(mipmap){
        if(img.type == 3){
            gluBuild2DMipmaps( GL_TEXTURE_2D, 3, img.width, img.height, GL_RGB, GL_UNSIGNED_BYTE, img.data);
        }else if(img.type == 4){
            gluBuild2DMipmaps( GL_TEXTURE_2D, 4, img.width, img.height, GL_RGBA, GL_UNSIGNED_BYTE, img.data);
        }
    }else{
        if(img.type == 3){
            glTexImage2D( GL_TEXTURE_2D, 0, 3, img.width, img.height,
                        0, GL_RGB, GL_UNSIGNED_BYTE, img.data );
        }else if(img.type == 4){
            glTexImage2D( GL_TEXTURE_2D, 0, 4, img.width, img.height,
                        0, GL_RGBA, GL_UNSIGNED_BYTE, img.data );
        }
    }
}
void cglTexture::getBitmapImageData( char *pFileName, Image *pImage ){
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;
    if( (pFile = fopen(pFileName, "rb") ) == NULL )
                printf("ERROR: getBitmapImageData - %s not found\n",pFileName);
    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );
    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
                printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n", pFileName);
    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
                printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n", pFileName);
    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
                printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);
    if( nNumPlanes != 1 )
                printf( "ERROR: getBitmapImageData - Plane count from %s is not 1: %u\n", pFileName, nNumPlanes );
    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
                printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n", pFileName );
    if( nNumBPP != 24 ){
                printf( "ERROR: getBitmapImageData - BPP from %s is not 24: %u\n", pFileName, nNumBPP );
                pImage->type = nNumBPP / 8;
    }else{
        pImage->type = 3;
    }
        // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );
        // Calculate the image's total size in bytes. Note how we multiply the
        // result of (width * height) by 3. This is becuase a 24 bit color BMP
        // file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;
    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
                printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n", pFileName);
        // Finally, rearrange BGR to RGB
        char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 ){
                charTemp = pImage->data[i];
                pImage->data[i] = pImage->data[i+2];
                pImage->data[i+2] = charTemp;
    }
}

