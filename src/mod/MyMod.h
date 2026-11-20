#pragma once

#include <optional>

#include "mod/Config.h"

#include <pl/Mod.hpp>

namespace color_grade {

class ColorGradeMod {
  public:
    static ColorGradeMod &instance();

    ColorGradeMod();

    [[nodiscard]] ll::mod::NativeMod &getSelf() const { return mSelf; }

    bool load();
    bool enable();
    bool disable();
    bool unload();

  private:
    ll::mod::NativeMod &mSelf;
    ModConfig mConfig;
    std::optional<pl::config::ConfigFile<ModConfig>> mConfigFile;
};

} // namespace color_grade
