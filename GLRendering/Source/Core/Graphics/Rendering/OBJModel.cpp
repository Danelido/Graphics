#include "OBJModel.h"


OBJModel::OBJModel(const std::string & objFile, const std::string & textureFile, MeshLoader * meshLoader)
{
	parser = new ParserOBJ();
	parser->loadFromFile("Resources/Models/" + objFile);

	this->p_rawMesh = meshLoader->createRawMesh(
		parser->getVertices(), parser->getTextureCoordinates(),
		parser->getNormals(), parser->getIndices()
	);

	this->p_meshTexture = meshLoader->createMeshTexture("Resources/Textures/" + textureFile);

}

OBJModel::~OBJModel()
{
	delete this->parser;
	delete this->p_rawMesh;
	delete this->p_meshTexture;
}

const RawMesh * OBJModel::rawMesh() const
{
	return this->p_rawMesh;
}

const MeshTexture * OBJModel::meshTexture() const
{
	return this->p_meshTexture;
}
