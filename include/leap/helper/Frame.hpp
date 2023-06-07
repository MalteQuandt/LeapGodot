#pragma once

#include <godot_cpp/classes/node.hpp>

#include <Leap.h>

#include <leap/helper/hands/Hand.hpp>
#include <leap/helper/hands/HandList.hpp>
#include <leap/helper/InteractionBox.hpp>
#include <leap/helper/gestures/Gesture.h>

#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/object.hpp>

// for more informations, view https://developer-archive.leapmotion.com/documentation/v2/cpp/api/Leap.InteractionBox.html
// this is effectively the same interface

namespace godot::leap {
class Frame : public Node {
  GDCLASS(Frame, Node);
public:
  explicit Frame();
  explicit Frame(Leap::Frame frame) : frame{frame} {}
// Leap Methods:
// -------------

  float currentFramesPerSecond();
  int64_t id();
  bool isValid();

  godot::leap::Hand* hand(int handID);
  godot::leap::HandList* hands();
  godot::leap::InteractionBox* interactionBox();

protected:
  static void _bind_methods();
private:
  Leap::Frame frame;

  // pointers
  std::shared_ptr<godot::leap::InteractionBox> box{nullptr};
  std::shared_ptr<godot::leap::HandList> handList{nullptr};

  std::vector<godot::leap::Hand> handVector{};
  std::vector<godot::leap::Gesture> gestureVector{};
};

} // namespace godot
