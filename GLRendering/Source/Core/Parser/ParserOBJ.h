#ifndef PARSEROBJH
#define PARSEROBJH
#include <vector>
#include <string>
#include <GL/glew.h>
#include "../Graphics//Rendering/RawMesh.h"

class ParserOBJ {
private:
	std::vector<GLfloat>	p_vertices;
	std::vector<GLuint>		p_indices;
	std::vector<GLfloat>	p_normals;
	std::vector<GLfloat>	p_textureCoordinates;
		
	std::vector<std::string> split(const std::string& line, const char c);
	std::string getType(const std::string& line);
	void processFace(GLuint f1, GLuint f2, GLuint f3, GLuint& iCounter,
		std::vector<GLfloat>& FB_vertices,
		std::vector<GLfloat>& FB_textureCoordinates, 
		std::vector<GLfloat>& FB_normals);


public:
	
	ParserOBJ();
	virtual ~ParserOBJ();
	bool loadFromFile(const std::string& filename);

	const std::vector<GLfloat>& getVertices() const;
	const std::vector<GLuint>& getIndices() const;
	const std::vector<GLfloat>& getNormals() const;
	const std::vector<GLfloat>& getTextureCoordinates() const;

};


#endif
