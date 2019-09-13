#pragma once

#include <Siv3D.hpp>
using namespace std;

class FixedField {
public:
	int width, height, startedAtUnixTime;
	vector<vector<int>> points;
	vector<vector<bool>> isWall;

	FixedField() = default;

	FixedField(const int& width, const int& height, const int& startedAtUnixTime, const vector<vector<int>>& points) :
		width(width),
		height(height),
		startedAtUnixTime(startedAtUnixTime),
		points(points),
		isWall(2 + height, vector<bool>(2 + width)) {
		for (int i = 0; i < 2 + height; ++i) {
			isWall[i].front() = true;
			isWall[i].back() = true;
		}

		for (int i = 0; i < 2 + width; ++i) {
			isWall.front()[i] = true;
			isWall.back()[i] = true;
		}
	}
};

class VariableField {
public:
	int turn;
	vector<vector<int>> tiled;

	VariableField() = default;

	VariableField(const int& turn, const vector<vector<int>>& tiled) :
		turn(turn),
		tiled(tiled)
	{}
};