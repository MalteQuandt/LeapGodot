#include <leap/helper/gestures/Gesture.h>

using namespace godot;
using namespace godot::leap;

Gesture::Gesture() {}

int64_t Gesture::duration() const {
  return this->gesture.duration();
}

float Gesture::durationSeconds() const {
  return this->gesture.durationSeconds();
}

int32_t Gesture::id() const {
  return this->gesture.id();
}

bool Gesture::isValid() const {
  return this->gesture.isValid();
}

int Gesture::state() const {
  return this->gesture.state();
}

int Gesture::type() const {
  return this->gesture.type();
}

String Gesture::toString() const {
  return Variant(this->gesture.toString().c_str());
}

void Gesture::_bind_methods() {
  ClassDB::bind_method(D_METHOD("duration"), &Gesture::duration);
  ClassDB::bind_method(D_METHOD("durationSeconds"), &Gesture::durationSeconds);
  ClassDB::bind_method(D_METHOD("id"), &Gesture::id);
  ClassDB::bind_method(D_METHOD("isValid"), &Gesture::isValid);
  ClassDB::bind_method(D_METHOD("state"), &Gesture::state);
  ClassDB::bind_method(D_METHOD("type"), &Gesture::type);
  ClassDB::bind_method(D_METHOD("toString"), &Gesture::toString);
}