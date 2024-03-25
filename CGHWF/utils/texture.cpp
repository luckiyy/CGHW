#ifndef GLWARP_H
#define GLWARP_H

#include "base.h"
#include "GL/lodepng.h"
#include <vector>
#include <iostream>

class Texture {
public:
    GLuint textureID;  // 纹理对象的 OpenGL 标识符

    // 构造函数：加载 PNG 图像并创建纹理

    Texture(const char* filename, bool generateMipmaps);

    // 析构函数：销毁纹理资源

    ~Texture();

    // 绑定纹理到指定的纹理单元

    void BindTexture(GLuint textureUnitID);
};

// 构造函数实现

Texture::Texture(const char* filename, bool generateMipmaps) {
    // 打印加载的图片文件名
    std::cout << "Loading texture file: " << filename << std::endl;
    std::vector<unsigned char> image;
    unsigned int width, height;
    unsigned int error = lodepng::decode(image, width, height, filename);

    if (error != 0) {
        std::cout << "Error " << error << ": " << lodepng_error_text(error) << std::endl;
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // 设置纹理参数

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // 根据 generateMipmaps 决定是否生成 Mipmap

    if (generateMipmaps) {
        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    }
    else {
        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    }
}

// 析构函数实现

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

// 绑定纹理实现

void Texture::BindTexture(GLuint textureUnitID) {
    glBindTexture(GL_TEXTURE_2D, textureUnitID);
}

#endif // GLWARP_H
