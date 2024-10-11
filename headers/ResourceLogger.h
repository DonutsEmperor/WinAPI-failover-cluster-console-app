#pragma once
#include "Logger.h"

class ResourceLogger : public Logger<Resource> {
public:
	explicit ResourceLogger() = default;
	void LogDiskInfo();
private:
};