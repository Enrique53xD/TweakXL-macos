#pragma once

namespace App::Migration
{
inline void CleanUp(const std::filesystem::path& aPath)
{
#ifdef __APPLE__
    // macOS port: DISABLED. remove_all() on a path derived from the module/game directory is too dangerous here (an
    // empty base path turns it into a path relative to the cwd; APFS is case-insensitive). See ArchiveXL-macos.
    (void)aPath;
    return;
#endif
    std::error_code error;
    if (std::filesystem::exists(aPath, error))
    {
        std::filesystem::remove_all(aPath, error);
    }
}
}
