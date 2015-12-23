#include <Engine/util/json.hpp>

namespace engine {

float jsonNodeAs<float>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asFloat();
}

double jsonNodeAs<double>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asDouble();
}

int jsonNodeAs<int>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asInt();
}

unsigned int jsonNodeAs<unsigned int>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asUInt();
}

int64_t jsonNodeAs<int64_t>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asInt64();
}

uint64_t jsonNodeAs<uint64_t>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asUInt64();
}

bool jsonNodeAs<bool>(const Json::Value& node) {
    if (node.isNull()) {
        return false;
    }
    return node.asBool();
}

const char* jsonNodeAs<const char*>(const Json::Value& node) {
    if (node.isNull()) {
        return nullptr;
    }
    return node.asCString();
}

std::string jsonNodeAs<std::string>(const Json::Value& node) {
    if (node.isNull()) {
        return "";
    }
    return node.asString();
}
}
