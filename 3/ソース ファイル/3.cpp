#include "downloader.h"
#include "matches.h"
#include "reader.h"
#include "writer.h"
using namespace std;

int main() {
	Downloader::download(Reader::readParameters());

	Matches matches = Reader::readMatches();

	Writer::writeMatch(matches.matches[2]);
}