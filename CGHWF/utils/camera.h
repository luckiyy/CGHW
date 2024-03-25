#ifndef CAMERA_H
#define CAMERA_H

#include "base.h"
#include <cmath>
#include "vec3.h"

// Camera ��
// ������������������ӽǣ�����λ�úͷ���
class Camera {
public:
    vec3 pos;          // �����������ռ�����
    vec3 forward;      // �������ǰ����
    vec3 right;        // ��������ҷ���
    vec3 up;           // ��������Ϸ���
    float pitch_speed; // �����Ǳ任�ٶ�
    float yaw_speed;   // ƫ�����ƶ��ٶ�
    float pitch, yaw;  // �����Ǻ�ƫ����ƫ�ƽǶ�

    // Ĭ�Ϲ��캯��
    Camera() {}

    // ���캯��
    // ���� at��ָ��������ĳ�ʼλ��
    Camera(vec3 at) {
        pos = at;  // �����λ������Ϊ���� 'at' �ṩ����ά���ꡣ
        pos.y += 1.0f; // �����������y�����������ƶ���'someValue' ������Ҫ���Ƶĵ�λ��

        pitch_speed = yaw_speed = 0.05f;  // �����Ǻ�ƫ���ǵı任�ٶȡ�
        pitch = 30.0f;  // ����������Ϊ 30 ��
        yaw = 90.0f;  // ƫ��������Ϊ 90 �ȣ���ʾ�������ʼʱ����z�᷽��

        forward = vec3(
            0.0f,                         // x����
            -std::sin(radian(pitch)),     // y����������Ϊ����
            -std::cos(radian(pitch))      // z��������ǰΪ����
        );

        right = vec3(1.0f, 0.0f, 0.0f);  // ��������ҷ��򱣳ֲ��䡣
        up = cross(right, forward);      // ʹ����������ǰ�����Ĳ�������¼�����������
        up = normalize(up);              // ȷ���������ǵ�λ������
    }



    // update ����
    // ���ܣ����� MODELVIEW ��������������ӽ�
    void update() {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        vec3 target = pos + forward;
        gluLookAt(
            pos.x, pos.y, pos.z,
            target.x, target.y, target.z,
            up.x, up.y, up.z
        );
    }

    // radian ����
    // ���ܣ����Ƕ�ת��Ϊ����
    // ���� angle���Ƕ�
    float radian(const float angle) {
        return angle * PI / 180.0f;
    }
};

#endif
