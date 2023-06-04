// Copied from godot-cpp/test/src and modified.
#include <RegisterExtension.hpp>

#include <audio/AudioController.hpp>
#include <leap/LeapController.hpp>
#include <leap/helper/Frame.hpp>

using namespace godot;

/// @file
/// Register our classes with Godot.

/// @brief Called by Godot to let us register our classes with Godot.
///
/// @param p_level the level being initialized by Godot
///
/// @see GDExtensionInit
void godot::initializeExtension(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }
  // register the nodes
  ClassDB::register_class<godot::leap::LeapController>();
  ClassDB::register_class<godot::leap::InteractionBox>();
  ClassDB::register_class<godot::leap::Frame>();
//  ClassDB::register_class<godot::leap::Hand>();
//  ClassDB::register_class<godot::leap::HandList>();
  ClassDB::register_class<godot::audio::AudioController>();
}

/// @brief Called by Godot to let us do any cleanup.
///
/// @see GDExtensionInit
void godot::uninitializeExtension(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }
}

extern "C" {
/// @brief This is the entry point for the shared library.
///
/// @note The name of this function must match the "entry_symbol" in
/// templates/template.*.gdextension.in
///
/// @param p_interface the interface (need more info)
/// @param p_library the library (need more info)
/// @param r_initialization the intialization (need more info)
///
/// @returns GDExtensionBool
GDExtensionBool GDE_EXPORT
GDExtensionInit(const GDExtensionInterface *p_interface,
                GDExtensionClassLibraryPtr p_library,
                GDExtensionInitialization *r_initialization) {

  {
    GDExtensionBinding::InitObject init_obj(p_interface, p_library,
                                            r_initialization);

    init_obj.register_initializer(initializeExtension);
    init_obj.register_terminator(uninitializeExtension);
    init_obj.set_minimum_library_initialization_level(
        MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
  }
}
}
