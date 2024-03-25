#ifndef CAMERA_H
#define CAMERA_H

#include "base.h"
#include <cmath>
#include "vec3.h"

// Camera 类
// 描述：控制摄像机的视角，包括位置和方向
class Camera {
public:
    vec3 pos;          // 摄像机的世界空间坐标
    vec3 forward;      // 摄像机的前方向
    vec3 right;        // 摄像机的右方向
    vec3 up;           // 摄像机的上方向
    float pitch_speed; // 俯仰角变换速度
    float yaw_speed;   // 偏航角移动速度
    float pitch, yaw;  // 俯仰角和偏航角偏移角度

    // 默认构造函数
    Camera() {}

    // 构造函数
    // 参数 at：指定摄像机的初始位置
    Camera(vec3 at) {
        pos = at;  // 摄像机位置设置为参数 'at' 提供的三维坐标。
        pos.y += 1.0f; // 增加摄像机的y坐标来向上移动，'someValue' 是你想要上移的单位量

        pitch_speed = yaw_speed = 0.05f;  // 俯仰角和偏航角的变换速度。
        pitch = 30.0f;  // 俯仰角设置为 30 度
        yaw = 90.0f;  // 偏航角设置为 90 度，表示摄像机初始时向正z轴方向。

        forward = vec3(
            0.0f,                         // x分量
            -std::sin(radian(pitch)),     // y分量（向下为负）
            -std::cos(radian(pitch))      // z分量（向前为负）
        );

        right = vec3(1.0f, 0.0f, 0.0f);  // 摄像机的右方向保持不变。
        up = cross(right, forward);      // 使用右向量和前向量的叉积来重新计算上向量。
        up = normalize(up);              // 确保上向量是单位向量。
    }



    // update 函数
    // 功能：更新 MODELVIEW 矩阵，设置摄像机视角
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

    // radian 函数
    // 功能：将角度转换为弧度
    // 参数 angle：角度
    float radian(const float angle) {
        return angle * PI / 180.0f;
    }
};

#endif
