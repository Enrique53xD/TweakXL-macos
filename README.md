# TweakXL-macos (macOS port)

Apple Silicon port of the upstream project, built on [RED4ext-macos](https://github.com/Enrique53xD/RED4ext-macos). See [cp2077-macos-tools](https://github.com/Enrique53xD/cp2077-macos-tools) for the full install guide.

**Build:** clone next to `RED4ext-macos` and `ArchiveXL-macos`, then `mkdir build && cd build && cmake .. && make -j8`, `codesign -f -s - TweakXL.dylib`.
**Install:** copy the dylib to `<game>/red4ext/plugins/TweakXL/` with an empty `rtti_experiment` file beside it.
**Status:** loads and runs on macOS. Uses the patched SDK from `../ArchiveXL-macos/vendor/RED4ext.SDK`.
Original README below.

---

# TweakXL

TweakXL is a modding tool and a framework to create mods that modify TweakDB, 
a proprietary database of REDengine 4, 
containing essential information about game entities and behavior.

- [YAML](https://github.com/psiberx/cp2077-tweak-xl/wiki/YAML-Tweaks) and [RED](https://github.com/psiberx/cp2077-tweak-xl/wiki/RED-Tweaks) formats for manipulating data in a declarative style 
- [Script extensions](https://github.com/psiberx/cp2077-tweak-xl/wiki/Script-Extensions) to add complex logic and dynamic changes 
- [Hot reloading](https://github.com/psiberx/cp2077-tweak-xl/wiki/Modder-Tools) to speed up development
- Focused on mods compatibility and maintainability  

## Getting Started

### Compatibility

- Cyberpunk 2077 2.3
- [redscript](https://github.com/jac3km4/redscript) 0.5.27+

### Installation

1. Install requirements:
   - [RED4ext](https://docs.red4ext.com/getting-started/installing-red4ext) 1.28.0+
2. Extract the release archive `TweakXL-x.x.x.zip` into the Cyberpunk 2077 directory.

## Documentation

- [TweakDB](https://github.com/psiberx/cp2077-tweak-xl/wiki/TweakDB)
- [YAML Tweaks](https://github.com/psiberx/cp2077-tweak-xl/wiki/YAML-Tweaks)
- [RED Tweaks](https://github.com/psiberx/cp2077-tweak-xl/wiki/RED-Tweaks)
- [Script Extensions](https://github.com/psiberx/cp2077-tweak-xl/wiki/Script-Extensions)
- [Modder Tools](https://github.com/psiberx/cp2077-tweak-xl/wiki/Modder-Tools)
- [Examples](https://github.com/psiberx/cp2077-tweak-xl/wiki/Examples)
