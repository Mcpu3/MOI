#pragma once

#include "field.h"
#include "match.h"
#include "reader.h"
#include "teams.h"
#include <Siv3D.hpp>
#include <queue>
using namespace std;

class Visualizer {
public:
	enum class AreaPoint {
		GARNET,
		GARNET_AND_TURQUOISE,
		GRAY,
		TURQUOISE
	};

private:
	Stopwatch _stopwatch;
	const FixedField _fixedField;
	VariableField _variableField;
	const Match _match;
	Teams _teams;
	const pair<Font, Font> _fonts;
	vector<vector<AreaPoint>> _areaPoints;
	vector<vector<RectF>> _rectfs;

	void initializeAreaPoints() {
		const vector<pair<int, int>> _dydx{ { -1, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 } };
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
				if (!_visits.first[i][j] && _teams.teams.first.teamID != _variableField.tiled[i][j]) {
					if (!_visits.second[i][j] && _teams.teams.second.teamID != _variableField.tiled[i][j]) _areaPoints[i][j] = AreaPoint::GARNET_AND_TURQUOISE;
					else _areaPoints[i][j] = AreaPoint::TURQUOISE;
				}
				else if (!_visits.second[i][j] && _teams.teams.second.teamID != _variableField.tiled[i][j]) _areaPoints[i][j] = AreaPoint::GARNET;
				else _areaPoints[i][j] = AreaPoint::GRAY;
			}
		}
	}

public:
	Visualizer() :
		_stopwatch(true),
		_fixedField(Reader::readFixedField()),
		_variableField(Reader::readVariableField(_fixedField)),
		_match(Reader::readMatch()),
		_teams(Reader::readTeams(_match)),
		_fonts(16, 32),
		_areaPoints(2 + _fixedField.height, vector<AreaPoint>(2 + _fixedField.width)),
		_rectfs(2 + _fixedField.height, vector<RectF>(2 + _fixedField.width)) {
		for (int i = 0; i < 2 + _fixedField.height; ++i) {
			for (int j = 0; j < 2 + _fixedField.width; ++j) _rectfs[i][j] = RectF({ 32.0 * j - 15.0, 32.0 * i + 81.0 }, { 30.0, 30.0 });
		}

		initializeAreaPoints();
	}

	void visualize() {
		if (_stopwatch.s()) {
			_stopwatch.restart();
			_teams = Reader::readTeams(_match);
			_variableField = Reader::readVariableField(_fixedField);
			initializeAreaPoints();
		}

		_fonts.second(Format(U"Team ID: ", _teams.teams.first.teamID)).drawAt({ 168.0, 80.0 }, { 0.0, 155.0 / 255.0, 159.0 / 255.0 });
		_fonts.second(Format(U"Team ID: ", _teams.teams.second.teamID)).drawAt({ 504.0, 80.0 }, { 148.0 / 255.0, 35.0 / 255.0, 67.0 / 255.0 });
		_fonts.second(Format(U"Turn: ", _variableField.turn)).drawAt({ 336.0, 32.0 }, ColorF(0.2));
		_fonts.second(_teams.teams.first.areaPoint + _teams.teams.first.tilePoint).drawAt({ 168.0, 784.0 }, { 0.0, 155.0 / 255.0, 159.0 / 255.0 });
		_fonts.second(_teams.teams.second.areaPoint + _teams.teams.second.tilePoint).drawAt({ 504.0, 784.0 }, { 148.0 / 255.0, 35.0 / 255.0, 67.0 / 255.0 });

		for (int i = 1; i <= _fixedField.height; ++i) {
			for (int j = 1; j <= _fixedField.width; ++j) {
				if (_variableField.tiled[i][j]) {
					if (_teams.teams.first.teamID == _variableField.tiled[i][j]) _rectfs[i][j].draw({ 0.0, 155.0 / 255.0, 159.0 / 255.0, 0.5 });
					else _rectfs[i][j].draw({ 148.0 / 255.0, 35.0 / 255.0, 67.0 / 255.0, 0.5 });
				}

				_fonts.first(_fixedField.points[i][j]).drawAt(_rectfs[i][j].center(), ColorF(0.2));

				if (AreaPoint::GARNET == _areaPoints[i][j]) _rectfs[i][j].drawFrame(2.0, 0.0, { 148.0 / 255.0, 35.0 / 255.0, 67.0 / 255.0 });
				else if (AreaPoint::GARNET_AND_TURQUOISE == _areaPoints[i][j]) _rectfs[i][j].drawFrame(2.0, 0.0, { 74.0 / 255.0, 95.0 / 255.0, 113.0 / 255.0 });
				else if (AreaPoint::GRAY == _areaPoints[i][j]) _rectfs[i][j].drawFrame(2.0, 0.0, ColorF(0.8));
				else _rectfs[i][j].drawFrame(2.0, 0.0, { 0.0, 155.0 / 255.0, 159.0 / 255.0 });
			}
		}
		for (const Agent& i : _teams.teams.first.agents.agents) {
			Circle _circle(_rectfs[i.yx.first][i.yx.second].center(), 8.0);

			_circle.draw({ 0.0, 155.0 / 255.0, 159.0 / 255.0 });
			_fonts.first(i.agentID).drawAt(_circle.center);
		}
		for (const Agent& i : _teams.teams.second.agents.agents) {
			Circle _circle(_rectfs[i.yx.first][i.yx.second].center(), 8.0);

			_circle.draw({ 148.0 / 255.0, 35.0 / 255.0, 67.0 / 255.0 });
			_fonts.first(i.agentID).drawAt(_circle.center);
		}
	}
};