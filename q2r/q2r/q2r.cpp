// q2r.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <fstream>
#include "q2r.h"
struct imgInfo
{
	int idx;
	int circleNum;
	vector<Vec3f> circles;
	int lineNum;
	vector<Vec4i> lines;
};
struct angleInfo
{
	int l1, l2;
	double angle;
};
string PtOnCircle2String(circleX circle, string pt[2])
{
	string ret = ""; 
	char leftpa = '('; char rightpa = ')'; string minus = " - "; string plus = " + "; string square = "^2"; string eq = " = ";
	ret += leftpa; ret += pt[0]; ret += minus; ret += (circle.c[0]); ret += rightpa; ret += square;
	ret += plus;
	ret += leftpa; ret += pt[1]; ret += minus; ret += (circle.c[1]); ret += rightpa; ret += square;
	ret += eq;
	ret += to_string(circle.radius); ret += square;
	//ret = '(' + pt[0] + " - " + to_string(circle.c[0]) + ')' + '^' + '2' + " + "+
	//	'(' + pt[1] + " - " + to_string(circle.c[1]) + ')' + '^' + '2' + " = " + to_string(circle.radius*circle.radius);
	return ret;
}
string PtOnLine2String(lineX line, string pt[2])
{
	string ret;
	char leftpa = '('; char rightpa = ')'; string minus = " - "; string plus = " + "; string mul = " * "; string eq = " = ";
	ret = line.w[0]; ret += mul; ret += pt[0]; ret += plus;
	ret += line.w[1]; ret += mul; ret += pt[1]; ret += plus;
	ret += line.w[2]; ret += eq; ret += "0";
	return ret;
}
string parallelLine2String(Vec2i prLinePair, vector<lineX> lines, vector<pointX> points)
{
	lineX line1, line2;
	line1 = lines[prLinePair[0]]; line2 = lines[prLinePair[1]];
	pointX pt1 = points[line1.p_idx1]; pointX pt2 = points[line1.p_idx2]; pointX pt3 = points[line2.p_idx1]; pointX pt4 = points[line2.p_idx2];
	string ret= ""; 
	char leftpa = '('; char rightpa = ')'; string minus = " - "; string plus = " + "; string mul = " * "; string eq = " = ";
	ret += leftpa; ret += pt4.p[1]; ret += minus; ret += pt3.p[1]; ret += rightpa; ret += mul;
	ret += leftpa; ret += pt2.p[0]; ret += minus; ret += pt1.p[0]; ret += rightpa; ret += minus;
	ret += leftpa; ret += pt4.p[0]; ret += minus; ret += pt3.p[0]; ret += rightpa; ret += mul;
	ret += leftpa; ret += pt2.p[1]; ret += minus; ret += pt1.p[1]; ret += rightpa; ret += eq;
	ret += "0";
	return ret;
}
string perpendicularLine2String(Vec2i ppLinePair, vector<lineX> lines, vector<pointX> points)
{
	lineX line1, line2;
	line1 = lines[ppLinePair[0]]; line2 = lines[ppLinePair[1]];
	pointX pt1 = points[line1.p_idx1]; pointX pt2 = points[line1.p_idx2]; pointX pt3 = points[line2.p_idx1]; pointX pt4 = points[line2.p_idx2];
	string ret = "";
	char leftpa = '('; char rightpa = ')'; string minus = " - "; string plus = " + "; string mul = " * "; string eq = " = ";
	ret += leftpa; ret += pt4.p[1]; ret += minus; ret += pt3.p[1]; ret += rightpa; ret += mul;
	ret += leftpa; ret += pt2.p[1]; ret += minus; ret += pt1.p[1]; ret += rightpa; ret += minus;
	ret += leftpa; ret += pt4.p[0]; ret += minus; ret += pt3.p[0]; ret += rightpa; ret += mul;
	ret += leftpa; ret += pt2.p[0]; ret += minus; ret += pt1.p[0]; ret += rightpa; ret += eq;
	ret += "0";
	return ret;
}
string leneqLine2String(Vec2i leLinePair, vector<lineX> lines, vector<pointX> points)
{
	lineX line1, line2;
	line1 = lines[leLinePair[0]]; line2 = lines[leLinePair[1]];
	pointX pt1 = points[line1.p_idx1]; pointX pt2 = points[line1.p_idx2]; pointX pt3 = points[line2.p_idx1]; pointX pt4 = points[line2.p_idx2];
	string ret = "";
	char leftpa = '('; char rightpa = ')'; string minus = " - "; string plus = " + "; string square = "^2"; string eq = " = ";
	ret += leftpa; ret += pt2.p[0]; ret += minus; ret += pt1.p[0]; ret += rightpa; ret += square; ret += plus;
	ret += leftpa; ret += pt2.p[1]; ret += minus; ret += pt1.p[1]; ret += rightpa; ret += square; ret += eq;
	ret += leftpa; ret += pt4.p[0]; ret += minus; ret += pt3.p[0]; ret += rightpa; ret += square; ret += plus;
	ret += leftpa; ret += pt4.p[1]; ret += minus; ret += pt3.p[1]; ret += rightpa; ret += square;
	return ret;
}
string angeqLine2String(Vec4i aeLinePair, vector<lineX> lines, vector<pointX> points)
{
	lineX line1, line2,line3, line4;
	line1 = lines[aeLinePair[0]]; line2 = lines[aeLinePair[1]]; line3 = lines[aeLinePair[2]]; line4 = lines[aeLinePair[3]];
	pointX pt1 = points[line1.p_idx1]; pointX pt2 = points[line1.p_idx2]; pointX pt3 = points[line2.p_idx1]; pointX pt4 = points[line2.p_idx2];
	pointX pt5 = points[line3.p_idx1]; pointX pt6 = points[line3.p_idx2]; pointX pt7 = points[line4.p_idx1]; pointX pt8 = points[line4.p_idx2];
	string ret = "";
	char leftpa = '('; char rightpa = ')'; string minus = " - "; string plus = " + "; string square = "^2"; string eq = " = ";
	char div = '/';
	ret += "theta1";
	ret += 
	ret += eq;
	ret += "theta2";

}
void readResultFile(char* fileName, vector<imgInfo> &imgInfos)
{
	ifstream file(fileName, ios::in || ios::binary);
	if (!file)
	{
		cout << "can't open file" << endl;
		exit(-1);
	}
	char strChars[256]; int currentsect = 1;
	while (file.getline(strChars, 100))
	{
		imgInfo info; bool breakFlag = false;
		while (!breakFlag)
		{
			if (currentsect == 1)
			{
				info.idx = atoi(strChars);
				file.getline(strChars, 100);
				currentsect++;
			}
			else if (currentsect == 2)
			{
				info.circleNum = atoi(strChars);
				currentsect++;
				if (info.circleNum == 0)
				{
					file.getline(strChars, 100);
				}
				else
				{
					for (int k = 0; k < info.circleNum; k++)
					{
						file.getline(strChars, 100);
						string s(strChars);
						Vec3f circle;
						typedef string::size_type string_size;
						string_size i = 0;
						// invariant: we have processed characters [original value of i, i) 
						int tempCount = 0;
						while (i != s.size())
						{
							// ignore leading blanks
							// invariant: characters in range [original i, current i) are all spaces

							while (i != s.size() && isspace(s[i]))
								++i;

							// find end of next word
							string_size j = i;
							// invariant: none of the characters in range [original j, current j)is a space
							while (j != s.size() && !isspace(s[j]))
								j++;
							// if we found some nonwhitespace characters 
							if (i != j) {
								// copy from s starting at i and taking j - i chars
								circle[tempCount++] = stof(s.substr(i, j - i));
								i = j;
							}
						}
						info.circles.push_back(circle);

					}
					file.getline(strChars, 100);
				}

			}
			else if (currentsect == 3)
			{
				info.lineNum = atoi(strChars);
				vector<Vec4i> lines;
				for (int k = 0; k < info.lineNum; k++)
				{
					file.getline(strChars, 100);
					string s(strChars);
					Vec4i line;
					typedef string::size_type string_size;
					string_size i = 0;
					// invariant: we have processed characters [original value of i, i) 
					int tempCount = 0;
					while (i != s.size())
					{
						// ignore leading blanks
						// invariant: characters in range [original i, current i) are all spaces

						while (i != s.size() && isspace(s[i]))
							++i;

						// find end of next word
						string_size j = i;
						// invariant: none of the characters in range [original j, current j)is a space
						while (j != s.size() && !isspace(s[j]))
							j++;
						// if we found some nonwhitespace characters 
						if (i != j) {
							// copy from s starting at i and taking j - i chars
							line[tempCount++] = stof(s.substr(i, j - i));
							i = j;
						}
					}
					info.lines.push_back(line);
				}
				file.getline(strChars, 100);
				//cout << endl<<"test begin"<< strChars <<"test end"<< endl;
				currentsect = 1;
				breakFlag = true;
			}

		}
		imgInfos.push_back(info);
		//cout << info.idx << endl;

	}
	cout << "end reading infos" << endl;
}
double p2pdistance(Vec2i pt1, Vec2i pt2)
{
	double distance;
	distance = sqrt(powf((pt1[0] - pt2[0]), 2) + powf((pt1[1] - pt2[1]), 2));
	return distance;
}
bool on_line(Vec4i line, Vec2i pt)
{
	double linedis_eps = 3; double pointdis_eps = 5;
	Vec2i ref_point = { line[0], line[1] };
	Vec2i pt2 = { -pt[1], pt[0] };
	Vec2i ref_point_t = { line[1], -line[0] };
	Vec2i vec = { line[2] - line[0], line[3] - line[1] };
	double point2line = abs((pt2.dot(vec) + ref_point_t.dot(vec))) / sqrt(vec.dot(vec));
	if (point2line < linedis_eps)
		return true;
	else
		return false;
}
bool on_circle(Vec2i pt, Vec3f circle)
{
	// check if the point pt is on one of the circles,or joints of multiple circles, or nothing to do with circles
	// joint_flag parameter: 0 means not on any circle, 1 means on a circle, 2 means on two circles and so on
	int dis = 5;// this parameter is to be set to check on the distance tolerants within the distance between radius and distance of pt and circle center point
	int count = 0;

	Vec2f center = { circle[0], circle[1] };
	double radius = circle[2];
	double distance = p2pdistance(center, pt);
	if (abs(distance - radius) <= dis)
		return true;
	else
		return false;

}
void point_on_circle_line_check(vector<Vec2i> basicEndpoints, vector<Vec3f> circle_candidates, vector<circleX> &circles,
	vector<Vec4i> line_candidates, vector<lineX> &lines, vector<pointX> &points)
{
	//cout << basicEndpoints.size() << endl;
	for (int i = 0; i < basicEndpoints.size(); ++i)
	{
		Vec2i bpoint = basicEndpoints[i];
		pointX point;
		point.p_idx = i; point.px = bpoint[0]; point.py = bpoint[1];
		for (int j = 0; j < circle_candidates.size(); ++j)
		{
			Vec3f bcircle = circle_candidates[j];
			if (on_circle(basicEndpoints[i], bcircle))
			{
				point.c_idx.push_back(j);
			}

		}
		for (size_t k = 0; k < line_candidates.size(); ++k)
		{
			Vec4i bline = line_candidates[k];
			point.cflag = false;
			if (on_line(line_candidates[k], bpoint))
			{
				point.l_idx.push_back(k);
			}
		}
		points.push_back(point);
	}
	for (size_t k = 0; k < line_candidates.size(); ++k)
	{
		Vec4i bline = line_candidates[k];
		lineX line; Vec2i bpoint1, bpoint2; bpoint1 = { bline[0], bline[1] }; bpoint2 = { bline[2], bline[3] };
		line.l_idx = k; line.px1 = bline[0]; line.py1 = bline[1]; line.px2 = bline[2]; line.py2 = bline[3];
		line.length = p2pdistance(bpoint1, bpoint2);
		for (size_t l = 0; l < basicEndpoints.size(); ++l)
		{
			Vec2i bpoint = basicEndpoints[l];
			if (on_line(line_candidates[k], bpoint))
			{
				line.p_idxs.push_back(l);
			}
			if (basicEndpoints[l] == bpoint1)
			{
				line.p_idx1 = l;
			}
			else if (basicEndpoints[l] == bpoint2)
			{
				line.p_idx2 = l;
			}
		}

		lines.push_back(line);
	}
	for (size_t k = 0; k < circle_candidates.size(); ++k)
	{
		Vec3f bcircle = circle_candidates[k];
		circleX circle; circle.c_idx = k; circle.cx = bcircle[0]; circle.cy = bcircle[1]; circle.radius = bcircle[2];
		Vec2i center = { cvRound(bcircle[0]), cvRound(bcircle[1]) };
		for (size_t l = 0; l < basicEndpoints.size(); ++l)
		{
			Vec2i bpoint = basicEndpoints[l];
			if (on_circle(basicEndpoints[l], bcircle))
			{
				circle.p_idxs.push_back(l);
			}
		}
		circles.push_back(circle);
	}

	for (int i = 0; i < points.size(); ++i)
	{
		pointX point = points[i];
		cout << "point " << point.p_idx << " (" << point.px << ", " << point.py << ") " << " on circle ";
		for (int j = 0; j < point.c_idx.size(); ++j)
		{
			cout << point.c_idx[j] << ", ";
		}
		cout << "on line ";
		for (int k = 0; k < point.l_idx.size(); ++k)
		{
			cout << point.l_idx[k] << ", ";
		}
		cout << endl;
	}
	for (int m = 0; m < lines.size(); ++m)
	{
		lineX line = lines[m];
		cout << "point ";
		for (int n = 0; n < line.p_idxs.size(); ++n)
		{
			cout << line.p_idxs[n] << ", ";
		}
		cout << " is on line " << line.l_idx << endl;
	}
	for (int m = 0; m < circles.size(); ++m)
	{
		circleX circle = circles[m];
		cout << "point ";
		for (int n = 0; n < circle.p_idxs.size(); ++n)
		{
			cout << circle.p_idxs[n] << ", ";
		}
		cout << " is on circle " << circle.c_idx << endl;
	}
}
double angleOfLines(Vec4i line1, Vec4i line2)
{
	Vec2i line1V = { line1[2] - line1[0], line1[3] - line1[1] }; Vec2i line2V = { line2[2] - line2[0], line2[3] - line2[1] };
	double theta1 = (line1V[0] <= 3) ? CV_PI/2.0 : atan2(line1V[1] , line1V[0]);
	double theta2 = (line2V[0] <= 3) ? CV_PI/2.0 : atan2(line2V[1] , line2V[0]);
	cout << "theta1: " << theta1 / CV_PI * 180 << " theta2: " << theta2 / CV_PI * 180 << endl;
	double angle = abs(theta1 - theta2) / CV_PI * 180;
	return angle;
}
void line_perpendicular_check(vector<lineX> lines, vector<Vec2i> &ppLinePairs, vector<Vec2i> &prLinePairs, vector<Vec2i> &leLinePairs,vector<Vec4i> &aeLinePairs)
{
	vector<angleInfo> angleSets;
	for (int i = 0; i < lines.size(); i++)
	{
		Vec4i line1 = { lines[i].px1, lines[i].py1, lines[i].px2, lines[i].py2 };
		Vec2i pt1 = { line1[0], line1[1] }; Vec2i pt2 = { line1[2], line1[3] };
		double line1Len = p2pdistance(pt1, pt2);
		Vec2i line1V = { line1[2] - line1[0], line1[3] - line1[1] };
		for (int j = i + 1; j < lines.size(); j++)
		{
			Vec4i line2 = { lines[j].px1, lines[j].py1, lines[j].px2, lines[j].py2 };
			Vec2i pt3 = { line2[0], line2[1] }; Vec2i pt4 = { line2[2], line2[3] };
			double line2Len = p2pdistance(pt3, pt4);
			double aol = abs(angleOfLines(line1, line2));
			cout << i<<", "<<j<<"     "<<aol << endl;
			if (abs(aol - 90) < 5)
			{
				Vec2i ppLinePair = { i, j };
				ppLinePairs.push_back(ppLinePair);
			}
			else if (aol < 5)
			{
				Vec2i prLinePair = { i, j };
				prLinePairs.push_back(prLinePair);
			}
			
			if (abs(line2Len - line1Len) < 5)
			{
				Vec2i leLinePair = { i, j };
				leLinePairs.push_back(leLinePair);
			}
			angleInfo aInfo = { i, j, aol };
			angleSets.push_back(aInfo);
				
		}
	}
	for (int k = 0; k < angleSets.size(); k++)
	{
		angleInfo ai1 = angleSets[k];
		for (int l = k + 1; l < angleSets.size(); l++)
		{
			angleInfo ai2 = angleSets[l];
			if (abs(ai1.angle - ai2.angle) < 3)
			{
				Vec4i arLinePair = { ai1.l1, ai1.l2, ai2.l1, ai2.l2 };
				aeLinePairs.push_back(arLinePair);
			}
		}
	}
	//if (ppLinePairs.size() != 0)
	//{
	//	for (int k = 0; k < ppLinePairs.size(); k++)
	//	{
	//		cout << "pp pair: " << ppLinePairs[k][0] << " " << ppLinePairs[k][1] << endl;
	//	}
	//}
	//else
	//{
	//	cout << "no pp line pairs exists" << endl;
	//}
	//if (prLinePairs.size() != 0)
	//{
	//	for (int k = 0; k < prLinePairs.size(); k++)
	//	{
	//		cout << "pr pair: " << prLinePairs[k][0] << " " << prLinePairs[k][1] << endl;
	//	}
	//}
	//else
	//{
	//	cout << "no pr line pairs exists" << endl;
	//}
	//if (leLinePairs.size() != 0)
	//{
	//	for (int k = 0; k < leLinePairs.size(); k++)
	//	{
	//		cout << "le pair: " << leLinePairs[k][0] << " " << leLinePairs[k][1] << endl;
	//	}
	//}
	//else
	//{
	//	cout << "no le line pairs exists" << endl;
	//}
	//if (aeLinePairs.size() != 0)
	//{
	//	for (int k = 0; k < aeLinePairs.size(); k++)
	//	{
	//		cout << "ae pair: " << aeLinePairs[k][0] << " " << aeLinePairs[k][1] << " "
	//			<<aeLinePairs[k][2]<<" "<<aeLinePairs[k][3]<< endl;
	//	}
	//}
	//else
	//{
	//	cout << "no le line pairs exists" << endl;
	//}
	
}
void equationGenerate(vector<circleX> &circles,vector<lineX> &lines, vector<pointX> &points,
	vector<Vec2i> ppLinePairs, vector<Vec2i> prLinePairs, vector<Vec2i> leLinePairs, vector<Vec4i> aeLinePairs)
{
	vector<string> circleEquations, LineEquations,angleEquations;
	/* first 
	arrange all the points axis variables with a character, and set general circle and line equations
	*/
	// first handle the circle centers, and set the first cirlce center to be the original point (0, 0)
	for (int j = 0; j < points.size(); j++)
	{
		char suffix = j + '0';
		points[j].p[0] = 'p_x'; points[j].p[0] += suffix;
		points[j].p[1] = 'p_y'; points[j].p[1] += suffix;
	}
	for (int i = 0; i < circles.size(); i++)
	{

		char suffix = i + '0';
		circles[i].c[0] = "c_x"; circles[i].c[0] += suffix;
		circles[i].c[1] = "c_y"; circles[i].c[1] += suffix;
		for (int j = 0; j < circles[i].p_idxs.size(); ++j)
		{
			string e;
			int p_idx = circles[i].p_idxs[j];
			pointX pt = points[p_idx];
			e = PtOnCircle2String(circles[i], pt.p);
			cout << e << endl;
			circleEquations.push_back(e);
		}
	}
	for (int k = 0; k < lines.size(); k++)
	{
		//lineX line = lines[k];
		char suffix = k + '0';
		lines[k].w[0] = 'A'; lines[k].w[0] += suffix;
		lines[k].w[1] = 'B'; lines[k].w[1] += suffix;
		lines[k].w[2] = 'C'; lines[k].w[2] += suffix;

		for (int l = 0; l < lines[k].p_idxs.size(); ++l)
		{
			string e;
			int p_idx = lines[k].p_idxs[l];
			pointX pt = points[p_idx]; 
			e = PtOnLine2String(lines[k],pt.p);
			cout << e << endl;
			LineEquations.push_back(e);
		}

	}
	// then handle the regular points axis info arrangement


	/* second 
	begin relation representation
	*/
	// parallel relation
	for (int i = 0; i < prLinePairs.size(); ++i)
	{
		Vec2i prLinePair = prLinePairs[i];
		string e = parallelLine2String(prLinePair, lines, points);
		cout << e << endl;
		LineEquations.push_back(e);
	}
	// perpendicular relation
	for (int j = 0; j < ppLinePairs.size(); ++j)
	{
		Vec2i ppLinePair = ppLinePairs[j];
		string e = perpendicularLine2String(ppLinePair, lines, points);
		cout << e << endl;
		LineEquations.push_back(e);
	}
	// line length relation
	for (int m = 0; m < leLinePairs.size(); ++m)
	{
		Vec2i leLinePair = leLinePairs[m];
		string e = leneqLine2String(leLinePair, lines, points);
		cout << e << endl;
		LineEquations.push_back(e);
	}
	// angle relation
	for (int n = 0; n < aeLinePairs.size(); ++n)
	{
		Vec4i aeLinePair = aeLinePairs[n];
		string e = angeqLine2String(aeLinePair, lines, points);
		cout << e << endl;
		angleEquations.push_back(e);
	}


}

void handleImgInfo(imgInfo imgif, vector<Vec2i>& imgifPoints, vector<circleX> &circles, vector<lineX>& lines, vector<pointX>& points)
{
	for (int i = 0; i < imgif.lineNum; i++)
	{
		Vec2i pt1, pt2;
		Vec4i line = imgif.lines[i];
		pt1 = { line[0], line[1] }; pt2 = { line[2], line[3] };
		imgifPoints.push_back(pt1); imgifPoints.push_back(pt2);
	}
	sort(imgifPoints.begin(), imgifPoints.end(), [](Vec2i a, Vec2i b)
	{
		if (a[0] != b[0])
			return (a[0] < b[0]);
		else
			return (a[1] < b[1]);
	});
	imgifPoints.erase(unique(imgifPoints.begin(), imgifPoints.end()), imgifPoints.end());
	//cout << imgifPoints.size() << endl;
	//cout << "imgif lines size " << imgif.lines.size() << endl;
	point_on_circle_line_check(imgifPoints, imgif.circles, circles, imgif.lines, lines, points);
}
int _tmain(int argc, _TCHAR* argv[])
{
	// first read the result file
	char* fileName = "detectedResult.txt";
	vector<imgInfo> imgInfos;
	readResultFile(fileName, imgInfos);
	imgInfo imgif = imgInfos[0];
	vector<Vec2i> imgifPoints;
	vector<circleX> circles; vector<lineX> lines; vector<pointX> points;
	handleImgInfo(imgif, imgifPoints, circles, lines, points);

	vector<Vec2i> ppLinePairs, prLinePairs, leLinePairs; vector<Vec4i> aeLinePairs;
	line_perpendicular_check(lines, ppLinePairs, prLinePairs, leLinePairs, aeLinePairs);
	equationGenerate(circles,lines,points,ppLinePairs,prLinePairs,leLinePairs,aeLinePairs);
	getchar();
	return 0;
}

