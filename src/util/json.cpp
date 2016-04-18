#include <Engine/util/json.hpp>

namespace engine {

template <> float jsonNodeAs<float>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asFloat();
}

template <> double jsonNodeAs<double>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asDouble();
}

template <> int jsonNodeAs<int>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asInt();
}

template <> unsigned int jsonNodeAs<unsigned int>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asUInt();
}

template <> int64_t jsonNodeAs<int64_t>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asInt64();
}

template <> uint64_t jsonNodeAs<uint64_t>(const Json::Value& node) {
    if (node.isNull()) {
        return 0;
    }
    return node.asUInt64();
}

template <> bool jsonNodeAs<bool>(const Json::Value& node) {
    if (node.isNull()) {
        return false;
    }
    return node.asBool();
}

template <> const char* jsonNodeAs<const char*>(const Json::Value& node) {
    if (node.isNull()) {
        return nullptr;
    }
    return node.asCString();
}

template <> std::string jsonNodeAs<std::string>(const Json::Value& node) {
    if (node.isNull()) {
        return "";
    }
    return node.asString();
}
}
