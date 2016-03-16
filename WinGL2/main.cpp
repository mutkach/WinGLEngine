
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"libnoise.lib")
#pragma comment(lib,"DevIL.lib")
#pragma comment(lib,"ilut.lib")
#pragma comment(lib,"ilu.lib")               
#pragma comment(lib,"assimp.lib")        
#pragma comment(lib,"freetype250.lib")
#pragma comment(lib,"BulletDynamics.lib") // Debug Debug Debug -- multithreaded dll debug
#pragma comment(lib,"BulletCollision.lib")
#pragma comment(lib,"LinearMath.lib")


#include "main.h"

#define BUFFER_OFFSET(i) ((void*)(i))
#define RIGHT_HAND 1
#define LEFT_HAND 0

HWND  g_hWnd;
RECT  g_rRect;
HDC   g_hDC;
HGLRC g_hRC;
HINSTANCE g_hInstance;
Renderer* renderer;






void Init(HWND hWnd)
{		
	



	g_hWnd = hWnd;
	GetClientRect(g_hWnd, &g_rRect);
	InitializeOpenGL(g_rRect.right, g_rRect.bottom);
	glewInit();

	ilInit();
	iluInit();

	glClearColor ( 0.0, 0.0, 0.0, 0.0 ) ;
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	
	
}


WPARAM MainLoop()
{	
	
	vec3 angles;
	MSG msg;
	const char* strError = "win";

	Timer* weapon = new Timer();

	weapon->StartTimer();
	float wait = 0;


	Light* point = new Light();
	point->name = "O4ko";
	point->SetPosition( vec3(5.0, 10.0, 10.0) );
	point->SetColour(vec3(0.8, 0.9, 1.0) );
	point->SetRadius(150.0);
	point->SetTransform();
	

	Scene* test = new Scene();
	Object* mod = new Object("default/titled.dae", true);
	
	

	Object* mod1 = new Object("default/sphere.dae", false);

	Object* sphere = new Object("default/sphere.dae", true);
	Object* cone = new Object("default/sphere.dae", false);

	point->type = sphere;


	renderer = new Renderer();	

	//test->CreateScene();
	test->AddObject(mod,  vec3( 0,   0,  0),   0);

	test->AddLight(point, vec3(0,0,0));

	//test->entities[0]->setScale(vec3(0.05,0.05,0.05));
	//test->entities[0]->setRotation(float(90.0), vec3(1,0,0));


	renderer->SetScene(test);
 	renderer->SetCamera();
	



	while(1)
	{	
				
				
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			if(msg.message == WM_QUIT)
				break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

		else
		{		
			

				if(GetKeyState(VK_LBUTTON) & 0x80) {
					 wait += weapon->StopTimer();
					 if(wait >= 400){
						test->AddObject(cone, test->camera->m_vPosition, 25);
						test->entities[test->entities.size()-1]->properties->rigidBody->applyCentralImpulse(600*btVector3(test->camera->m_vView.x - test->camera->m_vPosition.x , test->camera->m_vView.y - test->camera->m_vPosition.y, test->camera->m_vView.z - test->camera->m_vPosition.z));
						test->entities.back()->properties->rigidBody->setAngularVelocity(btVector3(0,0,36));
						
						quat tmp = toQuat(inverse(test->camera->viewMat));
					    //angles = eulerAngles(tmp);
						//angles /= 3.1415;
						//angles *= 180.0;
						
						//btQuaternion tmpQuat(angles.y, angles.z, angles.x);
						btQuaternion tmpQuat(0, tmp.y, 0, tmp.w);
						btVector3 tmpVec(test->entities.back()->position.x, test->entities.back()->position.y, test->entities.back()->position.z);
						test->entities.back()->properties->rigidBody->setWorldTransform(btTransform( tmpQuat, tmpVec ));
						//test->entities.back()->properties->rigidBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
						
						wait = 0;
					 }
					 weapon->StartTimer();
				}

				if(GetAsyncKeyState(VK_UP)){
					vec3 pio = vec3(test->camera->m_vView - test->camera->m_vPosition);
					btVector3 dir(pio.x, pio.y, pio.z);
					test->cameraCapsule->setLinearVelocity(30*dir);
					//test->cameraCapsule->getL
					//test->cameraCapsule->setFriction(10);

				}

				if(GetAsyncKeyState(VK_DOWN)){
					vec3 pio = vec3(test->camera->m_vView - test->camera->m_vPosition);
					btVector3 dir(pio.x, pio.y, pio.z);
					test->cameraCapsule->setLinearVelocity(-30*dir);
				}

				if(GetAsyncKeyState(VK_RIGHT)){
					vec3 pio = vec3(test->camera->m_vView - test->camera->m_vPosition);
					vec3 poi = cross(pio, test->camera->m_vUpVector);
					btVector3 dir(poi.x, poi.y, poi.z);
					test->cameraCapsule->setLinearVelocity(30*dir);
				}

				if(GetAsyncKeyState(VK_LEFT)){
					vec3 pio = vec3(test->camera->m_vView - test->camera->m_vPosition);
					vec3 poi = cross(pio, test->camera->m_vUpVector);
					btVector3 dir(poi.x, poi.y, poi.z);
					test->cameraCapsule->setLinearVelocity(-30*dir);
				}

				if( !( GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) ) ){
					btVector3 pom = test->cameraCapsule->getLinearVelocity();
					pom.setX(0);
					pom.setZ(0);

					test->cameraCapsule->setLinearVelocity(pom);
				}

				test->UpdateScene();
				renderer->RenderScene(test);		

				SwapBuffers(g_hDC);
				
        }
	}


	
	DeInit();
 
	return(msg.wParam);
}
 

LRESULT CALLBACK WinProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG    lRet = 0;
    PAINTSTRUCT    ps;
 
    switch (uMsg)
	{
    case WM_SIZE:		// Если изменён размер окна
 
		SizeOpenGLScreen(LOWORD(lParam),HIWORD(lParam));
		GetClientRect(hWnd, &g_rRect);		
        break;
 
	case WM_PAINT:		
		BeginPaint(hWnd, &ps);	
		EndPaint(hWnd, &ps);	
		break;
 
	case WM_KEYDOWN:	
				
		switch(wParam)
		{
			case VK_ESCAPE:		
				PostQuitMessage(0);	
				break;
			case 0x42:
				break;

		}
		break;
 
    case WM_CLOSE:		
        PostQuitMessage(0);	
        break;
 
    default:		
        lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
        break;
    //case WM_LBUTTONDOWN:                   


    }

 
    return lRet;
}
