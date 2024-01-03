
#define STB_IMAGE_IMPLEMENTATION  //Stops stb from importing extra stuff

#include <vector>
#include "Open_GL_Basics.h"
#include <GL/glew.h>
#include "thirdParty/glfw3.h" //Graphical usage
#include "thirdParty/stb_image.h" //Used for importing textures
#include <iostream>

using namespace std;


/*
	THIS CODE IS THE BACKEND STUFF AND NOT DESIGNED TO BE USED BY USER AS 
	THEIR IS A LOT OF REPEAT COORDINATES AND IT PROBABLY WONT BE READABLE
*/

struct vertex{
	GLfloat x, y, z, r, g, b, a, s, t, nx, ny, nz;
};

class Polygon
{
	public:
	Polygon();
	Polygon(int); //Create Polygon with no Vertexes as Default
	~Polygon();

	vertex get_Point(int index);
	void set_Point(int index, GLfloat X, GLfloat Y,GLfloat Z,GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat NX, GLfloat NY, GLfloat NZ);
	void set_Point(int, struct vertex);

	void setTexture(string); // Used to set a texture Input String name

	void changeSize(int); //

	void bind_Polygon(GLint);
	void draw_Polygon(GLenum);

	void output_Polygon(); //JUST FOR DEBUGGING IN FUTURE FOR NOW

	private:
	
	void calculateTextureCoords();

	vector<struct vertex> vertexes;
	int NumofPoints; //HOW MANY VERTEXES THEIR ARE
	int VertexSize = 12; //HOW MANY DATA POINTS ARE IN EACH VERTEX
	GLuint vao , vbo;
	string textureData;
	bool textureSet;
	int textLength, textHeight, numChannels; //Texture Data Stuff
};

Polygon::Polygon()
{
	NumofPoints = 0;
	textureSet = false;
}

Polygon::Polygon(int size)
{
	NumofPoints = size;
	vertexes.reserve(size);
	textureSet = false;
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
	calculateTextureCoords(); //Sets texture coordinates to their proper place on the shape
	
	stbi_set_flip_vertically_on_load(true);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	unsigned int texture;//Stores the texture ID	
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
    
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //This is used for setting how a texture works
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); //Currently set to GL_MIRRORED_REPEAT by default might add avility to change in future
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //ONCE AGAIN NOT SURE ABOUT MINMAPPING YET
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data;

	if(textureSet)
		data = stbi_load(textureData.c_str(), &textLength, &textHeight, &numChannels, 3); //Loads in texture data for usage
	else
		data = stbi_load("textures/noTexture.jpg", &textLength, &textHeight, &numChannels, 3); //Loads in texture data for usage


	if(data)
	{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textLength, textHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D); //Not Sure If this needed perhaps comeback to mipmapping later
	
	stbi_image_free(data); //deletes data
	
	errorCheck("Texture Binding");
	}
	else
	{
		cout << "FAILED TO LOAD TEXTURE" << endl;
		return;
	}
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


void Polygon::set_Point(int index, GLfloat X = 0, GLfloat Y = 0, GLfloat Z = 0, GLfloat R = 255, GLfloat G = 255, GLfloat B = 255, GLfloat A = 255, GLfloat NX = -1, GLfloat NY = -1, GLfloat NZ = -1)
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
	//vertexes[index].s = S;
	//vertexes[index].t = T;	
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

void Polygon::setTexture(string textureFile)
{
	textureData = textureFile;
	textureSet = true;
}

void Polygon::output_Polygon()
{
	for (int i = 0;  i < NumofPoints; i++)
	cout <<"Vertex " << i <<  " X: " <<vertexes[i].x <<" Y: "<< vertexes[i].y << " Z: "<< vertexes[i].z
	<< " R: "<< vertexes[i].r << " G: " << vertexes[i].g << " B: " << vertexes[i].b << endl;
}

void Polygon::calculateTextureCoords()
{
	GLfloat minX, maxX, minY, maxY;

	minX, minY = 2;
	maxX, maxY = -2;

	for(int i = 0; i < NumofPoints; i++)
	{
		if(minX > vertexes[i].x)
		minX = vertexes[i].x;
		if(minY > vertexes[i].y)
		minY = vertexes[i].y;
		if(maxX < vertexes[i].x)
		maxX = vertexes[i].x;
		if(maxY < vertexes[i].y)
		maxY = vertexes[i].y;
	}

	for(int i = 0;  i < NumofPoints; i++)
	{
		vertexes[i].s = (vertexes[i].x - minX) / (maxX - minX);
		vertexes[i].t = (vertexes[i].y - minY) / (maxY - minY);
		//cout << "Vertex S: " << vertexes[i].s << " Vertex T: " << vertexes[i].t << endl;
	}
}

// Equation for Perspective return x * (2 / (z - user_Z)); or return y * (2 / (z - user_Z));
