#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
#include<Eigen/Dense>
typedef struct{
	double x;
	double y;
}Point;
using namespace std;
using namespace Eigen;
bool comparator (const Point&, const Point&);
list<Point> findConvexHull(const list<Point>&);
bool middlePointDlt(const Point&, const Point&, const Point&);

int main()
{
	cout<<"Enter the number of points\n";
	int n;
	cin>>n;
	Point* p=new Point[n];
	cout<<"Enter the coordinates of the points separated by enter on prompt\n";
	for (int i=0;i<n;i++)
	{
		cout<<"Enter point "<<i+1<<"\n";
		cin>>p[i].x;
		cin>>p[i].y;
	}
	list<Point> points {p,p+n};
	points.sort(comparator);
	list<Point> ConvexHull = findConvexHull(points);
	for(auto I:ConvexHull)
	{
		cout<<I.x<<" "<<I.y<<" "<<"\n";
	}
	return 1;

}
bool comparator (const Point& P1, const Point& P2)
{
	if(P1.x<P2.x) return true;
	if((P1.x==P2.x)&&(P1.y<P2.y)) return true;
	return false;
}

list<Point> findConvexHull(const list<Point>& points)
{
	list<Point>::const_iterator iter1 = points.cbegin();
	list<Point>::const_reverse_iterator riter1 = points.crbegin();
	list<Point>::iterator iter2;
	list<Point> UpperHull { *iter1, *(++iter1) };
	list<Point> LowerHull { *(riter1), *(++riter1)};
	++iter1;
	for(;iter1!=points.cend();++iter1)
	{
		UpperHull.push_back(*iter1);
		while(UpperHull.size()>2)
		{
			iter2 = UpperHull.end();
			Point P1 = *(--iter2);
			Point P2 = *(--iter2);
			Point P3 = *(--iter2);
			if(middlePointDlt(P1,P2,P3))
				UpperHull.erase(++iter2);
			else break;
		}
	}
	++riter1;
	for(;riter1!=points.crend();++riter1)
	{
		LowerHull.push_back(*riter1);
		while(LowerHull.size()>2)
		{
			iter2 = LowerHull.end();
			Point P1 = *(--iter2);
			Point P2 = *(--iter2);
			Point P3 = *(--iter2);
			if(middlePointDlt(P1,P2,P3))
				UpperHull.erase(++iter2);
			else break;
		}
	}
	UpperHull.splice(UpperHull.end(),LowerHull,(LowerHull.begin())++,(LowerHull.end())--);
	return UpperHull;
}
bool middlePointDlt(const Point& P1, const Point& P2, const Point& P3)
{
	Vector2d V1;
	V1 << P1.x, P1.y;
	Vector2d V2;
	V2 << P2.x, P2.y;
	Vector2d V3;
	V3 << P3.x, P3.y;
	Vector2d A = (V1-V2).normalized();
	Vector2d B = (V3-V2).normalized();
	double dot = A.dot(B);
	if (dot > 1) dot = 1;
	if (dot < -1) dot = -1;
	double theta = acos(dot);
	if (theta > M_PI) return true;
	else return false;
}
