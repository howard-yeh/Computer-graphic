#include "glm.h"
#include <GL/glut.h>
#include <stdio.h>
#include <mmsystem.h>
#include "CMP3_MCI.h"
CMP3_MCI myMP3;
FILE * fout=NULL; ///檔案一開始是空的 NULL
FILE * fin=NULL; ///in檔案一開始是空的NULL
GLMmodel * modelbody = NULL;
GLMmodel * modelhand1 = NULL;
GLMmodel * modelhand2 = NULL;
GLMmodel * modelleg1 = NULL;
GLMmodel * modelleg2 = NULL;
float angle[20]={0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0};
float oldAngle[20]={0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0};
float newAngle[20]={0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0};
int oldX=0, now=0;
float alpha=0;

void mouse(int button, int state, int x,int y)
{
    oldX=x;
}

void timer(int t)
{
    printf("%d\n",t);
    glutTimerFunc(33, timer,t+1);

    if(t%29==0)
    {
        if(fin==NULL)fin=fopen("output.txt","r");
        for(int i=0;i<20;i++)
        {
            oldAngle[i] = newAngle[i];
            fscanf(fin,"%f", &newAngle[i]);
        }
    }
    float alpha = (t%29)/29.0;
    for(int i=0;i<20;i++)
    {
        angle[i] = newAngle[i]*alpha +  oldAngle[i]*(1-alpha);
    }
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{   ///讀入動畫資料
    if(key=='0') now=0;
    if(key=='1') now=1;///按1就會改變1號關節
    if(key=='2') now=2;///按2就會改變3號關節
    if(key=='3') now=3;
    if(key=='4') now=4;
    if(key=='5') now=5;
    if(key=='6') now=6;
    if(key=='7') now=7;
    if(key=='8') now=8;
    if(key=='9') now=9;
    if(key=='/') now=10;
    if(key=='*') now=11;
    if(key=='-') now=12;
    if(key=='w' || key=='W' || key=='s' || key=='S'){///按's'才會寫關節的角度,一次20個
        if(fout==NULL) fout = fopen("output.txt", "w+");///第一節教的開檔

        for(int i=0;i<20;i++) {
        printf("%.3f\n",angle[i]);
        fprintf(fout, "%.3f\n", angle[i]);///把角度印到檔案裡
        }
    }
    if(key=='r' || key=='R'){
       if(fin==NULL){ ///一開始空指標
            fin=fopen("output.txt", "r"); /// r 表示讀入read
        }
        for(int i=0;i<20;i++) {
            fscanf(fin, "%f", &angle[i]);///Now4:用陣列從檔案fin讀進來
            printf("%.3f\n",angle[i]);
        }
        glutPostRedisplay(); ///讀入資料馬上重畫
    }
     if(key=='p'){
        glutTimerFunc(0, timer,0);
        if(fin==NULL)fin = fopen("output.txt", "r");
        for(int i=0;i<20;i++){
        fscanf(fin, "%f", &newAngle[i]);
        }
    }
}


void motion(int x, int y) ///用Mouse motion來改關節angle
{
    angle[now]+= x-oldX; ///angle稍微增減
    oldX=x;  ///把舊換新
    glutPostRedisplay(); ///重畫畫面
}

static void resize(int width, int height)
{
        const float ar = (float) width / (float) height; ///aspect ratio 長寬比

        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,1,3,  0,0,0, 0,1,0);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        if (!modelbody) {
        modelbody = glmReadOBJ("body.obj");
        if (!modelbody) exit(0);
        glmUnitize(modelbody);
        glmFacetNormals(modelbody);
        glmVertexNormals(modelbody, 90.0);
        }
    glPopMatrix();

    glPushMatrix();
        if (!modelhand1) {
        modelhand1 = glmReadOBJ("hand1.obj");
        if (!modelhand1) exit(0);
        glmUnitize(modelhand1);
        glmFacetNormals(modelhand1);
        glmVertexNormals(modelhand1, 90.0);
        }
    glPopMatrix();

    glPushMatrix();
        if (!modelhand2) {
        modelhand2 = glmReadOBJ("hand2.obj");
        if (!modelhand2) exit(0);
        glmUnitize(modelhand2);
        glmFacetNormals(modelhand2);
        glmVertexNormals(modelhand2, 90.0);
        }
    glPopMatrix();

    glPushMatrix();
        if (!modelleg1) {
        modelleg1 = glmReadOBJ("leg1.obj");
        if (!modelleg1) exit(0);
        glmUnitize(modelleg1);
        glmFacetNormals(modelleg1);
        glmVertexNormals(modelleg1, 90.0);
        }
    glPopMatrix();

    glPushMatrix();
        if (!modelleg2) {
        modelleg2 = glmReadOBJ("leg2.obj");
        if (!modelleg2) exit(0);
        glmUnitize(modelleg2);
        glmFacetNormals(modelleg2);
        glmVertexNormals(modelleg2, 90.0);
        }
    glPopMatrix();

    ///Begin:---------------------------------------------------------------------------

    glPushMatrix();
        glTranslatef(0,0,0);
        glRotatef(angle[0],0,1,0);
        glmDraw(modelbody, GLM_SMOOTH | GLM_MATERIAL); ///body


        glPushMatrix();
            glTranslatef(0.2,0.1,0);
            glRotatef(angle[1],1,0,0);

            glTranslatef(0.2,-0.2,0);
            glmDraw(modelhand1, GLM_SMOOTH | GLM_MATERIAL); ///hand1

            glPushMatrix();
                glTranslatef(0,-0.2,0);
                glRotatef(angle[2],1,0,0);
                glRotatef(angle[3],0,0,1);
                glTranslatef(0,-0.2,0);
                glmDraw(modelhand2, GLM_SMOOTH | GLM_MATERIAL);///hand2
            glPopMatrix();
        glPopMatrix();

        ///leg
        glPushMatrix();
            glTranslatef(0.1,-0.35,0);
            glRotatef(angle[7],1,0,0);
            glTranslatef(0.1,-0.35,0);
            //glPushMatrix();
                glmDraw(modelleg1, GLM_SMOOTH | GLM_MATERIAL);///leg1
           // glPopMatrix();
            glPushMatrix();
                glTranslatef(0,-0.2,0.03);
                glRotatef(angle[8],1,0,0);
                glRotatef(angle[9],0,0,1);
                glTranslatef(0,-0.13,0.03);
                glmDraw(modelleg2, GLM_SMOOTH | GLM_MATERIAL);///leg2
            glPopMatrix();
         glPopMatrix();

        ///hand left

         glPushMatrix();
                glTranslatef(-0.2,0.1,0);
                glRotatef(angle[4],1,0,0);
                glTranslatef(-0.2,-0.2,0);
               // glPushMatrix();
                    glmDraw(modelhand1, GLM_SMOOTH | GLM_MATERIAL);///hand1
              //  glPopMatrix();
                glPushMatrix();
                    glTranslatef(0,-0.2,0);
                    glRotatef(angle[5],1,0,0);
                    glRotatef(angle[6],0,0,1);
                    glTranslatef(0,-0.2,0);
                    glmDraw(modelhand2, GLM_SMOOTH | GLM_MATERIAL);///hand2
                glPopMatrix();
        glPopMatrix();

        ///leg left

        glPushMatrix();
            glTranslatef(-0.1,-0.35,0);
            glRotatef(angle[10],1,0,0);
            glTranslatef(-0.1,-0.35,0);
           // glPushMatrix();
                glmDraw(modelleg1, GLM_SMOOTH | GLM_MATERIAL);///leg1
          //  glPopMatrix();
            glPushMatrix();
                glTranslatef(0,-0.2,0.03);
                glRotatef(angle[11],1,0,0);
                glRotatef(angle[12],0,0,1);
                glTranslatef(0,-0.13,0.03);
                glmDraw(modelleg2, GLM_SMOOTH | GLM_MATERIAL);///leg2
            glPopMatrix();
         glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 2.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


int main(int argc, char *argv[])
{
    myMP3.Load("dance.mp3");
    myMP3.Play();

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);

    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glClearColor(1,1,1,1);
   /// glEnable(GL_CULL_FACE);
   /// glCullFace(GL_BACK);

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
