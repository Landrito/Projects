#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

/*******************************/
/*STRUCT AND CLASS DECLARATIONS*/
/*******************************/
struct tuple
{
	double x;
	double y;
	tuple(){}
	tuple(const tuple & src)
	{
		this->x = src.x;
		this->y = src.y;
	}
	tuple(double xVal, double yVal) 
		: x(xVal), y(yVal) {}
};

struct triangle
{
	tuple p1;	//holds the points for the triangle
	tuple p2;
	tuple p3;
	
	triangle( const triangle & src)
	{
		this->p1 = src.p1;
		this->p2 = src.p2;
		this->p3 = src.p3;
	}

	triangle( const tuple & pt1, const tuple & pt2, const tuple & pt3 ) 
		: p1(pt1.x, pt1.y), p2(pt2.x, pt2.y), p3(pt3.x, pt3.y) {}

	double area()
	{
		return abs( ( p1.x * (p2.y - p3.y) + 
				  	  p2.x * (p1.y - p3.y) +
				  	  p3.x * (p1.y - p2.y) ) / 2.0 );
	}
};

class polygon
{
public:
	polygon();
	polygon(const polygon & src);
	~polygon();
	void loadFromTerminal();
	vector<triangle> * tesselate();
	int findEar();
	bool isClockwise();

private:
	vector<tuple> * points;
	bool clockwise;
};

/***********************/
/*FUNCTION DECLARATIONS*/
/***********************/
bool overlapsAPoint( vector<tuple> * points, int p1, int p2, int p3 );
void printTriangles( vector<triangle> * triangles );

/***********************/
/*MAIN FUNCTION*/
/***********************/
int main()
{
	//Output the instructions
	cout << endl;
	cout << "Ear Clip Tesselation" << endl;
	cout << "====================" << endl;
	cout << "This is a program that will read in N number of points of a polygon" << endl;
	cout << "The program will read in the the number of points in the polygon," << endl;
	cout << "followed by the points in the form x1 y1 x2 y2 ... xn yn" << endl;

	//Initialize your polygon
	polygon poly;

	//Load the points
	poly.loadFromTerminal();

	//Tesselate the points
	vector<triangle> * triangles = poly.tesselate();

	//Print the triangles points to the screen
	printTriangles(triangles);

	//Delete the vector of triangles for good measure
	delete triangles;

	return 0;
}


/**************************/
/*FUNCTION IMPLEMENTATIONS*/
/**************************/
bool overlapsAPoint( vector<tuple> * points, int p1, int p2, int p3 )
{
	//Barycentric Coordinate System Analysis
	for( int i = 0; i < points->size(); i++)
	{
		if( i != p1 && i != p2 && i != p3 )
		{
			//Barycentric coordinate system analysis
			double alpha = ( ( ( (*points)[p2].y -  (*points)[p3].y) * ( (*points)[i].x -  (*points)[p3].x) +
							( (*points)[p3].x -  (*points)[p2].x) * ( (*points)[i].y -  (*points)[p3].y) ) /
							( ( (*points)[p2].y -  (*points)[p3].y) * ( (*points)[p1].x -  (*points)[p3].x) +
							( (*points)[p3].x -  (*points)[p2].x) * ( (*points)[p1].y -  (*points)[p3].y) ) );

			double beta = ( ( ( (*points)[p3].y -  (*points)[p1].y) * ( (*points)[i].x -  (*points)[p3].x) +
							( (*points)[p1].x -  (*points)[p3].x) * ( (*points)[i].y -  (*points)[p3].y) ) /
							( ( (*points)[p2].y -  (*points)[p3].y) * ( (*points)[p1].x -  (*points)[p3].x) +
							( (*points)[p3].x -  (*points)[p2].x) * ( (*points)[p1].y -  (*points)[p3].y) ) );

			double gamma = 1.0 - alpha - beta;
			
			//return true if there is a point in the center
			if(0 <= alpha && alpha <= 1 
				&& 0 <= beta && beta <= 1 
				&& 0 <= gamma && gamma <= 1)
			{
				return true;
			}
		}
	}
	return false;
}

void printTriangles(vector<triangle> * triangles)
{
	//initialize variables
	int i = 1;

	//loop through each triangle and print it out
	for( vector<triangle>::iterator it = triangles->begin(); 
			it != triangles->end(); it++, i++ )
	{
		cout << "Triangle " << i <<": ";
		cout << "( " << it->p1.x << ", " << it->p1.y << " ) ";
		cout << "( " << it->p2.x << ", " << it->p2.y << " ) ";
		cout << "( " << it->p3.x << ", " << it->p3.y << " )" << endl;
	}
}

polygon::polygon()
{
	//Allocate Memory for Vector
	points = new vector<tuple>;

	//initialize clockwise boolean
	clockwise = true;
}

polygon::polygon( const polygon & src )
{
	//Allocate Memory for Vector
	points  = new vector<tuple>;

	//Push each point from the src list
	for(int i = 0; i < src.points->size(); i++)
	{
		points->push_back( (*(src.points))[i] ); //This looks super confusing
	}

	//Set the clockwise boolean
	clockwise = src.clockwise;
}

polygon::~polygon()
{
	//De-Allocate Memory for the vector;
	delete points;
}

void polygon::loadFromTerminal()
{
	//initialize variables and counters
	int numPoints = 0;
	int tempX = 0;
	int tempY = 0;

	//Get the input of the number of points
	cin >> numPoints;

	//for each point, push it into the list
	for(int i = 0; i < numPoints; i++)
	{
		cin >> tempX >> tempY;
		points->push_back( tuple(tempX, tempY) );
	}

	//set whether the polygon is oriented clockwise
	clockwise = isClockwise();

}

vector<triangle> * polygon::tesselate()
{
	//initialize the list of teselated triangles
	//this needs to be initialized here cause it is used in the loop
	vector<triangle> * triangles = new vector<triangle>;

	//while there are more than two points 
	//(when two points all triangles have been tesselated)
	while(points->size() > 2) 
	{
		//Declare the iterator that will be used to delete the ear point from the list of points
		vector<tuple>::iterator earIterator = points->begin();

		//Find the location of the ear point on the list
		int ear = findEar();

		//Initialize the points to the left and right of the ear point
		int left = 0;
		int right = 0;

		//Set the left and right point based on where the ear point is
		//If the ear is the first point on the list, then the left is the back
		if(ear != 0 )
			left = ear - 1;
		else
			left = points->size() - 1;

		//If the ear is the last point on the list, then the right is the front 
		if( ear + 1 != points->size() )
			right = ear + 1;
		else
			right = 0;

		//Start at a triangle made up of the ear points
		triangle tri = triangle(  (*points)[left],  (*points)[ear],  (*points)[right] );

		//Add the ear to the list if it has an area greater than 0
		if( tri.area() > 0 )
			triangles->push_back(tri);

		//take the ear point out of the list
		points->erase(earIterator + ear);
	}

	return triangles;
}

int polygon::findEar()
{
	//Initialize the counters
	bool found = false;
	int pointOne = points->size() - 1;
	int pointTwo = 0;
	int pointThree = 1;

	for(int i = 0; i < points->size() && !found; i++)
	{

		//Form Vectors from the three points using the iterators
		tuple vec1 = tuple( (*points)[pointOne].x -  (*points)[pointTwo].x,  (*points)[pointOne].y -  (*points)[pointTwo].y);
		tuple vec2 = tuple( (*points)[pointThree].x -  (*points)[pointTwo].x,  (*points)[pointThree].y -  (*points)[pointTwo].y);

		//Find the dot product of the vectors
		double dot = vec1.x * vec2.x + vec1.y * vec2.y;

		//Find the magnitude of the vectors
		double magnitude1 = sqrt(vec1.x * vec1.x + vec1.y * vec1.y);
		double magnitude2 = sqrt(vec2.x * vec2.x + vec2.y * vec2.y);

		//calculate the angle between the two vectors using dot product properties
		double angle = acos( dot / (magnitude1 * magnitude2) );

		//If the polygon is orientated clockwise and the angle is greater than 180 ddegrees
		//or the opposite, the center point is an ear point
		if( (clockwise && angle > M_PI) || (!clockwise && angle < M_PI) )
		{
			if( !overlapsAPoint( points, pointOne, pointTwo, pointThree ) )
				found = true;		
		}


		//else increase counters
		else
		{
			pointOne = (pointOne + 1) % points->size();	
			pointTwo = (pointTwo + 1) % points->size();
			pointThree = (pointThree + 1) % points->size();
		}
	}

	return pointTwo;
}

bool polygon::isClockwise()
{
	double sum = 0.0;
	for( vector<tuple>::iterator it = points->begin(); 
			it != points->end(); it++ )
	{
		if( (it+1) != points->end() )
			sum += ( (it+1)->x - it->x ) * ( (it+1)->y - it->y );
		else
			sum += ( points->begin()->x - it->x ) * ( points->begin()->y - it->y );
	}

	return sum > 0.0;
}
