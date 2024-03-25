#ifndef PLANET_H
#define PLANET_H

#include "vec3.h"
#include "texture.h"

// Planet 类
// 描述：模拟太阳系中行星的物理特性和视觉特性
class Planet {
public:
    float revolution;       // 行星公转当前角度
    float addRevolution;    // 行星公转的日增角度，即公转速度
    float rotation;         // 行星自转当前角度
    float addRotation;      // 行星自转的日增角度，即自转速度
    float radius;           // 行星半径
    float slope;            // 行星自转轴倾斜角度

    vec3 pos;               // 行星相对于其“父亲”的位置向量

    Texture* texture;       // 行星纹理

    // 材质属性

    float ambient[4];       // 环境光属性
    float diffuse[4];       // 漫反射属性
    float specular[4];      // 镜面反射属性
    float emission[4];      // 自发光属性
    float shininess;        // 材质光泽度

    // 构造函数
    // 参数：
    //   texname - 纹理文件路径
    //   revolution - 公转速度
    //   rotation - 自转速度
    //   slope - 转轴倾斜角度
    //   radius - 行星半径
    //   pos - 行星位置
    Planet(const char* texname, float revolution, float rotation, float slope, float radius, vec3 pos) {
        texture = new Texture(texname, true);  // 创建纹理对象
        this->slope = slope;                   // 设置转轴倾斜角度
        this->revolution = 0.0f;               // 初始公转角度
        this->addRevolution = revolution;      // 设置公转速度
        this->rotation = 0.0f;                 // 初始自转角度
        this->addRotation = rotation;          // 设置自转速度
        this->radius = radius;                 // 设置行星半径
        this->pos = pos;                       // 设置行星位置
    }

    // 析构函数
    // 功能：清理纹理资源
    ~Planet() {
        if (texture) {
            delete texture;                      // 删除纹理对象
            texture = NULL;                      // 将指针置空
        }
    }
};

#endif // PLANET_H
