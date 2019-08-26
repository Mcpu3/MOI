#pragma once

#include <Siv3D.hpp>
using namespace std;

class Action {
public:
	enum class Type {
		MOVE,
		REMOVE,
		STAY
	};

	Type type;
	const int agentID;
	int apply, turn;
	pair<int, int> dydx;

	Action(const Type& type, const int& agentID, const int& apply, const int& turn, const pair<int, int>& dydx) :
		type(type),
		agentID(agentID),
		apply(apply),
		turn(turn),
		dydx(dydx)
	{}

	Action(const Type& type, const int& agentID, const pair<int, int>& dydx) :
		type(type),
		agentID(agentID),
		dydx(dydx)
	{}

	Action(const int& agentID) : agentID(agentID) {}
};

class Actions {
public:
	vector<Action> actions;
};