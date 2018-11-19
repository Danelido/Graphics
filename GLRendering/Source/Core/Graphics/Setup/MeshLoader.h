#ifndef GLUPLOADH
#define GLUPLOADH
#include <vector>
#include <GL/glew.h>
#include "../Rendering/RawMesh.h"
#include "../Rendering/MeshTexture.h"
#include "../Vendor/stb_image.h"

class MeshLoader {
private:
	std::vector<GLuint*> p_vaos;
	std::vector<GLuint*> p_vbos;
	std::vector<GLuint*> p_textures;

private:
	/*Behind the scene functions*/
	GLuint createAndBindVAO();
	void bindIndices(const std::vector<GLuint>& indices);
	void storeDataInAttributeList(const GLuint& attribNum, const GLuint& dataPerVertex, const std::vector<GLfloat>& data);
	void unbindVAO();

public:
	MeshLoader();
	virtual ~MeshLoader();
	RawMesh* createRawMesh(const std::vector<GLfloat>& positionVec, const std::vector<GLfloat>& textureCoordinateVec,
		const std::vector<GLfloat>& normalVec, const std::vector<GLuint>& indicesVec);
	
	MeshTexture* createMeshTexture(const std::string& filename);

	

};

#endif
