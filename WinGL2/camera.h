#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

using namespace glm;

class CCamera {

public:
	float  g_FrameInterval;
	mat4 viewMat;
	mat4 projectionMat;
	mat4 VP;
	vec4 plane[6];
    vec3 m_vPosition;   
    vec3 m_vView;   
	vec3 m_vUpVector;   
	vec3 m_vStrafe;
	float zNear;
	float zFar; /////////////////////////////////////////////////////ADDDD MYTIMER

    vec3 Position() {   return m_vPosition; }
    vec3 View()     {   return m_vView; }
    vec3 UpVector() {   return m_vUpVector; }
    vec3 Strafe()   {   return m_vStrafe;}

    // Конструктор
    CCamera();


    void SetCamera(float positionX, float positionY, float positionZ,
                     float viewX,     float viewY,     float viewZ,
                 float upVectorX, float upVectorY, float upVectorZ);


    void MoveCamera(float speed);

	void RotateView(float angle, float x, float y, float z);
	void SetViewByMouse();
	void StrafeCamera(float speed);
	void GetFrameTime();
	void CheckForMovement();
	void ExtractPlanes();
	void Update();
	void Look();
};

#endif