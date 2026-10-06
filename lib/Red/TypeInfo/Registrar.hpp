#pragma once


#ifdef __APPLE__
#include <dlfcn.h>
#include <fstream>
#include <set>
#include <string>
#include <filesystem>
namespace Red::Detail
{
static int s_skipAnchor = 0;
// macOS debugging aid: <plugin dir>/rtti_skip lists type names (one per line) that must not be registered.
inline bool IsSkippedType(const char* aName)
{
    static const std::set<std::string> skipped = [] {
        std::set<std::string> out;
        Dl_info info{};
        if (dladdr(&s_skipAnchor, &info) && info.dli_fname)
        {
            std::ifstream in(std::filesystem::path(info.dli_fname).parent_path() / "rtti_skip");
            for (std::string line; std::getline(in, line);)
                if (!line.empty()) out.insert(line);
        }
        return out;
    }();
    return skipped.count(aName) != 0;
}
}
#endif

namespace Red
{
class TypeInfoRegistrar
{
public:
    using Callback = void(*)();

    TypeInfoRegistrar(Callback aRegister, Callback aDescribe)
    {
        AddRegisterCallback(aRegister);
        AddDescribeCallback(aDescribe);
    }

    static inline void RegisterDiscovered()
    {
        QueuePendingRegisterCallbacks();
        QueuePendingDescribeCallbacks();
    }

    // macOS port: the game may run its register/post-register phases before the plugin is loaded, so callbacks
    // queued through CRTTISystem would never fire. Run the pending ones directly.
    static inline void RunPendingNow()
    {
        fprintf(stderr, "[RedLib macOS] pending register=%zu describe=%zu\n", s_registerCallbacks.size(), s_describeCallbacks.size());
        ProcessPendingRegisterCallbacks();
        ProcessPendingDescriberCallbacks();
    }

    static inline void AddRegisterCallback(Callback aRegister)
    {
        if (aRegister)
        {
            s_registerCallbacks.push_back(aRegister);
        }
    }

    static inline void AddDescribeCallback(Callback aDescribe)
    {
        if (aDescribe)
        {
            s_describeCallbacks.push_back(aDescribe);
        }
    }

private:
    static inline void QueuePendingRegisterCallbacks()
    {
        if (!s_registerCallbacks.empty())
        {
            CRTTISystem::Get()->AddRegisterCallback(&OnRegister);
        }
    }

    static inline void QueuePendingDescribeCallbacks()
    {
        if (!s_describeCallbacks.empty())
        {
            CRTTISystem::Get()->AddPostRegisterCallback(&OnDescribe);
        }
    }

    static inline void ProcessPendingRegisterCallbacks()
    {
        auto callbacks = std::move(s_registerCallbacks);
        for (const auto& callback :callbacks)
        {
            callback();
        }
    }

    static inline void ProcessPendingDescriberCallbacks()
    {
        auto callbacks = std::move(s_describeCallbacks);
        for (const auto& callback :callbacks)
        {
            callback();
        }
    }

    static inline void OnRegister()
    {
        ProcessPendingRegisterCallbacks();
        QueuePendingRegisterCallbacks();
    }

    static inline void OnDescribe()
    {
        ProcessPendingDescriberCallbacks();
        QueuePendingDescribeCallbacks();
    }

    static inline std::vector<Callback> s_registerCallbacks;
    static inline std::vector<Callback> s_describeCallbacks;
};
}
