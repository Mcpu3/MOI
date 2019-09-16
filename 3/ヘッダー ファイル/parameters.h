#pragma once

#include <string>
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