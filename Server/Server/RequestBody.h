#pragma once
#include <map>
#include <string>
//RequestBody.h

#include <vector>
#include <nlohmann/json.hpp>


class RequestBody
{
public:
	RequestBody(std::string key, std::string body, int handle) : _key(key), _body(body), _handle(handle)
	{
	};

	std::string GetKey() {
		return _key;
	}

	std::string GetBody() {
		return _body;
	}

	int GetHandle() {
		return _handle;
	}

	nlohmann::json GetJson() {
		nlohmann::json j;

		j["key"] = _key;
		j["body"] = _body;
		j["userId"] = _handle;
		return j;
	}
private:
	std::string _key;
	std::string _body;
	int _handle;
};