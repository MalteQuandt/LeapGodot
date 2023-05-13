#pragma once

#include <godot_cpp/classes/Node.hpp>

#include <Leap.h>

namespace godot::leap {
class LeapController : public Node {
  /**
   * Simple Macro to define all necessary methods and attributes that a node has
   * to have
   */
  GDCLASS(LeapController, Node)

public:
  // Constructors
  // ------------

  explicit LeapController();

  // Public Interface
  // ---------------

  /**
   * @brief Process function for this node, will be called once per frame
   * @param delta The delta time since the last frame
   */
  void _process(double delta) override;

  // Properties
  // ----------

  // Signals:
  // --------

  // controller connection signals:

protected:
  /**
   * Bind the methods that can be used from Godots editor interface, and be
   * called from Godotscript
   */
  static void _bind_methods();

private:
  // Access point for the leap motion controller
  Leap::Controller controller;
  // if the leap motion controller is currently connected, always set to true before the first frame.
  // therefore the validity of this assumption has to be checked before doing any other calculations!
  bool isConnected{true};
};
} // namespace godot::leap