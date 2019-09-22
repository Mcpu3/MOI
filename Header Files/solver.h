#pragma once

#include "actions.h"
#include "field.h"
#include "matches.h"
#include "points.h"
#include "teams.h"
#include <Siv3D.hpp>
#include <future>
#include <queue>
using namespace std;

class Solver {
private:
	const FixedField& _fixedField;
	const VariableField& _variableField;
	const Matches& _matches;
	const Teams& _teams;

public:
	Solver(const FixedField& fixedField, const VariableField& variableField, const Matches& matches, const Teams& teams) :
		_fixedField(fixedField),
		_variableField(variableField),
		_matches(matches),
		_teams(teams)
	{}

private:
	int getChebyshevDistance(const Action& action, const Agent& agent) {
		int _chebyshevDistance = INT_MAX;

		for (const Agent& i : _teams.teams.first.agents.agents) {
			if (agent.agentID != i.agentID) _chebyshevDistance = min(_chebyshevDistance, max(abs(action.dydx.first + agent.yx.first - i.yx.first), abs(action.dydx.second + agent.yx.second - i.yx.second)));
		}

		for (const Agent& i : _teams.teams.second.agents.agents) _chebyshevDistance = min(_chebyshevDistance, max(abs(action.dydx.first + agent.yx.first - i.yx.first), abs(action.dydx.second + agent.yx.second - i.yx.second)));

		return _chebyshevDistance;
	}

	int getPoint(const VariableField& variableField) {
		Points _points(_fixedField, variableField, _teams);
		pair<int, int> _areaPoint = _points.getAreaPoint(), _tilePoint = _points.getTilePoint();

		return _areaPoint.first + _tilePoint.first - _areaPoint.second - _tilePoint.second;
	}

	Action getAction(const Agent& agent) {
		Action _action(agent.agentID);
		const int _point = getPoint(_variableField);
		const vector<pair<int, int>> _dydx{ { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 }, { 0, 1 }, { 1, -1 }, { 1, 0 }, { 1, 1 } };
		pair<deque<tuple<VariableField, Agent, int, pair<Action, Action>>>, deque<tuple<VariableField, Agent, int, pair<Action, Action>>>> _deque;

		for (const pair<int, int>& i : _dydx) {
			_action.dydx = i;

			if (!_fixedField.isWall[_action.dydx.first + agent.yx.first][_action.dydx.second + agent.yx.second] && 1 < getChebyshevDistance(_action, agent)) {
				if (_variableField.tiled[_action.dydx.first + agent.yx.first][_action.dydx.second + agent.yx.second]) _action.type = Action::Type::REMOVE;
				else _action.type = Action::Type::MOVE;

				_deque.first.emplace_back(_variableField, agent, _point, make_pair(_action, _action));
			}
		}

		if (_deque.first.empty()) {
			for (const pair<int, int>& i : _dydx) {
				_action.dydx = i;

				if (!_fixedField.isWall[_action.dydx.first + agent.yx.first][_action.dydx.second + agent.yx.second]) {
					if (_variableField.tiled[_action.dydx.first + agent.yx.first][_action.dydx.second + agent.yx.second]) _action.type = Action::Type::MOVE;
					else _action.type = Action::Type::REMOVE;

					_deque.first.emplace_back(_variableField, agent, _point, make_pair(_action, _action));
				}
			}
		}

		while (get<0>(_deque.first.front()).turn < min(1 + _matches.turns, 16 + _variableField.turn)) {
			while (!_deque.first.empty()) {
				VariableField _newVariableField(1 + get<0>(_deque.first.front()).turn, get<0>(_deque.first.front()).tiled);
				Agent _newAgent(agent.agentID);

				if (Action::Type::MOVE == get<3>(_deque.first.front()).first.type) {
					_newAgent.yx.first = get<1>(_deque.first.front()).yx.first + get<3>(_deque.first.front()).first.dydx.first;
					_newAgent.yx.second = get<1>(_deque.first.front()).yx.second + get<3>(_deque.first.front()).first.dydx.second;
					_newVariableField.tiled[_newAgent.yx.first][_newAgent.yx.second] = _teams.teams.first.teamID;
				}
				else {
					_newAgent.yx = get<1>(_deque.first.front()).yx;
					_newVariableField.tiled[_newAgent.yx.first + get<3>(_deque.first.front()).first.dydx.first][_newAgent.yx.second + get<3>(_deque.first.front()).first.dydx.second] = 0;
				}

				const int _newPoint = max(get<2>(_deque.first.front()), getPoint(_newVariableField));

				for (const pair<int, int>& i : _dydx) {
					Action _newAction(agent.agentID, i);

					if (!_fixedField.isWall[_newAction.dydx.first + _newAgent.yx.first][_newAction.dydx.second + _newAgent.yx.second]) {
						if (_newVariableField.tiled[_newAction.dydx.first + _newAgent.yx.first][_newAction.dydx.second + _newAgent.yx.second]) _newAction.type = Action::Type::REMOVE;
						else _newAction.type = Action::Type::MOVE;

						_deque.second.emplace_back(_newVariableField, _newAgent, _newPoint, make_pair(_newAction, get<3>(_deque.first.front()).second));
					}
				}

				_deque.first.pop_front();
			}

			sort(_deque.second.begin(), _deque.second.end(), [](const tuple <VariableField, Agent, int, pair<Action, Action>>& a, const tuple <VariableField, Agent, int, pair<Action, Action>>& b) { return get<2>(a) > get<2>(b); });

			if (512 < _deque.second.size()) _deque.second.erase(512 + _deque.second.begin(), _deque.second.end());

			_deque.first.swap(_deque.second);
		}

		if (_point < get<2>(_deque.first.front())) return get<3>(_deque.first.front()).second;
		
		return { agent.agentID, { 0, 0 } };
	}

public:
	Actions getActions() {
		Actions _actions;
		vector<future<Action>> _futures;

		for (const Agent& i : _teams.teams.first.agents.agents) _futures.push_back(async(launch::async, [&i, this]() { return getAction(i); }));

		for (future<Action>& i : _futures) _actions.actions.push_back(i.get());

		return _actions;
	}
};