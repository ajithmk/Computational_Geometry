#include "myheader.h"

void EVENTQ::eventifyPoint(const Point& P,const Context& C)
{
	auto p=event.find(P);
	if(p==event.end())
	{
		Event e{P,{C}};
		event.insert(std::make_pair(P,e));
	}
	else
	{
		(*p).second.info.push_back(C);
	}
}

std::pair<bool,Segment> STATUSTREE::nextSegment(const Segment& key)
{
	auto V=statusline.find(key);
	if(++V==statusline.end())
		return std::make_pair(false,key);
	else return std::make_pair(true,V->second);
}

std::pair<bool,Segment> STATUSTREE::beforeSegment(const Segment& key)
{
	auto V=statusline.find(key);
	if(V==statusline.begin())
		return std::make_pair(false,key);
	else return std::make_pair(true,(--V)->second);
}

std::pair<bool,Segment> STATUSTREE::nextNonOverlappingSegment(const EVENTQ& e,const Segment& key)
{
	auto V=statusline.find(key);
	Point P=key.A;
	auto I=e.event.find(P)->second.info;
			while(V!=statusline.end())
			{
			int found=0;
			for(auto I1:I)
			{
			if((I1.S.A==V->second.A)&&(I1.S.B==V->second.B))
			{
			found=1;
			break;
			}
}
			if(found==1)
			{
			++V;
			continue;
			}
			else
			break;
			
			}
			if(V==statusline.end())
				return std::make_pair(false,key);
			else
				return std::make_pair(true,V->second);
}

std::pair<bool,Segment> STATUSTREE::beforeNonOverlappingSegment(const EVENTQ& e,const Segment& key)
{
	auto V=statusline.find(key);
	if(V==statusline.begin())
		return std::make_pair(false,key);
	Point P=key.A;
	auto I=e.event.find(P)->second.info;
			do
			{
			int found=0;
			for(auto I1:I)
			{
			if((I1.S.A==V->second.A)&&(I1.S.B==V->second.B))
			{
			found=1;
			break;
			}
}
			if(found==1)
			{
			--V;
			continue;
			}
			else
			break;
			
			} while(V!=statusline.begin());
			if(V==statusline.begin())
				return std::make_pair(false,key);
			else
				return std::make_pair(true,V->second);
}

void IPCLASS::IPify(const Point& P,const Segment& S)
{
	auto p=IP.find(P);
	if(p==IP.end())
	{
		std::vector<Segment> V{S};
		IP.insert(make_pair(P,V));
	}
	else
	{
		(*p).second.push_back(S);
	}
}

bool operator==(const Point& A,const Point& B)
{
if((A.x==B.x)&&(A.y==B.y))
return true;
else return false;
}
