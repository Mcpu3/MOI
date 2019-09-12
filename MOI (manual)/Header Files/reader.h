#pragma once

#include "actions.h"
#include "field.h"
#include "picojson.h"
#include "teams.h"
#include <Siv3D.hpp>
#include <fstream>
using namespace std;

class Reader {
public:
	static Actions readActions() {
		Actions _actions;
		ifstream _ifstream("get.json");
		picojson::value _value;

		picojson::parse(_value, _ifstream);
		_ifstream.close();
		for (picojson::array::iterator i = _value.get<picojson::object>()["actions"].get<picojson::array>().begin(); i != _value.get<picojson::object>()["actions"].get<picojson::array>().end(); ++i) {
			Action _action(static_cast<int>(i->get<picojson::object>()["agentID"].get<double>()));

			if ("move" == i->get<picojson::object>()["type"].get<string>()) _action.type = Action::Type::MOVE;
			else if ("remove" == i->get<picojson::object>()["type"].get<string>()) _action.type = Action::Type::REMOVE;
			else _action.type = Action::Type::STAY;
			_action.dydx = { static_cast<int>(i->get<picojson::object>()["dy"].get<double>()), static_cast<int>(i->get<picojson::object>()["dx"].get<double>()) };
			_action.turn = static_cast<int>(i->get<picojson::object>()["turn"].get<double>());
			if (i->contains("apply")) _action.apply = static_cast<int>(i->get<picojson::object>()["apply"].get<double>());
			_actions.actions.push_back(_action);
		}
		return _actions;
	}

	static FixedField readFixedField() {
		ifstream _ifstream("get.json");
		int i = 1, j = 1;
		picojson::value _value;

		picojson::parse(_value, _ifstream);
		_ifstream.close();

		int _width = static_cast<int>(_value.get<picojson::object>()["width"].get<double>());
		int _height = static_cast<int>(_value.get<picojson::object>()["height"].get<double>());
		int _startedAtUnixTime = static_cast<int>(_value.get<picojson::object>()["startedAtUnixTime"].get<double>());
		vector<vector<int>> _points(2 + _height, vector<int>(2 + _width));

		for (picojson::array::iterator k = _value.get<picojson::object>()["points"].get<picojson::array>().begin(); i <= _height && k != _value.get<picojson::object>()["points"].get<picojson::array>().end(); ++i, ++k) {
			for (picojson::array::iterator l = k->get<picojson::array>().begin(); j <= _width && l != k->get<picojson::array>().end(); ++j, ++l) _points[i][j] = static_cast<int>(k->get<double>());
		}
		return { _width, _height, _startedAtUnixTime, _points };
	}

	static VariableField readVariableField(const FixedField& fixedField) {
		ifstream _ifstream("get.json");
		int i = 1, j = 1;
		picojson::value _value;

		picojson::parse(_value, _ifstream);
		_ifstream.close();

		int _turn = static_cast<int>(_value.get<picojson::object>()["turn"].get<double>());
		vector<vector<int>> _tiled(2 + fixedField.height, vector<int>(2 + fixedField.width));

		for (picojson::array::iterator k = _value.get<picojson::object>()["tiled"].get<picojson::array>().begin(); i <= fixedField.height && k != _value.get<picojson::object>()["tiled"].get<picojson::array>().end(); ++i, ++k) {
			for (picojson::array::iterator l = k->get<picojson::array>().begin(); j <= fixedField.width && l != k->get<picojson::array>().end(); ++j, ++l) _tiled[i][j] = static_cast<int>(k->get<double>());
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

	static Teams readTeams() {
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
		return { { _teams.front(), _teams.back() } };
	}
};