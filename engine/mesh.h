#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include "glm\glm.hpp"
#include <string>
#include <vector>
#include "obj_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal, const glm::vec3& color)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
		this->color = color;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }
	glm::vec3* GetColor() { return &color; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
	glm::vec3 color;
};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB,
	COLOR_VB
};

class Mesh
{
public:
    Mesh(const std::string& fileName);
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	virtual void Draw();

	virtual ~Mesh();
protected:
private:
	static const unsigned int NUM_BUFFERS = 5;
	void operator=(const Mesh& mesh) {}
	Mesh(const Mesh& mesh) {}

	virtual void InitMesh(const IndexedModel& model);

	unsigned int m_vertexArrayObject;
	unsigned int m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_numIndices;
};

#endif
