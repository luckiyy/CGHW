#include "myglwidget.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <utils/skybox.h>
#include <utils/objLoader.h>
#include <QtCore/qdir.h>
#include <qopenglextrafunctions.h>

#define N 1000              // ���Ǵ�������
#define M 100               // ���������
using namespace std;
ObjLoader stone;	        // ʵ���� ObjLoader
float vertices[2592*3*6];   // һ�����ӵĶ�������, �洢����:һ������λ��(x,y,z)��һ��������(nx,ny,nz)
float stoneArr[N][3];       // ���Ǵ����ӵ�����,�洢���ݣ�����λ��(stoneArr[i][0] = x,stoneArr[i][1] = y,0)�����Ӱ뾶���� stoneArr[i][2] = s 
float randomParticle[M][6]; // ����������ԣ��洢����: ����λ��(randomParticle[i][0] = x,randomParticle[i][1] = y,0)�����Ӱ뾶���� randomParticle[i][2] = s,������б�� randomParticle[i][3] = slope,������ת�Ƕ� randomParticle[i][4]��������ת�����Ƕ� randomParticle[i][5]


//����������Ǵ��������Ժ������������

void MyGLWidget::createStoneArr(){
    // ���Ǵ���������
    for(int i = 0; i < N;i++){
        float r = 2.0 *(double)rand() / (double)RAND_MAX - 1.0;         // ��ΧΪ [-1,1] �������
        r += 5.2f;
        float x = r * cos(i);           // Բ����
        float y = r * sin(i);
        float s = rand()%10+1;
        stoneArr[i][0] = x;
        stoneArr[i][1] = y;
        stoneArr[i][2] = s;
    }

    // �����������
    for(int i = 0; i < M; i++){
        float r = rand()%20 + 1;
        float x = r*cos(i);
        float y = r*sin(i);
        float s = rand()%10+1;
        float slope = rand()%180;
        float addRevolution = rand()%5+1;
        randomParticle[i][0] = x;
        randomParticle[i][1] = y;
        randomParticle[i][2] = s;
        randomParticle[i][3] = slope;
        randomParticle[i][4] = 0.0f;
        randomParticle[i][5] = addRevolution;
    }

}


//MyGLWidget��Ĺ��캯����ʵ������ʱ��timer

MyGLWidget::MyGLWidget(QWidget *parent)
	:QOpenGLWidget(parent)
{
	timer = new QTimer(this); // ʵ����һ����ʱ��
	timer->start(16); // ʱ��������Ϊ16ms�����Ը�����Ҫ����
	connect(timer, SIGNAL(timeout()), this, SLOT(update())); // ����update()������ÿ16ms����һ��update()�����������»�ͼ
    quadObj = gluNewQuadric();//����һ��������������
    camera = Camera(vec3(0.0f, 0.0f, 3.0f));
    lighting = false;
    stone = ObjLoader("./obj/stone.obj",vertices);
}


//����������ɾ��timer

MyGLWidget::~MyGLWidget()
{
	delete this->timer;
    delete sun;         // ̫��
    delete mercury;     // ˮ��
    delete venus;       // ����
    delete earth;       // ����
    delete mars;        // ����
    delete jupiter;     // ľ��
    delete saturn;      // ����
    delete uranus;      // ������
    delete neptune;     // ������
    gluDeleteQuadric(quadObj);
}


//��ʼ����ͼ���������Ӵ���С������ɫ�ȣ�����������ͼ����ʼ��vbo vao���������Ǵ��������Ժ������������

void MyGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Your Implementation

    glViewport(0, 0, width(), height());
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glShadeModel(GL_SMOOTH);                //����ƽ����ɫ

    // ������պ�����
    boxtex = new Texture("./picture/background.png", true);
    // ������������
	sun     = new Planet("./picture/sun.png",  0.0f,   0.1f,   0.0f,   1.0f,       vec3(0.0f, 0.0f, 0.0f));	// ��תÿ�����ӵĽǶȣ���תÿ�����ӵĽǶȣ���б�ǣ��뾶���빫ת����ľ���λ��
    mercury = new Planet("./picture/mercury.png",  2.09f,  0.614f,  0.034f, 0.07f,    vec3(1.3f, -0.1f, 0.0f));
	venus   = new Planet("./picture/venus.png",  1.20f,  0.233f,  177.3f, 0.142f,    vec3(1.885f, -0.4f, 0.0f));
	earth   = new Planet("./picture/earth.png",  0.5f,   3.0f,   23.4f,  0.15f,     vec3(2.6f, 0.0f, 0.0f));
	mars    = new Planet("./picture/mars.png",  1.524f, 20.1f, 25.2f,  0.123f,    vec3(3.952f, 0.0f, 0.0f));
	jupiter = new Planet("./picture/jupiter.png",  0.389f, 24.0f, 3.1f,   0.2227f,    vec3(6.52f, 0.0f, 0.0f));
	saturn  = new Planet("./picture/saturn.png",  0.334f, 27.4f, 26.7f,  0.266f,    vec3(9.804f, 1.0f, 0.0f));
	uranus  = new Planet("./picture/uranus.png",0.311f, 10.8f, 97.8f,  0.23f,    vec3(11.97f, 0.0f, 0.0f));
	neptune = new Planet("./picture/neptune.png",0.186f, 15.0f, 28.3f,  0.22f,    vec3(16.0f, 0.8f, 0.0f));

    // ��������Ĳ���
	sun->ambient[0] = 1.0f,sun->ambient[1] = 1.0f,sun->ambient[2] = 1.0f,sun->ambient[3] = 1.0f;            // ���������еĻ�����
    sun->diffuse[0] = 1.0f,sun->diffuse[1] = 1.0f,sun->diffuse[2] = 1.0f,sun->diffuse[3] = 1.0f;            // ���������е�ɢ���
    sun->specular[0] = 1.0f,sun->specular[1] = 1.0f,sun->specular[2] = 1.0f,sun->specular[3] = 1.0f;        // ���������еľ��淴���
    sun->emission[0] = 1.0f,sun->emission[1] = 1.0f,sun->emission[2] = 1.0f,sun->emission[3] = 1.0f;        // �������Եľ��淴��ָ��
    sun->shininess = 1.0f;

 	mercury->ambient[0] = 0.2f,mercury->ambient[1] = 0.2f,mercury->ambient[2] = 0.2f,mercury->ambient[3] = 1.0f;
    mercury->diffuse[0] = 0.8f,mercury->diffuse[1] = 0.8f,mercury->diffuse[2] = 0.8f,mercury->diffuse[3] = 1.0f;
    mercury->specular[0] = 0.0f,mercury->specular[1] = 0.0f,mercury->specular[2] = 0.0f,mercury->specular[3] = 1.0f;
    mercury->emission[0] = 0.0f,mercury->emission[1] = 0.0f,mercury->emission[2] = 1.0f,mercury->emission[3] = 1.0f;
    mercury->shininess = 0.0f;

 	venus->ambient[0] = 0.1f,venus->ambient[1] = 0.1f,venus->ambient[2] = 0.3f,venus->ambient[3] = 1.0f;
    venus->diffuse[0] = 0.0f,venus->diffuse[1] = 0.0f,venus->diffuse[2] = 0.0f,venus->diffuse[3] = 1.0f;
    venus->specular[0] = 0.0f,venus->specular[1] = 0.0f,venus->specular[2] = 1.0f,venus->specular[3] = 1.0f;
    venus->emission[0] = 0.5f,venus->emission[1] = 0.0f,venus->emission[2] = 0.0f,venus->emission[3] = 1.0f;
    venus->shininess = 30.0f;
       
	earth->ambient[0] = 0.0f,earth->ambient[1] = 0.0f,earth->ambient[2] = 0.0f,earth->ambient[3] = 1.0f;
    earth->diffuse[0] = 0.0f,earth->diffuse[1] = 0.0f,earth->diffuse[2] = 0.0f,earth->diffuse[3] = 1.0f;
    earth->specular[0] = 0.0f,earth->specular[1] = 0.0f,earth->specular[2] = 1.0f,earth->specular[3] = 1.0f;
    earth->emission[0] = 0.5f,earth->emission[1] = 0.0f,earth->emission[2] = 0.0f,earth->emission[3] = 1.0f;
    earth->shininess = 10.0f;


	mars->ambient[0] = 0.0f,mars->ambient[1] = 0.0f,mars->ambient[2] = 0.0f,mars->ambient[3] = 1.0f;
    mars->diffuse[0] = 0.0f,mars->diffuse[1] = 0.0f,mars->diffuse[2] = 0.0f,mars->diffuse[3] = 1.0f;
    mars->specular[0] = 0.0f,mars->specular[1] = 0.0f,mars->specular[2] = 1.0f,mars->specular[3] = 1.0f;
    mars->emission[0] = 0.5f,mars->emission[1] = 0.0f,mars->emission[2] = 0.0f,mars->emission[3] = 1.0f;
    mars->shininess = 10.0f;

	jupiter->ambient[0] = 0.0f,jupiter->ambient[1] = 0.0f,jupiter->ambient[2] = 0.0f,jupiter->ambient[3] = 1.0f;
    jupiter->diffuse[0] = 0.0f,jupiter->diffuse[1] = 0.0f,jupiter->diffuse[2] = 0.0f,jupiter->diffuse[3] = 1.0f;
    jupiter->specular[0] = 0.0f,jupiter->specular[1] = 0.0f,jupiter->specular[2] = 1.0f,jupiter->specular[3] = 1.0f;
    jupiter->emission[0] = 0.5f,jupiter->emission[1] = 0.0f,jupiter->emission[2] = 0.0f,jupiter->emission[3] = 1.0f;
    jupiter->shininess = 10.0f;

	saturn->ambient[0] = 0.0f,saturn->ambient[1] = 0.0f,saturn->ambient[2] = 0.0f,saturn->ambient[3] = 1.0f;
    saturn->diffuse[0] = 0.0f,saturn->diffuse[1] = 0.0f,saturn->diffuse[2] = 0.0f,saturn->diffuse[3] = 1.0f;
    saturn->specular[0] = 0.0f,saturn->specular[1] = 0.0f,saturn->specular[2] = 1.0f,saturn->specular[3] = 1.0f;
    saturn->emission[0] = 0.5f,saturn->emission[1] = 0.0f,saturn->emission[2] = 0.0f,saturn->emission[3] = 1.0f;
    saturn->shininess = 10.0f;

	uranus->ambient[0] = 0.0f,uranus->ambient[1] = 0.0f,uranus->ambient[2] = 0.0f,uranus->ambient[3] = 1.0f;
    uranus->diffuse[0] = 0.0f,uranus->diffuse[1] = 0.0f,uranus->diffuse[2] = 0.0f,uranus->diffuse[3] = 1.0f;
    uranus->specular[0] = 0.0f,uranus->specular[1] = 0.0f,uranus->specular[2] = 1.0f,uranus->specular[3] = 1.0f;
    uranus->emission[0] = 0.5f,uranus->emission[1] = 0.0f,uranus->emission[2] = 0.0f,uranus->emission[3] = 1.0f;
    uranus->shininess = 10.0f;

	neptune->ambient[0] = 0.0f,neptune->ambient[1] = 0.0f,neptune->ambient[2] = 0.0f,neptune->ambient[3] = 1.0f;
    neptune->diffuse[0] = 0.0f,neptune->diffuse[1] = 0.0f,neptune->diffuse[2] = 0.0f,neptune->diffuse[3] = 1.0f;
    neptune->specular[0] = 0.0f,neptune->specular[1] = 0.0f,neptune->specular[2] = 1.0f,neptune->specular[3] = 1.0f;
    neptune->emission[0] = 0.5f,neptune->emission[1] = 0.0f,neptune->emission[2] = 0.0f,neptune->emission[3] = 1.0f;
    neptune->shininess = 10.0f;


    // ��ʼ��vbo vao
    initVboVao();
    
    // ����������Ǵ�
    createStoneArr();
}


//��ʼ�����㻺�����VBO���Ͷ����������VAO��

void MyGLWidget::initVboVao() {
    // �������� VAO
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    // �������� VBO
    glGenBuffers(2, vboId);

    // ����λ������
    glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableClientState(GL_VERTEX_ARRAY);

    // ���㷨������
    glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableClientState(GL_NORMAL_ARRAY);

    // ��� VAO
    glBindVertexArray(0);
}

//���ù�Դ

void MyGLWidget::SetLight(bool lighting) {
    GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };     // ������
    GLfloat diffuseLight[] = { 0.6f, 0.6f, 0.9f, 1.0f };     // �������
    GLfloat specularLight[] = { 0.7f, 0.7f, 0.8f, 1.0f };    // ���淴���
    GLfloat lightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };    // ��Դλ��

    // ���ù�Դ����
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    if (lighting) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
    }
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_COLOR_MATERIAL);
    }

    glShadeModel(GL_SMOOTH);
}

//��������Ĳ�������

//p: ָ����������ָ��

void MyGLWidget::SetMaterial(Planet* p) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, p->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, p->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, p->specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, p->emission);
    glMaterialf(GL_FRONT, GL_SHININESS, p->shininess);
}



//���ó�������Ĭ��ֵ

void MyGLWidget::SetMaterialDefault(){
    float ambient[]   = {0.1f, 0.1f, 0.1f, 1.0f};
    float diffuse[]   = {0.3f, 0.3f, 0.3f, 1.0f};
    float specular[]  = {0.3f, 0.3f, 0.3f, 1.0f};
    float emission[]  = {0.3f, 0.3f, 0.3f, 1.0f};
    float shininess   = 0.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);        // ���������еĻ�����
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);        // ���������е�ɢ���
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);      // ���������еľ��淴���
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);      // ���������еķ����
    glMaterialf (GL_FRONT, GL_SHININESS,shininess);     // �������Եľ��淴��ָ��
}

//���ƶ�����������
//      radius: ����뾶
//      slices: ���徭��ϸ����
//      stack: ����γ��ϸ����
//      texture: �Ƿ�Ӧ������

void MyGLWidget::drawSphere(double radius, int slices, int stack, bool texture) {
    gluQuadricOrientation(quadObj, GLU_OUTSIDE);    // ��������ķ��߷�����
    gluQuadricTexture(quadObj, texture);            // ���û����������������
    gluSphere(quadObj, radius, slices, stack);      // ��������
}


// ���ƶ�������Բ��
//      innerRadius: ��Բ�뾶
//      outerRadius: ��Բ�뾶
//      slices: Բ�̵�ϸ����

void MyGLWidget::drawDisk(GLdouble innerRadius, GLdouble outerRadius, GLint slices) {
    gluDisk(quadObj, innerRadius, outerRadius, slices, 1);   // ����Բ��
}



//���ƻ���̫��ת������

void MyGLWidget::drawPlanet(Planet* planet){

    // SetMaterial(planet);                 // ���������������
    // �������ǹ켣
	glPushMatrix();
    glTranslatef(0.0f,planet->pos.y,0.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
	drawDisk(planet->pos.x, planet->pos.x+0.01f, 100);
    glPopMatrix();

    // ��������
    glPushMatrix();
	glRotatef(planet->revolution, 0.0f, 1.0f, 0.0f);	            // ��ת
	glTranslatef(planet->pos.x, planet->pos.y, planet->pos.z);      // ��ת�뾶or����λ��
	glRotatef(planet->slope, 0.0f, 0.0f, 1.0f);                     // �� z ����б����������б��
    glRotatef(planet->rotation, 0.0f, 1.0f, 0.0f);		            // �� x ����ת
    planet->texture->BindTexture(planet->texture->m_tex);           // ������
	drawSphere(planet->radius, 20, 20, true);                       // ��������
    
    planet->texture->BindTexture(0);                                // ȡ��������
	glPopMatrix();    

    planet->revolution += planet->addRevolution;                    // ��ת�Ƕ�����
    planet->rotation += planet->addRotation;                        // ��ת�Ƕ�����
}



//���ƴ���Ȧ������:����

void MyGLWidget::drawPlanet2(Planet * p)
{
    // SetMaterial(p);                                 // �����������

    // ��������켣
    glPushMatrix();
    glTranslatef(0.0f,p->pos.y,0.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
	drawDisk(p->pos.x, p->pos.x+0.01f, 100);
    glPopMatrix();

    // ��������
	glPushMatrix();
	p->texture->BindTexture(p->texture->m_tex);         // ������
    glRotatef(p->revolution, 0.0f, 1.0f, 0.0f);         // ��ת
	glTranslatef(p->pos.x, p->pos.y, p->pos.z);         // ��ת�뾶or����λ��
    glRotatef(p->slope, 0.0f, 0.0f, 1.0f);              // �� z ����б
    // ��Ȧ��Ե�ǰ����任��push��ǰ���󣬻�������    
        glPushMatrix();
	    glRotatef(p->rotation, 0.0f, 1.0f, 0.0f);       // �� x ����ת
	    drawSphere(p->radius, 20, 20, true);
        glPopMatrix();

    // ���ƹ�Ȧ
	glPushMatrix();  
    glRotatef(90, 1.0f, 0.0f, 0.0f);
	drawDisk(0.5,0.7, 50);

    // SetMaterialDefault();                            // �ָ�����Ĭ�ϲ���
    p->texture->BindTexture(0);                         // ȡ��������
	glPopMatrix();
	glPopMatrix();

    p->revolution += p->addRevolution;                  // ��ת�Ƕ�����
    p->rotation += p->addRotation;                      // ��ת�Ƕ�����
}


//��ͼ������ʵ��ͼ�λ���

void MyGLWidget::paintGL()
{
	// Your Implementation
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);	// ����ס�Ŀ�����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, width() / height(), 0.1f, 60000.0f);		// ���������

    camera.update();                            // ���������
	// glLoadIdentity();

	glEnable(GL_TEXTURE_2D);


    // ������պ�
    glPushMatrix();
    boxtex->BindTexture(boxtex->m_tex);	
    glRotatef(sun->rotation,1.0f,1.0f,1.0f);        // ��պ���ת
    gluSphere(quadObj,100.0f,20,20);
    boxtex->BindTexture(0);
    glPopMatrix();

    // ���ó�������
    SetLight(lighting);     

    // ����̫������
    SetMaterial(sun);
    drawPlanet(sun);
    SetMaterialDefault();

    // ����̫��ϵ
    drawPlanet(mercury);
    drawPlanet(venus);
    drawPlanet(earth);
    drawPlanet(mars);
    drawPlanet(jupiter);
    drawPlanet2(saturn);
    drawPlanet(uranus);
    drawPlanet(neptune);

    
    
    // �������Ǵ�
    glColor3f(0.345f,0.345f,0.345f);
    for(int i = 0; i < N;i++){
        glPushMatrix();
        glRotatef(sun->rotation, 0.0f, 1.0f, 0.0f);                 // ��ת
        glTranslatef(stoneArr[i][0],0.0f,stoneArr[i][1]);           // ��ת�뾶
        glScalef(0.00005f * stoneArr[i][2],0.00005f * stoneArr[i][2],0.00005f * stoneArr[i][2]);      // ʯͷ��С
        // vao ����
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, 2592 * 3);
        glBindVertexArray(0);
        glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
        glDisableClientState(GL_NORMAL_ARRAY);
        glPopMatrix();
    }

	glDisable(GL_TEXTURE_2D);

}


//  resizeGL �����ڴ�С�ı�ʱ�����Ӵ��ߴ�
void MyGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	update();
}

// MyGLWidget ���е� keyPressEvent ����
void MyGLWidget::keyPressEvent(QKeyEvent* e)
{
    float cameraSpeed = 0.2f; // ������ƶ��ٶ�

    // ���̿���
    if (e->key() == Qt::Key_W) {
        camera.pos += camera.forward * cameraSpeed;
    }
    if (e->key() == Qt::Key_S) {
        camera.pos -= camera.forward * cameraSpeed;
    }
    if (e->key() == Qt::Key_A) {
        camera.pos -= camera.right * cameraSpeed;
    }
    if (e->key() == Qt::Key_D) {
        camera.pos += camera.right * cameraSpeed;
    }

    if (e->key() == Qt::Key_O) {
        lighting = !lighting;
    }
    update();
}

