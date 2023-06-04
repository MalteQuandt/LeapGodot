#pragma once

#include <godot_cpp/classes/node.hpp>

#include <osc/OSCLeapClient.hpp>

namespace godot::audio {
class AudioController : public Node {
  GDCLASS(AudioController, Node)

  explicit AudioController();

  // Public Node Interface:
  // ----------------------

  /**
   * @brief Process function to call for each frame of the games execution
   * @param delta The time difference between the last and current frame
   */
  void _process(double delta) override;

  void set_port(unsigned int newPort);
  unsigned int get_port();

  void set_ip(godot::String newIP);
  godot::String get_ip();

  bool send(unsigned int channel = 1,
            godot::Dictionary data = godot::Dictionary()) const;

  bool send_caresian(unsigned int channel = 1, godot::Dictionary = godot::Dictionary()) const;

  /**
   * Set the volume level of the given channel
   *
   * @param channel The channel to modify, in [1, 16] (inclusive)
   * @param level The level to set, in the range [0.0, 1.0]
   *
   * @return If the setting was successful
   */
  bool setVolumeLevel(unsigned int channel = 1, float level = 1.0) const;

  /**
   * Set the azimuth of the given channel
   *
   * @param channel The channel to modify, in [1, 16] (inclusive)
   * @param azimuth The azimuth to set, in the range [0, 360]
   *
   * @return If the setting was successful
   */
  bool setAzimuth(unsigned int channel = 1, unsigned int azimuth = 0) const;

  /**
   * Set the elevation of the given channel
   *
   * @param channel The channel to modify, in [1, 16] (inclusive)
   * @param eleveation The elevation to set, in the range [-30, 30]
   *
   * @return If the setting was successful
   */
  bool setElevation(unsigned int channel = 1, signed int elevation = 0) const;

  /**
   * Set the spread of the given channel
   *
   * @param channel The channel to modify, in [1, 16] (inclusive)
   * @param spread The spread to set, in the range [0, 100]
   *
   * @return If the setting was successful
   */
  bool setSpread(unsigned int channel = 1, unsigned int spread = 0) const;

  /**
   * Set the distance of the given channel
   *
   * @param channel The channel to modify, in [1, 16] (inclusive)
   * @param distance The distance to set, in the range [0, infinity]
   *
   * @return If the setting was successful
   */
  bool setDistance(unsigned int channel = 1, float distance = 1.0f) const;

  /**
   * @brief Rebuild the osc connection object
   */
  void rebuild();

protected:
  /**
   * @brief Register the methods that should be callable in the gdscript
   * interface
   */
  static void _bind_methods();

private:
  /**
   * @brief The osc client
   */
  std::string ip;
  unsigned int port;
  std::unique_ptr<ctag::osc::OSCLeapClient> oscClient;
};
} // namespace godot::audio