#include <Manager.h>
#include <ClusterLogger.h>

void ClusterLogger::DisplayClusterInfo(const Manager& manager) const {
    const ClusterProvider* provider = manager.GetClusterProvider();

    HCLUSTER hCluster = provider->GetClusterHandle();
    std::wstring clusName;
    provider->GetClusterName(clusName);

    std::wcout << "Handle       [" << hCluster << "]\n";
    std::wcout << "Cluster Name [" << clusName << "]\n";

    DWORD state = 0;
    provider->GetClusterState(&state);
    std::wcout << "Cluster state[" << state << "]. Must be 19\n" << std::endl;
}