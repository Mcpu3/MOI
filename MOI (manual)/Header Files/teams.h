#pragma once

#include <Siv3D.hpp>
using namespace std;

class Agent {
public:
	const int agentID;
	pair<int, int> xy;

	Agent(const int& agentID) : agentID(agentID) {}
};

class Agents {
public:
	vector<Agent> agents;

	Agents(const vector<int>& agentIDs) {
		for (const int i : agentIDs) agents.push_back(Agent(i));
	}
};

class Team {
public:
	const int teamID;
	Agents agents;
	int tilePoint, areaPoint;

	Team(const int& teamID, const vector<int>& agentIDs) :
		teamID(teamID),
		agents(agentIDs)
	{}
};

class Teams {
public:
	pair<Team, Team> teams;

	Teams(const pair<int, int> teamID, const pair<vector<int>, vector<int>>& agentIDs) : teams({ teamID.first, agentIDs.first }, { teamID.second, agentIDs.second }) {}
};