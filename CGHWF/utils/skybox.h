#ifndef GLSKYBOX
#define GLSKYBOX
#include "base.h"
#include "texture.h"

/**
 * @brief ������պ�
 * @param tex ��պ�ʹ�õ��������ָ��
 * @param centerX ��պ����ĵ�� x ����
 * @param centerY ��պ����ĵ�� y ����
 * @param centerZ ��պ����ĵ�� z ����
 * @param width ��պеĿ��
 * @param height ��պеĸ߶�
 * @param length ��պеĳ���
 */

void drawSkyBox(Texture* tex, float centerX, float centerY, float centerZ, float width, float height, float length) {

    // ������

    tex->BindTexture(tex->m_tex);

    // ������պб߽����ʼ��

    float x = centerX - width / 2;
    float y = centerY - height / 2;
    float z = centerZ - length / 2;

    glPushMatrix();

    // ������պеĸ�����
    // ����

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();

    // ǰ��

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glEnd();

    // ����

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glEnd();

    // ����

    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + height, z);
    glEnd();

    // ����

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();

    // ����

    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
    glEnd();

    glPopMatrix();

    // ȡ�������

    tex->BindTexture(0);
}

#endif // GLSKYBOX
