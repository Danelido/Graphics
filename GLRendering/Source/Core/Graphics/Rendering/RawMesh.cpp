#include "RawMesh.h"

RawMesh::RawMesh(const GLuint& vao, const GLuint& numVertices)
	: p_vao(vao), p_numVertices(numVertices)
{}

RawMesh::~RawMesh(){}

const GLuint& RawMesh::getVAO() const{
	return this->p_vao;
}
const GLuint& RawMesh::getNumVertices() const{
	return this->p_numVertices;
}