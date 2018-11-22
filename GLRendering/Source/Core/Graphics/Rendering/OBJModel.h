#ifndef OBJMODELH
#define OBJMODELH
#include "../Setup/MeshLoader.h"
#include "MeshTexture.h"
#include "RawMesh.h"
#include "../../Parser/ParserOBJ.h"
class OBJModel {

private:
	const RawMesh* p_rawMesh;
	const MeshTexture* p_meshTexture;
	ParserOBJ* parser;
public:
	
	OBJModel() = delete;
	OBJModel(const OBJModel& object) = delete;
	OBJModel(const std::string& objFile, const std::string& textureFile);
	virtual ~OBJModel();

	const RawMesh* rawMesh() const;
	const MeshTexture* meshTexture() const;


};


#endif
