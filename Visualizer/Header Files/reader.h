#pragma once

#include "field.h"
#include "match.h"
#include "picojson.h"
#include "teams.h"
#include <Siv3D.hpp>
#include <fstream>
using namespace std;

class Reader {
public:
	static FixedField readFixedField() {
		ifstream _ifstream("get.json");
		picojson::value _value;

		picojson::parse(_value, _ifstream);
		_ifstream.close();

		int _width = static_cast<int>(_value.get<picojson::object>()["width"].get<double>());
		int _height = static_cast<int>(_value.get<picojson::object>()["height"].get<double>());
		int _startedAtUnixTime = static_cast<int>(_value.get<picojson::object>()["startedAtUnixTime"].get<double>());
		vector<vector<int>> _points(2 + _height, vector<int>(2 + _width));

		for (picojson::array::iterator i = _value.get<picojson::object>()["points"].get<picojson::array>().begin(); i != _value.get<picojson::object>()["points"].get<picojson::array>().end(); ++i) {
			for (picojson::array::iterator j = i->get<picojson::array>().begin(); j != i->get<picojson::array>().end(); ++j) _points[1 + i - _value.get<picojson::object>()["points"].get<picojson::array>().begin()][1 + j - i->get<picojson::array>().begin()] = static_cast<int>(j->get<double>());
		}

		return { _width, _height, _startedAtUnixTime, _points };
	}

	static VariableField readVariableField(const FixedField& fixedField) {
		ifstream _ifstream("get.json");
		picojson::value _value;

		picojson::parse(_value, _ifstream);
		_ifstream.close();

		int _turn = static_cast<int>(_value.get<picojson::object>()["turn"].get<double>());
		vector<vector<int>> _tiled(2 + fixedField.height, vector<int>(2 + fixedField.width));

		for (picojson::array::iterator i = _value.get<picojson::object>()["tiled"].get<picojson::array>().begin(); i != _value.get<picojson::object>()["tiled"].get<picojson::array>().end(); ++i) {
			for (picojson::array::iterator j = i->get<picojson::array>().begin(); j != i->get<picojson::array>().end(); ++j) _tiled[1 + i - _value.get<picojson::object>()["tiled"].get<picojson::array>().begin()][1 + j - i->get<picojson::array>().begin()] = static_cast<int>(j->get<double>());
		}

		return { _turn, _tiled };
	}

	static Match readMatch() {
		ifstream _ifstream("match.json");
		picojson::value _value;

		picojson::parse(_value, _ifstream);
		_ifstream.close();

		int _id = static_cast<int>(_value.get<picojson::object>()["id"].get<double>());
		int _intervalMillis = static_cast<int>(_value.get<picojson::object>()["intervalMillis"].get<double>());
		string _matchTo = _value.get<picojson::object>()["matchTo"].get<string>();
		int _teamID = static_cast<int>(_value.get<picojson::object>()["teamID"].get<double>());
		int _turnMillis = static_cast<int>(_value.get<picojson::object>()["turnMillis"].get<double>());
		int _turns = static_cast<int>(_value.get<picojson::object>()["turns"].get<double>());

		return { _id, _intervalMillis, _matchTo, _teamID, _turnMillis, _turns };
	}

	static Teams readTeams(const Match& match) {
		ifstream _ifstream("get.json");
		picojson::value _value;
		vector<Team> _teams;

		picojson::parse(_value, _ifstream);
		_ifstream.close();

		for (picojson::value& i : _value.get<picojson::object>()["teams"].get<picojson::array>()) {
			Agents _agents;
			int _teamID = static_cast<int>(i.get<picojson::object>()["teamID"].get<double>());

			for (picojson::value& j : i.get<picojson::object>()["agents"].get<picojson::array>()) {
				Agent _agent(static_cast<int>(j.get<picojson::object>()["agentID"].get<double>()));

				_agent.yx = { static_cast<int>(j.get<picojson::object>()["y"].get<double>()), static_cast<int>(j.get<picojson::object>()["x"].get<double>()) };
				_agents.agents.push_back(_agent);
			}

			int _tilePoint = static_cast<int>(i.get<picojson::object>()["tilePoint"].get<double>());
			int _areaPoint = static_cast<int>(i.get<picojson::object>()["areaPoint"].get<double>());

			_teams.emplace_back(_teamID, _agents, _tilePoint, _areaPoint);
		}

		if (_teams.front().teamID == match.teamID) return { { _teams.front(), _teams.back() } };

		return { { _teams.back(), _teams.front() } };
	}
};