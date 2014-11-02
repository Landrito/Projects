#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct tuple
{
	double x;
	double y;
	tuple(double xVal, double yVal) : x(xVal), y(yVal) {}
};

typedef struct triangle
{
	tuple p1;	//holds the points for the triangle
	tuple p2;
	tuple p3;
	triangle(tuple pt1, tuple pt2, tuple pt3) : p1(pt1.x, pt1.y), p2(pt2.x, pt2.y), p3(pt3.x, pt3.y) {}
}triangle;


vector<triangle> tesselate( vector<tuple> points );
bool overlapsAPoint( vector<tuple> points, int p1, int p2, int p3);
int findEar(vector<tuple> points);
bool isClockwise( vector<tuple> points );
double area(triangle tri);
void printTriangles(vector<triangle> triangles);

int main()
{
	int numPoints;
	double tempX, tempY;
	bool clockwise;
	vector<tuple> points;
	vector<triangle> triangles;

	//Output the instructions
	cout << endl;
	cout << "Ear Clip Tesselation" << endl;
	cout << "====================" << endl;
	cout << "This is a program that will read in N number of points of a polygon" << endl;
	cout << "The program will read in the the number of points in the polygon," << endl;
	cout << "followed by the points in the form x1 y1 x2 y2 ... xn yn" << endl;

	//Input the points
	cin >> numPoints;
	for(int i = 0; i < numPoints; i++)
	{
		cin >> tempX >> tempY;
		points.push_back( tuple(tempX, tempY) );
	}

	//Tesselate the points
	triangles = tesselate(points);

	//Print the triangles points to the screen
	printTriangles(triangles);
}

vector<triangle> tesselate( vector<tuple> points )
{
	//initialize the list of teselated triangles
	vector<triangle> triangles;


	//while there are more than two points 
	//(when two points all triangles have been tesselated)
	while(points.size() > 2) 
	{
		//Declare the iterator that will be used to delete the ear point from the list of points
		vector<tuple>::iterator earIterator = points.begin();

		//Find the location of the ear point on the list
		int ear = findEar( points);

		//Initialize the points to the left and right of the ear point
		int left, right;

		//Set the left and right point based on where the ear point is
		//If the ear is the first point on the list, then the left is the back
		if(ear != 0 )
			left = ear - 1;
		else
			left = points.size() - 1;

		//If the ear is the last point on the list, then the right is the front 
		if( ear + 1 != points.size() )
			right = ear + 1;
		else
			right = 0;

		//Start at a triangle made up of the ear points
		triangle tri = triangle(points[left], points[ear], points[right]);

		//Add the ear to the list if it has an area greater than 0
		if( area(tri) > 0 )
			triangles.push_back(tri);

		//take the ear point out of the list
		points.erase(earIterator + ear);

	}

	return triangles;
}

bool overlapsAPoint( vector<tuple> points, int p1, int p2, int p3 )
{
	//Barycentric Coordinate System Analysis
	for( int i = 0; i < points.size(); i++)
	{
		if( i != p1 && i != p2 && i != p3 )
		{
			//Barycentric coordinate system analysis
			double alpha = ( ( (points[p2].y - points[p3].y) * (points[i].x - points[p3].x) +
							(points[p3].x - points[p2].x) * (points[i].y - points[p3].y) ) /
							( (points[p2].y - points[p3].y) * (points[p1].x - points[p3].x) +
							(points[p3].x - points[p2].x) * (points[p1].y - points[p3].y) ) );

			double beta = ( ( (points[p3].y - points[p1].y) * (points[i].x - points[p3].x) +
							(points[p1].x - points[p3].x) * (points[i].y - points[p3].y) ) /
							( (points[p2].y - points[p3].y) * (points[p1].x - points[p3].x) +
							(points[p3].x - points[p2].x) * (points[p1].y - points[p3].y) ) );

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

int findEar(vector<tuple> points)
{
	vector<tuple>::iterator it1, it2, it3;

	//Initialize the iterators
	bool found = false;
	bool clockwise = isClockwise( points );

	int pointOne = points.size() - 1;
	int pointTwo = 0;
	int pointThree = 1;

	for(int i = 0; i < points.size() && !found; i++)
	{

		//Form Vectors from the three points using the iterators
		tuple vec1 = tuple(points[pointOne].x - points[pointTwo].x, points[pointOne].y - points[pointTwo].y);
		tuple vec2 = tuple(points[pointThree].x - points[pointTwo].x, points[pointThree].y - points[pointTwo].y);

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


		//else
		else
		{
			pointOne = pointOne + 1 % points.size();	
			pointTwo = pointTwo + 1 % points.size();
			pointThree = pointThree + 1 % points.size();
		}
	}
	return pointTwo;
}

bool isClockwise( vector<tuple> points )
{
	double sum = 0.0;
	for( vector<tuple>::iterator it = points.begin(); 
			it != points.end(); it++ )
	{
		if( (it+1) != points.end() )
			sum += ( (it+1)->x - it->x ) * ( (it+1)->y - it->y );
		else
			sum += ( points.begin()->x - it->x ) * ( points.begin()->y - it->y );
	}

	return sum > 0.0;
}

double area(triangle tri)
{
	return abs( ( tri.p1.x * (tri.p2.y - tri.p3.y) + 
				  tri.p2.x * (tri.p1.y - tri.p3.y) +
				  tri.p3.x * (tri.p1.y - tri.p2.y) ) / 2.0 );
}

void printTriangles(vector<triangle> triangles)
{
	int i = 1;
	for( vector<triangle>::iterator it = triangles.begin(); 
			it != triangles.end(); it++, i++ )
	{
		cout << "Triangle " << i <<": ";
		cout << "( " << it->p1.x << ", " << it->p1.y << " ) ";
		cout << "( " << it->p2.x << ", " << it->p2.y << " ) ";
		cout << "( " << it->p3.x << ", " << it->p3.y << " )" << endl;
	}
}
