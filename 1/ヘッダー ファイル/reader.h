#pragma once

#include "matches.h"
#include "picojson.h"
#include <fstream>
#include <string>

class Reader {
public:
	static Matches readMatches() {
		Matches _matches;
		ifstream _ifstream("matches.json");
		picojson::value _value;

		picojson::parse(_value, _ifstream);
		_ifstream.close();

		for (picojson::value& _i : _value.get<picojson::array>()) {
			int _id = static_cast<int>(_i.get<picojson::object>()["id"].get<double>());
			int _intervalMillis = static_cast<int>(_i.get<picojson::object>()["intervalMillis"].get<double>());
			string _matchTo = _i.get<picojson::object>()["matchTo"].get<string>();
			int _teamID = static_cast<int>(_i.get<picojson::object>()["teamID"].get<double>());
			int _turnMillis = static_cast<int>(_i.get<picojson::object>()["turnMillis"].get<double>());
			int _turns = static_cast<int>(_i.get<picojson::object>()["turns"].get<double>());

			_matches.matches.emplace_back(_id, _intervalMillis, _matchTo, _teamID, _turnMillis, _turns);
		}

		return _matches;
	}
};