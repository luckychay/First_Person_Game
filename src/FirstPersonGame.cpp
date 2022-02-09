// 摄像机漫游.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SkyBox.h"
#include "Camera.h"
#include <stdlib.h>     
#include<time.h>  
#include"Particles.h"    

#include<gl/glew.h>
#include<gl/glut.h>
#include<gl/glu.h>
#include<gl/gl.h>
#include <gl/glaux.h>

#include "CBMPLoader.h"

GLfloat rotate=0.0;//旋转角度
GLfloat r=5.0;//旋转速率

/** 定义光源的属性值 */
GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };    /**< 环境光参数 */
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };    /**< 漫射光参数 */
GLfloat LightSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   /**< 镜面光参数 */
GLfloat LightPosition0[] = { 100.0f, 28.0f, 90.0f, 0.0f };   /**< 光源位置 */
GLfloat LightPosition1[] = { 120.0f, 120.0f, 120.0f, 0.0f };   /**< 光源位置 */

Camera m_Camera;
CBMPLoader m_Texture1;//木箱纹理
CBMPLoader m_Texture2;//绿布箱纹理
CBMPLoader m_Texture3;//集装箱纹理
CBMPLoader m_Texture4;//地面纹理
CBMPLoader m_Texture5;//墙纹理
CBMPLoader m_Texture7;//粒子纹理
CBMPLoader m_Texture6;//镂空台纹理

/**照片箱纹理*/
CBMPLoader m_Texture8;
CBMPLoader m_Texture9;
CBMPLoader m_Texture10;
CBMPLoader m_Texture11;

CSkyBox m_SkyBox;//天空盒

emitter *e1;

particle* init_particle()//初始化粒子系统
{
	static int count = 0;
	float size = rand() % 50 * 0.02f;
	particle* p;
		p = new particle(size, size, float(rand() % 10-4) / 50, float(rand() % 100) / 200+0.5,
			0, -4.9 / 1000, rand() % 60, 0, m_Texture7.ID,false);
 
	return p;
}

void drawScene()
{
	e1->update();
}

void idle()//刷新粒子系统
{
	glutPostRedisplay();
}

/** 加载位图纹理(木箱贴图) */
bool LoadTexture1()
{
    if (!m_Texture1.LoadBitmap("woodbox.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture1.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture1.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture1.imageWidth,
        m_Texture1.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture1.image);

    return true;
}

/** 加载位图纹理(绿皮箱贴图) */
bool LoadTexture2()
{
    if (!m_Texture2.LoadBitmap("绿皮箱.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture2.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture2.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture2.imageWidth,
        m_Texture2.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture2.image);

    return true;
}

/** 加载位图纹理(集装箱贴图) */
bool LoadTexture3()
{
    if (!m_Texture3.LoadBitmap("集装箱.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture3.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture3.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture3.imageWidth,
        m_Texture3.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture3.image);

    return true;
}

/** 加载位图纹理(地面贴图) */
bool LoadTexture4()
{
    if (!m_Texture4.LoadBitmap("ground.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture4.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture4.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture4.imageWidth,
        m_Texture4.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture4.image);

    return true;
}

/** 加载位图纹理(墙贴图) */
bool LoadTexture5()
{
    if (!m_Texture5.LoadBitmap("wall.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture5.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture5.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture5.imageWidth,
        m_Texture5.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture5.image);

    return true;
}

/** 加载位图纹理(粒子贴图) */
bool LoadTexture7()
{
    if (!m_Texture7.LoadBitmap("p.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture7.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture7.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture7.imageWidth,
        m_Texture7.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture7.image);

    return true;
}

/** 加载位图纹理(镂空台贴图) */
bool LoadTexture6()
{
    if (!m_Texture6.LoadBitmap("镂空台.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture6.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture6.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture6.imageWidth,
        m_Texture6.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture6.image);

    return true;
}

/** 加载位图纹理(照片箱贴图) */
bool LoadTexture8()
{
    if (!m_Texture8.LoadBitmap("1.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture8.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture8.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture8.imageWidth,
        m_Texture8.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture8.image);

    return true;
}
bool LoadTexture9()
{
    if (!m_Texture9.LoadBitmap("2.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture9.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture9.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture9.imageWidth,
        m_Texture9.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture9.image);

    return true;
}
bool LoadTexture10()
{
    if (!m_Texture10.LoadBitmap("95.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture10.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture10.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture10.imageWidth,
        m_Texture10.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture10.image);

    return true;
}
bool LoadTexture11()
{
    if (!m_Texture11.LoadBitmap("556.bmp"))                                         /**< 载入位图文件 */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< 如果载入失败则弹出对话框 */
        return false;
    }

    glGenTextures(1, &m_Texture11.ID);                                                /**< 生成一个纹理对象名称 */
    glBindTexture(GL_TEXTURE_2D, m_Texture11.ID);                                     /**< 创建纹理对象 */

    /** 控制滤波 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** 创建纹理 */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture11.imageWidth,
        m_Texture11.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture11.image);

    return true;
}

void DrawPlane(void)//画飞机
{
	GLUquadric *gluQ = gluNewQuadric();

	glPushMatrix();
	gluCylinder(gluQ, 0.1, 0.1, 1.0, 20, 20);
	glTranslatef(0.0, 0.0, 1.0);
	gluCylinder(gluQ, 0.1, 0.0, 0.3, 20, 20);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.6);
	glScalef(2.0, 0.1, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	glScalef(1.0, 0.1, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();

	gluDeleteQuadric(gluQ);
}
/** 绘制球体 */

/** 绘制 */
void DrawBox1()//大木箱
{
    /** 设置材质属性 */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    glScalef(2.0f, 2.0f, 2.0f);
    /** 选择纹理 */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture1.ID);
    /** 开始绘制四边形 */
    glBegin(GL_QUADS);
    /// 前侧面
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< 指定法线指向观察者 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// 后侧面
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// 顶面
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// 底面
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< 指定法线朝下 */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// 右侧面
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// 左侧面
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawBox2()//小木箱
{
    /** 设置材质属性 */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


   // glScalef(0.5f, 0.5f, 0.5f);
    /** 选择纹理 */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture1.ID);
    /** 开始绘制四边形 */
    glBegin(GL_QUADS);
    /// 前侧面
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< 指定法线指向观察者 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// 后侧面
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// 顶面
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// 底面
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< 指定法线朝下 */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// 右侧面
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// 左侧面
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
    
}

void DrawBox3()//绿皮箱
{
    /** 设置材质属性 */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    glScalef(6.0f, 3.0f, 3.0f);
    /** 选择纹理 */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture2.ID);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    /** 开始绘制四边形 */
    glBegin(GL_QUADS);
    /// 前侧面
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< 指定法线指向观察者 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// 后侧面
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// 顶面
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// 底面
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< 指定法线朝下 */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// 右侧面
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// 左侧面
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawBox4()//集装箱
{
    /** 设置材质属性 */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    glScalef(6.0f, 3.0f, 3.0f);
    /** 选择纹理 */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture3.ID);
    /** 开始绘制四边形 */
    glBegin(GL_QUADS);
    /// 前侧面
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< 指定法线指向观察者 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// 后侧面
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// 顶面
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// 底面
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< 指定法线朝下 */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// 右侧面
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// 左侧面
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawBox5()//镂空台
{
    /** 设置材质属性 */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    glScalef(6.0f, 3.0f, 3.0f);
    /** 选择纹理 */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture6.ID);
    /** 开始绘制四边形 */
    glBegin(GL_QUADS);
    /// 前侧面
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< 指定法线指向观察者 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// 后侧面
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// 顶面
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// 底面
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< 指定法线朝下 */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// 右侧面
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// 左侧面
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawWall()//墙
{
    /** 设置材质属性 */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    glScalef(6.0f, 3.0f, 3.0f);
    /** 选择纹理 */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture5.ID);
    /** 开始绘制四边形 */
    glBegin(GL_QUADS);
    /// 前侧面
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< 指定法线指向观察者 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// 后侧面
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// 顶面
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// 底面
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< 指定法线朝下 */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// 右侧面
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// 左侧面
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawGround()//地面
{
    glScalef(6.0f, 3.0f, 3.0f);
    /** 选择纹理 */
    glBindTexture(GL_TEXTURE_2D, m_Texture4.ID);
    /** 开始绘制四边形 */
    glBegin(GL_QUADS);
    /// 前侧面
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< 指定法线指向观察者 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// 后侧面
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// 顶面
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
    glTexCoord2f(0.0f, 100.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(100.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(100.0f, 100.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// 底面
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< 指定法线朝下 */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// 右侧面
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// 左侧面
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawPhotoBox()
{
	glRotatef(rotate,0.0,1.0,0.0);

	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture8.ID);
    /** 开始绘制四边形 */
    glBegin(GL_QUADS);
    /// 前侧面
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< 指定法线指向观察者 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Texture9.ID);
	glBegin(GL_QUADS);
    /// 后侧面
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
    /// 顶面
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// 底面
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< 指定法线朝下 */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture10.ID);
	glBegin(GL_QUADS);
    /// 右侧面
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Texture11.ID);
	glBegin(GL_QUADS);
    /// 左侧面
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();

	rotate+=r;
}

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_PROJECTION);					  //创建透视效果
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
	glEnable ( GL_COLOR_MATERIAL );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glEnable(GL_BLEND);

    /** 设置光源的属性值 */
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);     /**< 设置环境光 */
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);     /**< 设置漫射光 */
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);   /**< 设置反射光 */
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     /**< 设置环境光 */
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     /**< 设置漫射光 */
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);   /**< 设置反射光 */

    /** 启用光源和纹理 */
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glDisable(GL_LIGHT1);
    glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE); //设置纹理受光照影响
	


	/** 初始化天空 */
    if (!m_SkyBox.Init())
    {
        MessageBox(NULL, (LPCWSTR)"3", (LPCWSTR)"4", MB_OK);
        exit(0);
    }

	//    ** 载入纹理 */
    /*glBindTexture(GL_TEXTURE_2D, m_Texture5.ID);*/
    if (!LoadTexture1()||!LoadTexture2()||!LoadTexture3()||!LoadTexture4()||!LoadTexture5()||!LoadTexture6()||!LoadTexture7()||!LoadTexture8()||!LoadTexture9()||!LoadTexture10()||!LoadTexture11())
        MessageBox(NULL, (LPCWSTR)"5", (LPCWSTR)"6", MB_OK);

    /** 设置摄像机 */
    m_Camera.setCamera(100.0f, 3.0f, 130.0f, 120.0f, -1.5f, 120.0f, 0.0f, 1.0f, 0.0f);

	e1 = new emitter(5000, 0,0, -30, -30);
	e1->emit(init_particle);
}

void display(void)
{
    /** 用户自定义的绘制过程 */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /** 放置摄像机 */
    m_Camera.setLook();
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);   /**< 设置光源位置 */
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);   /**< 设置光源位置 */


    /**绘制过程 */

	 /** 绘制天空 */
	m_SkyBox.CreateSkyBox(0.0, 0.0, 0.0, 0.25, 0.05, 0.25);
	
	
	glPushMatrix();
	glColor3f(0.8f,0.8f,0.8f);
	glRotatef(30,0.0,1.0,0.0);
	glTranslatef(80.0f, 30.0f, 90.0f);
	glScalef(10.0,10.0,10.0);
	DrawPlane();
	glColor3f(1.0f,1.0f,1.0f);
	glPopMatrix();

    //DrawGrid();
   // DrawSphere();

   //**中间**//

	glPushMatrix();//中间大箱子
    glTranslatef(120.0f, 2.0f, 120.0f);
    DrawBox1();
	glPopMatrix();

	glPushMatrix();//中间大箱子
    glTranslatef(120.0f, 2.0f, 124.0f);
    DrawBox1();
	glPopMatrix();
	
	glPushMatrix();//中间大箱子
    glTranslatef(120.0f, 2.0f, 128.0f);
    DrawBox1();
	glPopMatrix();

	glPushMatrix();//中间小箱子
    glTranslatef(120.0f, 4.0f, 120.0f);
	DrawBox2();
	glPopMatrix();

	glPushMatrix();//中间绿布箱
	glTranslatef(128.0f, 3.0f, 120.0f);
	DrawBox3();
	glPopMatrix();

	glPushMatrix();//中间大箱子
    glTranslatef(132.0f, 2.0f, 125.0f);
    DrawBox1();
	glPopMatrix();

	glPushMatrix();//中间小箱子
    glTranslatef(129.0f, 1.0f, 125.0f);
	DrawBox2();
	glPopMatrix();

	glPushMatrix();//中间绿布箱
	glTranslatef(136.0f, 3.0f, 85.0f);
	glRotatef(45.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox3();
	glPopMatrix();

	glPushMatrix();//中间绿布箱
	glTranslatef(115.0f, 3.0f, 90.0f);
	glRotatef(-45.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox3();
	glPopMatrix();

	//**右边**//

	glPushMatrix();//右下集装箱
	glTranslatef(150.0f, 3.0f, 26.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//右下集装箱
	glTranslatef(150.0f, 3.0f, 38.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//右下集装箱
	glTranslatef(150.0f, 3.0f, 50.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//右下集装箱
	glTranslatef(150.0f, 3.0f, 62.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//右下集装箱
	glTranslatef(150.0f, 3.0f, 74.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//右下集装箱
	glTranslatef(150.0f, 3.0f, 86.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//右下集装箱
	glTranslatef(150.0f, 3.0f, 98.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 右中集装箱
	glTranslatef(150.0f, 9.0f, 104.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 右中集装箱
	glTranslatef(150.0f, 9.0f, 116.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 右上集装箱
	glTranslatef(150.0f, 15.0f, 122.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 右中集装箱
	glTranslatef(150.0f, 9.0f, 128.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 右上镂空台顶钩
	glTranslatef(145.0f, 25.0f, 113.0f);
	glRotatef(90.0,0.0,0.0,1.0);//绕z轴旋转
	//glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	glScalef(0.8,0.02,0.02);
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 右上镂空台顶钩臂
	glTranslatef(145.0f, 20.5f, 60.0f);
	glRotatef(0.0,0.0,1.0,0.0);//绕y轴旋转
	glRotatef(80.0,1.0,0.0,0.0);//绕x轴旋转
	glRotatef(90.0,0.0,0.0,1.0);//绕z轴旋转
	glScalef(9.0,0.02,0.02);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// 右上镂空台顶
	glTranslatef(145.0f, 20.0f, 113.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	glScalef(0.5,0.02,1.0);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// 右上镂空台后壁
	glTranslatef(148.0f, 18.0f, 113.0f);
	glRotatef(90.0,0.0,0.0,1.0);//绕z轴旋转
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	glScalef(0.5,0.02,0.8);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// 右上镂空台左柱
	glTranslatef(143.0f, 18.0f, 111.0f);
	glRotatef(90.0,0.0,0.0,1.0);//绕z轴旋转
	//glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	glScalef(0.4,0.02,0.02);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// 右上镂空台右柱
	glTranslatef(143.0f, 18.0f, 115.0f);
	glRotatef(90.0,0.0,0.0,1.0);//绕z轴旋转
	//glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	glScalef(0.4,0.02,0.02);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// 右上镂空台底
	glTranslatef(145.0f, 15.0f, 113.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	glScalef(0.5,0.02,1.0);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// 右上集装箱
	glTranslatef(150.0f, 15.0f, 104.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//右下绿布箱
	glTranslatef(150.0f, 3.0f, 110.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox3();
	glPopMatrix();

	glPushMatrix();//右下绿布箱
	glTranslatef(150.0f, 3.0f, 122.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox3();
	glPopMatrix();

	glPushMatrix();//右下集装箱
	glTranslatef(150.0f, 3.0f, 134.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();


	//**左边**//

	glPushMatrix();//左边大箱子
    glTranslatef(100.0f, 2.0f, 124.0f);
    DrawBox1();
	glPopMatrix();

	glPushMatrix();//左下集装箱
	glTranslatef(95.0f, 3.0f, 122.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();
	
	glPushMatrix();//左下集装箱
	glTranslatef(95.0f, 3.0f, 134.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//左边大箱子
    glTranslatef(95.0f, 2.0f, 85.0f);
    DrawBox1();
	glPopMatrix();

	glPushMatrix();//左下集装箱
	glTranslatef(89.0f, 3.0f, 26.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//左下集装箱
	glTranslatef(89.0f, 3.0f, 38.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//左下集装箱
	glTranslatef(89.0f, 3.0f, 50.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//左下集装箱
	glTranslatef(89.0f, 3.0f, 62.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//左下集装箱
	glTranslatef(89.0f, 3.0f, 74.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//左下集装箱
	glTranslatef(89.0f, 3.0f, 86.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//左下集装箱
	glTranslatef(89.0f, 3.0f, 98.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//左下集装箱
	glTranslatef(89.0f, 3.0f, 110.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 左中集装箱
	glTranslatef(89.0f, 9.0f, 104.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 左中集装箱
	glTranslatef(89.0f, 9.0f, 116.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 左上集装箱
	glTranslatef(89.0f, 15.0f, 122.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 左中集装箱
	glTranslatef(89.0f, 9.0f, 128.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 左上集装箱
	glTranslatef(89.0f, 15.0f, 104.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// 底部前左墙
	glTranslatef(142.0f, 3.0f, 140.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//底部前右墙
	glTranslatef(97.0f, 3.0f, 140.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//底部前中墙
	glTranslatef(120.0f, 3.0f, 140.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//底部左侧墙
	glTranslatef(150.0f, 3.0f, 150.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	glScalef(1.60,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//底部右侧墙
	glTranslatef(89.0f, 3.0f, 150.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	glScalef(1.60,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();// 底部后墙
	glTranslatef(120.0f, 3.0f, 155.0f);
	glScalef(5.0,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(120.0f, -2.0f,70.0f);
	drawScene();//绘制粒子
	glPopMatrix();


	glPushMatrix();// 底部屋顶
	glTranslatef(120.0f, 7.0f, 150.0f);
	glRotatef(90.0,1.0,0.0,0.0);//绕x轴旋转
	glScalef(5.5,5.0,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();// 头部后墙
	glTranslatef(120.0f, 3.0f, 0.0f);
	glScalef(5.0,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();// 头部前左墙
	glTranslatef(142.0f, 3.0f, 20.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//头部前右墙
	glTranslatef(97.0f, 3.0f, 20.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//头部前中墙
	glTranslatef(120.0f, 3.0f, 20.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();// 头部屋顶
	glTranslatef(120.0f, 7.0f, 10.0f);
	glRotatef(90.0,1.0,0.0,0.0);//绕x轴旋转
	glScalef(5.5,5.0,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//头部左侧墙
	glTranslatef(150.0f, 3.0f, 10.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	glScalef(1.60,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//头部右侧墙
	glTranslatef(89.0f, 3.0f, 10.0f);
	glRotatef(90.0,0.0,1.0,0.0);//绕y轴旋转
	glScalef(1.60,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//底部照片箱
	glTranslatef(95.0f, 3.0f, 145.0f);
	DrawPhotoBox();
	glPopMatrix();


	glPushMatrix();// 地面
	glTranslatef(120.0f, -0.5f, 120.0f);
	glScalef(60.0,0.25,60);
	DrawGround();
	glPopMatrix();


    glFlush();
	glutSwapBuffers();//交换缓冲区 
}

void ChangeSize(int width, int height)
{
    glViewport(0, 0, width, height);                                    /**< 重新设置视口 */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 4000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void motion(int x, int y)
{
    m_Camera.setViewByMouse();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        case 49:
            m_Camera.setSpeed(0.2f);
            break;
        case 50:
            m_Camera.setSpeed(0.6f);
            break;
        case 119:
            m_Camera.moveCamera(m_Camera.getSpeed());
            break;
        case 115:
            m_Camera.moveCamera(-m_Camera.getSpeed());
            break;
        case 97:
            m_Camera.yawCamera(-m_Camera.getSpeed());
            break;
        case 100:
            m_Camera.yawCamera(m_Camera.getSpeed());
            break;
    }

    glutPostRedisplay();
    printf("========%d", key);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition((GetSystemMetrics(SM_CXSCREEN) >> 1) - 400, (GetSystemMetrics(SM_CYSCREEN) >> 1) - 300);
    glutCreateWindow("第一人称游戏");
    init();
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}


