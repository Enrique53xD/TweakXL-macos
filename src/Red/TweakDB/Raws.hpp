#pragma once

#include "Alias.hpp"

namespace Raw
{
constexpr auto InitTweakDB = Core::RawFunc<
    /* addr = */ Red::AddressLib::TweakDB_Init,
    /* type = */ void (*)(void*, void*)>();

constexpr auto LoadTweakDB = Core::RawFunc<
    /* addr = */ Red::AddressLib::TweakDB_Load,
    /* type = */ void (*)(Red::TweakDB*, Red::CString&)>();

constexpr auto TryLoadTweakDB = Core::RawFunc<
    /* addr = */ Red::AddressLib::TweakDB_TryLoad,
    /* type = */ bool (*)(void* a1, Red::TweakDB*, Red::CString&, void* a4)>();

constexpr auto CreateRecord = Core::RawFunc<
    /* addr = */ Red::AddressLib::TweakDB_CreateRecord,
    /* type = */ void (*)(Red::TweakDB*, uint32_t, Red::TweakDBID)>();

#ifdef __APPLE__
// macOS port: the game's function only registers the readable name of a TweakDBID (debug aid); the ids themselves are
// computed by the SDK (aBase + aName), so this is a no-op here.
struct NoOpCreateTweakDBID
{
    void operator()(const Red::TweakDBID*, const Red::TweakDBID*, const char*) const {}
};
constexpr auto CreateTweakDBID = NoOpCreateTweakDBID{};
#else
constexpr auto CreateTweakDBID = Core::RawFunc<
    /* addr = */ Red::AddressLib::TweakDBID_Derive,
    /* type = */ void (*)(const Red::TweakDBID*, const Red::TweakDBID*, const char*)>();

#endif
}
