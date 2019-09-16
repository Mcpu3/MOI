#pragma once

#include "actions.h"
#include "field.h"
#include "matches.h"
#include "reader.h"
#include "solver.h"
#include "teams.h"
#include "writer.h"
#include <Siv3D.hpp>
using namespace std;

class MOI {
public:
	void moi() {
		const Matches _matches(Reader::readMatches());

		Console::Open();
		cout << "MOI" << endl;

		while ('\n' != getchar()) {}

		const FixedField _fixedField = Reader::readFixedField();
		VariableField _variableField = Reader::readVariableField(_fixedField);
		Teams _teams = Reader::readTeams(_matches);
		Solver _solver(_fixedField, _variableField, _matches, _teams);

		FileSystem::Copy(L"get.json", L"visualizer.json", CopyOption::Overwrite_if_exists);
		System::LaunchFile(L"Visualizer.exe", LaunchVerb::Open);
		Writer::writeActions(_solver.getActions());
		cout << "MOI" << endl;

		while ('\n' != getchar()) {}

		while (true) {
			FileSystem::Copy(L"get.json", L"visualizer.json", CopyOption::Overwrite_if_exists);
			_variableField = Reader::readVariableField(_fixedField);
			_teams = Reader::readTeams(_matches);
			Writer::writeActions(_solver.getActions());
			cout << "MOI" << endl;

			while ('\n' != getchar()) {}
		}
	}
};