#include <locale>

#include <audio/AudioController.hpp>
#include <codecvt>

using namespace godot::audio;
using namespace ctag;

AudioController::AudioController()
    : port{9001}, ip{"127.0.0.1"}, oscClient{new ctag::osc::OSCLeapClient{ip, port}} {
}

void AudioController::_process(double delta) {
  // todo: implement behavior
}

bool AudioController::setVolumeLevel(unsigned int channel, float level) const {
  if (channel > 16 or channel == 0 or level > 1.0f or level < 0.0f) {
    return false;
  } else {
    this->oscClient->
            // set the path
            message("/dome/level")
            // send the arguments
            << static_cast<int>(channel)
            << static_cast<float>(level)
            // send the arguments
          << ::osc::EndMessage;
    this->oscClient->send();
    return true;
  }
}
bool AudioController::setAzimuth(unsigned int channel, unsigned int azimuth) const {
  if (azimuth > 360 or channel > 16 or channel == 0) {
    return false;
  } else {
    this->oscClient->
        // set the path
        message("/dome/azimuth")
        // send the arguments
        << static_cast<int>(channel)
        << static_cast<int>(azimuth)
        // send the arguments
        << ::osc::EndMessage;
    this->oscClient->send();
    return true;
  }
}
bool AudioController::setElevation(unsigned int channel, signed int elevation) const {
  if (channel > 16 or channel == 0 or elevation < -30 or elevation > 30) {
    return false;
  } else {
    this->oscClient->
        // set the path
        message("/dome/elevation")
        // send the arguments
        << static_cast<int>(channel)
        << static_cast<int>(elevation)
        // send the arguments
        << ::osc::EndMessage;
    this->oscClient->send();
    return true;
  }
}
bool AudioController::setSpread(unsigned int channel, unsigned int spread) const {
  if (channel > 16 or channel == 0 or spread > 100) {
    return false;
  } else {
    this->oscClient->
        // set the path
        message("/dome/spread")
        // send the arguments
        << static_cast<int>(channel)
        << static_cast<int>(spread)
        // send the arguments
        << ::osc::EndMessage;
    this->oscClient->send();
    return true;
  }
}

bool AudioController::setDistance(unsigned int channel, float distance) const {
  if (channel == 0 or channel > 16) {
    return false;
  } else {
    this->oscClient->
        // set the path
        message("/dome/distance")
        // send the arguments
        << static_cast<int>(channel)
        << static_cast<float>(distance)
        // send the arguments
        << ::osc::EndMessage;
    this->oscClient->send();
    return true;
  }
}

void AudioController::rebuild() {
  this->oscClient.reset();
  this->oscClient = std::make_unique<ctag::osc::OSCLeapClient>(this->ip, this->port);
}

void AudioController::set_port(unsigned int port) {
  this->port = port;
  this->rebuild();
}
unsigned int AudioController::get_port() { return this->port; }

void AudioController::set_ip(godot::String ip) {
  this->ip = std::string{ip.ascii().get_data()};
  this->rebuild();
}
godot::String AudioController::get_ip() { return Variant(this->ip.c_str()); }

bool AudioController::send(unsigned int channel, godot::Dictionary data) const {
  if (channel > 16 or channel == 0) {
    return false;
  } else {
    // fetch the keys
    const auto keys {data.keys()};

    // iterate over the keys in the dictionary
    for(auto i{0ull}; i < keys.size(); i++) {
      // fetch the current key
      const auto key = keys[static_cast<int>(i)].stringify();
      // check if the key matches one of the supported ones!
      if (key == String("volume")) {
        this->setVolumeLevel(channel, static_cast<float>(data[key]));
      }
      else if(key == String("azimuth")) {
        this->setAzimuth(channel, static_cast<unsigned int>(data[key]));
      }
      else if(key == String("elevation")) {
        this->setElevation(channel, static_cast<signed int>(data[key]));
      }
      else if(key == String("spread")) {
        this->setSpread(channel, static_cast<unsigned int>(data[key]));
      }
      else if(key == String("distance")) {
        this->setDistance(channel, static_cast<float>(data[key]));
      }
    }
    return true;
  }
}

// todo: continue writing this method:
bool AudioController::send_caresian(unsigned int channel, godot::Dictionary data) const {
  const bool condition {channel > 16 or channel == 0 };
  // if the channel is valid, validate the request
  if(condition) {
    const float x {0.0f};
    const float y {0.0f};
    const float z {0.0f};
    const godot::Vector3 to{0.0f, 0.0f, 0.0f};
    // fetch the keys
    const auto keys {data.keys()};
    // iterate over the input keys
    for(auto i{0ull}; i < keys.size();i++) {
      // fetch the current key
      const auto key {keys[static_cast<int>(i)]};
      // check the key against the expected values:
      if (key == String("volume")) {
        this->setVolumeLevel(channel, static_cast<float>(data[key]));
      }
      else if(key == String("x")) {
        // todo:
      }
      else if(key == String("y")) {
        // todo:
      }
      else if(key == String("z")) {
        // todo:
      }
      else if(key == String("to")) {
        // todo:
      }
      else if(key == String("distance")) {
        this->setDistance(channel, static_cast<float>(data[key]));
      }
    }
  }
  return condition;
}

void AudioController::_bind_methods() {
  // Register the callable methods:
  // ------------------------------
  using namespace godot;

  // method definitions:
  ClassDB::bind_method(D_METHOD("setSpread"), &AudioController::setSpread);
  ClassDB::bind_method(D_METHOD("setDistance"), &AudioController::setDistance);
  ClassDB::bind_method(D_METHOD("setVolumeLevel"),
                       &AudioController::setVolumeLevel);
  ClassDB::bind_method(D_METHOD("setAzimuth"), &AudioController::setAzimuth);
  ClassDB::bind_method(D_METHOD("setElevation"),
                       &AudioController::setElevation);
  ClassDB::bind_method(D_METHOD("rebuild"), &AudioController::rebuild);
  ClassDB::bind_method(D_METHOD("send"), &AudioController::send);

  // getter&setter:
  ClassDB::bind_method(D_METHOD("set_ip"), &AudioController::set_ip);
  ClassDB::bind_method(D_METHOD("get_ip"), &AudioController::get_ip);
  ClassDB::bind_method(D_METHOD("set_port"), &AudioController::set_port);
  ClassDB::bind_method(D_METHOD("get_port"), &AudioController::get_port);
}