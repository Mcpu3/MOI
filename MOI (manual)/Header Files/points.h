#pragma once

#include <Siv3D.hpp>
#include <queue>
#include "Field.h"
#include "teams.h"
using namespace std;

class Points {
private:
	const Field& _field;
	const Teams _teams;

public:
	Points(const Field& field, const Teams& teams) :
		_field(field),
		_teams(teams)
	{}

	pair<int, int> getTilePoint() {
		const vector<int> _teamID{ _teams.teams.first.teamID, _teams.teams.second.teamID };
		vector<int> _tilePoint(2);

		for (int i = 0; i < _field.height; ++i) {
			for (int j = 0; j < _field.weight; ++j) {
				for (int k = 0; k < 2; ++k) {
					if (_field.tiled[i][j] == _teamID[k]) _tilePoint[k] += _field.points[i][j];
				}
			}
		}
		return { _tilePoint[0], _tilePoint[1] };
	}

	pair<int, int> getAreaPoint() {
		const vector<int> _teamID{ _teams.teams.first.teamID, _teams.teams.second.teamID };
		queue<pair<int, int>> _queue;
		vector<int> _areaPoint(2);

		for (int i = 0; i < 2; ++i) {
			vector<vector<bool>> _visits(_field.height, vector<bool>(_field.weight));

			for (int j = 0; j < _field.height; ++j) {
				_queue.push({ j, _field.weight - 1 });
				_queue.push({ j, 0 });
				_visits[j].front() = true;
				_visits[j].back() = true;
				while (!_queue.empty()) {
					if (!_visits[_queue.front().first][_queue.front().second] && _field.tiled[_queue.front().first][_queue.front().second] != _teamID[i]) {
						if (_field.height - 1 != _queue.front().first) {
							_queue.push({ 1 + _queue.front().first, _queue.front().second });
							_visits[1 + _queue.front().first][_queue.front().second] = true;
						}
						if (_field.weight - 1 != _queue.front().second) {
							_queue.push({ _queue.front().first, 1 + _queue.front().second });
							_visits[_queue.front().first][1 + _queue.front().second] = true;
						}
						if (_queue.front().first) {
							_queue.push({ _queue.front().first - 1, _queue.front().second });
							_visits[_queue.front().first - 1][_queue.front().second] = true;
						}
						if (_queue.front().second) {
							_queue.push({ _queue.front().first, _queue.front().second - 1 });
							_visits[_queue.front().first][_queue.front().second - 1] = true;
						}
					}
					_queue.pop();
				}
			}
			for (int j = 0; j < _field.weight; ++j) {
				_queue.push({ _field.height - 1, j });
				_queue.push({ 0, j });
				_visits.front()[j] = true;
				_visits.back()[j] = true;
				while (!_queue.empty()) {
					if (!_visits[_queue.front().first][_queue.front().second] && _field.tiled[_queue.front().first][_queue.front().second] != _teamID[i]) {
						if (_field.height - 1 != _queue.front().first) {
							_queue.push({ 1 + _queue.front().first, _queue.front().second });
							_visits[1 + _queue.front().first][_queue.front().second] = true;
						}
						if (_field.weight - 1 != _queue.front().second) {
							_queue.push({ _queue.front().first, 1 + _queue.front().second });
							_visits[_queue.front().first][1 + _queue.front().second] = true;
						}
						if (_queue.front().first) {
							_queue.push({ _queue.front().first - 1, _queue.front().second });
							_visits[_queue.front().first - 1][_queue.front().second] = true;
						}
						if (_queue.front().second) {
							_queue.push({ _queue.front().first, _queue.front().second - 1 });
							_visits[_queue.front().first][_queue.front().second - 1] = true;
						}
					}
					_queue.pop();
				}
			}
			for (int j = 0; j < _field.height; ++j) {
				for (int k = 0; k < _field.weight; ++k) {
					if (!_visits[j][k] && _field.tiled[j][k] != _teamID[i]) _areaPoint[i] += abs(_field.points[j][k]);
				}
			}
		}
		return { _areaPoint[0], _areaPoint[1] };
	}
};