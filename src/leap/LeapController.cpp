#include <leap/LeapController.hpp>

using namespace godot;

namespace godot::leap {

  LeapController::LeapController() : controller{} {
    using Leap::Controller;
    // initialize the config of the leap controller
    controller.setPolicy(Controller::PolicyFlag::POLICY_BACKGROUND_FRAMES);
    controller.clearPolicy(Controller::PolicyFlag::POLICY_OPTIMIZE_HMD);
  }

  bool LeapController::get_isConnected() const {
    return this->isConnected;
  }

  bool LeapController::get_isServiceConnected() const {
    return this->serviceAvailable;
  }

  godot::leap::Frame* LeapController::get_currentFrame() const {
    return this->currentFrameContainer.get();
  }

  void LeapController::process(double delta) {
    // check if a device is currently connected
    const bool isCurrentlyConnected{controller.isConnected()};
    const bool isServiceConnected{controller.isServiceConnected()};

    // if the service has been disconnected:
    if(isServiceConnected and not serviceAvailable) {
      emit_signal("leap_service_disconnected", this);
      this->serviceAvailable = false;
    }
    else if(not isServiceConnected and serviceAvailable) {
      emit_signal("leap_service_connected", this);
      this->serviceAvailable = true;
    }

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

    // if the leap motion controller is now connected:
    if(this->isConnected and this->serviceAvailable) {
      auto currentFrame {controller.frame()};
      const auto lastProcessedFrameID{this->currentlyProcessedFrame.id()};
      const auto currentID {currentFrame.id()};
      // iterate over all frames that have been added since the last time _process has been called
      for(auto history {0l}; history < currentID - lastProcessedFrameID; history++) {
        auto frameToProcess {this->controller.frame(history)};
        // set the new currently-in-process frame
        this->currentlyProcessedFrame = frameToProcess;
        // set the value of the frame node
        this->currentFrameContainer = std::make_shared<godot::leap::Frame>(this->currentlyProcessedFrame);
        this->processNextFrame(frameToProcess);
      }
    }

  }

  void LeapController::_process(double delta) {
    this->process(delta);
  }

  void LeapController::processNextFrame(const Leap::Frame frame) {
    // signal that a new frame has been processed!
    emit_signal("frame_received", this);
  }

  void LeapController::_bind_methods() {

    // property definitions
    ClassDB::bind_method(D_METHOD("get_isConnected"), &LeapController::get_isConnected);
    ClassDB::bind_method(D_METHOD("get_isServiceConnected"), &LeapController::get_isServiceConnected);
    ClassDB::bind_method(D_METHOD("get_currentFrame"), &LeapController::get_currentFrame);
    ClassDB::bind_method(D_METHOD("process"), &LeapController::_process);

    // signal definitions
    ADD_SIGNAL(MethodInfo("leap_service_disconnected",
                          PropertyInfo(Variant::OBJECT, "node")));
    ADD_SIGNAL(MethodInfo("leap_service_connected",
                          PropertyInfo(Variant::OBJECT, "node")));
    ADD_SIGNAL(MethodInfo("leap_disconnected",
                          PropertyInfo(Variant::OBJECT, "node")));
    ADD_SIGNAL(MethodInfo("leap_connected",
                          PropertyInfo(Variant::OBJECT, "node")));
    ADD_SIGNAL(MethodInfo("incorrect_device_count",
                          PropertyInfo(Variant::OBJECT, "node"),
                          PropertyInfo(Variant::INT, "devices_count")));

    // frame signals
    ADD_SIGNAL(MethodInfo("frame_received",
                          PropertyInfo(Variant::OBJECT, "node")));
    // todo: remove this signal
    ADD_SIGNAL(MethodInfo("palm_position",
                          PropertyInfo(Variant::OBJECT, "node"),
                          PropertyInfo(Variant::VECTOR3, "palm_position")));
  }
}