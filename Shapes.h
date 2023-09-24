// Equation for Perspective return x * (2 / (z - user_Z)); or return y * (2 / (z - user_Z));

#include <vector>
#include "Open_GL_Basics.h"
#include <GL/glew.h>
#include "glfw3.h" //Graphical usage
#include <iostream>

using namespace std;
class Shape
{
	public:
	Shape(); //Create Shape with no Vertexes as Default
	Shape(int);//Create  Shape with set number of vertexes to speed up processes
	~Shape();
	
	

	void addCap(int); //Adds Capacity to the vertex vector for future usage
	int getNumPoints();

	GLfloat getPoint_X(int);
	GLfloat getPoint_Y(int);	
	GLfloat getPoint_Z(int);
	
	GLfloat getPoint_R(int);
	GLfloat getPoint_G(int);	
	GLfloat getPoint_B(int);
	GLfloat getPoint_A(int);

	GLfloat getPoint_Normal_X(int);
	GLfloat getPoint_Normal_Y(int);	
	GLfloat getPoint_Normal_Z(int);

	GLfloat getPoint_S(int);
	GLfloat getPoint_T(int);

	void add_Point(GLfloat X, GLfloat Y,GLfloat Z,GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat NX, GLfloat NY, GLfloat NZ, GLfloat S, GLfloat T);


	void set_X(int, GLfloat);
	void set_Y(int, GLfloat);
	void set_Z(int, GLfloat);

	void set_R(int, GLfloat);
	void set_G(int, GLfloat);
	void set_B(int, GLfloat);
	void set_A(int, GLfloat);

	void set_Normal_X(int, GLfloat);
	void set_Normal_Y(int, GLfloat);
	void set_Normal_Z(int, GLfloat);

	void set_S(int, GLfloat);
	void set_T(int, GLfloat);

	void ship_Shape(GLint); //TODO Get this to work Might need to use VAO's to store every aspet of the vertex in seperate VBO's and Use that perhaps location may need to be multiplied by 4 to allow for 3 locations for the VBO's to be store in
	unsigned int get_ID();
	
	private:
	vector<GLfloat> vertexes;
	int NumofPoints;
	int VertexSize = 12;
	unsigned int shape_location;
		
	bool ValidVertex(int); //Checks if the Vertex exists
};

static unsigned int num_of_Shapes = 0;

	Shape::Shape()
	{
	NumofPoints =0;
	shape_location = num_of_Shapes;
	num_of_Shapes++;
	}

	Shape::Shape(int Points)
	{
	NumofPoints = Points;
	addCap(Points);
	shape_location = num_of_Shapes;
	num_of_Shapes++;
	}

Shape::~Shape()
{

}

	void Shape::addCap(int newCapacity)
	{
	vertexes.reserve(vertexes.capacity() + newCapacity * VertexSize);
	}

	int Shape::getNumPoints()
	{
	return NumofPoints;
	}

	GLfloat Shape::getPoint_X(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize];
	else
	return -1;
	}

	GLfloat Shape::getPoint_Y(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize + 1];
	else
	return -1;
	}

	GLfloat Shape::getPoint_Z(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize + 2];
	else
	return -1;
	}

	GLfloat Shape::getPoint_R(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize + 3];
	else
	return -1;
	}

	GLfloat Shape::getPoint_G(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize + 4];
	else
	return -1;
	}

	GLfloat Shape::getPoint_B(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize + 5];
	else
	return -1;
	}

	GLfloat Shape::getPoint_A(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize + 6];
	else
	return -1;
	}	

	GLfloat Shape::getPoint_Normal_X(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize + 7];
	else
	return -1;
	}

	GLfloat Shape::getPoint_Normal_Y(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize + 8];
	else
	return -1;
	}

	GLfloat Shape::getPoint_Normal_Z(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize + 9];
	else
	return -1;
	}

	GLfloat Shape::getPoint_S(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize +10];
	else
	return -1;
	}

	GLfloat Shape::getPoint_T(int pointIndex)
	{
	if(ValidVertex(pointIndex))
	return vertexes[pointIndex * VertexSize + 11];
	else
	return -1;
	}

	void Shape::ship_Shape(GLint vShader)
	{


	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexes.capacity(), vertexes.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//Location LOCATION
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);//COLOR LOCATION
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);//Texture LOCATION
	glEnableVertexAttribArray(2);
	
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);//Normal LOCATION
	glEnableVertexAttribArray(3);
	
	glBindVertexArray(0);
	}


	bool Shape::ValidVertex(int pointIndex)
	{
	if(pointIndex > NumofPoints && 0 < pointIndex)
	{return true;}
	else
	{return false;}
	}

	void Shape::add_Point(GLfloat X = 0, GLfloat Y = 0, GLfloat Z = 0, GLfloat R = 255, GLfloat G = 255, GLfloat B = 255, GLfloat A = 255, GLfloat NX = -1, GLfloat NY = -1, GLfloat NZ = -1, GLfloat S = 0, GLfloat T = 0)
	{
	if(vertexes.size() > vertexes.capacity()-VertexSize)
	{
	addCap(1);
	}
	vertexes.push_back(X);
    vertexes.push_back(Y);
    vertexes.push_back(Z);
    vertexes.push_back(R);
    vertexes.push_back(G);
    vertexes.push_back(B);
    vertexes.push_back(A);
    vertexes.push_back(NX);
    vertexes.push_back(NY);
    vertexes.push_back(NZ);
    vertexes.push_back(S);
    vertexes.push_back(T);
	
	NumofPoints++;
	}



	void Shape::set_X(int point, GLfloat X)
	{
	if(point < NumofPoints)
	{
	vertexes[point*VertexSize] = X;
	}
	else
	{
		
	}
	}
	
	void Shape::set_Y(int point, GLfloat Y)
	{
	if(point < NumofPoints)
	{
	vertexes[point*VertexSize + 1] = Y;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}
	}

	void Shape::set_Z(int point, GLfloat Z)
	{
	if(point < NumofPoints)
	{
	vertexes[point * VertexSize + 2] = Z;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}
	}

	void Shape::set_R(int point, GLfloat R)
{
	if(point < NumofPoints)
	{
	vertexes[point * VertexSize + 3] = R;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}
}
	void Shape::set_G(int point, GLfloat G)
	{
	if(point < NumofPoints)
	{
	vertexes[point * VertexSize + 4] = G;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}
}
	void Shape::set_B(int point, GLfloat B)
{
if(point < NumofPoints)
	{
	vertexes[point * VertexSize + 5] = B;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}
}
	void Shape::set_A(int point, GLfloat A)
{
if(point < NumofPoints)
	{
		vertexes[point * VertexSize + 6] = A;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}
}

	void Shape::set_Normal_X(int point, GLfloat NX)
{
if(point < NumofPoints)
	{
	vertexes[point * VertexSize + 7] = NX;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}
}
	void Shape::set_Normal_Y(int point, GLfloat NY){
	if(point < NumofPoints)
	{
	vertexes[point * VertexSize + 8] = NY;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}
}
	void Shape::set_Normal_Z(int point, GLfloat NZ)
{
if(point < NumofPoints)
	{
	vertexes[point * VertexSize + 9] = NZ;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}
}
	void Shape::set_S(int point, GLfloat S)
{
if(point < NumofPoints)
	{
	vertexes[point * VertexSize + 10] = S;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}
}
	void Shape::set_T(int point, GLfloat T)
{
if(point < NumofPoints)
	{
	vertexes[point * VertexSize + 11] = T;
	}
	else
	{
	std::cout<<"CALLED INVALID POINT"<<endl;
	}	
}
