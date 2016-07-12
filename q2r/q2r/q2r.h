#include "stdafx.h"
struct pointX
{
	bool cflag;// wheather it's  circle center or not
	int p_idx; // the sequence, if -1 , it's a circle center.
	int px, py;
	vector<int> l_idx;
	vector<int> c_idx;
	string label = "";
	string p[2] ;
};
struct lineX
{
	int l_idx; vector<int> p_idxs;
	int px1, py1, px2, py2;
	double length;
	string label = "";
	string w[3];
};
struct circleX
{
	int c_idx; vector<int> p_idxs;
	float cx, cy;
	float radius;
	string label = "";
	string c[2] ;
	//string cEquation="";
};

struct distance_info
{
	Vec2i pt1; Vec2i pt2;// the points to calculate on
	double distance;//computed distance results with pt1 and pt2
};