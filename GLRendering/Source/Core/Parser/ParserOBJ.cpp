#include "ParserOBJ.h"
#include <fstream>
#include <sstream>
#include <iostream>

constexpr auto INITIAL_CAPACITY = 1000;

ParserOBJ::ParserOBJ()
{
}

ParserOBJ::~ParserOBJ()
{
	p_vertices.clear();
	p_textureCoordinates.clear();
	p_normals.clear();
	p_indices.clear();
}

bool ParserOBJ::loadFromFile(const std::string & filename)
{
	

	// This is what will be filled during the reading
	std::vector<GLfloat> fillBuffer_vertices;				fillBuffer_vertices.reserve(INITIAL_CAPACITY);
	std::vector<GLfloat> fillBuffer_textureCoordinates;		fillBuffer_textureCoordinates.reserve(INITIAL_CAPACITY);
	std::vector<GLfloat> fillBuffer_normals;				fillBuffer_normals.reserve(INITIAL_CAPACITY);

	// This is what will be the actual buffers
	// these is being "sorted" when the parser
	// gets to the faces
	p_vertices.reserve(INITIAL_CAPACITY);
	p_textureCoordinates.reserve(INITIAL_CAPACITY);
	p_normals.reserve(INITIAL_CAPACITY);
	p_indices.reserve(INITIAL_CAPACITY);
	// Used for indices buffer
	GLuint iCounter = 0;

	std::ifstream file(filename);
	if (!file.is_open()){
		printf("Couldn't find file %s\n", filename.c_str());
		return false;
	}
	std::string line;

	while (std::getline(file, line)) {
		
		std::string type = getType(line);
		if (type == "v"){
			std::vector<std::string> attributes = split(line, ' ');

			GLfloat v1 = std::stof(attributes.at(1));
			GLfloat v2 = std::stof(attributes.at(2));
			GLfloat v3 = std::stof(attributes.at(3));
			
			fillBuffer_vertices.emplace_back(v1);
			fillBuffer_vertices.emplace_back(v2);
			fillBuffer_vertices.emplace_back(v3);
		}
		else if (type == "vt") {
			std::vector<std::string> attributes = split(line, ' ');

			GLfloat vt1 = std::stof(attributes.at(1));
			GLfloat vt2 = std::stof(attributes.at(2));
			
			fillBuffer_textureCoordinates.emplace_back(vt1);
			fillBuffer_textureCoordinates.emplace_back(vt2);
		}
		else if (type == "vn") {
			std::vector<std::string> attributes = split(line, ' ');
			
			GLfloat vn1 = std::stof(attributes.at(1));
			GLfloat vn2 = std::stof(attributes.at(2));
			GLfloat vn3 = std::stof(attributes.at(3));

			fillBuffer_normals.emplace_back(vn1);
			fillBuffer_normals.emplace_back(vn2);
			fillBuffer_normals.emplace_back(vn3);
		}
		else if (type == "f") {
			std::vector<std::string> attributes = split(line, ' ');
			std::vector<std::string> faces_v1 = split(attributes.at(1), '/');
			std::vector<std::string> faces_v2 = split(attributes.at(2), '/');
			std::vector<std::string> faces_v3 = split(attributes.at(3), '/');

			GLuint f1_1 = static_cast<GLuint>(std::stoi(faces_v1.at(0)));
			GLuint f1_2 = static_cast<GLuint>(std::stoi(faces_v1.at(1)));
			GLuint f1_3 = static_cast<GLuint>(std::stoi(faces_v1.at(2)));
			processFace(f1_1, f1_2, f1_3, iCounter, fillBuffer_vertices, fillBuffer_textureCoordinates, fillBuffer_normals);


			GLuint f2_1 = static_cast<GLuint>(std::stoi(faces_v2.at(0)));
			GLuint f2_2 = static_cast<GLuint>(std::stoi(faces_v2.at(1)));
			GLuint f2_3 = static_cast<GLuint>(std::stoi(faces_v2.at(2)));
			processFace(f2_1, f2_2, f2_3, iCounter, fillBuffer_vertices, fillBuffer_textureCoordinates, fillBuffer_normals);

			GLuint f3_1 = static_cast<GLuint>(std::stoi(faces_v3.at(0)));
			GLuint f3_2 = static_cast<GLuint>(std::stoi(faces_v3.at(1)));
			GLuint f3_3 = static_cast<GLuint>(std::stoi(faces_v3.at(2)));
			processFace(f3_1, f3_2, f3_3, iCounter, fillBuffer_vertices, fillBuffer_textureCoordinates, fillBuffer_normals);
			
		}


	}

	file.close();

#ifdef _DEBUG
	printf("Loaded obj file: %s\n", filename.c_str());
#endif
	fillBuffer_vertices.clear();
	fillBuffer_textureCoordinates.clear();
	fillBuffer_normals.clear();
	return true;
}

const std::vector<GLfloat>& ParserOBJ::getVertices() const
{
	return this->p_vertices;
}

const std::vector<GLuint>& ParserOBJ::getIndices() const
{
	return this->p_indices;
}

const std::vector<GLfloat>& ParserOBJ::getNormals() const
{
	return this->p_normals;
}
const std::vector<GLfloat>& ParserOBJ::getTextureCoordinates() const
{
	return this->p_textureCoordinates;
}

std::vector<std::string> ParserOBJ::split(const std::string& line, const char c)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(line);
	while (std::getline(tokenStream, token, c))
	{
		tokens.emplace_back(token);
	}
	return tokens;

}

std::string ParserOBJ::getType(const std::string& line)
{
	std::string token;
	std::istringstream tokenStream(line);
	std::getline(tokenStream, token, ' ');
	return token;

}

void ParserOBJ::processFace(GLuint f1, GLuint f2, GLuint f3, GLuint& iCounter,
							std::vector<GLfloat>&	FB_vertices,
							std::vector<GLfloat>&	FB_textureCoordinates,
							std::vector<GLfloat>&	FB_normals)
{
	p_indices.emplace_back(iCounter++);

	int vertexStartPos =	(f1 - 1) * 3;
	int textureStartPos =	(f2 - 1) * 2;
	int normalStartPos =	(f3 - 1) * 3;

	p_vertices.emplace_back(FB_vertices.at(vertexStartPos));
	p_vertices.emplace_back(FB_vertices.at(vertexStartPos + 1));
	p_vertices.emplace_back(FB_vertices.at(vertexStartPos + 2));

	p_textureCoordinates.emplace_back(FB_textureCoordinates.at(textureStartPos));
	p_textureCoordinates.emplace_back(FB_textureCoordinates.at(textureStartPos + 1));

	p_normals.emplace_back(FB_normals.at(normalStartPos));
	p_normals.emplace_back(FB_normals.at(normalStartPos + 1));
	p_normals.emplace_back(FB_normals.at(normalStartPos + 2));

}
