#pragma once

#include "curl/curl.h"
#include "matches.h"
#include "parameters.h"
#include <Siv3D.hpp>
using namespace std;

class Uploader {
public:
	static void upload(const Matches& matches, const Parameters& parameters) {
		CURL* _curl = curl_easy_init();
		FILE* _file = fopen("get.json", "w");
		curl_slist* _curlSlist = NULL;

		_curlSlist = curl_slist_append(_curlSlist, "Content-Type:application/json");
		curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, curl_slist_append(_curlSlist, string("Authorization:" + parameters.token).c_str()));
		curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, TextReader(L"post.json").readAll().narrow().c_str());
		curl_easy_setopt(_curl, CURLOPT_URL, string("http://" + parameters.host + "/matches/" + to_string(matches.id) + "/action").c_str());
		curl_easy_setopt(_curl, CURLOPT_WRITEDATA, _file);
		curl_easy_perform(_curl);
		curl_easy_cleanup(_curl);
		fclose(_file);
	}
};