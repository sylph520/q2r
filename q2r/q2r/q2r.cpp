// q2r.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

struct imgInfo
{
	int idx;
	int circleNum;
	vector<Vec3f> circles;
	int lineNum;
	vector<Vec4i> lines;
};
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
		cout << info.idx << endl;

	}
	cout << "end reading infos" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// first read the result file
	char* fileName = "detectedResult.txt";
	vector<imgInfo> imgInfos;
	readResultFile(fileName, imgInfos);
	imgInfo imgif = imgInfos[0];
	vector<Vec2i> imgifPoints;

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
	cout << imgifPoints.size() << endl;
	getchar();
	return 0;
}

