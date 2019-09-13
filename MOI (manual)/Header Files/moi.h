#pragma once

#include "actions.h"
#include "field.h"
#include "match.h"
#include "reader.h"
#include "solver.h"
#include "teams.h"
#include "writer.h"
#include <Siv3D.hpp>
using namespace std;

class MOI {
public:
	void moi() {
		Match _match(Reader::readMatch());

		Console.open();
		cout << "MOI" << endl;

		while ('\n' != getchar()) {}

		FixedField _fixedField = Reader::readFixedField();
		VariableField _variableField = Reader::readVariableField(_fixedField);
		Teams _teams = Reader::readTeams(_match);
		Solver _solver(_fixedField, _variableField, _match, _teams);

		Writer::writeActions(_solver.getActions());

		while (true) {
			cout << "MOI" << endl;

			while ('\n' != getchar()) {}

			Actions _actions = Reader::readActions();

			_variableField = Reader::readVariableField(_fixedField);
			_teams = Reader::readTeams(_match);
			Writer::writeActions(_solver.getActions());
		}
	}
};