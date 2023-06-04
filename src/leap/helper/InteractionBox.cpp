#include <leap/helper/InteractionBox.hpp>


using namespace godot;
using namespace godot::leap;

InteractionBox::InteractionBox() {}

godot::Vector3 InteractionBox::center() {
  auto center {this->box.center()};
  return godot::Vector3{center.x, center.y, center.z};
}

godot::Vector3 InteractionBox::denormalizePoint(godot::Vector3 position) {
  const Leap::Vector pos {position.x, position.y, position.z};
  const auto point {this->box.denormalizePoint(pos)};
  return godot::Vector3{point.x, point.y, point.z};
}

godot::Vector3 InteractionBox::normalizePoint(godot::Vector3 position, bool clamp) {
  const Leap::Vector pos {position.x, position.y, position.z};
  const auto point {this->box.denormalizePoint(pos)};
  return godot::Vector3{point.x, point.y, point.z};
}

float InteractionBox::depth() {
  return this->box.depth();
}

float InteractionBox::height() {
  return this->box.height();
}

float InteractionBox::width() {
  return this->box.width();
}

bool InteractionBox::isValid() {
  return this->box.isValid();
}

String InteractionBox::toString() {
  return Variant(this->box.toString().c_str());
}

// Register the correct methods:
// -----------------------------

void InteractionBox::_bind_methods() {
  ClassDB::bind_method(D_METHOD("center"), &InteractionBox::center);
  ClassDB::bind_method(D_METHOD("denormalizePoint"), &InteractionBox::denormalizePoint);
  ClassDB::bind_method(D_METHOD("normalizePoint"), &InteractionBox::normalizePoint);
  ClassDB::bind_method(D_METHOD("depth"), &InteractionBox::depth);
  ClassDB::bind_method(D_METHOD("width"), &InteractionBox::width);
  ClassDB::bind_method(D_METHOD("height"), &InteractionBox::height);
  ClassDB::bind_method(D_METHOD("isValid"), &InteractionBox::isValid);
  ClassDB::bind_method(D_METHOD("toString"), &InteractionBox::toString);
}
