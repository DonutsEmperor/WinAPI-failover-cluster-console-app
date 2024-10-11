#pragma once
#include "Provider.h"

class GroupProvider : public Provider<Group> {
public:
    explicit GroupProvider(PCluster cluster);
};