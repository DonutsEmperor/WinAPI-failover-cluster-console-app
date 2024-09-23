# Cluster Backup Plugin for Hyper-V

## Problem Statement
The current HandyBackup agent does not adequately support clustering, treating each node as a separate machine. Tasks break when the target node changes, requiring manual setup for each node, and mutual differential and incremental backups do not function correctly.

## Proposed Solution
To address this issue, it is proposed to introduce new task parameters catered specifically for clusters. This will allow the creation of dedicated backup and restore tasks for clusters, with a checkbox for selecting task type (cluster / non-cluster), enabling seamless management and backup across cluster nodes.

## Development Plan
1. Develop a cluster-aware backup plugin leveraging failover cluster APIs to support various clustering variations and architectures.
2. Redesign the task file structure within the backup system to meet cluster-specific requirements.
3. Create four primary plugins: Cluster Plugin, Hyper-V Cluster Plugin, MSSQL Cluster Plugin, and MS Exchange Cluster Plugin tailored to the service areas' specific needs.

## Environment
The developed functionalities will be tested and executed on virtual machines with pre-configured clusters to ensure robustness and compatibility.

![Cluster Backup](https://github.com/user-attachments/assets/b3aa8b77-75bc-47f9-b584-7766de1c0c30)

### Additional Resources
- [Microsoft Documentation with API](https://learn.microsoft.com/en-us/previous-versions/windows/desktop/mscs/failover-cluster-apis-portal)
