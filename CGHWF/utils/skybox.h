#ifndef GLSKYBOX
#define GLSKYBOX
#include "base.h"
#include "texture.h"

/**
 * @brief 绘制天空盒
 * @param tex 天空盒使用的纹理对象指针
 * @param centerX 天空盒中心点的 x 坐标
 * @param centerY 天空盒中心点的 y 坐标
 * @param centerZ 天空盒中心点的 z 坐标
 * @param width 天空盒的宽度
 * @param height 天空盒的高度
 * @param length 天空盒的长度
 */

void drawSkyBox(Texture* tex, float centerX, float centerY, float centerZ, float width, float height, float length) {

    // 绑定纹理

    tex->BindTexture(tex->m_tex);

    // 计算天空盒边界的起始点

    float x = centerX - width / 2;
    float y = centerY - height / 2;
    float z = centerZ - length / 2;

    glPushMatrix();

    // 绘制天空盒的各个面
    // 后面

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();

    // 前面

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glEnd();

    // 底面

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glEnd();

    // 顶面

    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + height, z);
    glEnd();

    // 左面

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();

    // 右面

    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
    glEnd();

    glPopMatrix();

    // 取消纹理绑定

    tex->BindTexture(0);
}

#endif // GLSKYBOX
