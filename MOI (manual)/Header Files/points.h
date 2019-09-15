#pragma once

#include "field.h"
#include "teams.h"
#include <Siv3D.hpp>
#include <queue>
using namespace std;

class Points {
private:
	const FixedField& _fixedField;
	const VariableField& _variableField;
	const Teams& _teams;

public:
	Points(const FixedField& fieldPoints, const VariableField& fieldTiled, const Teams& teams) :
		_fixedField(fieldPoints),
		_variableField(fieldTiled),
		_teams(teams)
	{}

	pair<int, int> getAreaPoint() {
		const vector<pair<int, int>> _dydx{ { -1, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 } };
		pair<int, int> _areaPoint;
		pair<queue<pair<int, int>>, queue<pair<int, int>>> _queue;
		pair<vector<vector<bool>>, vector<vector<bool>>> _visits({ vector<vector<bool>>(2 + _fixedField.height, vector<bool>(2 + _fixedField.width)) }, { vector<vector<bool>>(2 + _fixedField.height, vector<bool>(2 + _fixedField.width)) });

		for (int i = 1; i <= _fixedField.height; ++i) {
			_visits.first[i][1] = true;
			_visits.first[i][_fixedField.width] = true;
			_visits.second[i][1] = true;
			_visits.second[i][_fixedField.width] = true;

			if (_teams.teams.first.teamID != _variableField.tiled[i][1]) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fixedField.isWall[i + j.first][1 + j.second] && !_visits.first[i + j.first][1 + j.second]) _queue.first.emplace(i + j.first, 1 + j.second);
				}
			}

			if (_teams.teams.first.teamID != _variableField.tiled[i][_fixedField.width]) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fixedField.isWall[i + j.first][_fixedField.width + j.second] && !_visits.first[i + j.first][_fixedField.width + j.second]) _queue.first.emplace(i + j.first, _fixedField.width + j.second);
				}
			}

			if (_teams.teams.second.teamID != _variableField.tiled[i][1]) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fixedField.isWall[i + j.first][1 + j.second] && !_visits.second[i + j.first][1 + j.second]) _queue.second.emplace(i + j.first, 1 + j.second);
				}
			}

			if (_teams.teams.second.teamID != _variableField.tiled[i][_fixedField.width]) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fixedField.isWall[i + j.first][_fixedField.width + j.second] && !_visits.second[i + j.first][_fixedField.width + j.second]) _queue.second.emplace(i + j.first, _fixedField.width + j.second);
				}
			}
		}

		for (int i = 1; i <= _fixedField.width; ++i) {
			_visits.first[1][i] = true;
			_visits.first[_fixedField.height][i] = true;
			_visits.second[1][i] = true;
			_visits.second[_fixedField.height][i] = true;

			if (_teams.teams.first.teamID != _variableField.tiled[1][i]) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fixedField.isWall[1 + j.first][i + j.second] && !_visits.first[1 + j.first][i + j.second]) _queue.first.emplace(1 + j.first, i + j.second);
				}
			}

			if (_teams.teams.first.teamID != _variableField.tiled[_fixedField.height][i]) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fixedField.isWall[_fixedField.height + j.first][i + j.second] && !_visits.first[_fixedField.height + j.first][i + j.second]) _queue.first.emplace(_fixedField.height + j.first, i + j.second);
				}
			}

			if (_teams.teams.second.teamID != _variableField.tiled[1][i]) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fixedField.isWall[1 + j.first][i + j.second] && !_visits.second[1 + j.first][i + j.second]) _queue.second.emplace(1 + j.first, i + j.second);
				}
			}

			if (_teams.teams.second.teamID != _variableField.tiled[_fixedField.height][i]) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fixedField.isWall[_fixedField.height + j.first][i + j.second] && !_visits.second[_fixedField.height + j.first][i + j.second]) _queue.second.emplace(_fixedField.height + j.first, i + j.second);
				}
			}
		}

		while (!_queue.first.empty()) {
			_visits.first[_queue.first.front().first][_queue.first.front().second] = true;

			if (_teams.teams.first.teamID != _variableField.tiled[_queue.first.front().first][_queue.first.front().second]) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fixedField.isWall[_queue.first.front().first + j.first][_queue.first.front().second + j.second] && !_visits.first[_queue.first.front().first + j.first][_queue.first.front().second + j.second]) _queue.first.emplace(_queue.first.front().first + j.first, _queue.first.front().second + j.second);
				}
			}

			_queue.first.pop();
		}

		while (!_queue.second.empty()) {
			_visits.second[_queue.second.front().first][_queue.second.front().second] = true;

			if (_teams.teams.second.teamID != _variableField.tiled[_queue.second.front().first][_queue.second.front().second]) {
				for (const pair<int, int>& j : _dydx) {
					if (!_fixedField.isWall[_queue.second.front().first + j.first][_queue.second.front().second + j.second] && !_visits.second[_queue.second.front().first + j.first][_queue.second.front().second + j.second]) _queue.second.emplace(_queue.second.front().first + j.first, _queue.second.front().second + j.second);
				}
			}

			_queue.second.pop();
		}

		for (int i = 1; i <= _fixedField.height; ++i) {
			for (int j = 1; j <= _fixedField.width; ++j) {
				if (!_visits.first[i][j] && _teams.teams.first.teamID != _variableField.tiled[i][j]) _areaPoint.first += abs(_fixedField.points[i][j]);
				else if (!_visits.second[i][j] && _teams.teams.second.teamID != _variableField.tiled[i][j]) _areaPoint.second += abs(_fixedField.points[i][j]);
			}
		}

		return _areaPoint;
	}

	pair<int, int> getTilePoint() {
		pair<int, int> _tilePoint;

		for (int i = 1; i <= _fixedField.height; ++i) {
			for (int j = 1; j <= _fixedField.width; ++j) {
				if (_teams.teams.first.teamID == _variableField.tiled[i][j]) _tilePoint.first += _fixedField.points[i][j];
				else if (_teams.teams.second.teamID == _variableField.tiled[i][j]) _tilePoint.second += _fixedField.points[i][j];
			}
		}

		return _tilePoint;
	}
};