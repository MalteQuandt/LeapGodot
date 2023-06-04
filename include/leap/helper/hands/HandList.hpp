#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/array.hpp>

#include <Leap.h>

#include <leap/helper/hands/HandList.hpp>
#include <leap/helper/hands/Hand.hpp>


namespace godot::leap {
class HandList : public Node {
GDCLASS(HandList, Node);
public:
  explicit HandList();
  explicit HandList(Leap::HandList handlist);
// Leap Methods:
// -------------
  godot::leap::Hand* get(int handID) const;
  int count() const;
  bool isEmpty() const;
  godot::leap::Hand* leftmost();
  godot::leap::Hand* rightmost();

protected:
  static void _bind_methods();
private:
  Leap::HandList handlist;
  // pointer
  std::vector<std::shared_ptr<godot::leap::Hand>> handVector{};
};

} // namespace godot
