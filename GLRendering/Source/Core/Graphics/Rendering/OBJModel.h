#ifndef OBJMODELH
#define OBJMODELH
#include "../Setup/MeshLoader.h"
#include "MeshTexture.h"
#include "RawMesh.h"
#include "../../Parser/ParserOBJ.h"
class OBJModel {

private:
	RawMesh* p_rawMesh;
	MeshTexture* p_meshTexture;
	ParserOBJ* parser;
public:
	
	OBJModel() = delete;
	OBJModel(const OBJModel& object) = delete;
	OBJModel(const std::string& objFile, const std::string& textureFile, MeshLoader* meshLoader);
	virtual ~OBJModel();

	const RawMesh* rawMesh() const;
	const MeshTexture* meshTexture() const;


};


#endif
