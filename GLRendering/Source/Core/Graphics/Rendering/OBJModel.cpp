#include "OBJModel.h"
#include "../Setup/MeshLoaderSingleton.h"
#include "../Resource/Resources.h"
#include "../../Vendor/SpdLog/Log.h"
OBJModel::OBJModel(const std::string & objFile, const std::string & textureFile)
{

	this->p_rawMesh = Resources::getRawMesh(objFile);

	if (this->p_rawMesh == nullptr) 
	{
		LOG_INFO("(Raw mesh) {0} added to resources", objFile.c_str());
		parser = new ParserOBJ();
		parser->loadFromFile("Resources/Models/" + objFile);


		this->p_rawMesh = MeshLoaderSingleton::Loader.createRawMesh(
			parser->getVertices(), parser->getTextureCoordinates(),
			parser->getNormals(), parser->getIndices()
		);
		delete this->parser;
		Resources::addRawMesh(objFile, this->p_rawMesh);
	}

	this->p_meshTexture = Resources::getMeshTexture(textureFile);
	
	if (this->p_meshTexture == nullptr)
	{
		// Debug
		LOG_INFO("(Mesh texture) {0} added to resources", textureFile.c_str());
		this->p_meshTexture = MeshLoaderSingleton::Loader.createMeshTexture("Resources/Textures/" + textureFile);
		Resources::addMeshTexture(textureFile, this->p_meshTexture);
	}

}

OBJModel::~OBJModel()
{
	
}

const RawMesh * OBJModel::rawMesh() const
{
	return this->p_rawMesh;
}

const MeshTexture * OBJModel::meshTexture() const
{
	return this->p_meshTexture;
}

bool operator==(const OBJModel& m1, const OBJModel& m2)
{
	if (m1.p_meshTexture->getTextureID() == m2.p_meshTexture->getTextureID()
		&& m1.p_rawMesh->getVAO() == m2.p_rawMesh->getVAO())
	{
		return true;
	}

	return false;
}