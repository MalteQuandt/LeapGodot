#include <godot_cpp/core/error_macros.hpp>

#include <leap/LeapController.hpp>

#define ENDL "\n"

namespace godot::leap {

  LeapController::LeapController() : controller{} {
    using Leap::Controller;
    // initialize the config of the leap controller
    controller.setPolicy(Controller::PolicyFlag::POLICY_BACKGROUND_FRAMES);
    controller.clearPolicy(Controller::PolicyFlag::POLICY_OPTIMIZE_HMD);
  }

  void LeapController::_process(double delta) {
    // check if a device is currently connected
    const bool isCurrentlyConnected{controller.isConnected() or controller.isServiceConnected()};
    // if the device was connected in the previous frame, but is not anymore:
    if(this->isConnected and not isCurrentlyConnected) {
      emit_signal("leap_disconnected", this);
      this->isConnected = false;
    }
      // if the device was not connected in the previous frame, but is now:
    else if(not this->isConnected and isCurrentlyConnected) {
      emit_signal("leap_connected", this);
      this->isConnected = true;
    }
    // check how many devices are connected:
    const int devices{controller.devices().count()};
    if(devices != 1) {
      emit_signal("incorrect_device_count", this, devices);
    }
  }

  void LeapController::_bind_methods() {
    using namespace godot;
    // signal definitions
    ADD_SIGNAL(MethodInfo("leap_disconnected",
                          PropertyInfo(Variant::OBJECT, "node")));
    ADD_SIGNAL(MethodInfo("leap_connected",
                          PropertyInfo(Variant::OBJECT, "node")));
    ADD_SIGNAL(MethodInfo("incorrect_device_count",
                          PropertyInfo(Variant::OBJECT, "node"),
                          PropertyInfo(Variant::INT, "devices_count")));
  }
}