#pragma once

#include <Siv3D.hpp>
using namespace std;

class Parameters {
public:
	string host, token;

	Parameters() = default;

	Parameters(const string& host, const string& token) :
		host(host),
		token(token)
	{}
};
