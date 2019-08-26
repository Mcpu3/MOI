#pragma once

#include <Siv3D.hpp>
using namespace std;

class FieldPoints {
public:
	const int height, weight;
	const vector<vector<int>> points;
	vector<vector<bool>> isWall;

	FieldPoints(const int& height, const int& weight, const vector<vector<int>>& points) :
		height(height),
		weight(weight),
		points(points),
		isWall(2 + height, vector<bool>(2 + weight)) {
		for (int i = 0; i < 2 + height; ++i) {
			isWall[i].front() = true;
			isWall[i].back() = true;
		}
		for (int i = 0; i < 2 + weight; ++i) {
			isWall.front()[i] = true;
			isWall.back()[i] = true;
		}
	}
};

class FieldTiled {
public:
	vector<vector<int>> tiled;

	FieldTiled(const int& height, const int& weight) : tiled(2 + height, vector<int>(2 + weight)) {}
};