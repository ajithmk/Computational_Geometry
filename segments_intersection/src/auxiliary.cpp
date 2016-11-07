#include"myheader.h"
#include"Dense"
#include<cmath>

std::istream& operator>>(std::istream& i,Segment& S)
{
	i>>S.A.x;
	i>>S.A.y;
	i>>S.B.x;
	i>>S.B.y;
	return i;
}

Segment manufactureKey(const Segment& S,const Point& P)
{
	if(S.A<S.B)
		return Segment{P,S.B};
	else
		return Segment{P,S.A};
}

std::pair<bool,Point> intersectionPoint(const Segment& S1,const Segment& S2)
{
	using namespace Eigen;
	Vector2d B;
	const double D1=(S1.B.y-S1.A.y)/(S1.B.x-S1.A.x);
	const double D2=(S2.B.y-S2.A.y)/(S2.B.x-S2.A.x);
	B << D1*S1.A.x-S1.A.y,D2*S2.A.x-S2.A.y;
	Matrix2d A;
	A << D1,-1,D2,-1;
	Vector2d X = A.colPivHouseholderQr().solve(B);
	double DistAtoX = std::pow((S1.A.x-X[0]),2)+std::pow((S1.A.y-X[1]),2);
	double DistBtoX = std::pow((S1.B.x-X[0]),2)+std::pow((S1.B.y-X[1]),2);
	double Dist = std::pow((S1.A.x-S1.B.x),2)+std::pow((S1.A.y-S1.B.y),2);
	double Dist1 = (DistAtoX>DistBtoX) ? DistAtoX : DistBtoX;
	if(Dist<Dist1)  return std::make_pair(false,S1.A); else return std::make_pair(true,Point{X[0],X[1]});
}

bool operator<(const Point& P1,const Point& P2)
{
	if(P1.y>P2.y) return true;
	if(P1.y<P2.y) return false;
	if(P1.x<P2.x) return true;
	else return false;
}

bool operator<(const Segment& S1,const Segment& S2)
{
	Point S1P1,S1P2,S2P1,S2P2;
	if(S1.A<S1.B) {S1P1=S1.A;S1P2=S1.B;}
	else {S1P1=S1.B;S1P2=S1.A;}
	if(S2.A<S2.B) {S2P1=S2.A;S2P2=S2.B;}
	else {S2P1=S2.B;S2P2=S2.A;}
	if(S1P1.x<S2P1.x) return true;
	if(S1P1.x>S2P1.x) return false;
	if(S1P2.x<S2P2.x) return true;
	if(S1P2.x>S2P2.x) return false;
}
