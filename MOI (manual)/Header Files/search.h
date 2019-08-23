#pragma once

#include <Siv3D.hpp>
#include <queue>
#include "actions.h"
#include "field.h"
#include "points.h"
#include "teams.h"
using namespace std;

class Search {
private:
	const Field& _field;
	const Teams _teams;

public:
	Search(const Field& field, const Teams& teams) : _field(field), _teams(teams) {}

private:
	int breadthFirstSearch(const Field& field, const Agent& agent) {

		queue<Field, pair<int, int>> _queue;
	}

public:
	Actions getActions() {
		vector<int> agentIDs;

		for (const Agent& i : _teams.teams.first.agents.agents) agentIDs.push_back(i.agentID);

		Actions actions(agentIDs);

		for (const Agent& i : _teams.teams.first.agents.agents) {

		}
		return actions;
	}
};