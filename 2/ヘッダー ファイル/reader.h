#pragma once

#include "boost/property_tree/ini_parser.hpp"
#include "boost/property_tree/ptree.hpp"
#include "matches.h"
#include "parameters.h"
#include "picojson.h"
#include <fstream>
#include <string>
using namespace std;

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

	static Parameters readParameters() {
		boost::property_tree::ptree _ptree;

		boost::property_tree::read_ini("Parameters.ini", _ptree);

		string _host = _ptree.get_optional<string>("Parameters.Host").get();
		string _token = _ptree.get_optional<string>("Parameters.Token").get();

		return { _host, _token };
	}
};