#pragma once
#include "Logger.h"

class GroupLogger : public Logger<Group> {
public:
	explicit GroupLogger() = default;
	void LogGroup();
private:
};