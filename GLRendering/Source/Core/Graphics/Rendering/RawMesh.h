#ifndef RAWMESHH
#define RAWMESHH
#include <GL/glew.h>

class RawMesh {

private:
	GLuint p_vao;
	GLuint p_numVertices;

public:

	RawMesh(const GLuint& vao, const GLuint& numVertices);
	virtual ~RawMesh();

	const GLuint& getVAO() const;
	const GLuint& getNumVertices() const;

};


#endif
