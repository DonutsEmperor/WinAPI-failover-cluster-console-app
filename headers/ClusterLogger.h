#pragma once
#include "Logger.h"

class Manager;

class ClusterLogger : public Logger<Cluster> {
public:
	explicit ClusterLogger() = default;
	void DisplayClusterInfo(const Manager& manager) const;
	void LogOneBase(const Cluster&) const override {}
	void LogOneSpecial(const Cluster&) const override {}
	void LogListBase(const std::list<Cluster>& items) const override {}
	void LogListSpecial(const std::list<Cluster>& items) const override {}

private:
};