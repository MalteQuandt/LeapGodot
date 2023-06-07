#pragma once

#include <leap/LeapController.hpp>

namespace godot::leap {
  class LeapMenuController : public LeapController {
    // establish hierarchy
    GDCLASS(LeapMenuController, LeapController);
  public:
    explicit LeapMenuController();

    // todo: Define the public interface

  protected:
    static void _bind_methods();
  private:
    LeapController controller;
  };
}