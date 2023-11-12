#include <vector>
#include "Open_GL_Basics.h"
#include <GL/glew.h>
#include "glfw3.h" //Graphical usage
#include <iostream>

using namespace std;


struct vertex{
	GLfloat x, y, z, r, g, b, a, nx, ny, nz, s, t;
};

class Polygon
{
	public:
	Polygon(); //Create Polygon with no Vertexes as Default
	~Polygon();

	vertex get_Point(int index);
	void set_Point(int index, GLfloat X, GLfloat Y,GLfloat Z,GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat NX, GLfloat NY, GLfloat NZ, GLfloat S, GLfloat T);

	void ship_Polygon(GLint); //TODO Get this to work Might need to use VAO's to store every aspet of the vertex in seperate VBO's and Use that perhaps location may need to be multiplied by 4 to allow for 3 locations for the VBO's to be store in
	void draw_Polygon(GLenum);

	void output_Polygon();

	private:
	struct vertex vertexes[3];
	int NumofPoints = 3;
	int VertexSize = 12;
	GLuint vao , vbo;
};


Polygon::Polygon()
{}


Polygon::~Polygon()
{}

void Polygon::ship_Polygon(GLint vShader)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NumofPoints * VertexSize, vertexes, GL_DYNAMIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 12, 0);//Location LOCATION
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 12, 0);//COLOR LOCATION
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 12, 0);//Texture LOCATION
	glEnableVertexAttribArray(2);
	
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 12, 0);//Normal LOCATION
	glEnableVertexAttribArray(3);
	
	glBindVertexArray(0);

}


void Polygon::set_Point(int index, GLfloat X = 0, GLfloat Y = 0, GLfloat Z = 0, GLfloat R = 255, GLfloat G = 255, GLfloat B = 255, GLfloat A = 255, GLfloat NX = -1, GLfloat NY = -1, GLfloat NZ = -1, GLfloat S = 0, GLfloat T = 0)
{
	if(index <  NumofPoints && 0 <= index)
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
	cout <<"Vertex 1  X:"<<vertexes[0].x <<" Y: "<< vertexes[0].y << " Z: "<< vertexes[0].z <<endl;
	cout <<"Vertex 2  X:"<<vertexes[1].x <<" Y: "<< vertexes[1].y << " Z: "<< vertexes[1].z <<endl;
	cout <<"Vertex 3  X:"<<vertexes[2].x <<" Y: "<< vertexes[2].y << " Z: "<< vertexes[2].z <<endl;
}

// Equation for Perspective return x * (2 / (z - user_Z)); or return y * (2 / (z - user_Z));