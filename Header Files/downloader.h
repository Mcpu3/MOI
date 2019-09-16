#pragma once

#include "curl/curl.h"
#include "matches.h"
#include "parameters.h"
#include <Siv3D.hpp>
using namespace std;

class Downloader {
public:
	static void download(const Matches& matches, const Parameters& parameters) {
		CURL* _curl = curl_easy_init();
		FILE* _file = fopen("get.json", "w");
		curl_slist* _curlSlist = NULL;

		curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, curl_slist_append(_curlSlist, string("Authorization:" + parameters.token).c_str()));
		curl_easy_setopt(_curl, CURLOPT_URL, string("http://" + parameters.host + "/matches/" + to_string(matches.id)).c_str());
		curl_easy_setopt(_curl, CURLOPT_WRITEDATA, _file);
		curl_easy_perform(_curl);
		curl_easy_cleanup(_curl);
		fclose(_file);
	}
};