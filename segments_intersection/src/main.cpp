#include"myheader.h"

using namespace std;

istream& operator>>(istream&,Segment&);
Segment manufactureKey(const Segment&,const Point&);
pair<bool,Point> intersectionPoint(const Segment&,const Segment&);

int main() 
{ 
	vector<Segment> segment_list; 
for(Segment S;cin>>S;) segment_list.push_back(S);
	auto hf=[](const Segment& S){return hash<unsigned long>{}(S.A.x)^hash<unsigned long>{}(S.A.y)^hash<unsigned long>{}(S.B.x)^hash<unsigned long>()(S.B.y);};
	auto he=[](const Segment& S,const Segment& S1){return (S.A==S1.A)&&(S.B==S1.B);};
	SLP segkey_lookup{1,hf,he}; 
	STATUSTREE statustree;
	EVENTQ eventQ;
	IPCLASS IPclass;
	for(auto I:segment_list)
	{
		Context c;
		if(I.A<I.B)
		{
			c.U=true;
			c.S=I;
			eventQ.eventifyPoint(I.A,c);
			c.U=false;
			c.L=true;
			c.S=I;
			eventQ.eventifyPoint(I.B,c);
		}
		else
		{
			c.L=true;
			c.S=I;
			eventQ.eventifyPoint(I.A,c);
			c.U=true;
			c.L=false;
			c.S=I;
			eventQ.eventifyPoint(I.B,c);
		}
	}
	for(auto COUNT:eventQ.event)
	{
		Event E=COUNT.second;
		Point P =COUNT.first;
		for(auto I:E.info)
		{
			if(I.U==true) 
			{
				auto key=manufactureKey(I.S,P);
				segkey_lookup.insert(make_pair(I.S,key));
				statustree.statusline.insert(make_pair(key,I.S));
				auto V1=statustree.nextNonOverlappingSegment(eventQ,key);
				auto V2=statustree.beforeNonOverlappingSegment(eventQ,key);
				pair<bool,Point> V3{},V4{};
				if(V1.first)
					V3=intersectionPoint(I.S,V1.second);
				if(V2.first)
					V4=intersectionPoint(I.S,V2.second);
				if(V3.first)
				{
					Context c{false,false,true,I.S};
					eventQ.eventifyPoint(V3.second,c);
					c=Context{false,false,true,V1.second};
					eventQ.eventifyPoint(V3.second,c);
				}
				if(V4.first)
				{
					Context c{false,false,true,I.S};
					eventQ.eventifyPoint(V4.second,c);
					c=Context{false,false,true,V2.second};
					eventQ.eventifyPoint(V4.second,c);
				}
			}
			if(I.L==1) 
			{
				auto key=(segkey_lookup.find(I.S))->second;
				auto V1=statustree.nextNonOverlappingSegment(eventQ,key);
				auto V2=statustree.beforeNonOverlappingSegment(eventQ,key);
				pair<bool,Point> V3{}; 
				if((V1.first)&&(V2.first))
					V3=intersectionPoint(I.S,V1.second);
				if(V3.first)
				{
					Context c{false,false,true,I.S};
					eventQ.eventifyPoint(V3.second,c);
					c=Context{false,false,true,V1.second};
					eventQ.eventifyPoint(V3.second,c);
				}
				statustree.statusline.erase(key);
			}
			if(I.M==1) 
			{
				auto key1=(segkey_lookup.find(I.S))->second;
				statustree.statusline.erase(key1);
				auto key=manufactureKey(I.S,P);
				segkey_lookup.insert(make_pair(I.S,key));
				statustree.statusline.insert(make_pair(key,I.S));
				auto V1=statustree.nextNonOverlappingSegment(eventQ,key);
				auto V2=statustree.beforeNonOverlappingSegment(eventQ,key);
				pair<bool,Point> V3{},V4{};
				if(V1.first)
					V3=intersectionPoint(I.S,V1.second);
				if(V2.first)
					V4=intersectionPoint(I.S,V2.second);
				if(V3.first)
				{
					Context c{false,false,true,I.S};
					eventQ.eventifyPoint(V3.second,c);
					c=Context{false,false,true,V1.second};
					eventQ.eventifyPoint(V3.second,c);
				}
				if(V4.first)
				{
					Context c{false,false,true,I.S};
					eventQ.eventifyPoint(V4.second,c);
					c=Context{false,false,true,V2.second};
					eventQ.eventifyPoint(V4.second,c);
				}

			}
		}
for(auto C:E.info)
    if(C.M==true) IPclass.IPify(P,C.S);
	}
	return 0;
}
