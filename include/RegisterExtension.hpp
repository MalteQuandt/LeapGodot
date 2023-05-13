#pragma once

#include <gdextension_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

namespace godot {
  void initializeExtension(godot::ModuleInitializationLevel);
  void uninitializeExtension(godot::ModuleInitializationLevel p_level);
} // namespace godot