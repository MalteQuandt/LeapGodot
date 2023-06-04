#include <leap/helper/hands/Handlist.hpp>

using namespace godot;
using namespace godot::leap;

HandList::HandList() {}

HandList::HandList(Leap::HandList handlist) : handlist{handlist} {
  for (const auto hand : handlist) {
    this->handVector.emplace_back(std::make_shared<Hand>(hand));
  }
}

godot::leap::Hand *HandList::get(int handID) const {
  if (handID >= this->handVector.size() || handID < 0) {
    return nullptr;
  }
  return this->handVector[handID].get();
}

int HandList::count() const { return this->handlist.count(); }

bool HandList::isEmpty() const { return this->handlist.isEmpty(); }

godot::leap::Hand *HandList::leftmost() {
  const auto id{handlist.leftmost().id()};
  if (this->handVector.empty()) {
    return nullptr;
  }
  // get the address of the matching pointer
  const std::vector<std::shared_ptr<Hand>>::iterator itr{
      std::find_if(this->handVector.begin(), this->handVector.end(),
                   [id](const std::shared_ptr<godot::leap::Hand>& hand) -> bool {
                     return id == hand->id();
                   })};
  // fetch the first result
  return (*itr).get();
}

godot::leap::Hand *HandList::rightmost() {
  const auto id{handlist.rightmost().id()};
  if (this->handVector.size() == 0) {
    return nullptr;
  }
  // get the address of the matching pointer
  const std::vector<std::shared_ptr<Hand>>::iterator itr{
      std::find_if(this->handVector.begin(), this->handVector.end(),
                   [id](const std::shared_ptr<godot::leap::Hand>& hand) -> bool {
                     return id == hand->id();
                   })};
  // fetch the first result
  return (*itr).get();
}

// Bind Methods:
// -------------

void HandList::_bind_methods() {
  ClassDB::bind_method(D_METHOD("get"), &HandList::get);
  ClassDB::bind_method(D_METHOD("count"), &HandList::count);
  ClassDB::bind_method(D_METHOD("isEmpty"), &HandList::isEmpty);
  ClassDB::bind_method(D_METHOD("leftmost"), &HandList::leftmost);
  ClassDB::bind_method(D_METHOD("rightmost"), &HandList::rightmost);
}