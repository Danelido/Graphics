#include "SkyBox.h"
#include "../../Parser/ParserOBJ.h"
#include "../Setup/MeshLoaderSingleton.h"
#include "GL/glew.h"
#include "../../Utils/CreateMatrix.h"
#include "GLFW/glfw3.h"
#include "../../Vendor/SpdLog/Log.h"
#include "../Resource/Resources.h"
SkyBox::SkyBox() :
	fogColor(0.f)
{	
	LOG_INFO("Creating skybox");
	ParserOBJ parser;
	parser.loadFromFile("Resources/Models/box.obj");
	p_rawCubeMap = MeshLoaderSingleton::Loader.createCubeMapRawMesh(parser.getVertices(), parser.getIndices());
	
	std::vector<std::string> files;
	files.emplace_back("Resources/Textures/skyboxes/night/Right.png");
	files.emplace_back("Resources/Textures/skyboxes/night/Left.png");
	files.emplace_back("Resources/Textures/skyboxes/night/Top.png");
	files.emplace_back("Resources/Textures/skyboxes/night/Bottom.png");
	files.emplace_back("Resources/Textures/skyboxes/night/Back.png");
	files.emplace_back("Resources/Textures/skyboxes/night/Front.png");
	p_cubeMapTexture = MeshLoaderSingleton::Loader.createCubeMapTexture(files);

	p_shader = new SkyBoxShader();
	p_shader->use();
	p_shader->setProjectionMatrix(CreateMatrix::PerspectiveProjectionMatrix(1280.f, 720.f, 0.1f, 5.f));
	p_shader->unuse();

}

SkyBox::~SkyBox()
{
	delete p_rawCubeMap;
	delete p_cubeMapTexture;
	delete p_shader;
}

void SkyBox::render(const Camera* camera)
{
	// use shader
	p_shader->use();

	glm::mat4 cubeView = glm::mat4(glm::mat3(CreateMatrix::viewMatrix(*camera)));
	glm::mat4 model = CreateMatrix::modelMatrix(glm::vec3(0.f), glm::vec3(0.f, 0.8f * glfwGetTime(), 0.f), 1.f);
	p_shader->setModelMatrix(model);
	p_shader->setViewMatrix(cubeView);
	p_shader->setFogColor(fogColor);
	glBindVertexArray(p_rawCubeMap->getVAO());
	glEnableVertexAttribArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, p_cubeMapTexture->getTextureID());
	glDrawElements(GL_TRIANGLES, p_rawCubeMap->getNumVertices(), GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(0);
	glBindVertexArray(NULL);
	// unuse shader
	p_shader->unuse();
}

void SkyBox::setFogColor(const glm::vec3& fogColor)
{
	this->fogColor = fogColor;
}