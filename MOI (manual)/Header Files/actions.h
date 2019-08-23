#pragma once

#include <Siv3D.hpp>
using namespace std;

class Action {
public:
	const int agentID;
	string type;
	pair<int, int> dxdy;
	int turn, apply;

	Action(const int& agentID) : agentID(agentID) {}
};

class Actions {
public:
	vector<Action> actions;

	Actions(const vector<int>& agentIDs) {
		for (const int i : agentIDs) actions.push_back(Action(i));
	}
};