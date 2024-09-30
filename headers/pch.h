#pragma once

#pragma comment(lib, "ClusAPI.lib")

#include <list>
#include <windows.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>

#include "ClusApi.h"

class Cluster;
typedef Cluster* PCluster;

#include "ClusterObjectProps.h"
#include "ClusterObject.h"

class SharedVolume; class Network; class NetInterface; class ResourceType;

#include "Node.h"
#include "Resource.h"
#include "Group.h"

#include "Cluster.h"
#include "IClusterProvider.h"
#include "IGroupProvider.h"
#include "IResourceProvider.h"
#include "INodeProvider.h"

#include "IClusterManager.h"