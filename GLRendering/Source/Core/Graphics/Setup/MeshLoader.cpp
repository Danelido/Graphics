#include "MeshLoader.h"
#include <iostream>
MeshLoader::MeshLoader()
{

}

MeshLoader::~MeshLoader()
{
	for (auto &id : this->p_textures) {
		glDeleteTextures(1, id);
	}

	for (auto &id : this->p_vbos) {
		glDeleteBuffers(1, id);
	}

	for (auto &id : this->p_vaos) {
		glDeleteVertexArrays(1, id);
	}
}

GLuint MeshLoader::createAndBindVAO()
{
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	this->p_vaos.push_back(&VAO);

	return VAO;
}

void MeshLoader::bindIndices(const std::vector<GLuint>& indices)
{
	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// It's deleted the same way as the a VBO so it's all cool
	this->p_vbos.push_back(&IBO);
}

void MeshLoader::storeDataInAttributeList(const GLuint & attribNum, const GLuint & dataPerVertex, const std::vector<GLfloat>& data)
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribNum, dataPerVertex, GL_FLOAT, GL_FALSE, NULL, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	this->p_vbos.push_back(&VBO);
}

void MeshLoader::unbindVAO()
{
	glBindVertexArray(NULL);
}

RawMesh * MeshLoader::createRawMesh(const std::vector<GLfloat>& positionVec, const std::vector<GLfloat>& textureCoordinateVec, const std::vector<GLfloat>& normalVec, const std::vector<GLuint>& indicesVec)
{
	GLuint VAO = createAndBindVAO();
	bindIndices(indicesVec);
	storeDataInAttributeList(0, 3, positionVec);
	storeDataInAttributeList(1, 2, textureCoordinateVec);
	storeDataInAttributeList(2, 3, normalVec);
	unbindVAO();

	this->p_vaos.push_back(&VAO);
	
	RawMesh* mesh = new RawMesh(VAO, static_cast<GLuint>(indicesVec.size()));

	return mesh;
}

RawMesh* MeshLoader::createCubeMapRawMesh(const std::vector<GLfloat>& positionVec, const std::vector<GLuint>& indicesVec)
{
	GLuint VAO = createAndBindVAO();
	bindIndices(indicesVec);
	storeDataInAttributeList(0, 3, positionVec);
	unbindVAO();
	this->p_vaos.push_back(&VAO);

	RawMesh* mesh = new RawMesh(VAO, static_cast<GLuint>(indicesVec.size()));
	return mesh;
}


MeshTexture * MeshLoader::createMeshTexture(const std::string & filename)
{
	GLint width;
	GLint height;
	GLint channels;
	
	stbi_set_flip_vertically_on_load(0);
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);

	// load in texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);
	glBindTexture(GL_TEXTURE_2D, 0);

	this->p_textures.push_back(&textureID);

	MeshTexture* meshTexture = new MeshTexture(textureID);


	return meshTexture;
}


/*	IMPORTANT!
	LOAD TEXTURES TO THE CUBE MAP VECTOR IN THIS ORDER!!
	1. Right
	2. Left
	3. Top
	4. Bottom
	5. Back
	6. Front
*/
MeshTexture* MeshLoader::createCubeMapTexture(const std::vector<std::string> files)
{
	GLint width;
	GLint height;
	GLint channels;

	// load in texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	stbi_set_flip_vertically_on_load(0);
	
	for (size_t i = 0; i < files.size(); i++)
	{
		unsigned char* imageData = stbi_load(files.at(i).c_str(), &width, &height, &channels, STBI_rgb);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		stbi_image_free(imageData);
	}
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	this->p_textures.push_back(&textureID);
	MeshTexture* meshTexture = new MeshTexture(textureID);

	return meshTexture;
}