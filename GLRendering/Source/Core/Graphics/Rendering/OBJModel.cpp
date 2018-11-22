#include "OBJModel.h"
#include "../Setup/MeshLoaderSingleton.h"
#include "../Resource/Resources.h"

OBJModel::OBJModel(const std::string & objFile, const std::string & textureFile)
{

	this->p_rawMesh = Resources::getRawMesh(objFile);

	if (this->p_rawMesh == nullptr) 
	{
		// Debug
		printf("Added raw mesh to resources: %s\n", objFile.c_str());
		parser = new ParserOBJ();
		parser->loadFromFile("Resources/Models/" + objFile);

		this->p_rawMesh = MeshLoaderSingleton::Loader.createRawMesh(
			parser->getVertices(), parser->getTextureCoordinates(),
			parser->getNormals(), parser->getIndices()
		);

		Resources::addRawMesh(objFile, this->p_rawMesh);

	}

	this->p_meshTexture = Resources::getMeshTexture(textureFile);
	
	if (this->p_meshTexture == nullptr)
	{
		// Debug
		printf("Added mesh texture to resources: %s\n", textureFile.c_str());
		this->p_meshTexture = MeshLoaderSingleton::Loader.createMeshTexture("Resources/Textures/" + textureFile);
		Resources::addMeshTexture(textureFile, this->p_meshTexture);
	}

}

OBJModel::~OBJModel()
{
	delete this->parser;
}

const RawMesh * OBJModel::rawMesh() const
{
	return this->p_rawMesh;
}

const MeshTexture * OBJModel::meshTexture() const
{
	return this->p_meshTexture;
}
