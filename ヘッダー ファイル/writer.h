#pragma once

#include "actions.h"
#include "picojson.h"
#include <Siv3D.hpp>
using namespace std;

class Writer {
public:
	static void writeActions(const Actions& actions) {
		ofstream _ofstream("post.json");
		picojson::array _array;
		picojson::object _object;

		for (const Action& i : actions.actions) {
			picojson::object _action;

			_action.emplace("agentID", static_cast<double>(i.agentID));

			if (i.dydx == make_pair(0, 0)) _action.emplace("type", "stay");
			else if (Action::Type::MOVE == i.type) _action.emplace("type", "move");
			else _action.emplace("type", "remove");

			_action.emplace("dx", static_cast<double>(i.dydx.second));
			_action.emplace("dy", static_cast<double>(i.dydx.first));
			_array.emplace_back(_action);
		}

		_object.emplace("actions", _array);
		_ofstream << picojson::value(_object);
		_ofstream.close();
	}
};