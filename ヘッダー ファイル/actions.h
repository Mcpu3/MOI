#pragma once

#include <Siv3D.hpp>
using namespace std;

class Action {
public:
	enum class Type {
		MOVE,
		REMOVE
	};

	int agentID;
	Type type;
	pair<int, int> dydx;
	int turn, apply;

	Action() = default;

	Action(const int& agentID) : agentID(agentID) {}

	Action(const int& agentID, const Type& type, const pair<int, int>& dydx) :
		agentID(agentID),
		type(type),
		dydx(dydx)
	{}

	Action(const int& agentID, const Type& type, const pair<int, int>& dydx, const int& turn) :
		agentID(agentID),
		type(type),
		dydx(dydx),
		turn(turn)
	{}

	Action(const int& agentID, const Type& type, const pair<int, int>& dydx, const int& turn, const int& apply) :
		agentID(agentID),
		type(type),
		dydx(dydx),
		turn(turn),
		apply(apply)
	{}

	Action(const int& agentID, const pair<int, int>& dydx) :
		agentID(agentID),
		type(type),
		dydx(dydx)
	{}

	Action(const int& agentID, const pair<int, int>& dydx, const int& turn) :
		agentID(agentID),
		type(type),
		dydx(dydx),
		turn(turn)
	{}

	Action(const int& agentID, const pair<int, int>& dydx, const int& turn, const int& apply) :
		agentID(agentID),
		type(type),
		dydx(dydx),
		turn(turn),
		apply(apply)
	{}
};

class Actions {
public:
	vector<Action> actions;
};