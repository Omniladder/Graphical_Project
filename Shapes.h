#include <cmath>    // for trigonometry functions
#include <math.h>
#include <string>
#include <list>
#include "glfw3.h" //Graphical usage
#include <iostream>

using namespace std;



/*
Vertex code Below






*/



class Vertex {       // The class
  public:             // Access specifier

    Vertex();
    Vertex(double, double, double);
    Vertex(double, double);
    Vertex(const Vertex&);

    void Set_X(double);
    void Set_Y(double);
    void Set_Z(double);

    void Set_Point(double,double,double);
    void Set_Point(double,double);

    void X_Rotation(double, double, double, double);
    void Y_Rotation(double, double, double, double);
    void Z_Rotation(double, double, double, double);

    double  get_X() const;
    double  get_Y() const;
    double  get_Z() const;

    double get_User_Z() const;
    void set_User_Z(double);

    double Real_X() const;
    double Real_Y() const;


    private:
    double x,y,z;
    static double user_Z;
    
};

double Vertex::user_Z = -2;

Vertex::Vertex()
{}

Vertex::Vertex(const Vertex& old)
{
    x = old.x;
    y = old.y;
    z = old.z;
}

Vertex::Vertex(double X_Value, double Y_Value)
{
    x = X_Value;
    y = Y_Value;
    z = 0;
}

Vertex::Vertex(double X_Value, double Y_Value, double Z_Value)
{
    x = X_Value;
    y = Y_Value;
    z = Z_Value;
}

double Vertex::get_User_Z() const
{return user_Z;}

void Vertex::set_User_Z(double newZ)
{user_Z = newZ;}

void Vertex::Set_Point(double X_Value, double Y_Value)
{
    x = X_Value;
    y = Y_Value;
    z = 0;
}

void Vertex::Set_Point(double X_Value, double Y_Value, double Z_Value)
{
    x = X_Value;
    y = Y_Value;
    z = Z_Value;
}

void Vertex::Set_X(double X_Value)
{
    x = X_Value;
}

void Vertex::Set_Y(double Y_Value)
{
    y = Y_Value;
}

void Vertex::Set_Z(double Z_Value)
{
    z = Z_Value;
}

double Vertex::get_Z() const
{
    return z;
}

double Vertex::get_Y() const
{
    return y;
}

double Vertex::get_X() const
{
    return x;
}

double Vertex::Real_X() const //x taking account for z where the point is actually displayed on the 2 dimensions
{
    if(z > user_Z)
    {return x * (2 / (z - user_Z));}
    else
    {
        return 20;
    }
}

double Vertex::Real_Y() const //y taking account for z where the point is actually displayed on the 2 dimensions
{
    //return y / (1 - (z / (-1 * perspective * sqrt(y * y + z *z ))));
    
    if(z > user_Z)
    {
        return y * (2 / (z - user_Z));
    }
    else
    {
        return 20;
    }
}


void Vertex::X_Rotation(double rPoint_x, double rPoint_y, double rPoint_z, double degrees)
{
    // Calculate Euclidean distance between vertex and rotation point
    double distance = sqrt(pow(y - rPoint_y, 2) + pow(z - rPoint_z, 2));

    // Calculate the angle using atan and convert degrees to radians
    double angle = atan2((y - rPoint_y), (z - rPoint_z)) + degrees * M_PI / 180.0;

    // Update y coordinate using sin of the angle and the distance
    y = rPoint_y +distance * sin(angle);

    // Update z coordinate using cos of the angle and the distance
    z = rPoint_z + distance * cos(angle);
}

void Vertex::Y_Rotation(double rPoint_x, double rPoint_y, double rPoint_z, double degrees)
{
    // Calculate Euclidean distance between vertex and rotation point
    double distance = sqrt(pow(x - rPoint_x, 2) + pow(z - rPoint_z, 2));

    // Calculate the angle using atan and convert degrees to radians
    double angle = atan2((z - rPoint_z), (x - rPoint_x)) + degrees * M_PI / 180.0;

    // Update y coordinate using sin of the angle and the distance
    z = rPoint_z +distance * sin(angle);

    // Update z coordinate using cos of the angle and the distance
    x = rPoint_x + distance * cos(angle);
}

void Vertex::Z_Rotation(double rPoint_x, double rPoint_y, double rPoint_z, double degrees)
{
    // Calculate Euclidean distance between vertex and rotation point
    double distance = sqrt(pow(x - rPoint_x, 2) + pow(y - rPoint_y, 2));

    // Calculate the angle using atan and convert degrees to radians
    double angle = atan2((y - rPoint_y), (x - rPoint_x)) + degrees * M_PI / 180.0;

    // Update y coordinate using sin of the angle and the distance
    y = rPoint_y +distance * sin(angle);

    // Update z coordinate using cos of the angle and the distance
    x = rPoint_x + distance * cos(angle);
}

/*
Polygon Code Below

Polygons are intended to be plane styled shapes either in a 2d atmosphere, the side of a shape or some sort of flat plane like surface












*/



class Polygon{

    public:
    Polygon();
    Polygon(float, float, float);
    Polygon(const Polygon&);
    void copy_Poly(const Polygon);


    Vertex getPoint(int) const;
    int get_Num_of_Points() const;

    void setPoint(int, double,double,double);
    void setPoint(int, double,double);
    void draw_Polygon(GLFWwindow*, bool);
    void setColor(float,float,float);
    void makePoint(double,double);
    void makePoint(double,double,double);
    void clear();

    void move_Polygon(double, double);
    void move_Polygon(double, double, double);
    void X_Rotation(double, double, double, double);
    void Y_Rotation(double, double, double, double);
    void Z_Rotation(double, double, double, double);


    private:
    //int num_of_sides;
    float r,g,b;
    list<Vertex> points;

};

Polygon::Polygon(const Polygon& old)
{
    r = old.r;
    g = old.g;
    b = old.b;
    for (list<Vertex>::const_iterator it = old.points.begin(); it != old.points.end(); ++it)
    {
        Vertex* newPoint = new Vertex(*it);
        points.push_back(*newPoint);
    }
}

Polygon::Polygon()
{
    r = 255;
    g = 255;
    b = 255;
}

Polygon::Polygon(float red, float blue, float green)
{
    r = red;
    b = blue;
    g = green;
}

void Polygon::clear()
{
    points.clear();
}

void Polygon::copy_Poly(const Polygon copyPoly)
{
    points.clear();
   list<Vertex>::const_iterator it = points.begin();

    for(int i = 0; i < copyPoly.get_Num_of_Points() ; i++)
    {
        makePoint((*it).get_X(),(*it).get_Y(),(*it).get_Z());
        it++;
    } 
}

Vertex Polygon::getPoint(int num_point) const
{
    list<Vertex>::const_iterator it = points.begin();
    for(int i = 0; i<num_point; i++)
    {
        it++;
    }
    return *it;
}

void Polygon::X_Rotation(double rPoint_x, double rPoint_y, double rPoint_z, double degrees)
{
    list<Vertex>::iterator it = points.begin();
    for(int i = 0; i < points.size(); i++)
        {
            (*it).X_Rotation(rPoint_x,rPoint_y,rPoint_z,degrees);
            it++;
        }
}

void Polygon::Y_Rotation(double rPoint_x, double rPoint_y, double rPoint_z, double degrees)
{
    list<Vertex>::iterator it = points.begin();
    for(int i = 0; i < points.size(); i++)
        {
            (*it).Y_Rotation(rPoint_x,rPoint_y,rPoint_z,degrees);
            it++;
        }
}

void Polygon::Z_Rotation(double rPoint_x, double rPoint_y, double rPoint_z, double degrees)
{
    list<Vertex>::iterator it = points.begin();
    for(int i = 0; i < points.size(); i++)
        {
            (*it).Z_Rotation(rPoint_x,rPoint_y,rPoint_z,degrees);
            it++;
        }
}

void Polygon::makePoint(double x, double y)
{
    Vertex* newPoint = new Vertex(x, y);
    points.push_back(*newPoint);

}



void Polygon::makePoint(double x, double y, double z)
{
    Vertex* newPoint = new Vertex(x, y, z);
    points.push_back(*newPoint);
}

int Polygon::get_Num_of_Points() const
{return points.size();}

void Polygon::setPoint(int side, double x, double y, double z)
{
    list<Vertex>::iterator it = points.begin();
    for(int i = 0; i<side; i++)
    {
        it++;
    }
    (*it).Set_Point(x, y, z);
}

void Polygon::move_Polygon(double xShift, double yShift)
{
    list<Vertex>::iterator it = points.begin();

    for(int i = 0; i < points.size(); i++)
    {
        (*it).Set_X((*it).get_X() + xShift);
        (*it).Set_Y((*it).get_Y() + yShift);
        it++;
    }
}

void Polygon::move_Polygon(double xShift, double yShift, double zShift)
{
    list<Vertex>::iterator it = points.begin();

    for(int i = 0; i < points.size(); i++)
    {
        (*it).Set_X((*it).get_X() + xShift);
        (*it).Set_Y((*it).get_Y() + yShift);
        (*it).Set_Z((*it).get_Z() + zShift);
        it++;
    }
}

void Polygon::setColor(float red, float green, float blue)
{
    r = red;
    g = green;
    b = blue;
}

void Polygon::setPoint(int side, double x, double y)
{
    list<Vertex>::iterator it = points.begin(); 
     for(int i = 0; i < side; i++)
    {
        it++;
    }
    (*it).Set_Point(x, y);
}

void Polygon::draw_Polygon(GLFWwindow* window, bool shaded)
{
    if(shaded)
    {
        glBegin(GL_TRIANGLE_FAN); //starts shape
    }
    else
    {
        glBegin(GL_LINE_STRIP); //starts shape
    }

    int window_width, window_height;

    glfwGetWindowSize(window, &window_width, &window_height);

    glColor3f(r / 255, g / 255, b / 255); 

    list<Vertex>::iterator it = points.begin(); 

    for (int i = 0; i < points.size(); i++)
    {
        glVertex2f((*it).Real_X() * (window_height * 1.0 / window_width), (*it).Real_Y() ); //graphs each point
        it++;
    }

    glVertex2f((*points.begin()).Real_X() * (window_height * 1.0 / window_width), (*points.begin()).Real_Y());
    

    glEnd(); //ends shape

}
/*
Shape Code Below
Shapes are collections of polygons which I can hopefully use to make more complicated non plane styled shapes polyhedras





*/

class Shape
{

    public:
    Shape();

    void draw_Shape(GLFWwindow*, bool);

    void setSide(int, Polygon);
    Polygon& getSide(int);
    Polygon getSide_const(int) const;

    void addSide(Polygon);

    void move_Polygon(double, double);
    void move_Polygon(double, double, double);
    void X_Rotation(double, double, double, double);
    void Y_Rotation(double, double, double, double);
    void Z_Rotation(double, double, double, double);

    void setColor(float,float,float);


    int get_number_of_sides() const;

    private:
    list<Polygon> sides;

};

Shape::Shape()
{}


int Shape::get_number_of_sides() const
{
    return sides.size();
}



void Shape::setColor(float r, float g, float b)
{
   list<Polygon>::iterator it = sides.begin();

    for(int i = 0; i < sides.size(); i++)
    {
        (*it).setColor(r,g,b);
        it++;
    } 
}

void Shape::Z_Rotation(double r_x, double r_y, double r_z, double angle)
{
   list<Polygon>::iterator it = sides.begin();

    for(int i = 0; i < sides.size(); i++)
    {
        (*it).Z_Rotation(r_x,r_y,r_z,angle);
        it++;
    } 
}


void Shape::Y_Rotation(double r_x, double r_y, double r_z, double angle)
{
   list<Polygon>::iterator it = sides.begin();

    for(int i = 0; i < sides.size(); i++)
    {
        (*it).Y_Rotation(r_x,r_y,r_z,angle);
        it++;
    } 
}

void Shape::X_Rotation(double r_x, double r_y, double r_z, double angle)
{
   list<Polygon>::iterator it = sides.begin();

    for(int i = 0; i < sides.size(); i++)
    {
        (*it).X_Rotation(r_x,r_y,r_z,angle);
        it++;
    } 
}

void Shape::move_Polygon(double xMove,double yMove, double zMove)
{
     list<Polygon>::iterator it = sides.begin();

    for(int i = 0; i < sides.size(); i++)
    {
        (*it).move_Polygon(xMove,yMove,zMove);
        it++;
    }
}

void Shape::move_Polygon(double xMove,double yMove)
{
     list<Polygon>::iterator it = sides.begin();

    for(int i = 0; i < sides.size(); i++)
    {
        (*it).move_Polygon(xMove,yMove);
        it++;
    }
}

void Shape::addSide(Polygon newPoly)
{
    sides.push_back(newPoly);
}

void Shape::setSide(int side, Polygon newSide)
{
    list<Polygon>::iterator it = sides.begin(); 

    for (int i = 0; i < side; i++)
    {
        it++;
    }
    (*it).copy_Poly(newSide);
}

Polygon& Shape::getSide(int side)
{
    list<Polygon>::iterator it = sides.begin(); 

    for (int i = 0; i < side; i++)
    {
        it++;
    }
    return (*it);
}

Polygon Shape::getSide_const(int side) const
{
    list<Polygon>::const_iterator it = sides.begin(); 

    for (int i = 0; i < side; i++)
    {
        it++;
    }
    return (*it);
}


void Shape::draw_Shape(GLFWwindow* window,bool shaded)
{
    list<Polygon>::iterator it = sides.begin(); 



    for (int i = 0; i < sides.size(); i++)
    {
        (*it).draw_Polygon(window, shaded);
        it++;
    }

    
}

