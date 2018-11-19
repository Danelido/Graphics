#ifndef MESHTEXTUREH
#define MESHTEXTUREH
#include <GL/glew.h>

class MeshTexture {
private:
	GLuint p_textureID;
	GLfloat p_shineDamper;
	GLfloat p_reflectivity;
	GLboolean p_useFakeLightning;
	GLboolean p_hasTransparency;

public:
	MeshTexture(const GLuint& textureID);
	virtual ~MeshTexture();

	void setShine(const GLfloat& shine);
	void setReflectivity(const GLfloat& reflectivity);
	void setUseFakeLightning(const GLboolean& fakeLightning);
	void setHasTransparency(const GLboolean& transparency);

	const GLuint& getTextureID() const;
	const GLfloat& getShine() const;
	const GLfloat& getReflectivity() const;
	const GLboolean& hasFakeLightning() const;
	const GLboolean& hasTransparency() const;

};



#endif
