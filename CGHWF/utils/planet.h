#ifndef PLANET_H
#define PLANET_H

#include "vec3.h"
#include "texture.h"

// Planet ��
// ������ģ��̫��ϵ�����ǵ��������Ժ��Ӿ�����
class Planet {
public:
    float revolution;       // ���ǹ�ת��ǰ�Ƕ�
    float addRevolution;    // ���ǹ�ת�������Ƕȣ�����ת�ٶ�
    float rotation;         // ������ת��ǰ�Ƕ�
    float addRotation;      // ������ת�������Ƕȣ�����ת�ٶ�
    float radius;           // ���ǰ뾶
    float slope;            // ������ת����б�Ƕ�

    vec3 pos;               // ����������䡰���ס���λ������

    Texture* texture;       // ��������

    // ��������

    float ambient[4];       // ����������
    float diffuse[4];       // ����������
    float specular[4];      // ���淴������
    float emission[4];      // �Է�������
    float shininess;        // ���ʹ����

    // ���캯��
    // ������
    //   texname - �����ļ�·��
    //   revolution - ��ת�ٶ�
    //   rotation - ��ת�ٶ�
    //   slope - ת����б�Ƕ�
    //   radius - ���ǰ뾶
    //   pos - ����λ��
    Planet(const char* texname, float revolution, float rotation, float slope, float radius, vec3 pos) {
        texture = new Texture(texname, true);  // �����������
        this->slope = slope;                   // ����ת����б�Ƕ�
        this->revolution = 0.0f;               // ��ʼ��ת�Ƕ�
        this->addRevolution = revolution;      // ���ù�ת�ٶ�
        this->rotation = 0.0f;                 // ��ʼ��ת�Ƕ�
        this->addRotation = rotation;          // ������ת�ٶ�
        this->radius = radius;                 // �������ǰ뾶
        this->pos = pos;                       // ��������λ��
    }

    // ��������
    // ���ܣ�����������Դ
    ~Planet() {
        if (texture) {
            delete texture;                      // ɾ���������
            texture = NULL;                      // ��ָ���ÿ�
        }
    }
};

#endif // PLANET_H
