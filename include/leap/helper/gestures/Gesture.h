#pragma once

#include <godot_cpp/classes/node.hpp>

#include <Leap.h>


namespace godot::leap {

class Gesture : public Node {
  GDCLASS(Gesture, Node);

public:
  explicit Gesture();
  explicit Gesture(Leap::Gesture gesture) : gesture{gesture} {}

  // Leap Methods:
  // -------------
  int64_t duration() const;
  float durationSeconds() const;
  int32_t id() const;
  bool isValid() const;
  int state() const;
  int type() const;
  String toString() const;

protected:
  static void _bind_methods();

private:
  Leap::Gesture gesture;
};
}