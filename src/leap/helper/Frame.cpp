#include <leap/helper/Frame.hpp>
#include <leap/helper/InteractionBox.hpp>

using namespace godot::leap;
using namespace godot;

Frame::Frame() {}

float Frame::currentFramesPerSecond() {
  return this->frame.currentFramesPerSecond();
}

int64_t Frame::id() {
  return this->frame.id();
}

bool Frame::isValid() {
  return this->frame.isValid();
}

Hand* Frame::hand(int handID) {
  return this->handList->get(handID);
}

HandList* Frame::hands() {
  if(this->handList == nullptr) {
    this->handList = std::make_shared<godot::leap::HandList>(this->frame.hands());
  }
  return this->handList.get();
}

godot::leap::InteractionBox* Frame::interactionBox() {
  if(this->box == nullptr) {
    this->box = std::make_shared<godot::leap::InteractionBox>(this->frame.interactionBox());
  }
  return this->box.get();
}

// Register Methods
// ----------------

void Frame::_bind_methods() {
  ClassDB::bind_method(D_METHOD("currentFramesPerSecond"), &Frame::currentFramesPerSecond);
  ClassDB::bind_method(D_METHOD("id"), &Frame::id);
  ClassDB::bind_method(D_METHOD("isValid"), &Frame::isValid);
  ClassDB::bind_method(D_METHOD("hand"), &Frame::hand);
  ClassDB::bind_method(D_METHOD("hands"), &Frame::hands);
  ClassDB::bind_method(D_METHOD("interactionBox"), &Frame::interactionBox);
}