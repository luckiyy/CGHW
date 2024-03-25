#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include "planet.h"
using namespace std;

class ObjLoader {
public:
	struct vertex {
		float x;
		float y;
		float z;
	};

	struct face3 {
		int vIndex[3];
		int vnIndex[3];
	};

	struct face4 {
		int vIndex[4];
		int vnIndex[4];
	};

	ObjLoader() {};
	ObjLoader(string filename, float* vertices);

	void Draw(Planet* p, int r);

private:
	vector<vertex> v;
	vector<vertex> vn;
	vector<face3> f3;
	vector<face4> f4;
	vector<float> vertices;
};

ObjLoader::ObjLoader(string filename, float* vertices) {
	int count = 0;
	ifstream file(filename.c_str());
	string line;
	while (getline(file, line)) {
		if (line.substr(0, 2) == "vn") {
			vertex Point;
			float x, y, z;
			istringstream s(line.substr(2));
			s >> Point.x; s >> Point.y; s >> Point.z;
			vn.push_back(Point);
		}
		else if (line.substr(0, 1) == "v") {
			vertex Point;
			float x, y, z;
			istringstream s(line.substr(2));
			s >> Point.x; s >> Point.y; s >> Point.z;
			v.push_back(Point);
		}
		else if (line.substr(0, 1) == "f") {
			string s = line.substr(2);
			int num = 0, x = 0, y = 0;
			vector<int> v;
			while (s.find('/', x) != string::npos) {
				num++;
				y = s.find('/', x);
				v.push_back(stoi(s.substr(x, y - x)) - 1);
				x = s.find('/', y + 1) + 1;
				y = s.find(' ', x);
				v.push_back(stoi(s.substr(x, y - x)) - 1);
				x = y + 1;
			}
			if (num == 3) {
				face3 face;
				for (int i = 0; i < 3; i++) {
					face.vIndex[i] = v[i * 2];
					face.vnIndex[i] = v[i * 2 + 1];
				}
				f3.push_back(face);
			}
			else if (num == 4) {
				face4 face;
				for (int i = 0; i < 4; i++) {
					face.vIndex[i] = v[i * 2];
					face.vnIndex[i] = v[i * 2 + 1];
				}
				f4.push_back(face);
			}
		}
	}
	file.close();
	int cnt = 0;
	for (int i = 0; i < f3.size(); i++) {
		for (int j = 0; j < 3; j++) {
			*(vertices + cnt) = v[f3[i].vIndex[j]].x;
			cnt++;
			*(vertices + cnt) = v[f3[i].vIndex[j]].y;
			cnt++;
			*(vertices + cnt) = v[f3[i].vIndex[j]].z;
			cnt++;

			*(vertices + cnt) = vn[f3[i].vnIndex[j]].x;
			cnt++;
			*(vertices + cnt) = vn[f3[i].vnIndex[j]].y;
			cnt++;
			*(vertices + cnt) = vn[f3[i].vnIndex[j]].z;
			cnt++;
		}
	}
}

void ObjLoader::Draw(Planet* p, int r)
{
	glColor3f(0.345f, 0.345f, 0.345f);
	int num = 10;
	for (int n = 0; n < num; n++) {
		glPushMatrix();
		float x = r * cos(n);
		float y = r * sin(n);
		glRotatef(p->rotation, 0.0f, 1.0f, 0.0f);
		glTranslatef(x, 0.0f, y);
		glScalef(0.0005f, 0.0005f, 0.0005f);
		for (int i = 0; i < f3.size(); i++) {
			glBegin(GL_TRIANGLES);

			glNormal3f(vn[f3[i].vnIndex[0]].x, vn[f3[i].vnIndex[0]].y, vn[f3[i].vnIndex[0]].z);
			glVertex3f(v[f3[i].vIndex[0]].x, v[f3[i].vIndex[0]].y, v[f3[i].vIndex[0]].z);

			glNormal3f(vn[f3[i].vnIndex[1]].x, vn[f3[i].vnIndex[1]].y, vn[f3[1].vnIndex[1]].z);
			glVertex3f(v[f3[i].vIndex[1]].x, v[f3[i].vIndex[1]].y, v[f3[i].vIndex[1]].z);

			glNormal3f(vn[f3[i].vnIndex[2]].x, vn[f3[i].vnIndex[2]].y, vn[f3[i].vnIndex[2]].z);
			glVertex3f(v[f3[i].vIndex[2]].x, v[f3[i].vIndex[2]].y, v[f3[i].vIndex[2]].z);

			glEnd();
		}
		glPopMatrix();
	}
}
