// Copied from godot-cpp/test/src and modified.

#include <gdextension_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include <GDExample.hpp>

using namespace godot;

/// @file
/// Register our classes with Godot.

namespace
{
    /// @brief Called by Godot to let us register our classes with Godot.
    ///
    /// @param p_level the level being initialized by Godot
    ///
    /// @see GDExtensionInit
    void initializeExtension( ModuleInitializationLevel p_level )
    {
        if ( p_level != MODULE_INITIALIZATION_LEVEL_SCENE )
        {
            return;
        }

        ClassDB::register_class<godot::GDExample>();
    }

    /// @brief Called by Godot to let us do any cleanup.
    ///
    /// @see GDExtensionInit
    void uninitializeExtension( ModuleInitializationLevel p_level )
    {
        if ( p_level != MODULE_INITIALIZATION_LEVEL_SCENE )
        {
            return;
        }
    }
}

extern "C"
{
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
    GDExtensionBool GDE_EXPORT GDExtensionInit( const GDExtensionInterface *p_interface,
                                                GDExtensionClassLibraryPtr p_library,
                                                GDExtensionInitialization *r_initialization )
    {

        {
            GDExtensionBinding::InitObject init_obj( p_interface, p_library,
                                                            r_initialization );

            init_obj.register_initializer( initializeExtension );
            init_obj.register_terminator( uninitializeExtension );
            init_obj.set_minimum_library_initialization_level(
                MODULE_INITIALIZATION_LEVEL_SCENE );

            return init_obj.init();
        }
    }
}
