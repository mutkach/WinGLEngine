#ifndef RENDERER_H
#define RENDERER_H


#include "framebuffer.h"
#include "shader.h"
#include "texture.h"
#include "font.h"
#include "camera.h"
#include "timer.h"
#include "skybox.h"
#include "object.h"
#include "light.h"
#include "entity.h"
#include "scene.h"


//#include "vertex.h"
//#include "mesh.h"
//#include "material.h"

#define MAX_SPLITS 3

#define INSIDE 0
#define INTERSECT 1
#define OUTSIDE 2

#define OCTREE_MAX_OBJECTS 15
#define OCTREE_MAX_DEPTH 1
#define OCTREE_BASE_LENGTH 500


class Texture;
class DirLight;
class CTetxure;
class Light;
class Object;
class Shader;
class Octree;
class Sun;
class Framebuffer;
class Font;
class Skybox;
class Pento;
class Scene;
class Timer;
struct Entity;


class Renderer{

public:
	Renderer();
	
	Shader* base;
	Shader* geom;
	Shader* light;
	Shader* dirLight;
	Shader* downSample;
	Shader* bloom;
	Shader* fxaa;
	Shader* blurW;
	Shader* blurH;
	Shader* combine;
	Shader* ssao;
	Shader* textShader;
	Shader* skybox;
	Pento* myPento;

	Octree* octree;

	
	Framebuffer* GBuffer;
	Framebuffer* LightAccBuffer;
	Framebuffer* BlurBuffer;
	Framebuffer* ShadowBuffer;
	Framebuffer* SSAOBuffer;
	Framebuffer* FinalBuffer;


	Texture* noise;
	Texture* font;

	Skybox* Sky;
	//CTexture* TextureManager;
	

	Font* Consolas;

	Timer* myTimer;

	DirLight* Sun;

	CCamera* Camera;

	Object* quad;

	//Terrain* terrain;

	float theta;
	
	void RenderToScreen();
	void SetScene(Scene* _scene);
	void GeomPass();
	void StencilPass();
	void LightPass();
	void CombinePass();
	void ShadowPrePass();
	void DirLightPass();
	void DownsamplePass();
	void PostFXPass();
	void SSAOPass();
	
	
	void SetCamera();
	void Update();
	void RenderSkybox();
	void RenderScene(Scene* scene);
	//void OctreeCull(Octree* node);
	//int FrustumCull(vec3* bounds, vec4 *planes);



	mat4 MVP;
	mat4 VP;
	mat4 invMatrix;
	mat3 normalMatrix;
	
private:
	std :: vector < Entity* > *entities;
	std :: vector < Light* > *Lights;
	Scene* scene;
};

#endif
