// ���������.cpp : �������̨Ӧ�ó������ڵ㡣
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

GLfloat rotate=0.0;//��ת�Ƕ�
GLfloat r=5.0;//��ת����

/** �����Դ������ֵ */
GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };    /**< ��������� */
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };    /**< �������� */
GLfloat LightSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   /**< �������� */
GLfloat LightPosition0[] = { 100.0f, 28.0f, 90.0f, 0.0f };   /**< ��Դλ�� */
GLfloat LightPosition1[] = { 120.0f, 120.0f, 120.0f, 0.0f };   /**< ��Դλ�� */

Camera m_Camera;
CBMPLoader m_Texture1;//ľ������
CBMPLoader m_Texture2;//�̲�������
CBMPLoader m_Texture3;//��װ������
CBMPLoader m_Texture4;//��������
CBMPLoader m_Texture5;//ǽ����
CBMPLoader m_Texture7;//��������
CBMPLoader m_Texture6;//�ο�̨����

/**��Ƭ������*/
CBMPLoader m_Texture8;
CBMPLoader m_Texture9;
CBMPLoader m_Texture10;
CBMPLoader m_Texture11;

CSkyBox m_SkyBox;//��պ�

emitter *e1;

particle* init_particle()//��ʼ������ϵͳ
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

void idle()//ˢ������ϵͳ
{
	glutPostRedisplay();
}

/** ����λͼ����(ľ����ͼ) */
bool LoadTexture1()
{
    if (!m_Texture1.LoadBitmap("woodbox.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture1.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture1.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture1.imageWidth,
        m_Texture1.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture1.image);

    return true;
}

/** ����λͼ����(��Ƥ����ͼ) */
bool LoadTexture2()
{
    if (!m_Texture2.LoadBitmap("��Ƥ��.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture2.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture2.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture2.imageWidth,
        m_Texture2.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture2.image);

    return true;
}

/** ����λͼ����(��װ����ͼ) */
bool LoadTexture3()
{
    if (!m_Texture3.LoadBitmap("��װ��.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture3.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture3.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture3.imageWidth,
        m_Texture3.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture3.image);

    return true;
}

/** ����λͼ����(������ͼ) */
bool LoadTexture4()
{
    if (!m_Texture4.LoadBitmap("ground.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture4.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture4.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture4.imageWidth,
        m_Texture4.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture4.image);

    return true;
}

/** ����λͼ����(ǽ��ͼ) */
bool LoadTexture5()
{
    if (!m_Texture5.LoadBitmap("wall.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture5.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture5.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture5.imageWidth,
        m_Texture5.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture5.image);

    return true;
}

/** ����λͼ����(������ͼ) */
bool LoadTexture7()
{
    if (!m_Texture7.LoadBitmap("p.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture7.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture7.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture7.imageWidth,
        m_Texture7.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture7.image);

    return true;
}

/** ����λͼ����(�ο�̨��ͼ) */
bool LoadTexture6()
{
    if (!m_Texture6.LoadBitmap("�ο�̨.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture6.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture6.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture6.imageWidth,
        m_Texture6.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture6.image);

    return true;
}

/** ����λͼ����(��Ƭ����ͼ) */
bool LoadTexture8()
{
    if (!m_Texture8.LoadBitmap("1.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture8.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture8.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture8.imageWidth,
        m_Texture8.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture8.image);

    return true;
}
bool LoadTexture9()
{
    if (!m_Texture9.LoadBitmap("2.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture9.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture9.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture9.imageWidth,
        m_Texture9.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture9.image);

    return true;
}
bool LoadTexture10()
{
    if (!m_Texture10.LoadBitmap("95.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture10.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture10.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture10.imageWidth,
        m_Texture10.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture10.image);

    return true;
}
bool LoadTexture11()
{
    if (!m_Texture11.LoadBitmap("556.bmp"))                                         /**< ����λͼ�ļ� */
    {
        MessageBox(NULL, (LPCWSTR)"loadTexture error", (LPCWSTR)"error", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
        return false;
    }

    glGenTextures(1, &m_Texture11.ID);                                                /**< ����һ������������� */
    glBindTexture(GL_TEXTURE_2D, m_Texture11.ID);                                     /**< ����������� */

    /** �����˲� */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** �������� */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture11.imageWidth,
        m_Texture11.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        m_Texture11.image);

    return true;
}

void DrawPlane(void)//���ɻ�
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
/** �������� */

/** ���� */
void DrawBox1()//��ľ��
{
    /** ���ò������� */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    glScalef(2.0f, 2.0f, 2.0f);
    /** ѡ������ */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture1.ID);
    /** ��ʼ�����ı��� */
    glBegin(GL_QUADS);
    /// ǰ����
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< ָ������ָ��۲��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// �����
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< ָ�����߱���۲��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< ָ���������� */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// �Ҳ���
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// �����
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawBox2()//Сľ��
{
    /** ���ò������� */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


   // glScalef(0.5f, 0.5f, 0.5f);
    /** ѡ������ */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture1.ID);
    /** ��ʼ�����ı��� */
    glBegin(GL_QUADS);
    /// ǰ����
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< ָ������ָ��۲��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// �����
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< ָ�����߱���۲��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< ָ���������� */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// �Ҳ���
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// �����
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
    
}

void DrawBox3()//��Ƥ��
{
    /** ���ò������� */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    glScalef(6.0f, 3.0f, 3.0f);
    /** ѡ������ */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture2.ID);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    /** ��ʼ�����ı��� */
    glBegin(GL_QUADS);
    /// ǰ����
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< ָ������ָ��۲��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// �����
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< ָ�����߱���۲��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< ָ���������� */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// �Ҳ���
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// �����
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawBox4()//��װ��
{
    /** ���ò������� */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    glScalef(6.0f, 3.0f, 3.0f);
    /** ѡ������ */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture3.ID);
    /** ��ʼ�����ı��� */
    glBegin(GL_QUADS);
    /// ǰ����
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< ָ������ָ��۲��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// �����
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< ָ�����߱���۲��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< ָ���������� */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// �Ҳ���
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// �����
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawBox5()//�ο�̨
{
    /** ���ò������� */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    glScalef(6.0f, 3.0f, 3.0f);
    /** ѡ������ */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture6.ID);
    /** ��ʼ�����ı��� */
    glBegin(GL_QUADS);
    /// ǰ����
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< ָ������ָ��۲��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// �����
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< ָ�����߱���۲��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< ָ���������� */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// �Ҳ���
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// �����
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawWall()//ǽ
{
    /** ���ò������� */
    GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    glScalef(6.0f, 3.0f, 3.0f);
    /** ѡ������ */
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture5.ID);
    /** ��ʼ�����ı��� */
    glBegin(GL_QUADS);
    /// ǰ����
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< ָ������ָ��۲��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// �����
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< ָ�����߱���۲��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< ָ���������� */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// �Ҳ���
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// �����
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glDisable(GL_TEXTURE_2D);
    glEnd();
}

void DrawGround()//����
{
    glScalef(6.0f, 3.0f, 3.0f);
    /** ѡ������ */
    glBindTexture(GL_TEXTURE_2D, m_Texture4.ID);
    /** ��ʼ�����ı��� */
    glBegin(GL_QUADS);
    /// ǰ����
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< ָ������ָ��۲��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    /// �����
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< ָ�����߱���۲��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< ָ���������� */
    glTexCoord2f(0.0f, 100.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(100.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(100.0f, 100.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    /// �Ҳ���
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    /// �����
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< ָ�����߳��� */
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
    /** ��ʼ�����ı��� */
    glBegin(GL_QUADS);
    /// ǰ����
    glNormal3f(0.0f, 0.0f, 1.0f);                               /**< ָ������ָ��۲��� */
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Texture9.ID);
	glBegin(GL_QUADS);
    /// �����
    glNormal3f(0.0f, 0.0f, -1.0f);                              /**< ָ�����߱���۲��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
    /// ����
    glNormal3f(0.0f, 1.0f, 0.0f);                               /**< ָ���������� */
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    /// ����
    glNormal3f(0.0f, -1.0f, 0.0f);                              /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture10.ID);
	glBegin(GL_QUADS);
    /// �Ҳ���
    glNormal3f(1.0f, 0.0f, 0.0f);                               /**< ָ�����߳��� */
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Texture11.ID);
	glBegin(GL_QUADS);
    /// �����
    glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< ָ�����߳��� */
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
	glMatrixMode(GL_PROJECTION);					  //����͸��Ч��
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
	glEnable ( GL_COLOR_MATERIAL );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glEnable(GL_BLEND);

    /** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);     /**< ���û����� */
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);     /**< ��������� */
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);   /**< ���÷���� */
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     /**< ���û����� */
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     /**< ��������� */
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);   /**< ���÷���� */

    /** ���ù�Դ������ */
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glDisable(GL_LIGHT1);
    glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE); //���������ܹ���Ӱ��
	


	/** ��ʼ����� */
    if (!m_SkyBox.Init())
    {
        MessageBox(NULL, (LPCWSTR)"3", (LPCWSTR)"4", MB_OK);
        exit(0);
    }

	//    ** �������� */
    /*glBindTexture(GL_TEXTURE_2D, m_Texture5.ID);*/
    if (!LoadTexture1()||!LoadTexture2()||!LoadTexture3()||!LoadTexture4()||!LoadTexture5()||!LoadTexture6()||!LoadTexture7()||!LoadTexture8()||!LoadTexture9()||!LoadTexture10()||!LoadTexture11())
        MessageBox(NULL, (LPCWSTR)"5", (LPCWSTR)"6", MB_OK);

    /** ��������� */
    m_Camera.setCamera(100.0f, 3.0f, 130.0f, 120.0f, -1.5f, 120.0f, 0.0f, 1.0f, 0.0f);

	e1 = new emitter(5000, 0,0, -30, -30);
	e1->emit(init_particle);
}

void display(void)
{
    /** �û��Զ���Ļ��ƹ��� */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /** ��������� */
    m_Camera.setLook();
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);   /**< ���ù�Դλ�� */
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);   /**< ���ù�Դλ�� */


    /**���ƹ��� */

	 /** ������� */
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

   //**�м�**//

	glPushMatrix();//�м������
    glTranslatef(120.0f, 2.0f, 120.0f);
    DrawBox1();
	glPopMatrix();

	glPushMatrix();//�м������
    glTranslatef(120.0f, 2.0f, 124.0f);
    DrawBox1();
	glPopMatrix();
	
	glPushMatrix();//�м������
    glTranslatef(120.0f, 2.0f, 128.0f);
    DrawBox1();
	glPopMatrix();

	glPushMatrix();//�м�С����
    glTranslatef(120.0f, 4.0f, 120.0f);
	DrawBox2();
	glPopMatrix();

	glPushMatrix();//�м��̲���
	glTranslatef(128.0f, 3.0f, 120.0f);
	DrawBox3();
	glPopMatrix();

	glPushMatrix();//�м������
    glTranslatef(132.0f, 2.0f, 125.0f);
    DrawBox1();
	glPopMatrix();

	glPushMatrix();//�м�С����
    glTranslatef(129.0f, 1.0f, 125.0f);
	DrawBox2();
	glPopMatrix();

	glPushMatrix();//�м��̲���
	glTranslatef(136.0f, 3.0f, 85.0f);
	glRotatef(45.0,0.0,1.0,0.0);//��y����ת
	DrawBox3();
	glPopMatrix();

	glPushMatrix();//�м��̲���
	glTranslatef(115.0f, 3.0f, 90.0f);
	glRotatef(-45.0,0.0,1.0,0.0);//��y����ת
	DrawBox3();
	glPopMatrix();

	//**�ұ�**//

	glPushMatrix();//���¼�װ��
	glTranslatef(150.0f, 3.0f, 26.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(150.0f, 3.0f, 38.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(150.0f, 3.0f, 50.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(150.0f, 3.0f, 62.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(150.0f, 3.0f, 74.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(150.0f, 3.0f, 86.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(150.0f, 3.0f, 98.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// ���м�װ��
	glTranslatef(150.0f, 9.0f, 104.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// ���м�װ��
	glTranslatef(150.0f, 9.0f, 116.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// ���ϼ�װ��
	glTranslatef(150.0f, 15.0f, 122.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// ���м�װ��
	glTranslatef(150.0f, 9.0f, 128.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// �����ο�̨����
	glTranslatef(145.0f, 25.0f, 113.0f);
	glRotatef(90.0,0.0,0.0,1.0);//��z����ת
	//glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	glScalef(0.8,0.02,0.02);
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// �����ο�̨������
	glTranslatef(145.0f, 20.5f, 60.0f);
	glRotatef(0.0,0.0,1.0,0.0);//��y����ת
	glRotatef(80.0,1.0,0.0,0.0);//��x����ת
	glRotatef(90.0,0.0,0.0,1.0);//��z����ת
	glScalef(9.0,0.02,0.02);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// �����ο�̨��
	glTranslatef(145.0f, 20.0f, 113.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	glScalef(0.5,0.02,1.0);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// �����ο�̨���
	glTranslatef(148.0f, 18.0f, 113.0f);
	glRotatef(90.0,0.0,0.0,1.0);//��z����ת
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	glScalef(0.5,0.02,0.8);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// �����ο�̨����
	glTranslatef(143.0f, 18.0f, 111.0f);
	glRotatef(90.0,0.0,0.0,1.0);//��z����ת
	//glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	glScalef(0.4,0.02,0.02);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// �����ο�̨����
	glTranslatef(143.0f, 18.0f, 115.0f);
	glRotatef(90.0,0.0,0.0,1.0);//��z����ת
	//glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	glScalef(0.4,0.02,0.02);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// �����ο�̨��
	glTranslatef(145.0f, 15.0f, 113.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	glScalef(0.5,0.02,1.0);
	DrawBox5();
	glPopMatrix();

	glPushMatrix();// ���ϼ�װ��
	glTranslatef(150.0f, 15.0f, 104.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//�����̲���
	glTranslatef(150.0f, 3.0f, 110.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox3();
	glPopMatrix();

	glPushMatrix();//�����̲���
	glTranslatef(150.0f, 3.0f, 122.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox3();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(150.0f, 3.0f, 134.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();


	//**���**//

	glPushMatrix();//��ߴ�����
    glTranslatef(100.0f, 2.0f, 124.0f);
    DrawBox1();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(95.0f, 3.0f, 122.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();
	
	glPushMatrix();//���¼�װ��
	glTranslatef(95.0f, 3.0f, 134.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//��ߴ�����
    glTranslatef(95.0f, 2.0f, 85.0f);
    DrawBox1();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(89.0f, 3.0f, 26.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(89.0f, 3.0f, 38.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(89.0f, 3.0f, 50.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(89.0f, 3.0f, 62.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(89.0f, 3.0f, 74.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(89.0f, 3.0f, 86.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(89.0f, 3.0f, 98.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();//���¼�װ��
	glTranslatef(89.0f, 3.0f, 110.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// ���м�װ��
	glTranslatef(89.0f, 9.0f, 104.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// ���м�װ��
	glTranslatef(89.0f, 9.0f, 116.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// ���ϼ�װ��
	glTranslatef(89.0f, 15.0f, 122.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// ���м�װ��
	glTranslatef(89.0f, 9.0f, 128.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// ���ϼ�װ��
	glTranslatef(89.0f, 15.0f, 104.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	DrawBox4();
	glPopMatrix();

	glPushMatrix();// �ײ�ǰ��ǽ
	glTranslatef(142.0f, 3.0f, 140.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//�ײ�ǰ��ǽ
	glTranslatef(97.0f, 3.0f, 140.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//�ײ�ǰ��ǽ
	glTranslatef(120.0f, 3.0f, 140.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//�ײ����ǽ
	glTranslatef(150.0f, 3.0f, 150.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	glScalef(1.60,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//�ײ��Ҳ�ǽ
	glTranslatef(89.0f, 3.0f, 150.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	glScalef(1.60,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();// �ײ���ǽ
	glTranslatef(120.0f, 3.0f, 155.0f);
	glScalef(5.0,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(120.0f, -2.0f,70.0f);
	drawScene();//��������
	glPopMatrix();


	glPushMatrix();// �ײ��ݶ�
	glTranslatef(120.0f, 7.0f, 150.0f);
	glRotatef(90.0,1.0,0.0,0.0);//��x����ת
	glScalef(5.5,5.0,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();// ͷ����ǽ
	glTranslatef(120.0f, 3.0f, 0.0f);
	glScalef(5.0,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();// ͷ��ǰ��ǽ
	glTranslatef(142.0f, 3.0f, 20.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//ͷ��ǰ��ǽ
	glTranslatef(97.0f, 3.0f, 20.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//ͷ��ǰ��ǽ
	glTranslatef(120.0f, 3.0f, 20.0f);
	glScalef(1.25,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();// ͷ���ݶ�
	glTranslatef(120.0f, 7.0f, 10.0f);
	glRotatef(90.0,1.0,0.0,0.0);//��x����ת
	glScalef(5.5,5.0,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//ͷ�����ǽ
	glTranslatef(150.0f, 3.0f, 10.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	glScalef(1.60,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//ͷ���Ҳ�ǽ
	glTranslatef(89.0f, 3.0f, 10.0f);
	glRotatef(90.0,0.0,1.0,0.0);//��y����ת
	glScalef(1.60,1.25,0.25);
	DrawWall();
	glPopMatrix();

	glPushMatrix();//�ײ���Ƭ��
	glTranslatef(95.0f, 3.0f, 145.0f);
	DrawPhotoBox();
	glPopMatrix();


	glPushMatrix();// ����
	glTranslatef(120.0f, -0.5f, 120.0f);
	glScalef(60.0,0.25,60);
	DrawGround();
	glPopMatrix();


    glFlush();
	glutSwapBuffers();//���������� 
}

void ChangeSize(int width, int height)
{
    glViewport(0, 0, width, height);                                    /**< ���������ӿ� */
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
    glutCreateWindow("��һ�˳���Ϸ");
    init();
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}


