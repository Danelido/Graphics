#include "MeshTexture.h"

MeshTexture::MeshTexture(const GLuint & textureID)
{
	this->p_textureID = textureID;
	this->p_shineDamper = 0.5f;
	this->p_reflectivity = 0.f;
	this->p_hasTransparency = false;
	this->p_useFakeLightning = false;
}

MeshTexture::~MeshTexture()
{
}

void MeshTexture::setShine(const GLfloat & shine)
{
	this->p_shineDamper = shine;
}

void MeshTexture::setReflectivity(const GLfloat & reflectivity)
{
	this->p_reflectivity = reflectivity;
}

void MeshTexture::setUseFakeLightning(const GLboolean & fakeLightning)
{
	this->p_useFakeLightning = fakeLightning;
}

void MeshTexture::setHasTransparency(const GLboolean & transparency)
{
	this->p_hasTransparency = transparency;
}

const GLuint & MeshTexture::getTextureID() const
{
	return this->p_textureID;
}

const GLfloat & MeshTexture::getShine() const
{
	return this->p_shineDamper;
}

const GLfloat & MeshTexture::getReflectivity() const
{
	return this->p_reflectivity;
}

const GLboolean & MeshTexture::hasFakeLightning() const
{
	return this->p_useFakeLightning;
}

const GLboolean & MeshTexture::hasTransparency() const
{
	return this->p_hasTransparency;
}
