#ifndef RESOURCESH
#define RESOURCESH
#include <map>
#include <string>
#include "../Rendering/MeshTexture.h"
#include "../Rendering/RawMesh.h"

/* SINGLETON */
class Resources
{
public:

	Resources();
	virtual ~Resources();

	static void addMeshTexture(const std::string& filename, const MeshTexture* meshTexture);
	static void addRawMesh(const std::string& filename, const RawMesh* rawMesh);
	static const MeshTexture* getMeshTexture(const std::string& filename);
	static const RawMesh* getRawMesh(const std::string& filename);

	static void clearResources();

private:
	static std::map<std::string, const MeshTexture*> p_textureMap;
	static std::map<std::string, const RawMesh*> p_rawMap;


};





#endif
