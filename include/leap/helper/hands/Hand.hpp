#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <Leap.h>

namespace godot::leap {
class Hand : public Node {
  GDCLASS(Hand, Node);

public:
  explicit Hand();
  explicit Hand(Leap::Hand hand) : hand{hand} {}
  // Leap Methods:
  // -------------
  float confidence();
  Vector3 direction();
  // Finger finger(int32_t finger); todo
  // FingerList fingers();
  float grabStrength();
  int32_t id();
  bool isLeft();
  bool isRight();
  bool isValid();
  Vector3 palmNormal();
  Vector3 palmPosition();
  Vector3 palmVelocity();
  float palmWidth();
  // Pointable pointable(int32_t pointable); todo
  // PointableList pointables();
  Vector3 sphereCenter();
  float sphereRadius();
  Vector3 stabilizedPalmPosition();
  Vector3 wristPosition();
  float timeVisible();

protected:
  static void _bind_methods();

private:
  Leap::Hand hand;
};
} // namespace godot::leap