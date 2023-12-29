#include <vector>
#include "Open_GL_Basics.h"
#include <GL/glew.h>
#include "glfw3.h" //Graphical usage
#include <iostream>
#include "Polygons.h"
#include <list>
#include <iterator>

class Shape{

	public:
	Shape(int);
	~Shape();

	void setVertex(int, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat,GLfloat,GLfloat, GLfloat, GLfloat, GLfloat); // Index, X value, Y value
	void setVertex(int, struct vertex);
	struct vertex getVertex(int); //Index

	void bindShape(GLint);	
	void drawShape();

	void outputPolygon(); //This outputs the polygons vertices for debugging
	void outputShape(); //This Outputs the inputted shapeverties for debugging

	private:

	void triangulate(); //This is an Ear Clipping Algorithm Although I'd like to look into using Seidel's Triangulation
						//I want to look into running this algorithm on the GPU as I think with simple vector multiplication and multithreading this can be really fast

	int numSides;
	Polygon triangles;
	struct vertex* points;
};

Shape::Shape(int size)
{
	numSides = size;
	triangles.changeSize(3 * (numSides - 2)); //Ear clipping makes n -2 triangles and each have 3 sides thus the size
	points = new struct vertex[size];
}

Shape::~Shape()
{
	delete[] points;
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

	points[index] = newVertex;
}
void Shape::setVertex(int index, struct vertex newVertex)
{
	if (index < 0 || index >= numSides)
	{
		printf("INVALID INDEX\n");
		return;
	}

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


void Shape::bindShape(GLint vShader)
{
	triangulate();
	triangles.bind_Polygon(vShader);
}

void Shape::drawShape()
{
	triangles.draw_Polygon(GL_TRIANGLES);
}

void Shape::triangulate() //Shapes must go clockwise for this too work else it'll like either do the outside or create an infinte loop
{
	list<struct vertex> vectorList; //This is a double Linked List that will be cycles through to see element before and after an element and allows for quick deleteion when vector is gone
	
	for (int i = 0; i < numSides; i++) //Sets up the linked list
		vectorList.emplace_back(points[i]);

	int sidesLeft = numSides; //Keeps track of how many sides we have left for when we hit the final 3
	int numPolygons = 0; //Keeps track of how many polygons have been inserted so we know where to add the new ones

	double area;

	list<struct vertex>::iterator currentPoint;
	list<struct vertex>::iterator nextPoint;
	list<struct vertex>::iterator prevPoint;
	list<struct vertex>::iterator insideChecker;
	
	bool isPolygon;

	currentPoint = vectorList.begin();
	nextPoint = next(vectorList.begin());	
	prevPoint = --vectorList.end();	
	
	while(sidesLeft > 3) //When we run down to 3 sides addthe last 3 as the polygon
	{
			
		isPolygon = true;


		if((currentPoint->x - nextPoint->x) * (prevPoint->y - nextPoint->y) - (currentPoint->y - nextPoint->y) * (prevPoint->x - nextPoint->x) > 0) //Check if point is acute or Straight 
		{
			if(insideChecker == vectorList.end())
			insideChecker = vectorList.begin();
			
			area = .5 * abs(currentPoint->x * (nextPoint->y - prevPoint->y) + nextPoint->x * (prevPoint->y - currentPoint->y) + prevPoint->x * (currentPoint->y - nextPoint->y));
			for(insideChecker = next(nextPoint); insideChecker != prevPoint; insideChecker++)//Check if inside Triangle
			{
				if(insideChecker == vectorList.end())
				insideChecker = vectorList.begin();

				double areaSum = .5 * abs(currentPoint->x * (nextPoint->y - insideChecker->y) + nextPoint->x * (insideChecker->y - currentPoint->y) + insideChecker->x * (currentPoint->y - nextPoint->y)) 
				+ 
				.5 * abs(nextPoint->x * (prevPoint->y - insideChecker->y) + prevPoint->x * (insideChecker->y - nextPoint->y) + insideChecker->x * (nextPoint->y - prevPoint->y)) 
				+ 
				.5 * abs(currentPoint->x * (prevPoint->y - insideChecker->y) + prevPoint->x * (insideChecker->y - currentPoint->y) + insideChecker->x * (currentPoint->y - prevPoint->y)); 


				if //Checks if the points is inside the triangle
				(
				abs(areaSum - area) <= 1e-6 //DEALS WITH FLOATING POINT ERRORS
				) //Checks if point in previous points
				{
					isPolygon = false;
					break;
				}
			}

			if(isPolygon) //add to polygons remove i from vectorList increment numPolgons decrement sidesLeft
			{
				triangles.set_Point(numPolygons * 3, *currentPoint);
				triangles.set_Point(numPolygons * 3 + 1, *nextPoint);
				triangles.set_Point(numPolygons * 3 + 2, *prevPoint);
				vectorList.erase(currentPoint);
				currentPoint = prevPoint;
				prevPoint = prev(currentPoint);
				if(currentPoint == vectorList.begin())
				{
					prevPoint = --vectorList.end();
				}
				sidesLeft--;
				numPolygons++;
			}
		}
		
		currentPoint++;
		nextPoint = currentPoint;
		nextPoint++;	
		prevPoint = currentPoint;
		prevPoint--;
		
		if(currentPoint == vectorList.end())
			currentPoint = vectorList.begin();
		if(currentPoint == vectorList.begin())
			prevPoint = --vectorList.end();	

		if(nextPoint == vectorList.end())
		nextPoint = vectorList.begin();		
	
	}
	
	currentPoint = vectorList.begin();
	nextPoint = ++vectorList.begin();	
	prevPoint = --vectorList.end();	


	triangles.set_Point(numPolygons * 3, (*currentPoint));
	triangles.set_Point(numPolygons * 3 + 1, (*nextPoint));
	triangles.set_Point(numPolygons * 3 + 2, (*prevPoint));
}


void Shape::outputPolygon()
{triangles.output_Polygon();}

void Shape::outputShape()
{
	for (int i = 0; i < numSides; i++)
	cout << "Vertex " << i << " X: "<< points[i].x << " Y: " << points[i].y << " Z: " << points[i].z 
	<< " R: "<< points[i].r << " G: " << points[i].g << " B: " << points[i].b << endl;
}
