#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <Leap.h>

#include <ForwardDeclarations.h>
// for more information, view https://developer-archive.leapmotion.com/documentation/v2/cpp/api/Leap.InteractionBox.html
// this is effectively the same interface

namespace godot::leap {

class InteractionBox : public Node {
    GDCLASS(InteractionBox, Node);
  public:
    explicit InteractionBox();
    explicit InteractionBox(Leap::InteractionBox box) : box{box} {}

    godot::Vector3 center();
    godot::Vector3 denormalizePoint(godot::Vector3 position);
    godot::Vector3 normalizePoint(godot::Vector3 position, bool clamp=true);
    float depth();
    float height();
    float width();
    bool isValid();
    String toString();

  protected:
    static void _bind_methods();

  private:
    Leap::InteractionBox box;
  };
}