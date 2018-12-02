#include "Resources.h"
#include "../../Vendor/SpdLog/Log.h"

// Static initializing
std::map<std::string, const MeshTexture*> Resources::p_textureMap;
std::map<std::string, const RawMesh*> Resources::p_rawMap;

Resources::Resources()
{
	/*Empty*/
}

Resources::~Resources()
{
}

void Resources::addMeshTexture(const std::string & filename, const MeshTexture * meshTexture)
{
	p_textureMap[filename] = meshTexture;
}

void Resources::addRawMesh(const std::string & filename, const RawMesh * rawMesh)
{
	p_rawMap[filename] = rawMesh;
}

const MeshTexture * Resources::getMeshTexture(const std::string & filename)
{
	if (p_textureMap.find(filename) == p_textureMap.end())
	{
		LOG_WARNING("(Mesh texture) {0} is not stored in resources", filename.c_str());
		return nullptr;
	}
	return p_textureMap[filename];
}

const RawMesh * Resources::getRawMesh(const std::string & filename)
{
	if (p_rawMap.find(filename) == p_rawMap.end())
	{
		LOG_WARNING("(Raw mesh) {0} is not stored in resources", filename.c_str());
		return nullptr;
	}
	return p_rawMap[filename];
}

void Resources::clearResources()
{
	for (auto meshTex : p_textureMap) 
	{
		delete meshTex.second;
	}

	for (auto rawMesh : p_rawMap)
	{
		delete rawMesh.second;
	}

	p_textureMap.clear();
	p_rawMap.clear();
}
