#pragma once

#include <Siv3D.hpp>
#include <queue>
#include "field.h"
#include "teams.h"
using namespace std;

class Points {
private:
	const FieldPoints& _fieldPoints;
	const FieldTiled& _fieldTiled;
	const Team& _team;

public:
	Points(const FieldPoints& fieldPoints, const FieldTiled& fieldTiled, const Team& team) :
		_fieldPoints(fieldPoints),
		_fieldTiled(fieldTiled),
		_team(team)
	{}

	int getAreaPoint() {
		const vector<pair<int, int>> _dydx{ { -1, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 } };
		int _areaPoint = 0;
		queue<pair<int, int>> _queue;
		vector<vector<bool>> _visits(2 + _fieldPoints.height, vector<bool>(2 + _fieldPoints.weight));

		for (int i = 1; i <= _fieldPoints.height; ++i) {
			_visits[i][1] = true;
			_visits[i][_fieldPoints.weight] = true;
			if (_fieldTiled.tiled[i][1] != _team.teamID) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fieldPoints.isWall[i + j.first][1 + j.second] && !_visits[i + j.first][1 + j.second]) _queue.emplace(i + j.first, 1 + j.second);
				}
			}
			if (_fieldTiled.tiled[i][_fieldPoints.weight] != _team.teamID) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fieldPoints.isWall[i + j.first][_fieldPoints.weight + j.second] && !_visits[i + j.first][_fieldPoints.weight + j.second]) _queue.emplace(i + j.first, _fieldPoints.weight + j.second);
				}
			}
			while (!_queue.empty()) {
				_visits[_queue.front().first][_queue.front().second] = true;
				if (_fieldTiled.tiled[_queue.front().first][_queue.front().second] != _team.teamID) {
					for (const pair<int, int>& j : _dydx) {
						if (!_fieldPoints.isWall[_queue.front().first + j.first][_queue.front().second + j.second] && !_visits[_queue.front().first + j.first][_queue.front().second + j.second]) _queue.emplace(_queue.front().first + j.first, _queue.front().second + j.second);
					}
				}
				_queue.pop();
			}
		}
		for (int i = 1; i <= _fieldPoints.weight; ++i) {
			_visits[1][i] = true;
			_visits[_fieldPoints.height][i] = true;
			if (_fieldTiled.tiled[1][i] != _team.teamID) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fieldPoints.isWall[1 + j.first][i + j.second] && !_visits[1 + j.first][i + j.second]) _queue.emplace(1 + j.first, i + j.second);
				}
			}
			if (_fieldTiled.tiled[_fieldPoints.height][i] != _team.teamID) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fieldPoints.isWall[_fieldPoints.height + j.first][i + j.second] && !_visits[_fieldPoints.height + j.first][i + j.second]) _queue.emplace(_fieldPoints.height + j.first, i + j.second);
				}
			}
			while (!_queue.empty()) {
				_visits[_queue.front().first][_queue.front().second] = true;
				if (_fieldTiled.tiled[_queue.front().first][_queue.front().second] != _team.teamID) {
					for (const pair<int, int>& j : _dydx) {
						if (!_fieldPoints.isWall[_queue.front().first + j.first][_queue.front().second + j.second] && !_visits[_queue.front().first + j.first][_queue.front().second + j.second]) _queue.emplace(_queue.front().first + j.first, _queue.front().second + j.second);
					}
				}
				_queue.pop();
			}
		}
		for (int i = 1; i <= _fieldPoints.height; ++i) {
			for (int j = 1; j <= _fieldPoints.weight; ++j) {
				if (!_visits[i][j] && _fieldTiled.tiled[i][j] != _team.teamID) _areaPoint += abs(_fieldPoints.points[i][j]);
			}
		}
		return _areaPoint;
	}

	int getTilePoint() {
		int _tilePoint = 0;

		for (int i = 1; i <= _fieldPoints.height; ++i) {
			for (int j = 1; j <= _fieldPoints.weight; ++j) {
				if (_fieldTiled.tiled[i][j] == _team.teamID) _tilePoint += _fieldPoints.points[i][j];
			}
		}
		return _tilePoint;
	}
};