#include "Cluster.h"
#include "ILogger.h"
#include "LoggerFactory.h"
#include "ItemLogger.h"

template <>
std::unique_ptr<ILogger<Node>> LoggerFactory::CreateLogger() {
    return std::make_unique<ItemLogger<Node>>();
}

template <>
std::unique_ptr<ILogger<Resource>> LoggerFactory::CreateLogger() {
    return std::make_unique<ItemLogger<Resource>>();
}

template <>
std::unique_ptr<ILogger<Group>> LoggerFactory::CreateLogger() {
    return std::make_unique<ItemLogger<Group>>();
}
