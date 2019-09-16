#pragma once

#include <Siv3D.hpp>
using namespace std;

class Matches {
public:
	int id, intervalMillis;
	string matchTo;
	int teamID, turnMillis, turns;

	Matches() = default;

	Matches(const int& id, const int& intervalMillis, const string& matchTo, const int& teamID, const int& turnMillis, const int& turns) :
		id(id),
		intervalMillis(intervalMillis),
		matchTo(matchTo),
		teamID(teamID),
		turnMillis(turnMillis),
		turns(turns)
	{}
};