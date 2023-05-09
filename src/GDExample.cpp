#include <gdexample.hpp>
#include <godot_cpp/core/class_db.hpp>

void godot::GDExample::_bind_methods() {}

godot::GDExample::GDExample() {
  // Initialize any variables here.
  this->time_passed = 0.0;
}

godot::GDExample::~GDExample() {
  // Add your cleanup here.
}

void godot::GDExample::_process(double delta) {
  this->time_passed += delta;

  const double scale {100.0};
  const double offset {.0};

  godot::Vector2 new_position = Vector2(
      static_cast<real_t>(offset + (10.0 * Math::sin(this->time_passed * scale))),
      static_cast<real_t>(offset + (10.0 * Math::sin(this->time_passed * scale))));

  set_position(new_position);
}