#ifndef SKYBOX_H
#define SKYBOX_H
#include "MeshTexture.h"
#include "RawMesh.h"
#include "../Shaders/SkyBoxShader.h"
#include "../../Camera/Camera.h"

class SkyBox
{
private:
	MeshTexture* p_cubeMapTexture;
	RawMesh* p_rawCubeMap;
	SkyBoxShader* p_shader;
	glm::vec3 fogColor;

	float rotationVal;
public:
	SkyBox();
	virtual ~SkyBox();
	void render(const Camera* camera);


	void setFogColor(const glm::vec3& fogColor);
};


#endif
