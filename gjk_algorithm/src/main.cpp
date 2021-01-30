#include<iostream> 
#include<vector> 
#include<fstream> 
#include<sstream>
#include<string>

#include"vocab1.h"

void fillgeometry(std::vector<Point>&,const std::string&);
int farthestPointIndex(const std::vector<Point>&,const Point&);
Point farthestMinowskiPoint(const std::vector<Point>&,
                            const std::vector<Point>&,
                            const Point&);
bool fartherthanOrigin(const Point&,const Point&);
Point operator-(const Point&,const Point&); 
Point cross(const Point&,const Point&);
float dot(const Point&,const Point&);
void reportNonIntersection();

int main(int argv,char** argc)
{
  if(argv!=2)
  {
    std::cout<<"Usage gjk-algorithm filename\n";
    return 0;
  }
  std::ifstream file{argc[1]}; 
  std::vector<Point> geometry1,geometry2; 
  std::string line; 
  getline(file,line); 
  fillgeometry(geometry1,line);
  getline(file,line);
  fillgeometry(geometry2,line);
  geometry1.shrink_to_fit();
  geometry2.shrink_to_fit();
  Point direction{1,1,1};
  const Point Origin{0,0,0};
  std::vector<Point> simplex;
  Point lastadded = farthestMinowskiPoint(geometry1,geometry2,direction);
  simplex.push_back(lastadded);
  direction = Origin-lastadded;
  lastadded = farthestMinowskiPoint(geometry1,geometry2,direction);
  if(!fartherthanOrigin(lastadded,direction)) 
  {
    reportNonIntersection();
    return 0;
  }
  simplex.push_back(lastadded);
  direction = cross(simplex[1]-simplex[0],
                    cross(Origin-simplex[0],simplex[1]-simplex[0]));
  lastadded = farthestMinowskiPoint(geometry1,geometry2,direction);
  if(!fartherthanOrigin(lastadded,direction)) 
  {
    reportNonIntersection();
    return 0;
  }
  simplex.push_back(lastadded);
  direction = cross(simplex[1]-simplex[0],simplex[2]-simplex[0]);
  lastadded = farthestMinowskiPoint(geometry1,geometry2,direction);
  simplex.push_back(lastadded);
  Point temp = simplex[0];
  simplex[0] = simplex[3];
  simplex[3] = temp;
  const int MAX_ITERATION = 20;
  int iteration = 0;
  while(fartherthanOrigin(lastadded,direction))
  {
    iteration++;
    if(iteration>MAX_ITERATION) 
    {
      std::cout<<"Intersection found\n";
      return 0;
    }
    else if(dot(cross((simplex[1]-simplex[0]),(simplex[2]-simplex[0])),(simplex[0]))>0)
    {
      if(dot(cross((simplex[3]-simplex[0]),(simplex[1]-simplex[0])),(simplex[0]))>0)
      {
        //Origin is in 6
	std::cout<<"Origin is in 6\n";
	direction = cross(simplex[1]-simplex[3],simplex[2]-simplex[3]);
	simplex[3] = simplex[0];
	simplex[0] = farthestMinowskiPoint(geometry1,geometry2,direction);
	lastadded = simplex[0];
      }
      else if(dot(cross((simplex[2]-simplex[0]),(simplex[3]-simplex[0])),(simplex[0]))>0)
      {
        //Origin is in 2
        std::cout<<"Origin is in 2\n";
        direction = cross(simplex[1]-simplex[3],simplex[2]-simplex[3]);
	simplex[3] = simplex[0];
	simplex[0] = farthestMinowskiPoint(geometry1,geometry2,direction);
	lastadded = simplex[0];

      }
      else
      {
        //Origin is in 1
        std::cout<<"Origin is in 1\n";
	direction = cross(simplex[1]-simplex[3],simplex[2]-simplex[3]);
	simplex[3] = simplex[0];
	simplex[0] = farthestMinowskiPoint(geometry1,geometry2,direction);
	lastadded = simplex[0];

      }
    }
    else if(dot(cross((simplex[3]-simplex[0]),(simplex[1]-simplex[0])),(simplex[0]))>0)
    {
      if(dot(cross((simplex[3]-simplex[0]),(simplex[2]-simplex[0])),(simplex[0]))>0)
      {
        //Origin is in 5
        std::cout<<"Origin is in 5\n";
        direction = cross(simplex[0]-simplex[3],simplex[1]-simplex[3]);
	simplex[2] = simplex[0];
	simplex[0] = farthestMinowskiPoint(geometry1,geometry2,direction);
	lastadded = simplex[0];

      }
      else
      {
        //Origin is in 4
        std::cout<<"Origin is in 4\n";
        direction = cross(simplex[0]-simplex[3],simplex[1]-simplex[3]);
	simplex[2] = simplex[0];
	simplex[0] = farthestMinowskiPoint(geometry1,geometry2,direction);
	lastadded = simplex[0];

      }
    }
    else
    {
      if(dot(cross((simplex[3]-simplex[0]),(simplex[2]-simplex[0])),(simplex[0]))>0)
      {
        //Origin is in 7
	std::cout<<"Intersection found\n";
	return 0;
      }
      else
      {
        //Origin is in 3 
	std::cout<<"Origin is in 3\n";
        direction = cross(simplex[2]-simplex[3],simplex[0]-simplex[3]);
	simplex[1] = simplex[0];
	simplex[0] = farthestMinowskiPoint(geometry1,geometry2,direction);
	lastadded = simplex[0];

      }
    }
  }
  return 0;
}

void fillgeometry(std::vector<Point>& geometry,const std::string& line)
{
  std::istringstream s{line};
  Point P;
  char c;
  while(s>>c)
  {
    if(c==',') s>>c;
    s>>P.X;
    s.ignore();
    s>>P.Y;
    s.ignore();
    s>>P.Z;
    s.ignore();
    geometry.push_back(P);
  }
}

int farthestPointIndex(const std::vector<Point>& geometry, const Point& dir) {
  float max = -20000.0;
  int index = 0;
  int maxIndex = 0;
  for(auto& P:geometry) {
    float temp = P.X*dir.X + P.Y*dir.Y + P.Z*dir.Z;
    if(temp > max ) {
      max = temp; 
      maxIndex = index;
    }
    index++;
  }
  return maxIndex;
}

Point farthestMinowskiPoint(const std::vector<Point>& geometry1,
                            const std::vector<Point>& geometry2,
                            const Point& dir)
{
  int index1 = farthestPointIndex(geometry1,dir);
  int index2 = farthestPointIndex(geometry2,Point{0,0,0}-dir);
  Point point;
  point.X = geometry1[index1].X - geometry2[index2].X;
  point.Y = geometry1[index1].Y - geometry2[index2].Y;
  point.Z = geometry1[index1].Z - geometry2[index2].Z;
  return point;
}

bool fartherthanOrigin(const Point& point,const Point& dir)
{
  return (point.X*dir.X + point.Y*dir.Y + point.Z*dir.Z > 0.0); 
}

Point operator-(const Point& point1,const Point& point2)
{
  return Point{point1.X-point2.X,point1.Y-point2.Y,point1.Z-point2.Z};
}

void reportNonIntersection()
{
  std::cout<<"No intersection";
}

Point cross(const Point& point1,const Point& point2)
{
  Point p;
  p.X = point1.Y*point2.Z - point2.Y*point1.Z;
  p.Y = point2.X*point1.Z - point2.Z*point1.X;
  p.Z = point1.X*point2.Y - point1.Y*point2.X;
  return p;
}

float dot(const Point& point1,const Point& point2)
{
  return (point1.X*point2.X+point1.Y+point2.Y+point1.Z*point2.Z);
}
