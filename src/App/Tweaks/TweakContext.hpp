#pragma once

#include "Core/Facades/Runtime.hpp"
#include "Core/Runtime/HostImage.hpp"

namespace App
{
class TweakContext
{
public:
    TweakContext(const Core::SemvVer& aProductVer)
        : m_gameVersion(static_cast<uint8_t>(aProductVer.major),
                        static_cast<uint8_t>(aProductVer.minor),
                        static_cast<uint8_t>(aProductVer.patch))
        , m_isEpisodeOne(false)
    {
#ifdef __APPLE__
        // macOS port: no RTTI function invocation yet. Phantom Liberty (EP1) is installed when its archives exist.
        std::error_code error;
        m_isEpisodeOne = std::filesystem::exists(Core::Runtime::GetRootDir() / "archive" / "Mac" / "ep1", error);
#else
        Red::CallGlobal("IsEP1", m_isEpisodeOne);
#endif
    }

    [[nodiscard]] inline bool CheckGameVersion(const std::string& aCondition) const
    {
        return semver::range::satisfies(m_gameVersion, aCondition);
    }

    [[nodiscard]] inline bool CheckInstalledDLC(const std::string& aCondition) const
    {
        if (aCondition == "EP1") {
            return m_isEpisodeOne;
        }

        return aCondition.empty();
    }

private:
    semver::version m_gameVersion;
    bool m_isEpisodeOne;
};
}
