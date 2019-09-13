#pragma once

#include <string>
#include <vector>
using namespace std;

class Match {
public:
	int id, intervalMillis;
	string matchTo;
	int teamID, turnMillis, turns;

	Match() = default;

	Match(const int& id, const int& intervalMillis, const string& matchTo, const int& teamID, const int& turnMillis, const int& turns) :
		id(id),
		intervalMillis(intervalMillis),
		matchTo(matchTo),
		teamID(teamID),
		turnMillis(turnMillis),
		turns(turns)
	{}
};

class Matches {
public:
	vector<Match> matches;
};