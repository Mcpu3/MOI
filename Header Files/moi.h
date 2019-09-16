#pragma once

#include "actions.h"
#include "downloader.h"
#include "field.h"
#include "matches.h"
#include "reader.h"
#include "solver.h"
#include "teams.h"
#include "uploader.h"
#include "writer.h"
#include <Siv3D.hpp>
using namespace std;

class MOI {
public:
	void moi() {
		const Matches _matches = Reader::readMatches();
		const Parameters _parameters = Reader::readParameters();

		Console::Open();
		cout << "ID: " << _matches.id << endl;
		cout << "Interval Millis" << _matches.intervalMillis << endl;
		cout << "Match To: " << _matches.matchTo << endl;
		cout << "Team ID: " << _matches.teamID << endl;
		cout << "Turn Millis: " << _matches.turnMillis << endl;
		cout << "Turns: " << _matches.turns << endl;
		cout << endl;
		cout << "Host: " << _parameters.host << endl;
		cout << "Token: " << _parameters.token << endl;
		cout << endl;

		while ('\n' != getchar()) {}

		Downloader::download(_matches, _parameters);
		FileSystem::Copy(L"get.json", L"visualizer.json", CopyOption::Overwrite_if_exists);
		System::LaunchFile(L"Visualizer.exe", LaunchVerb::Open);

		const FixedField _fixedField = Reader::readFixedField();
		VariableField _variableField = Reader::readVariableField(_fixedField);
		Teams _teams = Reader::readTeams(_matches);
		Solver _solver(_fixedField, _variableField, _matches, _teams);

		Writer::writeActions(_solver.getActions());
		Uploader::upload(_matches, _parameters);

		Actions _actions = Reader::readActions();

		for (const Action& i : _actions.actions) {
			cout << "Agent ID: " << i.agentID << endl;
			cout << "Type: ";

			if (i.dydx == make_pair(0, 0)) cout << "Stay";
			else if (Action::Type::MOVE == i.type) cout << "Move";
			else cout << "Remove";

			cout << endl;
			cout << "dx: " << i.dydx.second << endl;
			cout << "dy: " << i.dydx.first << endl;
			cout << "Turn: " << i.turn << endl;
			cout << endl;
		}

		while ('\n' != getchar()) {}

		while (true) {
			Downloader::download(_matches, _parameters);
			FileSystem::Copy(L"get.json", L"visualizer.json", CopyOption::Overwrite_if_exists);
			_actions = Reader::readActions();

			for (const Action& i : _actions.actions) {
				cout << "Agent ID: " << i.agentID << endl;
				cout << "Type: ";

				if (i.dydx == make_pair(0, 0)) cout << "Stay";
				else if (Action::Type::MOVE == i.type) cout << "Move";
				else cout << "Remove";

				cout << endl;
				cout << "dx: " << i.dydx.second << endl;
				cout << "dy: " << i.dydx.first << endl;
				cout << "Turn: " << i.turn << endl;
				cout << "Apply: " << i.apply << endl;
				cout << endl;
			}

			_variableField = Reader::readVariableField(_fixedField);
			_teams = Reader::readTeams(_matches);
			Writer::writeActions(_solver.getActions());
			Uploader::upload(_matches, _parameters);
			_actions = Reader::readActions();

			for (const Action& i : _actions.actions) {
				cout << "Agent ID: " << i.agentID << endl;
				cout << "Type: ";

				if (i.dydx == make_pair(0, 0)) cout << "Stay";
				else if (Action::Type::MOVE == i.type) cout << "Move";
				else cout << "Remove";

				cout << endl;
				cout << "dx: " << i.dydx.second << endl;
				cout << "dy: " << i.dydx.first << endl;
				cout << "Turn: " << i.turn << endl;
				cout << endl;
			}

			while ('\n' != getchar()) {}
		}
	}
};