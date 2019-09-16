#include "downloader.h"
#include "matches.h"
#include "reader.h"
#include "writer.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	string host, token;

	cout << "Host: ";
	cin >> host;
	cout << "Token: ";
	cin >> token;
	Downloader::download(host, token);

	Matches matches = Reader::readMatches();

	Writer::writeMatch(matches.matches[0]);
}