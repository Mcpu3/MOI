#pragma once

#include <Siv3D.hpp>
using namespace std;

class Agent {
public:
	const int agentID;
	pair<int, int> yx;

	Agent(const int& agentID) : agentID(agentID) {}

	Agent(const int& agentID, const pair<int, int>& yx) :
		agentID(agentID),
		yx(yx)
	{}
};

class Agents {
public:
	vector<Agent> agents;
};

class Team {
public:
	const int teamID;
	Agents agents;
	int tilePoint, areaPoint;

	Team(const int& teamID) : teamID(teamID) {}

	Team(const int& teamID, const Agents& agents, const int& tilePoint, const int& areaPoint) :
		teamID(teamID),
		agents(agents),
		tilePoint(tilePoint),
		areaPoint(areaPoint)
	{}
};

class Teams {
public:
	pair<Team, Team> teams;

	Teams(const pair<int, int>& teamID) : teams(teamID) {}
};