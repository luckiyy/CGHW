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

    void keyPressEvent(QKeyEvent* e);           // 处理键盘输入
    void drawPlanet(Planet* planet);            // 绘制绕太阳旋转的行星
    void drawPlanet2(Planet* p);               // 绘制带有光环的行星
    void drawSphere(double radius, int slices, int stack, bool texture); // 绘制球体
    void drawDisk(GLdouble innerRadius, GLdouble outerRadius, GLint slices); // 绘制圆盘
    void SetLight(bool lighting);               // 设置光照效果
    void SetMaterial(Planet* p);                // 设置物体的材料属性
    void SetMaterialDefault();                  // 恢复默认场景设置
    void initVboVao();                          // 初始化 VBO 和 VAO
    void createStoneArr();                      // 初始化行星带的粒子属性

private:
    QTimer *timer;
    Camera camera;          // 场景摄像机
    bool lighting;          // 是否设置光照
    Texture *boxtex;        // 球行天空盒纹理贴图

    GLuint vboId[2];        
    GLuint vaoId;

    // 星球
    Planet* sun;         // 太阳
    Planet* mercury;     // 水星
    Planet* venus;       // 金星
    Planet* earth;       // 地球
    Planet* mars;        // 火星
    Planet* jupiter;     // 木星
    Planet* saturn;      // 土星
    Planet* uranus;      // 天王星
    Planet* neptune;     // 海王星
    Planet* particle;    // 流行粒子

    GLUquadricObj *quadObj = NULL;      // 二次曲面对象
    
};
#endif // MYGLWIDGET_H
