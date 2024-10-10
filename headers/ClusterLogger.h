#pragma once

class Manager;

class ClusterLogger : public Logger<Cluster> {
public:
	void DisplayClusterInfo(const Manager& manager) const;
	void LogBase(const Cluster&) const override {}
	void LogList(const std::list<Cluster>&) const override {}
private:
};