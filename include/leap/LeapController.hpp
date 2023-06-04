#pragma once

#include <godot_cpp/classes/Node.hpp>

#include <Leap.h>
#include <leap/helper/Frame.hpp>

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

  /**
   * @brief Helper function to call the connection details from the
   * @param delta The delta time since the last frame
   */
  void process(double delta);

  // Properties
  // ----------
  
  /**
   * Check if the leap motion hardware is connected and available
   */
  bool get_isConnected [[nodiscard]] () const;

  /**
   * @brief Check whethere the leap motion service is running and connected to this application.
   */
   bool get_isServiceConnected [[nodiscard]] () const;

  /**
   * @brief Fetch the currently set frame
   */
   godot::leap::Frame* get_currentFrame[[nodiscard]] () const;

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
  bool serviceAvailable{true};
  // information about the last processed frame
  Leap::Frame currentlyProcessedFrame{};
  std::shared_ptr<godot::leap::Frame> currentFrameContainer{nullptr};

  // Private Methods
  // ---------------

  /**
   * @brief Process a frame
   * @param frame The frame to process
   */
  void processNextFrame(const Leap::Frame frame);
};
} // namespace godot::leap