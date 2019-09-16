#pragma once

#include "matches.h"
#include "picojson.h"
#include <fstream>

class Writer {
public:
	static void writeMatch(const Match& match) {
		ofstream _ofstream("match.json");
		picojson::object _object;

		_object.emplace("id", picojson::value(static_cast<double>(match.id)));
		_object.emplace("intervalMillis", picojson::value(static_cast<double>(match.intervalMillis)));
		_object.emplace("matchTo", picojson::value(match.matchTo));
		_object.emplace("teamID", picojson::value(static_cast<double>(match.teamID)));
		_object.emplace("turnMillis", picojson::value(static_cast<double>(match.turnMillis)));
		_object.emplace("turns", picojson::value(static_cast<double>(match.turns)));
		_ofstream << picojson::value(_object);
		_ofstream.close();
	}
};