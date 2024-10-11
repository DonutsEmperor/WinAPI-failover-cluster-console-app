#pragma once
#include "Logger.h"

class NodeLogger : public Logger<Node> {
public:
	explicit NodeLogger() = default;
	void LogNode();
private:
};