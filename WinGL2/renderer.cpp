#include "renderer.h"




void Renderer :: RenderToScreen(){


	myTimer->StartTimer();
	GeomPass();
	Consolas->CombinePushSequence("pass_geometry frametime..........%0.5f", myTimer->StopTimer());

	
	myTimer->StartTimer();
	//ShadowPrePass();
	Consolas->CombinePushSequence("pass_shadowPrePass frametime.....%0.5f", myTimer->StopTimer() );


	myTimer->StartTimer();
	SSAOPass();
	Consolas->CombinePushSequence("pass_SSAO frametime..............%0.5f", myTimer->StopTimer());


	
	
	myTimer->StartTimer();
	LightPass();
	DirLightPass();
	Consolas->CombinePushSequence("pass_light frametime.............%0.5f", myTimer->StopTimer());
	
	//DownsamplePass();
	CombinePass();
	PostFXPass();
	
	
	
}




Renderer :: Renderer(){
	

	 //-------------------------------------------------------------------------SHaders	

	 base = new Shader("shaders/defshading_null.vert", "shaders/defshading_null.frag");
		 base->setAttribute(0, "point");
		 base->setAttribute(1, "normal");
	 base->linkProgram();


	 geom = new Shader("shaders/defshading_geom.vert", "shaders/defshading_geom.frag");


		 geom->setFragData(0, "bufferColour");
		 geom->setFragData(1, "bufferNormal");


		 geom->setAttribute(0, "point");
		 geom->setAttribute(1, "normal");
		 geom->setAttribute(2, "texCoord");
		 geom->setAttribute(3, "tangent");


	 geom->linkProgram();


	 geom->bind();


		geom->passTexture(0, "baseImage");
		//geom->passTexture(1, "specMap");
		geom->passTexture(1, "normalMap");


	 geom->unbind();




	 light = new Shader("shaders/defshading_light.vert", "shaders/defshading_light.frag");
		 light->setFragData(0, "lightAccTex");
		 light->setAttribute(0, "point");
		 light->setAttribute(1, "normal");
	 light->linkProgram();
	 light->bind();
		 light->passTexture(0, "normalTex");
		 light->passTexture(1, "depthTex");
		 light->passUniform(g_rRect.right, "screenSizeW");
		 light->passUniform(g_rRect.bottom, "screenSizeH");
	 light->unbind();


	 dirLight = new Shader("shaders/defshading_dirlight.vert", "shaders/defshading_dirlight.frag");
		 dirLight->setFragData(0, "lightAccTex");

		 dirLight->setAttribute(0, "point");
		 dirLight->setAttribute(1, "normal");
	 dirLight->linkProgram();
	 dirLight->bind();
		 dirLight->passTexture(0, "normalTex");
		 dirLight->passTexture(1, "depthTex");
		 dirLight->passTexture(2, "shadowDepthTex");
		 dirLight->passUniform(g_rRect.right, "screenSizeW");
		 dirLight->passUniform(g_rRect.bottom, "screenSizeH");
	dirLight->unbind();




	fxaa = new Shader("shaders/post_fxaa.vert", "shaders/post_fxaa.frag");
		fxaa->setFragData(0, "endTex");
		fxaa->setAttribute(0, "point");
		fxaa->setAttribute(2, "texCoord");
	fxaa->linkProgram();
	fxaa->bind();
		fxaa->passTexture(0, "colourTex");
		fxaa->passUniform(g_rRect.right, "screenSizeW");
		fxaa->passUniform(g_rRect.bottom, "screenSizeH");
	fxaa->unbind();

	downSample = new Shader("shaders/post_downsample.vert", "shaders/post_downsample.frag");
		downSample->setFragData(0, "downsampledTex");

		downSample->setAttribute(0, "point");
		downSample->setAttribute(1, "normal");
		downSample->setAttribute(2, "texCoord");
	downSample->linkProgram();

	downSample->bind();
		downSample->passTexture(0, "lightAccTex");
		downSample->passUniform(g_rRect.right/2.0, "screenSizeW");
		downSample->passUniform(g_rRect.bottom/2.0, "screenSizeH");
	downSample->unbind();


	blurW = new Shader("shaders/post_blurW.vert", "shaders/post_blurW.frag");
		blurW->setFragData(0, "blurredWTex");
		downSample->setAttribute(0, "point");
		downSample->setAttribute(1, "normal");
		downSample->setAttribute(2, "texCoord");
	blurW->linkProgram();
	blurW->bind();
		blurW->passTexture(0, "downsampledTex");
		blurW->passUniform(g_rRect.right/2.0, "screenSizeW");
		blurW->passUniform(g_rRect.bottom/2.0, "screenSizeH");
	blurW->unbind();

	blurH = new Shader("shaders/post_blurH.vert", "shaders/post_blurH.frag");
		blurW->setFragData(0, "blurredHTex");
		downSample->setAttribute(0, "point");
		downSample->setAttribute(1, "normal");
		downSample->setAttribute(2, "texCoord");
	blurH->linkProgram();
	blurH->bind();
		blurH->passTexture(0, "blurredWTex");
		blurH->passUniform(g_rRect.right/2.0, "screenSizeW");
		blurH->passUniform(g_rRect.bottom/2.0, "screenSizeH");
	blurH->unbind(); 

	combine = new Shader("shaders/defshading_combine.vert", "shaders/defshading_combine.frag");
		combine->setFragData(0, "finalTex");
		combine->setAttribute(0, "point");
		combine->setAttribute(1, "normal");
		combine->setAttribute(2, "texCoord");
	combine->linkProgram();
	combine->bind();	
		combine->passTexture(0, "colourTex");
		combine->passTexture(1, "lightAccTex");
		combine->passTexture(2, "bloomTex");
		combine->passTexture(3, "ssaoTex");

	combine->unbind();


	ssao = new Shader("shaders/post_ssao.vert", "shaders/post_ssao.frag");
		ssao->setFragData(0, "occlusion");
		ssao->setAttribute(0, "point");
		ssao->setAttribute(1, "normal");
		ssao->setAttribute(2, "texCoord");
	ssao->linkProgram();
	ssao->bind();
		ssao->passTexture(0, "normalTex");
		ssao->passTexture(1, "depthTex");
		ssao->passTexture(2, "noiseTex");
		ssao->passUniform(g_rRect.right, "screenSizeW");
		ssao->passUniform(g_rRect.bottom, "screenSizeH");
	ssao->unbind();

	textShader = new Shader("shaders/post_text.vert", "shaders/post_text.frag");
		//textShader->setFragData(0, "final");
		textShader->setAttribute(0, "point");
		textShader->setAttribute(1, "texCoord");
	textShader->linkProgram();

	textShader->bind();
		textShader->passTexture(0, "text");
		textShader->passUniform(g_rRect.right, "screenSizeW");
		textShader->passUniform(g_rRect.bottom, "screenSizeH");
	textShader->unbind();

	skybox = new Shader("shaders/defshading_skybox.vert", "shaders/defshading_skybox.frag");
		skybox->setFragData(0, "bufferColour");
		skybox->setAttribute(0, "point");
		skybox->setAttribute(1, "normal");
		skybox->setAttribute(2, "texCoord");
	skybox->linkProgram();
	skybox->bind();
		skybox->passTexture(0, "skybox");
		skybox->passUniform(g_rRect.right, "screenSizeW");
		skybox->passUniform(g_rRect.bottom, "screenSizeH");
	skybox->unbind();
		
	
	
	//------------------------------------------------------------------Framebuffers

	quad = new Object("default/quad.dae", 0);	


	GBuffer = new Framebuffer(g_rRect.right, g_rRect.bottom, 2, GL_RGB8, 1);
	GBuffer->Init();


	
	LightAccBuffer = new Framebuffer(g_rRect.right, g_rRect.bottom, 1, GL_RGB8, 0);
	LightAccBuffer->Init();



	
	BlurBuffer = new Framebuffer( g_rRect.right/2.0, g_rRect.bottom/2.0,  2, GL_RGB8, 0);
	BlurBuffer->Init();

	ShadowBuffer = new Framebuffer(2048, 2048, 1, GL_R8, 3);
	ShadowBuffer->Init();

	SSAOBuffer = new Framebuffer(g_rRect.right, g_rRect.bottom, 1, GL_R8, 0);
	SSAOBuffer->Init();

	FinalBuffer = new Framebuffer(g_rRect.right, g_rRect.bottom, 1, GL_RGB8, 0);
	FinalBuffer->Init();



	


	//---------------------------------------------------------------Random tetxure

	noise = new Texture("default/textures/noise.bmp");
	noise->SetFiltering(false, GL_NEAREST, GL_NEAREST );
	//myPento = new Pento();
	


	Consolas = new Font("default/fonts/OCRA.ttf");
	myTimer = new Timer();

	Sun = new DirLight();


	Sky = new Skybox("default/skybox/Skybox360 002 Front +z.png", "default/skybox/Skybox360 002 Back -z.png",
					 "default/skybox/Skybox360 002 Right +x.png", "default/skybox/Skybox360 002 Left -x.png",
					 "default/skybox/Skybox360 002 Down -y.png", "default/skybox/Skybox360 002 Up +y.png");

	theta = 0;

	Sun->SetColour(vec3(0.8, 0.8, 0.9) );
	Sun->SetDirection( vec3(0.1, -1.0, 0) );

 

	
}

void Renderer :: SetScene(Scene* _scene){
	entities = &_scene->entities;
	Lights = &_scene->lights;
	Camera = _scene->camera;
	scene = _scene;

}


void Renderer :: SetCamera(){
	//Camera->SetCamera(0, 0, 0,
	//				  0, 0, 1,
	//				  0, 1, 0);
	//Camera->projectionMat = perspective<float>(55,(GLfloat)g_rRect.right/(GLfloat)g_rRect.bottom, Camera->zNear, Camera->zFar);
	mat4 invProjectionMatrix = inverse(Camera->projectionMat);
	mat4 Orth = ortho<float>(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	


	downSample->bind();
	downSample->passUniform(Orth, "orthMatrix");
	downSample->unbind();

	blurW->bind();
	blurW->passUniform(Orth, "orthMatrix");
	blurW->unbind();

	blurH->bind();
	blurH->passUniform(Orth, "orthMatrix");
	blurH->unbind();

	fxaa->bind();
	fxaa->passUniform(Orth, "orthMatrix");
	fxaa->unbind();

	char buffer[16][15];

	ssao->bind();
	ssao->passUniform(Orth, "orthMatrix");
	ssao->passUniform(invProjectionMatrix, "invProjectionMatrix");
	ssao->passUniform(Camera->VP, "VPMatrix");
	ssao->passUniform(Camera->projectionMat, "projectionMatrix");
	ssao->passUniform(Camera->zNear, "zNear");
	ssao->passUniform(Camera->zFar, "zFar");

	for(int i = 0; i < 16; ++i){
		sprintf(buffer[i], "kernel[%d]", i);

		vec3 randomVector =   vec3( ( (float) rand()/RAND_MAX + 0.1)*2.0 - 1.0,
								    ( (float) rand()/RAND_MAX + 0.1)*2.0 - 1.0,
								    ( (float) rand()/RAND_MAX + 0.1));//(float) rand()/RAND_MAX + 0.1 )*2.0 - 1.0
		randomVector = randomVector * ( (float) rand()/RAND_MAX );
		ssao->passUniform(randomVector, buffer[i]);
	}
	
	ssao->unbind();




}



void Renderer :: GeomPass(){

	int n = 0;

	GLenum bufs[]= {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	GBuffer->Bind();
	GBuffer->BindAttachments(2, bufs);
	GBuffer->Clear(GL_COLOR_BUFFER_BIT);


	GBuffer->BindAttachment(GL_COLOR_ATTACHMENT0);

	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

		RenderSkybox();

	
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	
//	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	GBuffer->BindAttachments(2, bufs);
	GBuffer->Clear(GL_DEPTH_BUFFER_BIT);
	 
	for(int i = 0; i < (*entities).size(); ++i){
		Object* ObjectInstance;
		ObjectInstance = (*entities)[i]->body;
		//if(FrustumCull(entities[i]->bounds, Camera->plane) == OUTSIDE ){	
			//	++n;
		    //	continue;
			//}

		/*
		if((*entities)[i]->currentOctreeVisibility <= 0){
			++n;
			(*entities)[i]->currentOctreeVisibility = (*entities)[i]->octreeVisibility;
			continue;
		}
		(*entities)[i]->currentOctreeVisibility = (*entities)[i]->octreeVisibility;
		if((*entities)[i]->properties->mass != 0)
			(*entities)[i]->octreeVisibility = 8;
		*/

		for(int j = 0; j < ObjectInstance->numOfMeshes; ++j){
			int diffuse, specular, normal;
			Mesh* MeshInstance;
			
			MeshInstance =  &ObjectInstance->mesh[j];
			
			
			
				
				diffuse = ObjectInstance->materials[MeshInstance->materialID].textureDiffuse->texID;
				//specular = ObjectInstance->materials[MeshInstance->materialID].textureSpecular->texID;
				normal = ObjectInstance->materials[MeshInstance->materialID].textureNormal->texID;
				
				glActiveTexture(GL_TEXTURE0);
				glBindTexture( GL_TEXTURE_2D, diffuse);
				//glActiveTexture(GL_TEXTURE1);
				//glBindTexture( GL_TEXTURE_2D, specular);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture( GL_TEXTURE_2D, normal);




			

				//Consolas->CombinePushSequence("position YYYYY...................%3.3f", (float)ObjectInstance->bounds[0].y );
				//MVP =  Sun->projectionMatrix[0] * Sun->viewMatrix[0] * entities[i]->transform;
				MVP = VP * (*entities)[i]->transform;
				normalMatrix = mat3( inverse(transpose(Camera->viewMat * (*entities)[i]->transform) ) ) ;
				
				geom->bind();
				

						geom->passUniform(MVP, "MVPMatrix");
						geom->passUniform(normalMatrix, "normalMatrix");
						geom->passUniform(Camera->viewMat, "viewMatrix");		
						MeshInstance->RenderMesh();


				geom->unbind();

		}

	}

	Consolas->CombinePushSequence("objects culled...................%d", n);
	
	glDepthMask(GL_FALSE);	

	GBuffer->Unbind();

	
	
}



void Renderer :: ShadowPrePass(){

int n = 0;


ShadowBuffer->Bind();
ShadowBuffer->BindAttachment(GL_NONE);
glDepthMask(GL_TRUE);
glEnable(GL_CULL_FACE);
glCullFace(GL_FRONT);
for(int k = 0; k < MAX_SPLITS; ++k){

	ShadowBuffer->BindDepthAttachment(k);
	glClear (GL_DEPTH_BUFFER_BIT);
	Sun->UpdateShadowMatrix(invMatrix, k);

	for(int i = 0; i < (*entities).size(); ++i){
			Object* ObjectInstance;
			ObjectInstance = (*entities)[i]->body;
			for(int j = 0; j < ObjectInstance->numOfMeshes; ++j){
				Mesh* MeshInstance;
				MeshInstance =  &ObjectInstance->mesh[j];
				//if( FrustumCull((*entities)[i]->bounds, Sun->plane[k]) == OUTSIDE){
				//	++n;
				//	continue;					
				//}

				Sun->MVP[k] = Sun->projectionMatrix[k] * Sun->viewMatrix[k] * (*entities)[i]->transform;

				base->bind();
				base->passUniform(Sun->MVP[k], "MVPMatrix");
					
						
						MeshInstance->RenderMesh();
				base->unbind();
	
				
			
			}

	}

}

Consolas->CombinePushSequence("objects culled...................%d", n);
ShadowBuffer->Unbind();

glDepthMask(GL_FALSE);	 
}



void Renderer :: LightPass(){
	/*
	 glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	 glViewport(0,0, g_rRect.right, g_rRect.bottom);
	 glClear(GL_COLOR_BUFFER_BIT);
	 */
	 
	LightAccBuffer->Bind();
	LightAccBuffer->BindAttachment(GL_COLOR_ATTACHMENT0);
	LightAccBuffer->Clear(GL_COLOR_BUFFER_BIT);
	

    glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

	glActiveTexture(GL_TEXTURE0);	
	glBindTexture(GL_TEXTURE_2D, GBuffer->textures[NORMAL]);
	glActiveTexture(GL_TEXTURE1);	
	glBindTexture(GL_TEXTURE_2D, GBuffer->textures[2]);


	
	for(int i = 0; i < (*Lights).size(); ++i){
		Light* LightInstance;
		LightInstance = (*Lights)[i];
		
		MVP = VP * LightInstance->transform;
		normalMatrix = mat3( inverse(transpose(Camera->viewMat * LightInstance->transform) ) ) ;

		light->bind();
		light->passUniform(MVP, "MVPMatrix");
		light->passUniform(invMatrix, "invMatrix");
		light->passUniform(normalMatrix, "normalMatrix");

		light->passUniform(LightInstance->position, "lightPosition");
		light->passUniform(LightInstance->colour, "lightColour");
		light->passUniform(LightInstance->radius, "lightRadius");

		LightInstance->type->mesh[0].RenderMesh();
		light->unbind();

	}

	glDisable(GL_BLEND);
	LightAccBuffer->Unbind();
}



void Renderer :: SSAOPass(){
	SSAOBuffer->Bind();
	SSAOBuffer->BindAttachment(GL_COLOR_ATTACHMENT0);
	SSAOBuffer->Clear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GBuffer->textures[NORMAL]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, GBuffer->textures[2]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, noise->texID);

	ssao->bind();
	ssao->passUniform(invMatrix, "invMatrix");


	quad->mesh[0].RenderMesh();

	ssao->bind();
	SSAOBuffer->Unbind();
	glDisable(GL_BLEND);
}



void Renderer :: DirLightPass(){

	LightAccBuffer->Bind();
	LightAccBuffer->BindAttachment(GL_COLOR_ATTACHMENT0);
	
	glActiveTexture(GL_TEXTURE0);	
	glBindTexture(GL_TEXTURE_2D, GBuffer->textures[NORMAL]);
	glActiveTexture(GL_TEXTURE1);	
	glBindTexture(GL_TEXTURE_2D, GBuffer->textures[2]);
	glActiveTexture(GL_TEXTURE2);	
	glBindTexture(GL_TEXTURE_2D_ARRAY, ShadowBuffer->textures[1]);

	glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	vec3 direction = vec3(Camera->viewMat * vec4(Sun->direction, 0.0) );

	mat4 bias = mat4 ( 0.5, 0.0, 0.0, 0.0,
					   0.0, 0.5, 0.0, 0.0,
		               0.0, 0.0, 0.5, 0.0,
		               0.5, 0.5, 0.5, 1.0);

	mat4 nearShadowMVP = bias * Sun->projectionMatrix[0] * Sun->viewMatrix[0];
	mat4 mediumShadowMVP = bias * Sun->projectionMatrix[1] * Sun->viewMatrix[1]; 
	mat4 farShadowMVP = bias * Sun->projectionMatrix[2] * Sun->viewMatrix[2]; 
	
	dirLight->bind();
		
		dirLight->passUniform(Camera->zNear, "zNear");
	    dirLight->passUniform(Camera->zFar, "zFar");
		dirLight->passUniform(Sun->colour, "lightColour");
		dirLight->passUniform(direction, "lightDirection");

		dirLight->passUniform(invMatrix, "invMatrix");
		
		dirLight->passUniform(nearShadowMVP, "shadowNearMVPMatrix");
		dirLight->passUniform(mediumShadowMVP, "shadowMediumMVPMatrix");
		dirLight->passUniform(farShadowMVP, "shadowFarMVPMatrix");

		quad->mesh[0].RenderMesh();

	dirLight->unbind();

	glDisable(GL_BLEND);
	LightAccBuffer->Unbind();

}



void Renderer :: DownsamplePass(){

	BlurBuffer->Bind();
	BlurBuffer->BindAttachment(GL_COLOR_ATTACHMENT0);
	BlurBuffer->Clear(GL_COLOR_BUFFER_BIT);
	
	glDepthMask(GL_FALSE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, LightAccBuffer->textures[0]);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	downSample->bind();

		quad->mesh[0].RenderMesh();

	downSample->unbind();
	
	/*
    BlurBuffer->BindAttachment(GL_COLOR_ATTACHMENT1);
	BlurBuffer->Clear(GL_COLOR_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BlurBuffer->textures[0]);
	//BlurBuffer->Clear(GL_COLOR_ATTACHMENT1, GL_COLOR_BUFFER_BIT);

	blurW->bind();
		quad->mesh[0].RenderMesh();
	blurW->unbind();


	BlurBuffer->BindAttachment(GL_COLOR_ATTACHMENT0);
	BlurBuffer->Clear(GL_COLOR_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, BlurBuffer->textures[1]);

	blurH->bind();

		quad->mesh[0].RenderMesh();
    
	blurH->unbind();

	
	*/
	BlurBuffer->Unbind();
	
	
}




void Renderer :: CombinePass(){
	/*
	 glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	 glViewport(0,0, g_rRect.right, g_rRect.bottom);
	 //glClear(GL_COLOR_BUFFER_BIT);
	 */
	FinalBuffer->Bind();
	FinalBuffer->BindAttachment(GL_COLOR_ATTACHMENT0);
	glViewport(0,0, g_rRect.right, g_rRect.bottom);
	


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GBuffer->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, LightAccBuffer->textures[0]);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, BlurBuffer->textures[0]);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, SSAOBuffer->textures[0]);


	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	
	
	
	combine->bind();
		
		quad->mesh[0].RenderMesh();
	
	combine->unbind();
	

	
	//glUseProgram(0);
	//glDisable(GL_BLEND);
	FinalBuffer->Unbind();
}


void Renderer :: PostFXPass(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//1 glBindFramebuffer(GL_DRAW_FRAMEBUFFER, bufferFBO);
	//1 glDrawBuffer(GL_COLOR_ATTACHMENT3);
	
	glViewport(0,0, g_rRect.right, g_rRect.bottom);
	glClear(GL_COLOR_BUFFER_BIT);
	
	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, FinalBuffer->textures[0]);

	
	fxaa->bind();
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	quad->mesh[0].RenderMesh();
	fxaa->unbind();

	textShader->bind();
		Consolas->RenderSequence();
		//Consolas->RenderText("frame time:", -0.95, 0.9, 2.0/g_rRect.right, 2.0/g_rRect.bottom);
	textShader->unbind();

	
}



void Renderer :: Update(){

	//Camera->Update(); 	
	
	//myPento->UpdateSimulation();
	//for(int i = 0; i < entities.size(); ++i){
	//	entities[i]->UpdateTransform();
	//}
	invMatrix = inverse(Camera->projectionMat * Camera->viewMat);
	VP = Camera->VP; 
	theta += 0.008; 
	Consolas->CombinePushSequence("ViewDir (XYZ) .......... %0.3f, %0.3f, %0.3f", Camera->m_vView.x - Camera->m_vPosition.x , Camera->m_vView.y - Camera->m_vPosition.y, Camera->m_vView.z - Camera->m_vPosition.z) ;
	Consolas->CombinePushSequence("Position (XYZ) ......... %3.3f, %3.3f, %3.3f", Camera->m_vPosition.x , Camera->m_vPosition.y, Camera->m_vPosition.z) ;
	
	//Sun->SetDirection( vec3( cos(theta/4.0), sin(theta/4.0), 0 ) );	


	


}


void Renderer :: RenderScene(Scene* scene){
	Update();
	
	RenderToScreen();
}




void Renderer :: RenderSkybox(){
	
	vec3 currentPosition = Camera->m_vPosition;
	vec3 direction[6];
	direction[0] =   vec3(   0,   0,-500);
	direction[1] =   vec3(   0,   0, 500);
	direction[2] =   vec3(-500,   0,   0);
	direction[3] =   vec3( 500,   0,   0);
	direction[4] =   vec3(   0,-500,   0);
	direction[5] =   vec3(   0, 500,   0);


	mat4 transform;
	mat4 rotation;
	skybox->bind();

	for(int i = 0; i < 6; ++i){

		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, Sky->textures[i]);
		if(i == 1)
		rotation = rotate(float(-180),vec3(0, 1, 0) );
		if(i == 2)
		rotation = rotate(float( 90), vec3(0, 1, 0) );
		if(i == 3)
		rotation = rotate(float(-90), vec3(0, 1, 0) ); // Коряво. Сохранить заранее.
		if(i == 4)
		rotation = rotate(float(-90), vec3(1, 0, 0) );
		if(i == 5)
		rotation = rotate(float( 90), vec3(1, 0, 0) );
		
		transform = translate(currentPosition + direction[i]) * rotation * scale(vec3(500, 500, 500) );
		MVP = VP * transform;
		
			skybox->passUniform(MVP, "MVPMatrix");
			quad->mesh[0].RenderMesh();
			



	}

	skybox->unbind();



}
