#include <vector>
#include "Open_GL_Basics.h"
#include <GL/glew.h>
#include "glfw3.h" //Graphical usage
#include <iostream>
#include "Polygons.h"

struct edge
{
	struct vertex vertex1, vertex2;
};

class Shape{

	public:
	Shape(int);
	~Shape();

	void setVertex(int, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat,GLfloat,GLfloat, GLfloat, GLfloat, GLfloat); // Index, X value, Y value
	void setVertex(int, struct vertex);
	struct vertex getVertex(int); //Index
	struct edge getSide(int); //Index

	void bindShape(GLint);	
	void drawShape(GLenum);

	private:

	void triangulate();

	int numSides;
	Polygon* triangles; //Dynamically Allocated Polygon Array
	struct edge* sides;
	struct vertex* points;
};

Shape::Shape(int size)
{
	numSides = size;
	triangles = new Polygon[size - 2];
	sides = new struct edge[size];
	points = new struct vertex[size];
}

Shape::~Shape()
{
	delete[] triangles;
	delete[] sides;
}

void Shape::setVertex(int index, GLfloat X = 0, GLfloat Y = 0, GLfloat Z = 0, GLfloat R = 255, GLfloat G = 255, GLfloat B = 255, GLfloat A = 255, GLfloat NX = -1, GLfloat NY = -1, GLfloat NZ = -1, GLfloat S = 0, GLfloat T = 0)
{
	if (index < 0 || index >= numSides)
	{
		printf("INVALID INDEX\n");
		return;
	}
	
	struct vertex newVertex;

	newVertex.x = X;
	newVertex.y = Y;
	newVertex.z = Z;
	newVertex.r = R / 255;
	newVertex.g = G / 255;
	newVertex.b = B / 255;
	newVertex.a = A / 255;
	newVertex.nx = NX;
	newVertex.ny = NY;
	newVertex.nz = NZ;
	newVertex.s = S;
	newVertex.t = T;

	sides[index].vertex2 = newVertex;
	sides[(index + 1) % numSides].vertex1 = newVertex;

	points[index] = newVertex;
}
void Shape::setVertex(int index, struct vertex newVertex)
{
	if (index < 0 || index >= numSides)
	{
		printf("INVALID INDEX\n");
		return;
	}

	sides[index].vertex2 = newVertex;
	sides[(index + 1) % numSides].vertex1 = newVertex;

	points[index] = newVertex;
}

struct vertex Shape::getVertex(int index)
{
	if (index < 0 || index >= numSides)
	{
		printf("INVALID INDEX\n");
		return points[0];
	}
	return points[index];
}


struct edge Shape::getSide(int index)
{
	if (index < 0 || index >= numSides)
	{
		printf("INVALID INDEX\n");
		return sides[0];
	}
	return sides[index];
}

void Shape::bindShape(GLint vShader)
{
	triangulate();

	for (int i = 0; i < numSides - 2; i++)
	{
		triangles[i].bind_Polygon(vShader);
	}
}

void Shape::drawShape(GLenum primitive)
{
	for (int i = 0 ; i < numSides - 2; i++)
	{
		triangles[i].draw_Polygon(primitive);
	}
}

void Shape::triangulate()
{
	for (int i = 0;  i < 3; i++)
	triangles[0].set_Point(i, points[i]);
}
