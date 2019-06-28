/*
* Final Assignment | 2nd Year 2nd Semester 2017
* Student | Adhisha Gammanpila
* Exam No | AS2015384
* Project | Knight Rider
*/


#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Constants
float PI = 22/7;

//Development environment
void DrawAxis();
void DrawQuad(float,float);
void DrawCuboid(float,float,float);
void DrawQuad(float,float,float[],float[]);

//World
float worldLength=100;
float worldWidth =100;
void DrawFloor();

//Tree Functions and variables
void DrawPineTreeLayered(float);
void DrawPineTreeLayered(float,float);

//Fractal Tree
void DrawFractalForest();
void DrawFractalBranch(float);
void DrawFractalTree();
void DrawFractalBushTree();

//Road Functions
void DrawRoadLines(float);
void DrawMainRoad(float,float,float ,float[],float[]);
void DrawRoadSystem();


//Vehicle Body Parts
void DrawBody_1();
void DrawBody_2();
void DrawBody_3();
void DrawBody_4();
void DrawTopMiddle();
void DrawBackGlass();
void DrawFrontGlass();
void DrawFrontBumper();
void DrawKITTScanner();
void DrawBackWheels(float);
void DrawFrontWheels(float,float);
void DrawReverseLights(int);
void DrawKITT();

//Turbo Boost Variables
float turboHeight=0;
void TurboBoost();
float angle=0;

//Vehicle Lights
/* 0 - All off ,
1 - Breaks ,
2- Reverse ,
3- Left Turn,
4 - Right Turn*/
int KITT_Back_Lights=0;
float break_lights_rgb[] ={0,0,0};
float reverse_left_lights_rgb[] ={0,0,0};
float reverse_right_lights_rgb[] ={0,0,0};


//Vehicle and Camera translations
double transX =0;
double transY =0;
double transZ=0;
float turn=0;

//Wheel Rotate
float wheel_rotate_z=0;

//Cylinder Object
GLUquadric* qobj;

//Collision detection variables
//Tree coordinates
float TreeX =-0.2;
float TreeY =0;
float TreeZ =-2;

float TreeSafeReg=0.5; //Collision detection region for the Tree
float KITTSafeReg=0.5; //Collision detection region for the Car

float dx = 0;
float dy = 0;
float dz = 0;

float gap = 0;

//Pond wave and curve surface variables
float angle_Rot_Water=0;
float pond_translate_x=-20;
float pond_translate_y=-20;
void curved_surface_tile(float ,float);
void Drawcurved_surface_atom();
void DrawPondSurface();
void DrawWaterTile(float,float);
void DrawPond();

//Camera settings
int camera_view=0; // 0 - From the side , 1 - Car from Back, 2 - Near Tire View

//Variables for Animations
int refreshMills = 15;
float relative_clock=0; // The developer defined clock for the app
void initialize_animations(); //Animations are executed in this function
float scannerY_dark =0;


//Variables for Texturing
GLuint texture[2];
GLint slices=16;
GLint stacks=16;

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

#define checkImageWidth 64
#define checkImageHeight 64

GLubyte checkImage[checkImageWidth][checkImageHeight][3];
void myinit(void);

//Lighting and Shading
void colorInit();

void TurboBoost(){

        turboHeight = 2*sin(3.14*angle/180);
        transZ -= 2.1;
        printf("%f\n",turboHeight);
        angle+=10;

}

void DrawPond(){

    angle_Rot_Water = sin(3.14*relative_clock*10/180);
        glPushMatrix();
        glTranslatef(pond_translate_x,0,pond_translate_y);
        glRotatef(angle_Rot_Water,1,1,1);
            glPushMatrix();
            glTranslatef(0,0.01,0);
            for(float j=0;j<360;j+=1){
                glRotatef(j,0,1,0);
                glPushMatrix();
                for(float i=0;i<5;i++){
                glTranslatef(0.1,0,0);
                DrawWaterTile(0.1,0.1);
                }
                glPopMatrix();
            }

            glPopMatrix();
        glPopMatrix();
}

void curved_surface_tile(float length,float height){
    //With Texture

    /*
    Texture rendering was stopped due to crashing of the system. All works until we make it a half circle.
    */

    //myinit();
    //glBindTexture(GL_TEXTURE_2D, texture[0]);

    glBegin(GL_QUADS);
        //glTexCoord2f(-length/2,-height/2);
        glColor3f(0,0.5,0);
        glVertex3f(-length/2,-height/2,0);

        //glTexCoord2f(length/2,-height/2);
        glVertex3f(length/2,-height/2,0);
        glColor3f(0,0.8,0);
       // glTexCoord2f(length/2,height/2);
        glVertex3f(length/2,height/2,0);

       // glTexCoord2f(-length/2,height/2);
        glVertex3f(-length/2,height/2,0);
    glEnd();

   // glDisable(GL_TEXTURE_2D);
   // glShadeModel(GL_SMOOTH);

}



void DrawWaterTile(float length, float height){
    glPushMatrix();

    float mat_ambient[] ={ 0.105882f, 0.058824f, 0.113725f, 1.0f };
    float mat_diffuse[] ={0.427451f, 0.470588f, 0.541176f, 1.0f };
    float mat_specular[] ={0.333333f, 0.333333f, 0.521569f, 1.0f };
    float shine = 9.84615f;

    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialf(GL_FRONT,GL_SHININESS,shine);

    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_specular);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);

    glRotatef(90,1,0,0);
    glBegin(GL_QUADS);
        //glTexCoord2f(-length/2,-height/2);
        glColor3f(0,0,0.5);
        glVertex3f(-length/2,-height/2,0);

        //glTexCoord2f(length/2,-height/2);
        glVertex3f(length/2,-height/2,0);
        glColor3f(0,0,0.8);
       // glTexCoord2f(length/2,height/2);
        glVertex3f(length/2,height/2,0);

       // glTexCoord2f(-length/2,height/2);
        glVertex3f(-length/2,height/2,0);
    glEnd();
    glPopMatrix();

}


void DrawPondSurface(){
        glTranslatef(pond_translate_x,0,pond_translate_y);
        glPushMatrix();

        for(float curve=0;curve<360;curve+=0.5){

            glRotatef(curve,0,1,0);
            Drawcurved_surface_atom();
        }
        glPopMatrix();

        //Inverse rotation
        for(float curve=0;curve<360;curve+=0.5){

            glRotatef(-curve,0,1,0);
        }
        glTranslatef(-pond_translate_x,0,-pond_translate_y);
}

void Drawcurved_surface_atom(){

    glPushMatrix();

                for(float angle=0;angle<=14;angle+=2){

                        glRotatef(-angle/2,0,0,1); // Gradient of the Slope

                        glTranslatef(-cos(3.14*(angle)/180)*0.1,0,0);

                        glPushMatrix();
                        glTranslatef(0.1/2,0,0); // Get around Y axis
                        glRotatef(90,1,0,0);//Get to Z axis

                        curved_surface_tile(0.1,0.1);
                        glPopMatrix();

                }
                glPopMatrix();

                glPushMatrix();
                glRotatef(180,0,1,0);
                glTranslatef(1.55,0,0);
                glPushMatrix();
                for(float angle=0;angle<=14;angle+=2){

                        glRotatef(-angle/2,0,0,1); // Gradient of the Slope

                        glTranslatef(-cos(3.14*(angle)/180)*0.1,0,0);

                        glPushMatrix();
                        glTranslatef(0.1/2,0,0); // Get around Y axis
                        glRotatef(90,1,0,0);//Get to Z axis

                        curved_surface_tile(0.1,0.1);
                        glPopMatrix();

                }
                glPopMatrix();
                glPopMatrix();

}



void colorInit(){
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_DEPTH_TEST);

    //Setting up lights
    GLfloat light_ambient[]={1,1,1,1.0};
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);

    GLfloat light_diffuse[]={1,1,1.0,1.0};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);

    GLfloat light_position[]={0.5,1.5,-2.0,0.0};
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);

    GLfloat light_specular[]={1,1.0,1,1.0};
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);


    GLfloat light1_ambient[]={1,1,1,1};
    GLfloat light1_diffuse[]={1,1,1,1};
    GLfloat light1_specular[]={1,1,1,1};
    GLfloat light1_position[]={1+transX,1+transY,3+transZ,0};

    GLfloat spot_direction[]={0,-3,-3};

    glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
    glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
    glLightfv(GL_LIGHT1,GL_POSITION,light1_position);

    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,spot_direction);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45);
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,1);

    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

}

void DrawFractalBushTree(){

    for(float i=0;i<=360;i+=10){
        glPushMatrix();
        glRotatef(i,0,1,0);
        glColor3f(0.1,i/400,0.1);
        DrawFractalTree();
        glPopMatrix();
    }

}

void DrawFractalBranch(float len){


    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,0.1,0);
    glEnd();



    glTranslatef(0,0.1,0);


    len *= 0.66;


    if(len>2){
        glPushMatrix();
        glRotatef(30,0,0,1);
        DrawFractalBranch(len);
        glPopMatrix();

        glPushMatrix();
            glRotatef(-30,0,0,1);
            DrawFractalBranch(len);
        glPopMatrix();
    }


}


void DrawFractalTree(){
    glPushMatrix();

        DrawFractalBranch(8);
        DrawFractalBranch(8);
        glTranslatef(0,-0.1,0);
    glPopMatrix();
}

void DrawFractalForest(){

    int amount_of_colums=8;

    for(int j=4;j<amount_of_colums;j++){

       for(float i=0;i<20;i++){
        glTranslatef(amount_of_colums,1,i);
        glRotatef(90,0,1,0);
        DrawFractalBushTree();
        glRotatef(-90,0,1,0);
        glTranslatef(-amount_of_colums,-1,-i);
        }

    }

    for(int j=4;j<amount_of_colums;j++){
       for(float i=0;i<20;i++){
        glTranslatef(-amount_of_colums,1,i+35.5);
        glRotatef(90,0,1,0);
        DrawFractalBushTree();
        glRotatef(-90,0,1,0);
        glTranslatef(amount_of_colums,-1,-i-35.5);
        }
    }

}


void timer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void initialize_animations(){
    //Time
    relative_clock++;
    //KITT Scanner motion //Simple Harmonic Motion equation
    scannerY_dark = 0.15*sin(1*relative_clock);
}



//Variables for Texture Ends

//New Functions for Texture START

void makeCheckImage(void)
{
    int i, j, c;
    for (i = 0; i < checkImageWidth; i++) {
    for (j = 0; j < checkImageHeight; j++) {
    c = ((((i&0x8)==0)^((j&0x8)==0)))*255;
    checkImage[i][j][0] = (GLubyte) c;
    checkImage[i][j][1] = (GLubyte) c;
    checkImage[i][j][2] = (GLubyte) c;
}
}
}
int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size; // size of the image in bytes.
    unsigned long i; // standard counter.
    unsigned short int plane; // number of planes in image

    unsigned short int bpp; // number of bits per pixel
    char temp; // temporary color storage for
// make sure the file is there.
if ((file = fopen(filename, "rb"))==NULL)
{
    printf("File Not Found : %s\n",filename);
    return 0;
}
// seek through the bmp header, up to the width/height:
fseek(file, 18, SEEK_CUR);
// read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
    printf("Error reading width from %s.\n", filename);
    return 0;
}
//printf("Width of %s: %lu\n", filename, image->sizeX);
// read the height
if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
    printf("Error reading height from %s.\n", filename);
    return 0;
}
//printf("Height of %s: %lu\n", filename, image->sizeY);
// calculate the size (assuming 24 bits or 3 bytes per pixel).
size = image->sizeX * image->sizeY * 3;
// read the planes
if ((fread(&plane, 2, 1, file)) != 1) {
    printf("Error reading planes from %s.\n", filename);
    return 0;
}
if (plane != 1) {
        printf("Planes from %s is not 1: %u\n", filename, plane);
    return 0;
}
// read the bitsperpixel
if ((i = fread(&bpp, 2, 1, file)) != 1) {
    printf("Error reading bpp from %s.\n", filename);

return 0;
}
if (bpp != 24) {
    printf("Bpp from %s is not 24: %u\n", filename, bpp);
    return 0;
}
// seek past the rest of the bitmap header.
fseek(file, 24, SEEK_CUR);
// read the data.
image->data = (char *) malloc(size);
if (image->data == NULL) {
    printf("Error allocating memory for color-corrected image data");
    return 0;
}
if ((i = fread(image->data, size, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename);
    return 0;
}
for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
    temp = image->data[i];
    image->data[i] = image->data[i+2];
    image->data[i+2] = temp;
}
// we're done.
return 1;
}
    Image * loadTexture()
{
Image *image1;
// allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
    printf("Error allocating space for image");
    exit(0);
}
//pic.bmp is a 64x64 picture
if (!ImageLoad("C:\\Users\\USER\\Desktop\\OpenGL Assignments\\Final Assignment\\KnightRider Race\\grass5.bmp", image1)) {
    exit(1);
}
return image1;
}

void myinit(void)
{
   // glClearColor (0.5, 0.5, 0.5, 0.0);
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

Image *image1 = loadTexture();
if(image1 == NULL)
{
    printf("Image was not returned from loadTexture\n");
    exit(0);
}
makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
// Create Texture
    glGenTextures(2, texture);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //
//scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //
//scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image1->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

   glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
    &checkImage[0][0][0]);
   glEnable(GL_TEXTURE_2D);
     glShadeModel(GL_FLAT);
}


//End Texture Functions

void display(void)
{

    dx = transX*0.15 - TreeX;
    dy = transY*0.15 - TreeY;
    dz = transZ*0.15 - TreeZ;

    gap = sqrtf(dx*dx + dy*dy + dz*dz);

    //Debug PrintF console
    /*printf("gap = %f\n",gap);
    printf("tranz = %f \t treez = %f \t dz = %f\n",transZ*0.15,TreeZ, dz);*/

    //Collision Detection
    if(gap <=KITTSafeReg+TreeSafeReg){
        printf("Danger. Collision Detected\n");
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     /* Use UP,DOWN,LEFT, RIGHT, Page UP and Page Down keys */

    //Camera Movement
    glLoadIdentity();
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    //Initialize Animations
    initialize_animations();


    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(80.0,1,0,15);

    //Select camera view
    if(camera_view ==0){
         // From the side
       gluLookAt(1+transX/6.65,1,1+transZ/6.65,transX/6.65,0,transZ/6.65,0,1,0);

    }
    else if(camera_view ==1){
         // Car from Back
            gluLookAt(0+transX/6.65,0.4,0.5+transZ/6.65,transX/6.65,0,transZ/6.65,0,1,0);
    }
    else if(camera_view ==2){
         // Near Tire View
        gluLookAt(0.2+transX/6.65,0.1,-0.1+transZ/6.67,transX/6.65,0,-1+transZ/6.65,0,1,0);
    }
    else if(camera_view ==3){
         // Near Tire View
        gluLookAt(0.2+transX/6.65,0.15,-0.7+transZ/6.67,transX/6.65,0,0+transZ/6.65,0,1,0);
    }
    else{
        //Full Map view
        gluLookAt(1+transX/6.65,100,1+transZ/6.65,transX/6.65,0,transZ/6.65,0,1,0);
    }

    //colorInit();

    //Draw Tire
    DrawFloor();
    //Draw Road Network
    DrawRoadSystem();
    //Draw Road junction
    float col1[] = {0,0,0};
    float col2[] ={0.1,0.1,0.1};

    glPushMatrix();
    glTranslatef(0,0,50);
    glRotatef(90,1,0,0);
    DrawQuad(1,1,col1,col2);
    glPopMatrix();

    //Fallen Tree for Collision detection
    glPushMatrix();
        glTranslatef(TreeX,TreeY,TreeZ);
        glRotatef(-90,0,0,1);
         glScalef(2,2,2);
        DrawPineTreeLayered(3,0);
    glPopMatrix();

    //ACTIVATE LATER FRACTAL TREES. Commented for Better Rendering
    /*for(float i=0;i<10;i++){
        glTranslatef(4,0.1,i+5.5);
        glRotatef(90,0,1,0);
        DrawFractalBushTree();
        glRotatef(-90,0,1,0);
        glTranslatef(-4,-0.1,-i-5.5);
    }*/

    //ACTIVATE LATER Commented for Better Rendering
    //DrawFractalForest(); //ACTIVATE LATER. Commented for Better Rendering
    //DrawPondSurface(); //ACTIVATE LATER. Commented for Better Rendering

    DrawPond(); //ACTIVATE LATER
    glPopMatrix();

    /*
    Always keep the scaling above since, this affects the coordinate consideration
    in collision detection. Translating of coordinates are affected in scaling.
    */
    glTranslatef(0,0,0);
    glScalef(0.15,0.15,0.15);
    glTranslatef(transX,turboHeight,transZ);
    DrawKITT();


    //Turbo Boost Logic
    if(angle>=1 && angle <=180){
        TurboBoost();
    }
    else if(angle >180){
        angle =0;
        turboHeight=0;
        printf("\nFinal Turbo Height = %f\n",turboHeight);
    }


    //DrawAxis();
    glutSwapBuffers();


}


void DrawPineTreeLayered(float tree_colour_variator,float indent){

    float treeHeight =0.08;
    glPushMatrix();
    glColor3f(0.1,0.2,0);
    glTranslatef(indent,0,0);
    glRotatef(-90,1,0,0);
    gluCylinder(qobj, 0.05, 0.05, 0.2,5, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(indent,treeHeight,0);
    glRotatef(-90,1,0,0);

        glPushMatrix();
            for(float i=10;i>=3;i--){
               glColor3f(0,i/(tree_colour_variator*10),0);
               glTranslatef(0,0,0.01);
              glutSolidCone((i+6)/100,0.4,20,20);
            }

        glPopMatrix();
    glPopMatrix();
}

void DrawRoadSystem(){
    glEnable(GL_SMOOTH);
    //Road A tile Properties
    float startColor[]={0,0,0};
    float endColor[]={0.1,0.1,0.1};
    float road_tile_size=1;
    float roadLength=(worldLength*2)*0.65; //Along X axis
    float roadTurn =0;

    //Draw Road A
    glTranslatef(0,0,-worldWidth*0.15);
    DrawMainRoad(road_tile_size,roadLength,roadTurn,startColor,endColor);
    glTranslatef(0,0,worldWidth*0.15);

    //Draw Road D
    glTranslatef(0,0,worldLength*0.71);
    DrawMainRoad(road_tile_size,worldLength*0.4,roadTurn,startColor,endColor);
    glTranslatef(0,0,-worldLength*0.71);

    ////Road B & C tile Properties, ONLY IF CHANGES ARE THERE
    roadLength=(worldLength*0.75);
    roadTurn =90;
    float moveRoadZ=50;
    float moveRoadX=roadLength/2;
    //Move Road B
    glTranslatef(-moveRoadX,0,moveRoadZ);
    DrawMainRoad(road_tile_size,roadLength,roadTurn,startColor,endColor);
    glTranslatef(moveRoadX,0,-moveRoadZ);
    //Translate

    //Move Road C
    glTranslatef(moveRoadX+road_tile_size,0,moveRoadZ);
    DrawMainRoad(road_tile_size,roadLength,roadTurn,startColor,endColor);
    glTranslatef(-moveRoadX-road_tile_size,0,-moveRoadZ);
    //Translate

}
void DrawMainRoad(float road_tile_size,float roadLength,float roadTurn,float startColor[],float endColor[]){

    //Draw Road
    //Road Matrix
    glPushMatrix();
    glRotatef(roadTurn,0,1,0);
    glTranslatef(0,0,-roadLength/2);
    for(int i=0;i<roadLength;i++){

        glPushMatrix();
            //Get the Road atom to Z axis
            glRotatef(90,1,0,0);

            //If condition to swap colours
            if(i%2==0){
                //Road Tile Atom
                DrawQuad(road_tile_size,road_tile_size,startColor,endColor);
                //Draw Road Lines
                DrawRoadLines(road_tile_size);
            }
            else{
                //Road Tile Atom
                DrawQuad(road_tile_size,road_tile_size,endColor,startColor);
                //Draw Road Lines
                DrawRoadLines(road_tile_size);
            }

        glPopMatrix();

        glScalef(1.5,1.5,1.5);
        DrawPineTreeLayered(1.5,road_tile_size*(5/4));
        DrawPineTreeLayered(1.5,-road_tile_size*(5/4));
        glScalef(1/1.5,1/1.5,1/1.5);

        glTranslatef(0,0,road_tile_size);
    }
    glPopMatrix();

}
//Void Road Lines
void DrawRoadLines(float road_tile_size){
        float lineColor[]={1,1,1};
        DrawQuad(road_tile_size/16,road_tile_size/4,lineColor,lineColor);
}


void DrawQuad(float length, float height, float startColor[], float endColor[]){
    glPushMatrix();
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
        glColor3f(startColor[0],startColor[1],startColor[2]);
        glVertex3f(-length/2,-height/2,0);
        glVertex3f(length/2,-height/2,0);

        glColor3f(endColor[0],endColor[1],endColor[2]);
        glVertex3f(length/2,height/2,0);
        glVertex3f(-length/2,height/2,0);
    glEnd();
    glPopMatrix();
}

//Draw Body 1
void DrawBody_1(){
    glPushMatrix();
    glTranslatef(-0.9,0.3+0.49,0);
    DrawCuboid(2.1,0.6,1.51);
    glPopMatrix();
}

//Draw Body 2
void DrawBody_2(){
    glPushMatrix();
    glTranslatef(-0.62-1.95,0.3+0.49,0);
    DrawCuboid(1.64,0.6,1.51);
    glPopMatrix();
}

//Draw Body 3
void DrawBody_3(){
    glPushMatrix();
    glTranslatef(0.35+0.15,0.18+0.49,0);
    DrawCuboid(0.7,0.36,1.51);
    glPopMatrix();
}

//Draw Body Top Middle
void DrawTopMiddle(){
    glPushMatrix();
    glTranslatef(-1.25-0.375,1.25,0);
    DrawCuboid(0.65,0.32,1.51);
    glPopMatrix();
}


//Draw Back Glass
void DrawBackGlass(){
    glPushMatrix();
        glTranslatef(-1.90,1.07,0.755);
        //Draw 2 Triangles
        glBegin(GL_TRIANGLES);
            glVertex3f(0,0,0);
            glVertex3f(0,0.32,0);
            glVertex3f(-1.3,0,0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0,0,-1.51);
            glVertex3f(0,0.32,-1.51);
            glVertex3f(-1.3,0,-1.51);
        glEnd();

        //Draw Slanted Glass
        glBegin(GL_QUADS);
            glColor3f(0,0,0);
            glVertex3f(0,0.32,0);
            glVertex3f(0,0.32,-1.51);
            glVertex3f(-1.30,0,-1.51);
            glVertex3f(-1.3,0,0);
        glEnd();
    glPopMatrix();
}

//Draw Front Glass
void DrawFrontGlass(){

    glPushMatrix();
        glTranslatef(-1.30,1.07,0.755);
        //Draw 2 Triangles
        glBegin(GL_TRIANGLES);
            glVertex3f(0,0,0);
            glVertex3f(0.9,0,0);
            glVertex3f(0,0.32,0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0,0,-1.51);
            glVertex3f(0.9,0,-1.51);
            glVertex3f(0,0.32,-1.51);
        glEnd();

        //Draw Slanted Glass
        glBegin(GL_QUADS);
            glColor3f(0,0,0);
            glVertex3f(0,0.32,0);
            glVertex3f(0.9,0,0);
            glVertex3f(0.9,0,-1.51);
            glVertex3f(0,0.32,-1.51);
        glEnd();
    glPopMatrix();

}

//Body 4 Engine like part
void DrawBody_4(){
    glPushMatrix();
        glTranslatef(0.15,0.85,0.755);

        //Draw 2 Triangles
        glBegin(GL_TRIANGLES);
            glVertex3f(0,0.24,0);
            glVertex3f(0,0,0);
            glVertex3f(0.8,0,0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glColor3f(0,0,0);
            glVertex3f(0,0.24,-1.51);
            glVertex3f(0,0,-1.51);
            glVertex3f(0.8,0,-1.51);
        glEnd();

        //Draw Slanted Glass
        glBegin(GL_QUADS);
            glColor3f(0,0,0);
            glVertex3f(0,0.24,0);
            glVertex3f(0.8,0,0);
            glVertex3f(0.8,0,-1.51);
            glVertex3f(0,0.24,-1.51);
        glEnd();
    glPopMatrix();
}

//Draw Back Wheels
void DrawBackWheels(float rotZ){

    float increase;
    float wheel_height=0.5;
    float wheel_posX=-2.5;

    //Left Wheel
    glPushMatrix();
        glTranslatef(wheel_posX,wheel_height,-0.785);
        for(increase=0;increase<=0.3;increase=increase+0.03){
        //Continously draw cylinders within
        glColor3f(0.5-increase,0.5-increase,0.5-increase);
        glRotatef(wheel_rotate_z,0,0,1);
        gluCylinder(qobj, increase, increase, 0.2,5, 16);
        }
    glPopMatrix();

    //Right Wheel
    glPushMatrix();
        glTranslatef(wheel_posX,wheel_height,0.755);
        for(increase=0;increase<=0.3;increase=increase+0.03){
        //Continously draw cylinders within
        glColor3f(0.5-increase,0.5-increase,0.5-increase);
        glRotatef(wheel_rotate_z,0,0,1);
        gluCylinder(qobj, increase, increase, 0.2,5, 16);
        }
    glPopMatrix();

}

//Draw Front Wheels
void DrawFrontWheels(float rotZ, float rotY){

    float increase;
    float wheel_height=0.5;
    float wheel_posX=0;
    //Left Wheel

    glPushMatrix();
        glTranslatef(wheel_posX,wheel_height,-0.755);
        for(increase=0;increase<=0.3;increase=increase+0.03){
        //Continously draw cylinders within
        glColor3f(0.5-increase,0.5-increase,0.5-increase);
        glRotatef(wheel_rotate_z,0,0,1);
        gluCylinder(qobj, increase, increase, 0.2,5, 16);
        }
    glPopMatrix();

    //Right Wheel
    glPushMatrix();
        glTranslatef(wheel_posX,wheel_height,0.755);
        for(increase=0;increase<=0.3;increase=increase+0.03){
        //Continously draw cylinders within
        glColor3f(0.5-increase,0.5-increase,0.5-increase);
        glRotatef(wheel_rotate_z,0,0,1);
        gluCylinder(qobj, increase, increase, 0.2, 5, 16);
        }
    glPopMatrix();

}

//Draw Front Bumper
void DrawFrontBumper(){

    glPushMatrix();
        glTranslatef(0.85,0.25,0.755);
        //Draw Top Triangles
        glBegin(GL_TRIANGLES);
            glVertex3f(0,0.60,0);
            glVertex3f(0,0.36,0);
            glVertex3f(0.1,0.60,0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0,0.60,-1.51);
            glVertex3f(0,0.36,-1.51);
            glVertex3f(0.1,0.60,-1.51);
        glEnd();

        //Top Slant
        glBegin(GL_QUADS);
            glColor3f(0.1,0.1,0.1);
            glVertex3f(0,0.36,0);
            glVertex3f(0,0.36,-1.51);
            glColor3f(0,0,0);
            glVertex3f(0.1,0.6,-1.51);
            glVertex3f(0.1,0.6,0);
        glEnd();

        //Draw Bottom Triangles
        glBegin(GL_TRIANGLES);
            glColor3f(0,0,0);
            glVertex3f(0,0.36,0);
            glVertex3f(0,0.25,0);
            glVertex3f(0.1,0.25,0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0,0.36,-1.51);
            glVertex3f(0,0.25,-1.51);
            glVertex3f(0.1,0.25,-1.51);
        glEnd();

        //Bottom Slant
        glBegin(GL_QUADS);
            glColor3f(0,0,0);
            glVertex3f(0,0.36,0);
            glVertex3f(0.1,0.25,0);
            glVertex3f(0.1,0.25,-1.51);
            glVertex3f(0,0.36,-1.51);
        glEnd();
        //Bottom SurfFace
        glBegin(GL_QUADS);
            glColor3f(0,0,0);
            glVertex3f(0,0.25,0);
            glVertex3f(0.1,0.25,0);
            glVertex3f(0.1,0.25,-1.51);
            glVertex3f(0,0.25,-1.51);
        glEnd();
    glPopMatrix();

}

void DrawKITTScanner(){
    glPushMatrix();
        glRotatef(90,0,1,0);
        glTranslatef(-0.025-scannerY_dark,0.7,0.2);

        glBegin(GL_QUADS);
            glColor3f(1,0,0);
            glVertex3f(0,0,0);
            glVertex3f(0.2,0,0);
            glVertex3f(0.2,0.1,0);
            glVertex3f(0,0.1,0);
        glEnd();
    glPopMatrix();
}

void DrawReverseLights(){

    //Colour swap for lights
    switch(KITT_Back_Lights){
        case 0:
        //All off
        break_lights_rgb[0]=0;
        break_lights_rgb[1]=0;
        break_lights_rgb[2]=0;

        reverse_left_lights_rgb[0]=0;
        reverse_left_lights_rgb[1]=0;
        reverse_left_lights_rgb[2]=0;

        reverse_right_lights_rgb[0]=0;
        reverse_right_lights_rgb[1]=0;
        reverse_right_lights_rgb[2]=0;
        break;

        case 1:
        //Breaks
        break;

        case 2:
        //Reverse
        break_lights_rgb[0]=1;
        break_lights_rgb[1]=0;
        break_lights_rgb[2]=0;

        reverse_left_lights_rgb[0]=1;
        reverse_left_lights_rgb[1]=1;
        reverse_left_lights_rgb[2]=1;

        reverse_right_lights_rgb[0]=1;
        reverse_right_lights_rgb[1]=1;
        reverse_right_lights_rgb[2]=1;
        break;

        case 3:
        //Left signal lights
        break_lights_rgb[0]=0;
        break_lights_rgb[1]=0;
        break_lights_rgb[2]=0;

        reverse_left_lights_rgb[0]=1;
        reverse_left_lights_rgb[1]=1;
        reverse_left_lights_rgb[2]=0;

        reverse_right_lights_rgb[0]=0;
        reverse_right_lights_rgb[1]=0;
        reverse_right_lights_rgb[2]=0;
        break;

        case 4:
        //Right signal lights

        break_lights_rgb[0]=0;
        break_lights_rgb[1]=0;
        break_lights_rgb[2]=0;

        reverse_left_lights_rgb[0]=0;
        reverse_left_lights_rgb[1]=0;
        reverse_left_lights_rgb[2]=0;

        reverse_right_lights_rgb[0]=1;
        reverse_right_lights_rgb[1]=1;
        reverse_right_lights_rgb[2]=0;
        break;

        default:
        break;
    }

    glPushMatrix();

    glRotatef(90,0,1,0);
    glTranslatef(0,0.9,-3.4);
    //Left Lights

        glPushMatrix();
        glTranslatef(0.68,0,0);
        //Break lights
        glBegin(GL_QUADS);

                glColor3f(break_lights_rgb[0],break_lights_rgb[1],break_lights_rgb[2]);
                glVertex3f(-0.20,0,0);
                glVertex3f(0.07,0,0);
                glVertex3f(0.07,0.18,0);
                glVertex3f(-0.20,0.18,0);
        glEnd();
        //Reverse Lights
        glBegin(GL_QUADS);
                glColor3f(reverse_left_lights_rgb[0],reverse_left_lights_rgb[1],reverse_left_lights_rgb[2]);
                glVertex3f(-0.2,0,0);
                glVertex3f(-0.4,0,0);
                glVertex3f(-0.4,0.18,0);
                glVertex3f(-0.2,0.18,0);
        glEnd();
        glPopMatrix();

    //Right Lights

        glPushMatrix();
        glTranslatef(-0.68,0,0);
        //Break lights
        glBegin(GL_QUADS);

                glColor3f(break_lights_rgb[0],break_lights_rgb[1],break_lights_rgb[2]);
                glVertex3f(0.20,0,0);
                glVertex3f(-0.07,0,0);
                glVertex3f(-0.07,0.18,0);
                glVertex3f(0.20,0.18,0);
        glEnd();
        //Reverse Lights
        glBegin(GL_QUADS);

                glColor3f(reverse_right_lights_rgb[0],reverse_right_lights_rgb[1],reverse_right_lights_rgb[2]);
                glVertex3f(0.2,0,0);
                glVertex3f(0.4,0,0);
                glVertex3f(0.4,0.18,0);
                glVertex3f(0.2,0.18,0);
        glEnd();
        glPopMatrix();
    glPopMatrix();
}

//Draw Car
void DrawKITT(){

    glRotatef(90,0,1,0);
    glRotatef(turn,0,1,0);
    glTranslatef(2,0,0);

    DrawBody_1();
    DrawBody_2();
    DrawBody_3();
    DrawTopMiddle();
    DrawBackGlass();
    DrawBackGlass();
    DrawFrontGlass();
    DrawBody_4();
    DrawFrontBumper();
    DrawBackWheels(0);
    DrawFrontWheels(0,0);
    DrawReverseLights();
    DrawKITTScanner();
}

void DrawFloor(){
    //With Texture
    myinit();
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(-worldLength, -worldWidth);
        //glColor3f(0,1,0);
        glVertex3f(-worldLength,0,-worldWidth);

        glTexCoord2f(worldLength, -worldWidth);
        glVertex3f(worldLength,0,-worldWidth);

        glTexCoord2f(worldLength, worldWidth);
        glVertex3f(worldLength,0,worldWidth);

        glTexCoord2f(-worldLength, worldWidth);
        glVertex3f(-worldLength,0,worldWidth);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);

    //Without Texture
    /*glBegin(GL_QUADS);

        glColor3f(0,0.5,0);
        glVertex3f(-worldLength,0,-worldWidth);

        glColor3f(0,0.1,0);
        glVertex3f(worldLength,0,-worldWidth);

        glColor3f(0,7,0);
        glVertex3f(worldLength,0,worldWidth);

        glColor3f(0,3,0);
        glVertex3f(-worldLength,0,worldWidth);
    glEnd();*/

}

//Draw Cuboid with given Parameters
void DrawCuboid(float length, float height, float width){

    //Draw Front Quad
    glPushMatrix();
        glTranslatef(0,0,width/2);
        DrawQuad(length,height);
    glPopMatrix();

    //Draw Back Quad
    glPushMatrix();
        glTranslatef(0,0,-width/2);
        DrawQuad(length,height);
    glPopMatrix();

    //Draw Top Quad
    glPushMatrix();
        glTranslatef(0,height/2,0);
        glRotatef(90,1,0,0);
        DrawQuad(length,width);
    glPopMatrix();

    //Draw Top Quad
    glPushMatrix();
        glTranslatef(0,-height/2,0);
        glRotatef(90,1,0,0);
        DrawQuad(length,width);
    glPopMatrix();

    //Draw Left Quad
    glPushMatrix();
        glTranslatef(-length/2,0,0);
        glRotatef(90,0,1,0);
        DrawQuad(width,height);
    glPopMatrix();

    //Draw RightQuad
    glPushMatrix();
        glTranslatef(length/2,0,0);
        glRotatef(90,0,1,0);
        DrawQuad(width,height);
    glPopMatrix();
}

//Draw Quad with given Parameters
void DrawQuad(float length, float height){

    /*
    I tried to add lighting and shading to the quad directly.
    But it is too much related to other places to add.
    Coupled too many.
    */

    /*glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);*/

    glPushMatrix();

    /*float mat_ambient[] ={ 0.02f, 0.02f, 0.02f, 1.0f };
    float mat_diffuse[] ={ 0.01f, 0.01f, 0.01f, 1.0f};
    float mat_specular[] ={0.4f, 0.4f, 0.4f, 1.0f };
    float shine = 10.0f;

    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialf(GL_FRONT,GL_SHININESS,shine);

    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_specular);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);*/


    glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex3f(-length/2,-height/2,0);
        glColor3f(0.1,0.1,0.1);
        glVertex3f(length/2,-height/2,0);
        glColor3f(0.1,0.1,0.1);
        glVertex3f(length/2,height/2,0);
        glColor3f(0.1,0.1,0.1);
        glVertex3f(-length/2,height/2,0);
    glEnd();
    glPopMatrix();

/*glDisable(GL_CULL_FACE);
glDisable(GL_DEPTH_TEST);*/
//glCullFace(GL_FRONT);
}


//DrawAxis
void DrawAxis(){
    float scaleX=10;
    float scaleY=10;
    float scaleZ = 10;
//XAxis

   glPushMatrix();
   glTranslatef(0,0,0);
    glScalef(scaleX,scaleY,scaleZ);
    glBegin(GL_LINES);
        glColor3f(1,0,1);
        glVertex3f(-1,0,0);
        glColor3f(1,1,1);
        glVertex3f(1,0,0);
    glEnd();
   glPopMatrix();

   //YAxis
   glPushMatrix();
   glTranslatef(0,0,0);
   glScalef(scaleX,scaleY,scaleZ);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glColor3f(0,0,1);
        glVertex3f(0,-1,0);
        glColor3f(1,1,1);
        glVertex3f(0,1,0);
    glEnd();
   glPopMatrix();


   //ZAxis
   glPushMatrix();
   glTranslatef(0,0,0);
   glScalef(scaleX,scaleY,scaleZ);
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,-1);
        glColor3f(1,1,0);
        glVertex3f(0,0,1);
    glEnd();
   glPopMatrix();



}

void keyboard(int key, int x,int y){
    float straight_distance_constant = 2.1;
    float turn_angle_per_turn = 3; // Degrees
    switch(key){

    case GLUT_KEY_UP:
        //Go straight.
        transZ = transZ - straight_distance_constant*cos((PI/180)*turn);
        transX = transX -   straight_distance_constant*sin((PI/180)*turn);

        //Wheel Rotate
        wheel_rotate_z = wheel_rotate_z + 10;

        //Switch off all back lights
        KITT_Back_Lights = 0;

        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:

        //Go Back
        transZ = transZ + straight_distance_constant*cos((PI/180)*turn);
        transX = transX +   straight_distance_constant*sin((PI/180)*turn);

        //Wheel Rotate
        wheel_rotate_z = wheel_rotate_z - 10;

        //Reverse lights on
        KITT_Back_Lights = 2;

        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT:
        turn = turn + turn_angle_per_turn;
        //transX = tan(turn)*2.1;

        //Left Signal lights
        KITT_Back_Lights = 3;

        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:
        turn = turn - turn_angle_per_turn;

        //Left Signal lights
        KITT_Back_Lights = 4;

        //transX = tan(turn)*2.1;
        glutPostRedisplay();
        break;

     case GLUT_KEY_PAGE_UP:
        if(camera_view==4){
            camera_view=0;
        }
        else{
            camera_view++;
        }
        glutPostRedisplay();
        break;

     case GLUT_KEY_PAGE_DOWN:
        angle = 1;
        break;

    }

}

/* Program entry point */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutTimerFunc(0, timer, 0);
    glutCreateWindow("Knight Rider by Adhisha Gammanpila");

    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);

    glutDisplayFunc(display);
    glMatrixMode(GL_MODELVIEW);
    glutSpecialFunc(keyboard);

    glutMainLoop();

    return EXIT_SUCCESS;
}
