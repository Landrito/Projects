#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

/******************/
/*GLOBAL CONSTANTS*/
/******************/
//This value is to be used to check if any variable of type double is zero
//Anything less than this tolerance, should be considered zero.
const double TOLERANCE = 0.000001; 

/*******************************/
/*STRUCT AND CLASS DECLARATIONS*/
/*******************************/
//Disclaimer for Evan: My gut feeling is that constructors dont need to be
//outside of the structs. I went on this train of thought because there is no
//dynamic memory within the struct. This is safe as long as the tuple is
//initialized at declaration (like all of the other variables we are using).
//After our last sessions this train of thought feels ultra dangerous to me
//mostly cause people suck and are stupid. After feeling this way, I looked up
//ways to initialize the structs outside of the struct, but none seemed to show
//any sort of advantage because if the coder forgets to initialize the struct
//with {} notation, what makes you think they are gonna take the time to use
//an outside function to initialize.
struct tuple
{
	double x;
	double y;
};

struct triangle
{
	tuple p1;
	tuple p2;
	tuple p3;
};

/***********************/
/*FUNCTION DECLARATIONS*/
/***********************/
bool overlapsAPoint( const vector<tuple> & points, int p1, int p2, int p3 );
void printTriangles( vector<triangle> * triangles );
double findAngle( const tuple & p1, const tuple & p2, const tuple & p3);
int findBadPoint(const vector<tuple> & points);

//These were from my old class
vector<tuple> * loadFromTerminal();
vector<triangle> * tesselate(const vector<tuple> & points);
int findEar(const vector<tuple> & points, bool clockwise);
bool isClockwise(const vector<tuple> & points);
double area(const triangle & tri);

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

	//Initialize your polygon and load data
    vector<tuple> * polygon = loadFromTerminal();

	//Tesselate the points
	vector<triangle> * triangles = tesselate(*polygon);

	//Print the triangles points to the screen
	printTriangles(triangles);

	//Delete the vector of triangles for good measure
	delete triangles;

	return 0;
}


/**************************/
/*FUNCTION IMPLEMENTATIONS*/
/**************************/
bool overlapsAPoint( const vector<tuple> & points, int point1Index, int point2Index, int point3Index ) 
{
	//Barycentric Coordinate System Analysis
	for( int i = 0; i < points.size(); i++)
	{
		tuple pointOne = points[point1Index];
		tuple pointTwo = points[point2Index];
		tuple pointThree = points[point3Index];
		tuple indexPoint = points[i];

		if( i != point1Index && i != point2Index && i != point3Index )
		{
			//Barycentric coordinate system analysis
			double alpha = ( ( ( pointTwo.y -  pointThree.y) * ( indexPoint.x -  pointThree.x) +
							( pointThree.x -  pointTwo.x) * ( indexPoint.y -  pointThree.y) ) /
							( ( pointTwo.y -  pointThree.y) * ( pointOne.x -  pointThree.x) +
							( pointThree.x -  pointTwo.x) * ( pointOne.y -  pointThree.y) ) );

			double beta = ( ( ( pointThree.y -  pointOne.y) * ( indexPoint.x -  pointThree.x) +
							( pointOne.x -  pointThree.x) * ( indexPoint.y -  pointThree.y) ) /
							( ( pointTwo.y -  pointThree.y) * ( pointOne.x -  pointThree.x) +
							( pointThree.x -  pointTwo.x) * ( pointOne.y -  pointThree.y) ) );

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

double findAngle( const tuple & p1, const tuple & p2, const tuple & p3)
{
	//Form Vectors from the three points using the iterators
    tuple vec1 = { (p1.x -  p2.x), (p1.y -  p2.y) };
    tuple vec2 = { (p3.x -  p2.x), (p3.y -  p2.y) };

	//Find the dot product of the vectors
	double dot = vec1.x * vec2.x + vec1.y * vec2.y;

	//Find the magnitude of the vectors
	double magnitude1 = sqrt(vec1.x * vec1.x + vec1.y * vec1.y);
	double magnitude2 = sqrt(vec2.x * vec2.x + vec2.y * vec2.y);

	//calculate the angle between the two vectors using dot product properties
	return acos( dot / (magnitude1 * magnitude2) );
}

int findBadPoint( const vector<tuple> & points )
{
	//Initialize the counters
	int pointOne = points.size() - 1;
	int pointTwo = 0;
	int pointThree = 1;

	//loop through each point in the vector
	for( int i = 0; i < points.size(); i++ )
	{
		//set find the angle of the vectors that make up the points
		double angle = findAngle( points[pointOne], points[pointTwo], points[pointThree] );

		//if the angle is extremely small, it should be removed from the list
		if( angle < TOLERANCE )
			return pointTwo;

		//other wise increment counters
		else
		{
			pointOne = (pointOne + 1) % points.size();	
			pointTwo = (pointTwo + 1) % points.size();
			pointThree = (pointThree + 1) % points.size();
		}
	}

	//return a negative if none was found
	return -1;
}

vector<tuple> * loadFromTerminal()
{
    //initialize the vector to return
    vector<tuple> * points = new vector<tuple>;
    
	//initialize variables and counters
	int numPoints = 0;
	int tempX = 0;
	int tempY = 0;

	//Get the input of the number of points
	cin >> numPoints;

	//for each point, push it into the list
	for(int i = 0; i < numPoints; i++)
	{
		//input the temporary x and y values
		cin >> tempX >> tempY;
        tuple tempTuple = {tempX, tempY};

		//push back the point if it not the same point that was just inputted
		//the algorithm will not work if two of the same points are inserted consecutively
		if( points->empty() )
            points->push_back( tempTuple );
		else if( points->back().x != tempX || points->back().y != tempY )
		{
			//also account for the case where the last point 
			//is the same as the first point inputted
			if( i != numPoints - 1 )
				points->push_back( tempTuple );
			else if( points->front().x != tempX || points->front().y != tempY )
				points->push_back( tempTuple );
		}
	}
    
    return points;
}

vector<triangle> * tesselate(const vector<tuple> & points)
{
	//initialize the list of teselated triangles
	vector<triangle> * triangles = new vector<triangle>;

	//Create a temporary list of points
	vector<tuple> tempPoints = points;

	//Find if the polygon is oriented clockwise
	bool clockwise = isClockwise(points);

	//while there are more than two points 
	//(when two points all triangles have been tesselated)
	while(tempPoints.size() > 2) 
	{
		//Find any points that just form a line to the polygon and remove them from the list
		//Start a block to be able to deallocate badPoint after done needing it
		{
			int badPoint = findBadPoint(tempPoints);
			while( badPoint != -1 )
			{
				//Declare the iterator that will be used to delete the ear point from the list of points
				vector<tuple>::iterator badPointIterator = tempPoints.begin();
				tempPoints.erase(badPointIterator + badPoint);
				badPoint = findBadPoint(tempPoints);
			}
		}

		//Find the location of the ear point on the list
		int ear = findEar(points, clockwise);

		//Initialize the points to the left and right of the ear point
		int left = 0;
		int right = 0;

		//Set the left and right point based on where the ear point is
		//If the ear is the first point on the list, then the left is the back
		if(ear != 0 )
			left = ear - 1;
		else
			left = tempPoints.size() - 1;

		//If the ear is the last point on the list, then the right is the front 
		if( ear + 1 != tempPoints.size() )
			right = ear + 1;
		else
			right = 0;

		//Start at a triangle made up of the ear points
        triangle tri = { tempPoints[left], tempPoints[ear], tempPoints[right] };

		//Add the ear to the list if it has an area greater than 0
		if( area(tri) > 0 )
			triangles->push_back(tri);

		//Declare the iterator that will be used to delete the ear point from the list of points
		vector<tuple>::iterator earIterator = tempPoints.begin();

		//take the ear point out of the list
		tempPoints.erase(earIterator + ear);
	}

	return triangles;
}

int findEar(const vector<tuple> & points, bool clockwise)
{
	//Initialize the counters
	bool found = false;
	int pointOneIndex = points.size() - 1;
	int pointTwoIndex = 0;
	int pointThreeIndex = 1;

	for(int i = 0; i < points.size() && !found; i++)
	{
		//calculate the angle between the two vectors using dot product properties
		double angle = findAngle( points[pointOneIndex], points[pointTwoIndex], points[pointThreeIndex] );

		//If the polygon is orientated clockwise and the angle is greater than 180 ddegrees
		//or the opposite, the center point is an ear point
		if( (clockwise && angle > M_PI) || (!clockwise && angle < M_PI) )
		{
			if( !overlapsAPoint( points, pointOneIndex, pointTwoIndex, pointThreeIndex ) )
				found = true;		
		}


		//else increase counters
		else
		{
			pointOneIndex = (pointOneIndex + 1) % points.size();
			pointTwoIndex = (pointTwoIndex + 1) % points.size();
			pointThreeIndex = (pointThreeIndex + 1) % points.size();
		}
	}

	return pointTwoIndex;
}

bool isClockwise(const vector<tuple> & points)
{
	//initialize values
	double sum = 0.0;

	//loop through each point and add up the displacements
	for( int i = 0; i < points.size(); i++ )
	{
		if( (i+1) != points.size() )
			sum += ( points[i+1].x - points[i].x ) * ( points[i+1].y - points[i].y );
		else
			sum += ( points[0].x - points[i].x ) * ( points[0].y - points[i].y );
	}

	//if it is greater than 0, it is clockwise oriented
	return sum > 0.0;
}

double area( const triangle & tri )
{
    return abs( ( tri.p1.x * (tri.p2.y - tri.p3.y) +
                 tri.p2.x * (tri.p1.y - tri.p3.y) +
                 tri.p3.x * (tri.p1.y - tri.p2.y) ) / 2.0 );
}
