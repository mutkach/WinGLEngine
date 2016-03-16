
#include "main.h"
#define kSpeed 4


CCamera::CCamera()
{
    //Инициализируем вектор нашей позиции в нулевые координаты
    vec3 vZero = vec3(0.0, 0.0, 0.0);   //Инициализируем вектор нашей позиции
                           
    vec3 vView = vec3(0.0, 1.0, 0.5);   //Иниц. вектор взгляда
    vec3 vUp = vec3(0.0, 0.0, 1.0);     //Вектор верт.

    m_vPosition = vZero;
    m_vView = vView;
    m_vUpVector = vUp;
	zNear = 0.5;
	zFar = 1000;

}


GLvoid CCamera::SetCamera(float positionX, float positionY, float positionZ,
        float viewX, float viewY, float viewZ,
        float upVectorX, float upVectorY, float upVectorZ)
{	


    vec3 vPosition  = vec3(positionX, positionY, positionZ);
    vec3 vView      = vec3(viewX, viewY, viewZ);
    vec3 vUpVector  = vec3(upVectorX, upVectorY, upVectorZ);
	viewMat = lookAt(vView, vPosition, vUpVector);


	projectionMat = perspective<float>(55,(GLfloat)g_rRect.right/(GLfloat)g_rRect.bottom, zNear, zFar);
    m_vPosition = vPosition;
    m_vView = vView;
    m_vUpVector = vUpVector;


}


vec3 Cross(vec3 vVector1, vec3 vVector2)
{
    vec3 vNormal;
    vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
    vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
    vNormal.z  = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));
    return vNormal;
}


void CCamera::RotateView(float angle, float x, float y, float z)
{
    vec3 vNewView;
    vec3 vView;


    vView.x = m_vView.x - m_vPosition.x;    //направление по X
    vView.y = m_vView.y - m_vPosition.y;    //направление по Y
    vView.z = m_vView.z - m_vPosition.z;    //направление по Z


    float cosTheta = (float)cos(angle);
    float sinTheta = (float)sin(angle);


    vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)   * vView.x;
    vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)   * vView.y;
    vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)   * vView.z;

 
    vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)   * vView.x;
    vNewView.y += (cosTheta + (1 - cosTheta) * y * y)   * vView.y;
    vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)   * vView.z;

    
    vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)   * vView.x;
    vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)   * vView.y;
    vNewView.z += (cosTheta + (1 - cosTheta) * z * z)   * vView.z;


    m_vView.x = m_vPosition.x + vNewView.x;
    m_vView.y = m_vPosition.y + vNewView.y;
    m_vView.z = m_vPosition.z + vNewView.z;
}


float Magnitude(vec3 vNormal)
{

 
    return (float)sqrt( (vNormal.x * vNormal.x) +
            (vNormal.y * vNormal.y) +
            (vNormal.z * vNormal.z) );
}


vec3 Normalize(vec3 vVector)
{
    float magnitude = Magnitude(vVector);
    vVector = vVector / magnitude;
    return vVector;
}


void CCamera::MoveCamera(float speed)
{
    vec3 vVector = m_vView - m_vPosition;
	//vVector.y = 1.0f;
	vVector = normalize(vVector);		
    m_vPosition.x += vVector.x * speed;
    m_vPosition.z += vVector.z * speed;
	m_vPosition.y += vVector.y * speed;

    m_vView.x += vVector.x * speed;
    m_vView.z += vVector.z * speed;
	m_vView.y += vVector.y * speed;

}


void CCamera::SetViewByMouse()
{	
    POINT mousePos;         

    
    int middleX = SCREEN_WIDTH  >> 1;   
    int middleY = SCREEN_HEIGHT >> 1;   
    float angleY = 0.0f;   
    float angleZ = 0.0f;    
    static float currentRotX = 0.0f;

    GetCursorPos(&mousePos);

    if( (mousePos.x == middleX) && (mousePos.y == middleY) ) return;
 
 
    SetCursorPos(middleX, middleY);
 

    angleY = (float)((middleX - mousePos.x)) / 1000.0f;
    angleZ = (float)((middleY - mousePos.y)) / 1000.0f;
 
    static float lastRotX = 0.0f;
    lastRotX = currentRotX;     
 
    if(currentRotX > 1.0f)
    {
        currentRotX = 1.0f; 
        if(lastRotX != 1.0f)
        {
            vec3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
            vAxis = Normalize(vAxis);
 

            RotateView(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
        }
    }
 

    else if(currentRotX < -1.0f)
    {
        currentRotX = -1.0f;
        if(lastRotX != -1.0f)
        {
   
            vec3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
            vAxis = Normalize(vAxis);
 
            RotateView( -1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
        }
    }

    else
    {
        vec3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
        vAxis = Normalize(vAxis);
        RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
    }
 
    RotateView(angleY, 0, 1, 0);
}


void CCamera::StrafeCamera(float speed)
{

    m_vPosition.x += m_vStrafe.x * speed*0.5;
    m_vPosition.z += m_vStrafe.z * speed*0.5;
 

    m_vView.x += m_vStrafe.x * speed*0.5;
    m_vView.z += m_vStrafe.z * speed*0.5;
}


void CCamera::GetFrameTime()
{
    static float frameTime = 0.0f;  // Время последнего кадра

    float currentTime = timeGetTime() * 0.00001f;

    // Интервал времени, прошедшего с прошлого кадра
    g_FrameInterval =  0.1;

    frameTime = currentTime;
}


void CCamera::CheckForMovement()
{	
	float speed = kSpeed* g_FrameInterval;
	
    if( GetKeyState('W') & 0x80) {
        MoveCamera(speed);
    }
 
    // ВНИЗ или S
    if( GetKeyState('S') & 0x80) {
        MoveCamera(-speed);
    }
 
    
    if( GetKeyState('A') & 0x80) {
 
    
        StrafeCamera(-speed);
    }
 
    
    if( GetKeyState('D') & 0x80) {
    
        StrafeCamera(speed);
    }
	
	

}
 

void CCamera::Update()
{

    vec3 vCross = cross(m_vView - m_vPosition, m_vUpVector);
     
    m_vStrafe = normalize(vCross);

    viewMat = glm ::lookAt(m_vPosition, m_vView, m_vUpVector);
 
    // Проверим нажатия
	GetFrameTime();
	SetViewByMouse();
    CheckForMovement();
	ExtractPlanes();
	
}
 

void CCamera::ExtractPlanes(){

	VP = projectionMat * viewMat;
	mat4 v = viewMat;
	mat4 p = projectionMat;
	mat4 clipMatrix;
	clipMatrix[0][0] = v[0][0]*p[0][0]+v[0][1]*p[1][0]+v[0][2]*p[2][0]+v[0][3]*p[3][0];
	clipMatrix[1][0] = v[0][0]*p[0][1]+v[0][1]*p[1][1]+v[0][2]*p[2][1]+v[0][3]*p[3][1];
	clipMatrix[2][0] = v[0][0]*p[0][2]+v[0][1]*p[1][2]+v[0][2]*p[2][2]+v[0][3]*p[3][2];
	clipMatrix[3][0] = v[0][0]*p[0][3]+v[0][1]*p[1][3]+v[0][2]*p[2][3]+v[0][3]*p[3][3];
	clipMatrix[0][1] = v[1][0]*p[0][0]+v[1][1]*p[1][0]+v[1][2]*p[2][0]+v[1][3]*p[3][0];
	clipMatrix[1][1] = v[1][0]*p[0][1]+v[1][1]*p[1][1]+v[1][2]*p[2][1]+v[1][3]*p[3][1];
	clipMatrix[2][1] = v[1][0]*p[0][2]+v[1][1]*p[1][2]+v[1][2]*p[2][2]+v[1][3]*p[3][2];
	clipMatrix[3][1] = v[1][0]*p[0][3]+v[1][1]*p[1][3]+v[1][2]*p[2][3]+v[1][3]*p[3][3];
	clipMatrix[0][2] = v[2][0]*p[0][0]+v[2][1]*p[1][0]+v[2][2]*p[2][0]+v[2][3]*p[3][0];
	clipMatrix[1][2] = v[2][0]*p[0][1]+v[2][1]*p[1][1]+v[2][2]*p[2][1]+v[2][3]*p[3][1];
	clipMatrix[2][2] = v[2][0]*p[0][2]+v[2][1]*p[1][2]+v[2][2]*p[2][2]+v[2][3]*p[3][2];
	clipMatrix[3][2] = v[2][0]*p[0][3]+v[2][1]*p[1][3]+v[2][2]*p[2][3]+v[2][3]*p[3][3];
	clipMatrix[0][3] = v[3][0]*p[0][0]+v[3][1]*p[1][0]+v[3][2]*p[2][0]+v[3][3]*p[3][0];
	clipMatrix[1][3] = v[3][0]*p[0][1]+v[3][1]*p[1][1]+v[3][2]*p[2][1]+v[3][3]*p[3][1];
	clipMatrix[2][3] = v[3][0]*p[0][2]+v[3][1]*p[1][2]+v[3][2]*p[2][2]+v[3][3]*p[3][2];
	clipMatrix[3][3] = v[3][0]*p[0][3]+v[3][1]*p[1][3]+v[3][2]*p[2][3]+v[3][3]*p[3][3];

	mat4 VP1 =  clipMatrix;
	//left
	plane[0].x = VP1[3][0] + VP1[0][0];
	plane[0].y = VP1[3][1] + VP1[0][1];
	plane[0].z = VP1[3][2] + VP1[0][2];
	plane[0].w = VP1[3][3] + VP1[0][3];

	//right
	plane[1].x = VP1[3][0] - VP1[0][0];
	plane[1].y = VP1[3][1] - VP1[0][1];
	plane[1].z = VP1[3][2] - VP1[0][2];
	plane[1].w = VP1[3][3] - VP1[0][3];

	//bottom
	plane[2].x = VP1[3][0] + VP1[1][0];
	plane[2].y = VP1[3][1] + VP1[1][1];
	plane[2].z = VP1[3][2] + VP1[1][2];
	plane[2].w = VP1[3][3] + VP1[1][3];

	//upper
	plane[3].x = VP1[3][0] - VP1[1][0];
	plane[3].y = VP1[3][1] - VP1[1][1];
	plane[3].z = VP1[3][2] - VP1[1][2];
	plane[3].w = VP1[3][3] - VP1[1][3];

	//near
	plane[4].x = VP1[3][0] + VP1[2][0];
	plane[4].y = VP1[3][1] + VP1[2][1];
	plane[4].z = VP1[3][2] + VP1[2][2];
	plane[4].w = VP1[3][3] + VP1[2][3];

	//far
	plane[5].x = VP1[3][0] - VP1[2][0];
	plane[5].y = VP1[3][1] - VP1[2][1];
	plane[5].z = VP1[3][2] - VP1[2][2];
	plane[5].w = VP1[3][3] - VP1[2][3];

	


	/*
	plane[0].x = VP[0][3] + VP[0][0];
	plane[0].y = VP[1][3] + VP[1][0];
	plane[0].z = VP[2][3] + VP[2][0];
	plane[0].w = VP[3][3] + VP[3][0];

	//right
	plane[1].x = VP[0][3] - VP[0][0];
	plane[1].y = VP[1][3] - VP[1][0];
	plane[1].z = VP[2][3] - VP[2][0];
	plane[1].w = VP[3][3] - VP[3][0];
	//bottom
	plane[2].x = VP[0][3] + VP[0][1];
	plane[2].y = VP[1][3] + VP[1][1];
	plane[2].z = VP[2][3] + VP[2][1];
	plane[2].w = VP[3][3] + VP[3][1];
	//upper
	plane[3].x = VP[0][3] - VP[0][1];
	plane[3].y = VP[1][3] - VP[1][1];
	plane[3].z = VP[2][3] - VP[2][1];
	plane[3].w = VP[3][3] - VP[3][1];
	//near
	plane[4].x = VP[0][3] + VP[0][2];
	plane[4].y = VP[1][3] + VP[1][2];
	plane[4].z = VP[2][3] + VP[2][2];
	plane[4].w = VP[3][3] + VP[3][2];
	//far
	plane[5].x = VP[0][3] - VP[0][2];
	plane[5].y = VP[1][3] - VP[1][2];
	plane[5].z = VP[2][3] - VP[2][2];
	plane[5].w = VP[3][3] - VP[3][2];
	*/

	for(int i = 0; i < 6; ++i){
		plane[i] = glm::normalize(plane[i]);
	}
}