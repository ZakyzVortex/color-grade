#pragma once

namespace color_grade {

struct Settings {
    bool enabled = true;
    float brightness = 0.0f;  // -0.5 .. 0.5   (added to the color)
    float contrast = 1.05f;   //  0.5 .. 1.5
    float saturation = 1.2f;  //  0.0 .. 2.0
    float gamma = 1.0f;       //  0.5 .. 2.0   (>1 brightens the midtones)
    float temperature = 0.0f; // -1.0 .. 1.0   (>0 warmer, <0 cooler)
    float vibrance = 0.0f;    // -1.0 .. 1.0   (boosts muted colors more than vivid ones)
    float vignette = 0.0f;    //  0.0 .. 1.0   (darkens the screen corners)
};

// Clamps every field to its valid range.
Settings sanitize(Settings s);

// Must be called before installHook().
void setSettings(const Settings &settings);

// Starts a background thread that waits for libminecraftpe.so and redirects its eglSwapBuffers import
// to our function. Returns immediately.
void installHook();

// Stops the thread and puts the original eglSwapBuffers back.
void removeHook();

} // namespace color_grade
