#include "mod/MyMod.h"

#include "render/ColorGrade.h"

#include <filesystem>

#include <pl/Mod.hpp>

namespace color_grade {

ColorGradeMod &ColorGradeMod::instance() {
    static ColorGradeMod instance;
    return instance;
}

ColorGradeMod::ColorGradeMod() : mSelf(*ll::mod::NativeMod::current()) {}

bool ColorGradeMod::load() {
    auto &self = getSelf();
    self.getLogger().debug("Loading...");

    std::error_code ec;
    std::filesystem::create_directories(self.getDataDir(), ec);
    if (ec) {
        self.getLogger().error("Failed to create data directory {}: {}", self.getDataDir().string(),
                               ec.message());
        return false;
    }

    std::filesystem::create_directories(self.getConfigDir(), ec);
    if (ec) {
        self.getLogger().error("Failed to create config directory {}: {}",
                               self.getConfigDir().string(), ec.message());
        return false;
    }

    mConfigFile.emplace();
    if (!mConfigFile->load()) {
        self.getLogger().warn("Failed to load typed config");
        return false;
    }
    mConfig = mConfigFile->value();

    self.getLogger().info("Loaded {} from {}", self.getName(), self.getModDir().string());
    return true;
}

bool ColorGradeMod::enable() {
    auto &self = getSelf();
    self.getLogger().debug("Enabling...");
    if (!mConfig.enabled) {
        self.getLogger().info("Color Grade is disabled by config");
        return true;
    }

    Settings settings;
    settings.enabled = mConfig.enabled;
    settings.brightness = mConfig.brightness;
    settings.contrast = mConfig.contrast;
    settings.saturation = mConfig.saturation;
    settings.gamma = mConfig.gamma;
    settings.temperature = mConfig.temperature;
    settings.vibrance = mConfig.vibrance;
    settings.vignette = mConfig.vignette;
    setSettings(settings);

    installHook();
    self.getLogger().info("Color filter requested (brightness {}, contrast {}, saturation {}, gamma {})",
                          mConfig.brightness, mConfig.contrast, mConfig.saturation, mConfig.gamma);
    return true;
}

bool ColorGradeMod::disable() {
    getSelf().getLogger().debug("Disabling...");
    removeHook();
    return true;
}

bool ColorGradeMod::unload() {
    getSelf().getLogger().debug("Unloading...");
    mConfigFile.reset();
    return true;
}

} // namespace color_grade
