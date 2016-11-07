#include<iostream>
#include<vector>
#include<istream>
#include<iterator>
#include<map>
#include<unordered_map>
#include<utility>
struct Point
{
	double x=0,y=0;
};

struct Segment
{
	Point A,B;
};

bool operator<(const Point&,const Point&);
bool operator<(const Segment&,const Segment&);
bool operator==(const Point&,const Point&);

struct Context
{
	bool U=false,L=false,M=false;
	Segment S;
};

struct Event
{
	Point P;
	std::vector<Context> info;
};
using SLP=std::unordered_map<Segment,Segment,size_t(*)(const Segment&),bool(*)(const Segment&,const Segment&)>;

struct EVENTQ;

struct STATUSTREE {
	std::map<Segment,Segment> statusline;
	std::pair<bool,Segment> nextNonOverlappingSegment(const EVENTQ&,const Segment&);
	std::pair<bool,Segment> beforeNonOverlappingSegment(const EVENTQ&,const Segment&);
	std::pair<bool,Segment> nextSegment(const Segment&);
	std::pair<bool,Segment> beforeSegment(const Segment&);
};

struct EVENTQ {
	std::map<Point,Event> event;
	void eventifyPoint(const Point&,const Context&);
	friend std::pair<bool,Segment> STATUSTREE::nextNonOverlappingSegment(const EVENTQ&,const Segment&);
	friend std::pair<bool,Segment> STATUSTREE::beforeNonOverlappingSegment(const EVENTQ&,const Segment&);
};

struct IPCLASS {
std::map<Point,std::vector<Segment>> IP;
void IPify(const Point&,const Segment&);
};
