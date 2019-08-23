#pragma once

#include <Siv3D.hpp>
using namespace std;

class Field {
public:
	const int weight, height;
	const vector<vector<int>> points;
	vector<vector<int>> tiled;

	Field(const int& weight, const int& height, const vector<vector<int>>& points) :
		weight(weight),
		height(height),
		points(points) {
		tiled = vector<vector<int>>(height, vector<int>(weight));
	}
};