#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <functional>

namespace cdocs
{
namespace backend
{
class Project
{
public:
    typedef std::function<bool(const std::string_view& strFile)> BuildProgress;

public:
    Project(const std::string& strDirectory);
    Project(int argc, const char* argv[]);
    ~Project();

public:
    int32_t Build(BuildProgress&& bp);
};
}  //namespace backend
}  //namespace cdocs