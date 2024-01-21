#define STB_IMAGE_IMPLEMENTATION  //Stops stb from importing extra stuff

#include <vector>
#include "Open_GL_Basics.h"
#include <GL/glew.h>
#include "thirdParty/glfw3.h" //Graphical usage
#include "thirdParty/stb_image.h" //Used for importing textures
#include <iostream>
#include "thirdParty/glm/glm/glm.hpp"

using namespace std;


/*
	THIS CODE IS THE BACKEND STUFF AND NOT DESIGNED TO BE USED BY USER AS 
	THEIR IS A LOT OF REPEAT COORDINATES AND IT PROBABLY WONT BE READABLE
*/

struct vertex{
	GLfloat x, y, z, r, g, b, a, s, t, nx, ny, nz; // Location Coordinates, Color, Texture Coordinates, Normal Vector
	GLint objectId;
};

class Polygon
{
	public:
	Polygon(int); //Create Polygon with no Vertexes as Default
	Polygon(int, GLint); //Used for setting multiple Objects to Move Together
	~Polygon(); //Deletes Polygon

	vertex getPoint(int index); //returns a vertex
	void setPoint(int index, GLfloat X, GLfloat Y,GLfloat Z,GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat NX, GLfloat NY, GLfloat NZ); // used to set a points values
	void setPoint(int, struct vertex); //used to set a point via vertex more similar to a copy function

	void setTexture(string); // Used to set a texture Input String name

	void changeSize(int); //used to add or remove space for polygons from the vertex vector

	void bindPolygon(GLint); //Sets up and send vertex data to the GPU
	void drawPolygon(GLenum); //Sends the draw requests to the GPU

	void outputPolygon(); //JUST FOR DEBUGGING IN FUTURE FOR NOW

	GLint getObjectId();//needed to retrieve objectId so other stuff can be set to it

	private:
	
	void calculateTextureCoords(); //this is for identifying all the texture coordinates which is calculated in runtime

	vector<struct vertex> vertexes; //this holds all the vertexes every 3 vertexes makes a new triangle
	int NumofPoints; //HOW MANY VERTEXES THEIR ARE
	int VertexSize = 12; //HOW MANY DATA POINTS ARE IN EACH VERTEX

	//Vertex Array Object 
	GLuint vao , vbo; //ID for Vertex Array Object and Vertex Buffer Object
	
	GLint objectId;
	string textureData; //stores texture file location and name
	bool textureSet; //holds if the texture has been set or not defaults to off
	int textLength, textHeight, numChannels; //Texture Data Stuff
};


Polygon::Polygon(int size = 0) //COnstructor for Polygon
{
	static GLint newObjectId = 0;
	NumofPoints = size; //Keeps track of the size
	vertexes.reserve(size); //Sets up the Number of vectors to its expected amount
	textureSet = false; //Deafults textures to not set as the user has yet to actually input the texture that they want to use
	objectId = newObjectId;
	newObjectId++;
}

Polygon::Polygon(int size, GLint newObjectId)
{	
	vertexes.reserve(size); //Sets up the Number of vectors to its expected amount
	textureSet = false; //Deafults textures to not set as the user has yet to actually input the texture that they want to use
	objectId = newObjectId;
}

Polygon::~Polygon()
{}

void Polygon::changeSize(int newSize) //Don't use if you dont have to the time complexity is O(n)
{
	NumofPoints = newSize; //Updates the number of vectors
	vertexes.reserve(NumofPoints); //reallocates the space 
}

vertex Polygon::getPoint(int index) // Returns a point for modification or just ot get the values
{return vertexes[index];}

GLint Polygon::getObjectId()
{return objectId;}

void Polygon::bindPolygon(GLint vShader)  //binds the Polygon to the Pgraphics Pipeline //Input is the vertex Shader to use on the data 
{
	ClearErrors();
	calculateTextureCoords(); //Sets texture coordinates to their proper place on the shape
	
	stbi_set_flip_vertically_on_load(true); //Flips picture back rightside up

	glGenVertexArrays(1, &vao); //Creates the Vertex Array
	glBindVertexArray(vao); // sets vao as the VAO to use
	
	for(int i = 0; i < NumofPoints; i++)
	{vertexes[i].objectId = objectId;}

	//This Section Sets up Textures
	unsigned int texture;//Stores the texture ID	
	glGenTextures(1, &texture); //creates a texture for the pipeline
	glActiveTexture(GL_TEXTURE0); //selects a texture unit ot use 
	glBindTexture(GL_TEXTURE_2D, texture); //binds the created texture to the graphics pipeline
    
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //This is used for setting how a texture works
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); //Currently set to GL_MIRRORED_REPEAT by default might add avility to change in future
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // sets color to be linear menaing it'll blur colors near eachother meaning it'll all be more blurry but also less pixelated
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Uses MinMapping when you shrink the image down
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //uses the more pixelated strategy since we are increasing pixels per inch or whatever thus resolution shouldnt be a problem as long as the picutre itself isn't too grainy

	unsigned char* data; //Holds the color information on the imported texture

	if(textureSet)//checks if the user has set a texture
		data = stbi_load(textureData.c_str(), &textLength, &textHeight, &numChannels, 3); //Loads in texture data for usage
	else
		data = stbi_load("textures/noTexture.jpg", &textLength, &textHeight, &numChannels, 3); //Sets texture to white so it'll act as if their is no texture


	if(data) //Checks if data has been created
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textLength, textHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //sets the textures data to the pulled image
		stbi_image_free(data); //deletes data
		
		glGenerateMipmap(GL_TEXTURE_2D); //Creates versions of the texture to use 
		errorCheck("Texture Binding"); //Tests to make sure Texture Binding All Worked Properly
	}
	else
	{
		cout << "FAILED TO LOAD TEXTURE" << endl; //Tells user texture creation failed
		errorCheck("Failed Texture Loading"); //Explains Problem
		return;//exits 
	}

	//This is where we set up buffers and send it to the GPU for usage

	glGenBuffers(1, &vbo); //Makes the buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo); //binds the buffer to the Graphics Pipeline	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * NumofPoints, vertexes.data(), GL_DYNAMIC_DRAW); //sets the buffer data to the vertex data

	

//	int dataSize = VertexSize * sizeof(GLfloat); // calculates the size of the vertex array



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);//Location LOCATION //Sets stride for Location 
	glEnableVertexAttribArray(0); // Activates Location Variables

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid *) (3 * sizeof(GLfloat)));//COLOR LOCATION Sets Stride for the Color variables
	glEnableVertexAttribArray(1); //Activates Color Variables

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid *) (7 * sizeof(GLfloat)));//Texture LOCATION Sets the stride for the Texture coordinates
	glEnableVertexAttribArray(2); //Activates Texture Coordinates
	
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid *) (9 * sizeof(GLfloat)));//Normal LOCATION Sets the stride for Normal vector
	glEnableVertexAttribArray(3); //Acitvates tge Normal Vectors
	
	glVertexAttribPointer(4, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(vertex), (GLvoid *) (12 * sizeof(GLfloat)));//Normal LOCATION Sets the stride for Normal vector
	glEnableVertexAttribArray(4); //Acitvates tge Normal Vectors
	
	glBindVertexArray(0); //Detaches the vertex array from the Graphics Pipeline

}


void Polygon::setPoint(int index, GLfloat X = 0, GLfloat Y = 0, GLfloat Z = 0, GLfloat R = 255, GLfloat G = 255, GLfloat B = 255, GLfloat A = 255, GLfloat NX = -1, GLfloat NY = -1, GLfloat NZ = -1)
{
	vertexes[index].x = X; //Sets X
	vertexes[index].y = Y; // Sets Y
	vertexes[index].z = Z; // Sets Z
	vertexes[index].r = R / 255; //Sets R and puts it into a 255 based range rather than a 1 based version
	vertexes[index].g = G / 255; // Sets G and puts it in a 255 range
	vertexes[index].b = B / 255; // Buts B in a 255 Range
	vertexes[index].a = A / 255; //Lastly A is Also in the same range
	vertexes[index].nx = NX; //Sets X normal
	vertexes[index].ny = NY; // Sets Y normal
	vertexes[index].nz = NZ; //Sets the Z Normal //These Will Likely b commented out as I think I'll need to calculate thee normal vector by hand
	//vertexes[index].s = S;
	//vertexes[index].t = T; // These are Now calculated since we need all the vertexes to be set 	
}

void Polygon::setPoint(int index, struct vertex newVertex)
{
	vertexes[index] = newVertex;
}

void Polygon::drawPolygon(GLenum primitive)
{
	// Bind the vertex array and buffer
	glBindVertexArray(vao); //attaches vertex Array to the Graphics pipeline
	glBindBuffer(GL_ARRAY_BUFFER, vbo); //attaches the VBO to the VAO

	// Draw the triangle
	glDrawArrays(primitive, 0, NumofPoints);

	// Unbind VAO
	glBindVertexArray(0); 
}

void Polygon::setTexture(string textureFile)
{
	ClearErrors();
	textureData = textureFile; //Assigns the texture Location to the Object
	textureSet = true; //Identifies that the texture Has been Set
	errorCheck("INSIDE SET TEXTURE"); //Error Testing
}

void Polygon::outputPolygon()
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
