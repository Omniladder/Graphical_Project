#include <vector>
#include "Open_GL_Basics.h"
#include <GL/glew.h>
#include "glfw3.h" //Graphical usage
#include <iostream>

using namespace std;


/*
	THIS CODE IS THE BACKEND STUFF AND NOT DESIGNED TO BE USED BY USER AS 
	THEIR IS A LOT OF REPEAT COORDINATES AND IT PROBABLY WONT BE READABLE
*/

struct vertex{
	GLfloat x, y, z, r, g, b, a, nx, ny, nz, s, t;
};

class Polygon
{
	public:
	Polygon();
	Polygon(int); //Create Polygon with no Vertexes as Default
	~Polygon();

	vertex get_Point(int index);
	void set_Point(int index, GLfloat X, GLfloat Y,GLfloat Z,GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat NX, GLfloat NY, GLfloat NZ, GLfloat S, GLfloat T);
	void set_Point(int, struct vertex);

	void changeSize(int);

	void bind_Polygon(GLint); //TODO Get this to work Might need to use VAO's to store every aspet of the vertex in seperate VBO's and Use that perhaps location may need to be multiplied by 4 to allow for 3 locations for the VBO's to be store in
	void draw_Polygon(GLenum);

	void output_Polygon(); //JUST FOR DEBUGGING IN FUTURE FOR NOW

	private:
	vector<struct vertex> vertexes;
	int NumofPoints; //HOW MANY VERTEXES THEIR ARE
	int VertexSize = 12; //HOW MANY DATA POINTS ARE IN EACH VERTEX
	GLuint vao , vbo;
};

Polygon::Polygon()
{
	NumofPoints = 0;
}

Polygon::Polygon(int size)
{
	NumofPoints = size;
	vertexes.reserve(size);
}


Polygon::~Polygon()
{}

void Polygon::changeSize(int newSize)
{
	NumofPoints = newSize;
	vertexes.reserve(NumofPoints);
}

vertex Polygon::get_Point(int index)
{return vertexes[index];}

void Polygon::bind_Polygon(GLint vShader)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NumofPoints * VertexSize, vertexes.data(), GL_DYNAMIC_DRAW);

	int dataSize = VertexSize * sizeof(GLfloat);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 12, 0);//Location LOCATION
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 12, (GLvoid *) (3 * sizeof(GLfloat)));//COLOR LOCATION
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 12, (GLvoid *) (7 * sizeof(GLfloat)));//Texture LOCATION
	glEnableVertexAttribArray(2);
	
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 12, (GLvoid *) (9 * sizeof(GLfloat)));//Normal LOCATION
	glEnableVertexAttribArray(3);
	
	glBindVertexArray(0);

}


void Polygon::set_Point(int index, GLfloat X = 0, GLfloat Y = 0, GLfloat Z = 0, GLfloat R = 255, GLfloat G = 255, GLfloat B = 255, GLfloat A = 255, GLfloat NX = -1, GLfloat NY = -1, GLfloat NZ = -1, GLfloat S = 0, GLfloat T = 0)
{
	vertexes[index].x = X;
	vertexes[index].y = Y;
	vertexes[index].z = Z;
	vertexes[index].r = R / 255;
	vertexes[index].g = G / 255;
	vertexes[index].b = B / 255;
	vertexes[index].a = A / 255;
	vertexes[index].nx = NX;
	vertexes[index].ny = NY;
	vertexes[index].nz = NZ;
	vertexes[index].s = S;
	vertexes[index].t = T;	
}

void Polygon::set_Point(int index, struct vertex newVertex)
{
	vertexes[index] = newVertex;
}

void Polygon::draw_Polygon(GLenum primitive)
{
	// Bind the vertex array and buffer
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Draw the triangle
	glDrawArrays(primitive, 0, NumofPoints);

	// Unbind VAO (optional but good practice)
	glBindVertexArray(0);
}

void Polygon::output_Polygon()
{
	for (int i = 0;  i < NumofPoints; i++)
	cout <<"Vertex " << i <<  " X: " <<vertexes[i].x <<" Y: "<< vertexes[i].y << " Z: "<< vertexes[i].z
	<< " R: "<< vertexes[i].r << " G: " << vertexes[i].g << " B: " << vertexes[i].b << endl;
}

// Equation for Perspective return x * (2 / (z - user_Z)); or return y * (2 / (z - user_Z));
