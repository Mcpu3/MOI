#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "curl/curl.h"
#include "parameters.h"
#include <string>
using namespace std;

class Downloader {
public:
	static void download(const Parameters& parameters) {
		CURL* _curl = curl_easy_init();
		FILE* _file = fopen("matches.json", "w");
		curl_slist* _curlSlist = NULL;

		curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, curl_slist_append(_curlSlist, string("Authorization:" + parameters.token).c_str()));
		curl_easy_setopt(_curl, CURLOPT_URL, string("http://" + parameters.host + "/matches").c_str());
		curl_easy_setopt(_curl, CURLOPT_WRITEDATA, _file);
		curl_easy_perform(_curl);
		curl_easy_cleanup(_curl);
		fclose(_file);
	}
};