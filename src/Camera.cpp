
#include "stdafx.h"
#include "Camera.h"                    /**< ���������ͷ�ļ� */

/** ���캯�� */
Camera::Camera()
{
    /** ��ʼ������ֵ */
    Vector3 zero = Vector3(0.0, 3.0, 0.0);      
    Vector3 view = Vector3(0.0, 3.0, 0.5);      
    Vector3 up   = Vector3(0.0, 3.0, 1.0);      

    /** ��ʼ������� */
    m_Position  = zero;                 
    m_View      = view;             
    m_UpVector  = up;   
    m_Speed     = 1.0f;

}

Camera::~Camera()
{
}

/** �����������λ��,������������� */
void Camera::setCamera( float positionX, float positionY, float positionZ,
                        float viewX,     float viewY,     float viewZ,
                        float upVectorX, float upVectorY, float upVectorZ)
{
    /** �������� */
    Vector3 Position    = Vector3(positionX, positionY, positionZ);
    Vector3 View        = Vector3(viewX, viewY, viewZ);
    Vector3 UpVector    = Vector3(upVectorX, upVectorY, upVectorZ);

    /** ��������� */
    m_Position = Position;  
    m_View     = View;          
    m_UpVector = UpVector;  
}

/**  ��ת���������  */
void Camera::rotateView(float angle, float x, float y, float z)
{
    Vector3 newView;

    /** ���㷽������ */
    Vector3 view = m_View - m_Position;     

    /** ���� sin ��cosֵ */
    float cosTheta = (float)cos(angle);
    float sinTheta = (float)sin(angle);

    /** ������ת������xֵ */
    newView.x  = (cosTheta + (1 - cosTheta) * x * x)        * view.x;
    newView.x += ((1 - cosTheta) * x * y - z * sinTheta)    * view.y;
    newView.x += ((1 - cosTheta) * x * z + y * sinTheta)    * view.z;

    /** ������ת������yֵ */
    newView.y  = ((1 - cosTheta) * x * y + z * sinTheta)    * view.x;
    newView.y += (cosTheta + (1 - cosTheta) * y * y)        * view.y;
    newView.y += ((1 - cosTheta) * y * z - x * sinTheta)    * view.z;

    /** ������ת������zֵ */
    newView.z  = ((1 - cosTheta) * x * z - y * sinTheta)    * view.x;
    newView.z += ((1 - cosTheta) * y * z + x * sinTheta)    * view.y;
    newView.z += (cosTheta + (1 - cosTheta) * z * z)        * view.z;

    /** ����������ķ��� */
    m_View = m_Position + newView;
}

/** �������ת����� */
void Camera::setViewByMouse()
{
    POINT mousePos;                                   /**< ���浱ǰ���λ�� */
    int middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; /**< �õ���Ļ���ȵ�һ�� */
    int middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; /**< �õ���Ļ�߶ȵ�һ�� */
    float angleY = 0.0f;                              /**< �����������ת�Ƕ� */
    float angleZ = 0.0f;                              /**< �����������ת�Ƕ� */                 
    static float currentRotX = 0.0f;

    /** �õ���ǰ���λ�� */
    GetCursorPos(&mousePos);                        
    ShowCursor(TRUE);

    /** ������û���ƶ�,���ø��� */
    if( (mousePos.x == middleX) && (mousePos.y == middleY) )
        return;

    /** �������λ������Ļ���� */
    SetCursorPos(middleX, middleY); 

    /**< �õ�����ƶ����� */
    angleY = (float)( (middleX - mousePos.x) ) / 1000.0f;       
    angleZ = (float)( (middleY - mousePos.y) ) / 1000.0f;       

   // static float lastRotX = 0.0f;      /**< ���ڱ�����ת�Ƕ� */
   // lastRotX = currentRotX; 

   // /** ���������������ת�Ƕ� */
   // currentRotX += angleZ;

   // /** ���������ת���ȴ���10.0,���ǽ�ȡ��10.0����ת */
   // if(currentRotX > 10.0f)     
   // {
   //     currentRotX = 10.0f;

   //     /** ���ݱ���ĽǶ���ת���� */
   //     if(lastRotX != 10.0f) 
   //     {
   //         /** ͨ������ҵ�����ת����ֱ������ */
   //         Vector3 vAxis = m_View - m_Position;
   //         vAxis = vAxis.crossProduct(m_UpVector);
   //         vAxis = vAxis.normalize();

   //         ///��ת
   //         rotateView( 10.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
   //     }
   // }
   // /* �����ת����С��-10.0,��Ҳ��ȡ��-10.0����ת */
   // else if(currentRotX < -10.0f)
   // {
   //     currentRotX = -10.0f;

   //     if(lastRotX != -10.0f)
   //     {

   //         /** ͨ������ҵ�����ת����ֱ������ */
   //         Vector3 vAxis = m_View - m_Position;
   //         vAxis = vAxis.crossProduct(m_UpVector);
   //         vAxis = vAxis.normalize();

   //         ///��ת
   //         rotateView( -10.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
   //     }
   // }
   // /** �������תangleZ�� */
   // else 
   //{   
   //     /** �ҵ�����ת����ֱ���� */
   //     Vector3 vAxis = m_View - m_Position;
   //     vAxis = vAxis.crossProduct(m_UpVector);
   //     vAxis = vAxis.normalize();

   //     ///��ת
   //     rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
   //}

	rotateView(angleZ, 0, 0, 1);
    /** ����������ת����� */
    rotateView(angleY, 0, 1, 0);
}

/** �����ƶ������ */
void Camera::yawCamera(float speed)
{
    Vector3 yaw;
    Vector3 cross = m_View - m_Position;
    cross = cross.crossProduct(m_UpVector);

    // Normalize the strafe vector
    yaw = cross.normalize();

    m_Position.x += yaw.x * speed*10;
    m_Position.z += yaw.z * speed*10;

    // Add the strafe vector to our view
    m_View.x += yaw.x * speed*10;
    m_View.z += yaw.z * speed*10;
}

/** ǰ���ƶ������ */
void Camera::moveCamera(float speed)
{
    /** ���㷽������ */
    Vector3 vector = m_View - m_Position;
    vector = vector.normalize();         /**< ��λ�� */

    /** ��������� */
    m_Position.x += vector.x * speed*10;    /**< �����ٶȸ���λ�� */
    m_Position.z += vector.z * speed*10;       
    m_View.x += vector.x * speed*10;        /**< �����ٶȸ��·��� */   
    m_View.z += vector.z * speed*10;           
}


/** �����ӵ� */
void Camera::setLook()
{
    /** �����ӿ� */
    gluLookAt(m_Position.x, m_Position.y, m_Position.z, 
              m_View.x,  m_View.y,     m_View.z,    
              m_UpVector.x, m_UpVector.y, m_UpVector.z);
}