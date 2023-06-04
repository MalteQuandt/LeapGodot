#include <leap/helper/hands/Hand.hpp>

using namespace godot;
using namespace godot::leap;

Hand::Hand() {}

float Hand::confidence() {
  return this->hand.confidence();
}

Vector3 Hand::direction() {
  const auto direction {this->hand.direction()};
  return Vector3{direction.x, direction.y, direction.z};
}

float Hand::grabStrength() {
  return this->hand.grabStrength();
}

int32_t Hand::id() {
  return this->hand.id();
}

bool Hand::isLeft() {
  return this->hand.isLeft();
}

bool Hand::isRight() {
  return this->hand.isRight();
}

bool Hand::isValid() {
  return this->hand.isValid();
}

Vector3 Hand::palmNormal() {
  const auto normal {this->hand.palmNormal()};
  return Vector3{normal.x, normal.y, normal.z};
}

Vector3 Hand::palmPosition() {
  const auto normal {this->hand.palmPosition()};
  return Vector3{normal.x, normal.y, normal.z};
}

Vector3 Hand::palmVelocity() {
  const auto normal {this->hand.palmVelocity()};
  return Vector3{normal.x, normal.y, normal.z};
}

float Hand::palmWidth() {
  return this->hand.palmWidth();
}

Vector3 Hand::sphereCenter() {
  const auto center {this->hand.sphereCenter()};
  return Vector3{center.x, center.y, center.z};
}

float Hand::sphereRadius() {
  return this->hand.sphereRadius();
}

Vector3 Hand::stabilizedPalmPosition() {
  const auto palm {this->hand.stabilizedPalmPosition()};
  return Vector3{palm.x, palm.y, palm.z};
}

Vector3 Hand::wristPosition() {
  const auto wrist {this->hand.wristPosition()};
  return Vector3{wrist.x, wrist.y, wrist.z};

}

float Hand::timeVisible() {
  return this->hand.timeVisible();
}

// Bind Methods
// ------------

void Hand::_bind_methods() {
  ClassDB::bind_method(D_METHOD("confidence"), &Hand::confidence);
  ClassDB::bind_method(D_METHOD("direction"), &Hand::direction);
  ClassDB::bind_method(D_METHOD("grabStrength"), &Hand::grabStrength);
  ClassDB::bind_method(D_METHOD("id"), &Hand::id);
  ClassDB::bind_method(D_METHOD("isLeft"), &Hand::isLeft);
  ClassDB::bind_method(D_METHOD("isRight"), &Hand::isRight);
  ClassDB::bind_method(D_METHOD("isValid"), &Hand::isValid);
  ClassDB::bind_method(D_METHOD("palmNormal"), &Hand::palmNormal);
  ClassDB::bind_method(D_METHOD("palmPosition"), &Hand::palmPosition);
  ClassDB::bind_method(D_METHOD("palmVelocity"), &Hand::palmVelocity);
  ClassDB::bind_method(D_METHOD("palmWidth"), &Hand::palmWidth);
  ClassDB::bind_method(D_METHOD("sphereCenter"), &Hand::sphereCenter);
  ClassDB::bind_method(D_METHOD("sphereRadius"), &Hand::sphereRadius);
  ClassDB::bind_method(D_METHOD("stabilizedPalmPosition"), &Hand::stabilizedPalmPosition);
  ClassDB::bind_method(D_METHOD("wristPosition"), &Hand::wristPosition);
  ClassDB::bind_method(D_METHOD("timeVisible"), &Hand::timeVisible);
}