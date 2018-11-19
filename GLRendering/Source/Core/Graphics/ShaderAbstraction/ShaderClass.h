#ifndef SHADERCLASSH
#define SHADERCLASSH
#include <GL/glew.h>
#include <string>

class ShaderClass {

private:
	GLuint p_program;

	bool errorReadingData(GLuint shader);
	std::string getDataFromFile(const char* filepath);
	void createProgramAndLinkShaders(const GLuint& vs, const GLuint& fs);

	GLuint createShader(GLenum shaderType, const char* data);
public:

	ShaderClass(){}
	virtual ~ShaderClass(){}
	bool loadShadersFromFile(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

	const GLuint& program() const;

	void use();
	void unuse();

};


#endif
