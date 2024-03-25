# 计图大作业报告

## 主题：太阳系行星运行

### 实现的内容

1. 画球体
2. 搜索对应行星的纹理图片，完成贴图
3. 绘制行星类
4. 绘制行星运行轨迹
5. 添加键盘交互功能
6. 设置光照
7. 绘制行星带

### 项目细节

#### 1. vec3类

+ 因为该项目是在3D空间中实现的，所以构造了`vec3`类，在`vec3.h`文件中主要实现了：

  **定义了3D向量结构 `vec3`：**

  - `vec3` 结构表示三维向量，包含 `x`、`y` 和 `z` 分量。
  - 提供了不同的构造函数，用于初始化向量。

  **实现了向量运算和比较的运算符重载：**

  - `+`: 向量加法。
  - `-`: 向量减法，以及取负。
  - `*`: 向量与标量的乘法。
  - `/`: 向量与标量的除法。
  - `==` 和 `!=`: 向量的相等和不相等比较。
  - `+=`, `-=`, `*=`, `/=`: 向量的复合运算符。

  **实现了向量操作的成员函数：**

  - `length()`: 计算向量的长度。
  - `normalize()`: 将向量归一化。
  - `normalize(const vec3& v)`: 返回参数向量的归一化版本。
  - `cross(const vec3 &v1, const vec3 &v2)`: 计算两个向量的叉乘。

  **提供了数组和指针的访问方式：**

  - 使用 `union` 允许以数组形式 (`v[3]`) 或结构体形式 (`x`, `y`, `z`) 访问向量分量。

  **定义了向量的点乘积运算：**

  - `operator*`: 实现了向量的点乘积。

#### 2.画球体

+ 参考网上搜索了OpenGL绘制球体的教程：

  ![image-20240113115734897](picture\image-20240113115734897.png)

#### 3.贴图功能的实现

+ 首先先按预想的需求搜索合适的贴图并统一为png格式，收集到的结果如下：

  ![image-20240113120013300](picture\image-20240113120013300.png)

+ 收集完成后我们使用`loadpng`来实现图片读入

  > LodePNG是一个集合了PNG图像解码器和编码器的代码文件，不依赖于诸如zlib和libpng的外部链接/库，提供方便友好的PNG编解码器调用方法。LodePNG主要是采用C（ISO C90）编写的，并提供了C++的接口。LodePNG的使用非常简单，只要在项目文件中包含lodepng.cpp和lodepng.h或者lodepng.c和lodepng.h就可以。	

+ 先在`texture.h`文件中构造名为 `Texture` 的简单纹理类提供了创建、销毁和绑定纹理的基本功能。在构造函数中，通过加载文件数据并生成纹理对象，可以方便地创建纹理。析构函数用于释放相关的OpenGL资源，避免内存泄漏。成员函数 `BindTexture` 使用户可以将纹理绑定到指定的纹理单元。

+ 然后在`texturn.cpp`中实现完成对函数的定义：

  **成员变量:**`GLuint textureID`: 存储OpenGL中纹理对象的标识符。

  **构造函数 `Texture(const char\* filename, bool generateMipmaps)`:**

  - 通过构造函数加载PNG图像文件并创建纹理。
  - 使用 lodepng 库解码PNG图像文件，将图像数据存储在 `image` 向量中。
  - 启用2D纹理映射 (`glEnable(GL_TEXTURE_2D)`)。
  - 生成纹理对象 (`glGenTextures`) 并绑定到当前纹理单元 (`glBindTexture(GL_TEXTURE_2D, textureID)`)。
  - 设置纹理参数，如重复方式 (`GL_REPEAT`)、环境模式 (`GL_MODULATE`)、放大和缩小过滤方式 (`GL_LINEAR`)。
  - 根据 `generateMipmaps` 参数决定是否生成 Mipmap。

  **析构函数 `~Texture()`:**析构函数用于释放纹理资源。调用 `glDeleteTextures` 删除纹理对象。

  **成员函数 `BindTexture(GLuint textureUnitID)`:**将纹理绑定到指定的纹理单元。调用 `glBindTexture` 将当前纹理对象绑定到指定的纹理单元 (`GL_TEXTURE_2D, textureUnitID)`。

  **打印信息:**在构造函数中打印加载的图像文件名和可能的错误信息。

#### 4.绘制行星

+ 绘制行星就要构建一个星球类，根据需求这个类里面应该包括以下信息：

  ~~~
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
  ~~~

+ 行星相关信息我们均从晚上收集，实际情况可能与我们的初始化有一定区别。

#### 5.绘制行星运行

+ 绘制行星后需要绘制行星运行轨迹，我们利用`rawDisk`函数

  ~~~
  // 绘制二次曲面圆盘
  //      innerRadius: 内圆半径
  //      outerRadius: 外圆半径
  //      slices: 圆盘的细分数
  
  void MyGLWidget::drawDisk(GLdouble innerRadius, GLdouble outerRadius, GLint slices) {
      gluDisk(quadObj, innerRadius, outerRadius, slices, 1);   // 绘制圆盘
  }
  ~~~

+ **绘制行星轨迹:**使用 `glPushMatrix` 和 `glPopMatrix` 保护当前矩阵状态。平移矩阵使得绘制的行星轨迹位于Y轴上。以Z轴为旋转轴，绘制一个盘状的行星轨迹，使用 `drawDisk` 函数，起点和终点分别为 `planet->pos.x` 和 `planet->pos.x+0.01f`。

+ **绘制星球:**使用 `glPushMatrix` 和 `glPopMatrix` 保护当前矩阵状态。`glRotatef` 旋转矩阵，根据 `planet->revolution` 进行绕Y轴的公转。平移矩阵，将行星定位到指定位置 (`planet->pos.x, planet->pos.y, planet->pos.z`)。使用 `glRotatef` 进行倾斜，绕Z轴旋转，角度由 `planet->slope` 决定。使用 `glRotatef` 进行自转，绕X轴旋转，角度由 `planet->rotation` 决定。使用 `planet->texture->BindTexture(planet->texture->m_tex)` 将纹理绑定到行星。使用 `drawSphere` 函数绘制行星，参数包括半径 `planet->radius` 和细分数。

+ **恢复状态和增加角度:**使用 `glPopMatrix` 恢复矩阵状态。增加 `planet->revolution` 和 `planet->rotation`，以模拟行星的公转和自转。

+ 其中土星需要额外绘制一个在星球周围的光圈，但是他的原理是和星球运行轨迹的实现原理是一样的
  ![image-20240113144640891](picture\image-20240113144640891.png)

#### 6.天空盒

+ 在`skybox.h`实现了在OpenGL场景中绘制一个具有纹理的天空盒。通过将六个面绘制在场景的特定位置，可以创建出一个环绕整个场景的背景，增强视觉效果。

  ~~~
  void drawSkyBox(Texture* tex, float centerX, float centerY, float centerZ, float width, float height, float length)
  ~~~

  

#### 7.设置键盘交互功能

+ 在该部分我们主要实现了两个交互功能：

  **摄像机移动:**

  - 按下 "W" 键，摄像机沿着视角方向的正向移动。
  - 按下 "S" 键，摄像机沿着视角方向的负向移动。
  - 按下 "A" 键，摄像机向左移动。
  - 按下 "D" 键，摄像机向右移动。

  **光照控制:**

  - 如果按下 "O" 键，切换 `lighting` 变量的值，用于控制光照的开启和关闭。

+ 在实现方法上我们是通过构建了一个`Camera`类，用于控制摄像机的视角，包括位置和方向。初始时，摄像机的 `pitch` 设置为30度，`yaw` 设置为90度，表示摄像机初始时向正Z轴方向。通过俯仰角 `pitch` 和偏航角 `yaw` 计算摄像机的前向量 `forward`。计算摄像机的右向量 `right`。通过右向量和前向量的叉积重新计算上向量 `up`。

  

#### 8. 光照设置

+ 这一部分套用了网上搜索到的例子，初始化的值也是尝试后的结果

  

#### 9.绘制陨石带

首先将在网上找的石头形状的obj文件保存下来，在代码中通过设置颜色为灰色（RGB: 0.345, 0.345, 0.345），然后在一个循环中绘制每个石头。每次都经历了以下步骤：

1. **保存和还原模型视图矩阵状态:**
   - 使用 `glPushMatrix` 保存当前的模型视图矩阵状态，以确保后续的操作不会影响其他对象的绘制。
   - 使用 `glPopMatrix` 在每次迭代结束时还原模型视图矩阵状态。
2. **太阳的公转效果:**
   - 使用 `glRotatef` 对太阳进行公转，以实现太阳的自转效果。
3. **平移和缩放:**
   - 使用 `glTranslatef` 将石头放置到对应的位置，实现公转半径的平移操作。
   - 使用 `glScalef` 调整石头的大小，实现石头的缩放操作。
4. **启用和绘制VAO:**
   - 启用法线和顶点数组的客户端状态。
   - 使用 `glBindVertexArray` 绑定 VAO。
   - 使用 `glDrawArrays` 绘制石头的几何图形。
5. **禁用VAO和客户端状态:**
   - 使用 `glBindVertexArray(0)` 解绑 VAO。
   - 使用 `glDisableClientState` 禁用顶点数组和法线数组的客户端状态。
6. **循环结束后禁用2D纹理:**
   - 使用 `glDisable(GL_TEXTURE_2D)` 禁用2D纹理。

这样，通过循环迭代，绘制了具有不同位置、大小和公转效果的多个石头，整个过程使用了 Vertex Array Object（VAO）来提高渲染效率。

### 运行结果

![image-20240113150650061](picture\image-20240113150650061.png)

![image-20240113150704831](picture\image-20240113150704831.png)

+ **打开光源**

![image-20240113150734190](picture\image-20240113150734190.png)

![image-20240113150819552](picture\image-20240113150819552.png)
