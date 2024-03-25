#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#ifdef MAC_OS
#include <QtOpenGL/QtOpenGL>
#else
#include <GL/glew.h>
#endif
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "utils/planet.h"
#include "utils/camera.h"
#include "utils/vec3.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    MyGLWidget(QWidget* parent = nullptr);
    ~MyGLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void keyPressEvent(QKeyEvent* e);           // �����������
    void drawPlanet(Planet* planet);            // ������̫����ת������
    void drawPlanet2(Planet* p);               // ���ƴ��й⻷������
    void drawSphere(double radius, int slices, int stack, bool texture); // ��������
    void drawDisk(GLdouble innerRadius, GLdouble outerRadius, GLint slices); // ����Բ��
    void SetLight(bool lighting);               // ���ù���Ч��
    void SetMaterial(Planet* p);                // ��������Ĳ�������
    void SetMaterialDefault();                  // �ָ�Ĭ�ϳ�������
    void initVboVao();                          // ��ʼ�� VBO �� VAO
    void createStoneArr();                      // ��ʼ�����Ǵ�����������

private:
    QTimer *timer;
    Camera camera;          // ���������
    bool lighting;          // �Ƿ����ù���
    Texture *boxtex;        // ������պ�������ͼ

    GLuint vboId[2];        
    GLuint vaoId;

    // ����
    Planet* sun;         // ̫��
    Planet* mercury;     // ˮ��
    Planet* venus;       // ����
    Planet* earth;       // ����
    Planet* mars;        // ����
    Planet* jupiter;     // ľ��
    Planet* saturn;      // ����
    Planet* uranus;      // ������
    Planet* neptune;     // ������
    Planet* particle;    // ��������

    GLUquadricObj *quadObj = NULL;      // �����������
    
};
#endif // MYGLWIDGET_H
