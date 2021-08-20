/**
 * @brief Abstract interface for external control of sushi over rpc, osc or similar
 * @copyright MIND Music Labs AB, Stockholm
 */


#ifndef SUSHI_CONTROL_INTERFACE_H
#define SUSHI_CONTROL_INTERFACE_H

#include <functional>
#include <utility>
#include <optional>
#include <string>
#include <vector>
#include <variant>

#include "controller_types.h"

namespace sushi_controller {

class SystemController
{

};

class TransportController
{
public:
    virtual ~TransportController() = default;

    /**
     * @brief Get the current samplerate
     *
     * @return float The current samplerate
     */
    virtual std::pair<ControlStatus, float> get_samplerate() const = 0;

    /**
     * @brief Get the current playing mode
     *
     * @return PlayingMode The current playing mode
     */
    virtual std::pair<ControlStatus, PlayingMode> get_playing_mode() const = 0;

    /**
     * @brief Set the playing mode
     *
     * @param playing_mode The playing mode to set
     */
    virtual ControlStatus set_playing_mode(PlayingMode playing_mode) = 0;

    /**
     * @brief Get the sync mode
     *
     * @return SyncMode The current sync mode
     */
    virtual std::pair<ControlStatus, SyncMode> get_sync_mode() const = 0;

    /**
     * @brief Set the sync mode
     *
     * @param sync_mode The sync mode to set
     */
    virtual ControlStatus set_sync_mode(SyncMode sync_mode) = 0;

    /**
     * @brief Get the tempo
     *
     * @return float The current tempo
     */
    virtual std::pair<ControlStatus, float> get_tempo() const = 0;

    /**
     * @brief Set the tempo
     *
     * @param tempo The tempo to set
     * @return ControlStatus
     */
    virtual ControlStatus set_tempo(float tempo) = 0;

    /**
     * @brief Get the time signature
     *
     * @return TimeSignature The current time signature
     */
    virtual std::pair<ControlStatus, TimeSignature> get_time_signature() const = 0;

    /**
     * @brief Set the time signature
     *
     * @param signature The time signature to set
     * @return ControlStatus
     */
    virtual ControlStatus set_time_signature(TimeSignature signature) = 0;
protected:
    TransportController() = default;
};

class TimingController
{
public:
    virtual ~TimingController() = default;

    /**
     * @brief Check if timings are enabled
     *
     * @return std::pair<ControlStatus, bool> true if enabled. false if not
     */
    virtual std::pair<ControlStatus, bool> get_timings_enabled() const = 0;

    /**
     * @brief Set if timings should be enabled
     *
     * @param enabled true if timings should be enabled. false if not
     * @return ControlStatus
     */
    virtual ControlStatus set_timings_enabled(bool enabled) = 0;

    /**
     * @brief Get the engine timings
     *
     * @return std::pair<ControlStatus, CpuTimings>
     */
    virtual std::pair<ControlStatus, CpuTimings> get_engine_timings() const = 0;

    /**
     * @brief Get the track timings
     *
     * @param track_id The id of the track to get the timings from
     * @return std::pair<ControlStatus, CpuTimings>
     */
    virtual std::pair<ControlStatus, CpuTimings> get_track_timings(int track_id) const = 0;

    /**
     * @brief Get the processor timings
     *
     * @param processor_id The id of the processor to get the timings from
     * @return std::pair<ControlStatus, CpuTimings>
     */
    virtual std::pair<ControlStatus, CpuTimings> get_processor_timings(int processor_id) const = 0;

    /**
     * @brief Reset all the timings measurements
     *
     * @return ControlStatus
     */
    virtual ControlStatus reset_all_timings() = 0;

    /**
     * @brief Reset the timings measurements of a track
     *
     * @param track_id The id of the track to reset the timings of
     * @return ControlStatus
     */
    virtual ControlStatus reset_track_timings(int track_id) = 0;

    /**
     * @brief Reset the timings measurements of a processor
     *
     * @param processor_id The id of the processor to reset the timings of
     * @return ControlStatus
     */
    virtual ControlStatus reset_processor_timings(int processor_id) = 0;


protected:
    TimingController() = default;
};

class KeyboardController
{
public:
    virtual ~KeyboardController() = default;

      /**
     * @brief Send note on message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param channel The channel on which the message should be sent
     * @param note The note to send. Follows the MIDI standard where middle c = 60
     * @param velocity The velocity of the note. Should be in range (0.0-1.0)
     * @return ControlStatus
     */
    virtual ControlStatus send_note_on(int track_id, int channel, int note, float velocity) = 0;

    /**
     * @brief Send note off message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param note The note to send. Follows the MIDI standard where middle c = 60
     * @param channel The channel on which the message should be sent
     * @param velocity The velocity of the note. Should be in range (0.0-1.0)
     * @return ControlStatus
     */
    virtual ControlStatus send_note_off(int track_id, int channel, int note, float velocity) = 0;

    /**
     * @brief Send note aftertouch message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param channel The channel on which the message should be sent
     * @param note The note to send. Follows the MIDI standard where middle c = 60
     * @param value
     * @return ControlStatus
     */
    virtual ControlStatus send_note_aftertouch(int track_id, int channel, int note, float value) = 0;

    /**
     * @brief Send aftertouch message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param channel The channel on which the message should be sent
     * @param value
     * @return ControlStatus
     */
    virtual ControlStatus send_aftertouch(int track_id, int channel, float value) = 0;

     /**
     * @brief Send pitch bend message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param channel The channel on which the message should be sent
     * @param value
     * @return ControlStatus
     */
    virtual ControlStatus send_pitch_bend(int track_id, int channel, float value) = 0;

    /**
     * @brief Send modulation message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param channel The channel on which the message should be sent
     * @param value
     * @return ControlStatus
     */
    virtual ControlStatus send_modulation(int track_id, int channel, float value) = 0;

protected:
    KeyboardController() = default;
};

class AudioGraphController
{
public:
    virtual ~AudioGraphController() = default;

    /**
     * @brief Get the info for all available processors
     *
     * @return std::pair<ControlStatus, std::vector<ProcessorInfo>>
     * Vector containing the info of each processor
     */
    virtual std::pair<ControlStatus, std::vector<ProcessorInfo>> get_all_processors() const = 0;

    /**
     * @brief Get the info for all avilable tracks
     *
     * @return std::vector<TrackInfo> Vector containing the info of each track
     */
    virtual std::pair<ControlStatus, std::vector<TrackInfo>> get_all_tracks() const = 0;

    /**
     * @brief Get the track id from a name
     *
     * @param track_name The name of the track to get the id from
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_track_id(const std::string& track_name) const = 0;

    /**
     * @brief Get the info from a track
     *
     * @param track_id The id of the track to get the info from
     * @return std::pair<ControlStatus, TrackInfo>
     */
    virtual std::pair<ControlStatus, TrackInfo> get_track_info(int track_id) const = 0;

    /**
     * @brief Get the info of avilable processors on a track
     *
     * @param track_id The id of the track to get the available processors from
     * @return std::pair<ControlStatus, std::vector<ProcessorInfo>>
     */
    virtual std::pair<ControlStatus, std::vector<ProcessorInfo>> get_track_processors(int track_id) const = 0;

     /**
     * @brief Get the id of a processor from its name
     *
     * @param processor_name The name of the processor to get the id from
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_processor_id(const std::string& processor_name) const = 0;

    /**
     * @brief Get the info about a processor
     *
     * @param processor_id The id of the processor to get the info from
     * @return std::pair<ControlStatus, ProcessorInfo>
     */
    virtual std::pair<ControlStatus, ProcessorInfo> get_processor_info(int processor_id) const = 0;

    /**
     * @brief Get the bypass state of a processor
     *
     * @param processor_id The id of the processor to get the bypass state from
     * @return std::pair<ControlStatus, bool>
     */
    virtual std::pair<ControlStatus, bool> get_processor_bypass_state(int processor_id) const = 0;

    /**
     * @brief Set the bypass state of a processor
     *
     * @param processor_id The id of the processor to set the bypass state of
     * @param bypass_enabled True to bypass processor, False to enable processor
     * @return ControlStatus
     */
    virtual ControlStatus set_processor_bypass_state(int processor_id, bool bypass_enabled) = 0;

    /**
     * @brief Create a new track in sushi
     *
     * @param name The name of the new track
     * @param channels The number of channels to assign the new track
     * @return ControlStatus
     */
    virtual ControlStatus create_track(const std::string& name, int channels) = 0;

    /**
     * @brief Create a new multibus track in sushi
     *
     * @param name The name of the the new track
     * @param output_busses The number of output busses to assign the new track
     * @param input_busses The number of input busses to assign the new track
     * @return ControlStatus
     */
    virtual ControlStatus create_multibus_track(const std::string& name,
                                                int output_busses,
                                                int input_busses) = 0;

    /**
     * @brief Create a new processor on an existing track
     *
     * @param name The name to assign the processor. Must be unique
     * @param uid The uid of an internal sushi processor or the URI of an LV2
     *            processor. Not applicable for vst2x and vst3x
     * @param path The path to the processor library. Only for vst2x and vst3x
     * @param type The type of processor to create
     * @param track_id The id of the track to add the processor to
     * @param before_processor Which existing processor to create the new
     * processor in front of
     * @param add_to_back Set to true to add the processor to the back of the
     * processing chain on the track. Overrides the `before_processor` parameter
     * @return ControlStatus
     */
    virtual ControlStatus create_processor_on_track(const std::string& name,
                                                    const std::string& uid,
                                                    const std::string& path,
                                                    PluginType type,
                                                    int track_id,
                                                    int before_processor,
                                                    bool add_to_back) = 0;

    /**
     * @brief Move an existing processor
     *
     * @param processor The id of the processor to move
     * @param source_track The id of the track to move the processor from
     * @param destination_track The id of the track to move the processor to
     * @param before_processor The id of another processor to move this processor
     * in front of
     * @param add_to_back Set to true to move the processor the end of the processing
     * chain on the destination track. Overrides the `before_processor` parameter
     * @return ControlStatus
     */
    virtual ControlStatus move_processor_on_track(int processor,
                                                  int source_track,
                                                  int destination_track,
                                                  int before_processor,
                                                  bool add_to_back) = 0;

    /**
     * @brief Delete an existing processor from a track
     *
     * @param processor The id of the processor to delete
     * @param track The id of the track that has the processor
     * @return ControlStatus
     */
    virtual ControlStatus delete_processor_from_track(int processor,
                                                      int track) = 0;

    /**
     * @brief Delete a track an all processors on it
     *
     * @param track_id The id of the track to delete
     * @return ControlStatus
     */
    virtual ControlStatus delete_track(int track_id) = 0;

protected:
    AudioGraphController() = default;
};

class ProgramController
{
public:
    virtual ~ProgramController() = default;

    /**
     * @brief Get the id of the current program of a processor
     *
     * @param processor_id The id of the processor to get the current program id from
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_processor_current_program(int processor_id) const = 0;

    /**
     * @brief Get the name of the current program of a processor
     *
     * @param processor_id The id of the processor to get the current program name from
     * @return std::pair<ControlStatus, std::string>
     */
    virtual std::pair<ControlStatus, std::string> get_processor_current_program_name(int processor_id) const = 0;

    /**
     * @brief Get the name of a program from a processor
     *
     * @param processor_id The id of the processor containing the program
     * @param program_id The id of program to get the name from
     * @return std::pair<ControlStatus, std::string>
     */
    virtual std::pair<ControlStatus, std::string> get_processor_program_name(int processor_id,
                                                                             int program_id) const = 0;

    /**
     * @brief Get the names of the programs available to a processor
     *
     * @param processor_id The id of the processor to get the program names from
     * @return std::pair<ControlStatus, std::vector<std::string>>
     */
    virtual std::pair<ControlStatus, std::vector<std::string>> get_processor_programs(int processor_id) const = 0;

    /**
     * @brief Set the current program of a processor
     *
     * @param processor_id The id of the processor to set the program on
     * @param program_id The id of the program to set on the processor
     * @return ControlStatus
     */
    virtual ControlStatus set_processor_program(int processor_id,
                                                int program_id)= 0;

protected:
    ProgramController() = default;
};

class ParameterController
{
public:
    virtual ~ParameterController() = default;

    /**
     * @brief Get the parameters available to a track
     *
     * @param track_id The id of the track to get the parameters from
     * @return std::pair<ControlStatus, std::vector<ParameterInfo>>
     */
    virtual std::pair<ControlStatus, std::vector<ParameterInfo>> get_track_parameters(int track_id) const = 0;

    /**
     * @brief Get the parameters available to a processor
     *
     * @param processor_id The id of the processor to get the parameters from
     * @return std::pair<ControlStatus, std::vector<ParameterInfo>>
     */
    virtual std::pair<ControlStatus, std::vector<ParameterInfo>> get_processor_parameters(int processor_id) const = 0;

    /**
     * @brief Get the id of a parameter from its name
     *
     * @param processor_id The id of the processor containing the parameter
     * @param parameter The name of the parameter to get the id from
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_parameter_id(int processor_id,
                                                           const std::string& parameter) const = 0;

    /**
     * @brief Get the info of a parameter
     *
     * @param processor_id The id of the processors containing the parameter
     * @param parameter_id The id of the parameter to get the info from
     * @return std::pair<ControlStatus, ParameterInfo>
     */
    virtual std::pair<ControlStatus, ParameterInfo> get_parameter_info(int processor_id,
                                                                       int parameter_id) const = 0;

    /**
     * @brief Get the current value of a parameter
     *
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of parameter to get the value from
     * @return std::pair<ControlStatus, float>
     */
    virtual std::pair<ControlStatus, float> get_parameter_value(int processor_id,
                                                                int parameter_id) const = 0;

    /**
     * @brief Get the normalised current value of a parameter
     *
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to get the normalised value from
     * @return std::pair<ControlStatus, float>
     */
    virtual std::pair<ControlStatus, float> get_parameter_value_in_domain(int processor_id,
                                                                          int parameter_id) const = 0;

    /**
     * @brief Get the current value of a parameter as a string
     *
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to get value as a string from
     * @return std::pair<ControlStatus, std::string>
     */
    virtual std::pair<ControlStatus, std::string> get_parameter_value_as_string(int processor_id,
                                                                                int parameter_id) const = 0;

    /**
     * @brief Set the value of a parameter
     *
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to set the value of
     * @param value The value to set the parameter to
     * @return ControlStatus
     */
    virtual ControlStatus set_parameter_value(int processor_id,
                                              int parameter_id,
                                              float value) = 0;

protected:
    ParameterController() = default;
};

class MidiController
{
public:
    virtual ~MidiController() = default;

protected:
    MidiController() = default;
};

class AudioRoutingController
{
public:
    virtual ~AudioRoutingController() = default;

protected:
    AudioRoutingController() = default;
};

class CvGateController
{
public:
    virtual ~CvGateController() = default;

protected:
    CvGateController() = default;
};

class OscController
{
public:
    virtual ~OscController() = default;

protected:
    OscController() = default;
};

class NotificationController
{
public:
    virtual ~NotificationController() = default;

    /**
     * @brief Subscribe to changes on the transport
     *
     * @param callback The callback to run when a change is made to the transport
     */
    virtual void subscribe_to_transport_changes(std::function<void(TransportUpdate update, TransportUpdateType type)> callback) = 0;

    /**
     * @brief Subscribe to timing updates
     *
     * @param callback The callback to run when the timings are updated
     */
    virtual void subscribe_to_engine_cpu_timing_updates(std::function<void(CpuTimings timings)> callback) = 0;

    /**
     * @brief Subscribe to track changes
     *
     * @param callback The callback to run when the tracks are changed
     */
    virtual void subscribe_to_track_changes(std::function<void(TrackUpdate update)> callback) = 0;

    /**
     * @brief Subscribe to processor changes
     *
     * @param callback The callback to run when the processors are changed
     */
    virtual void subscribe_to_processor_changes(std::function<void(ProcessorUpdate update)> callback) = 0;

    /**
     * @brief Subscribe callback to parameter change updates
     *
     * @param callback The callback to run when a parameter update is received
     * @param parameter_blocklist Parameters to blocklist. The first int in the
     * pair is a processor id. The second int is a processor id
     */
    virtual void subscribe_to_parameter_updates(std::function<void(int parameter_id, int processor_id, float value)> callback,
                                                std::vector<std::pair<int,int>> parameter_blocklist) = 0;


protected:
    NotificationController() = default;
};

/**
 * @brief A class to control sushi
 *
 */

class SushiController
{
public:
    virtual ~SushiController() = default;

    SystemController* system_controller() { return _system_controller; }
    TransportController* transport_controller() { return _transport_controller; }
    TimingController* timing_controller() { return _timing_controller; }
    KeyboardController* keyboard_controller() { return _keyboard_controller; }
    AudioGraphController* audio_graph_controller() { return _audio_graph_controller; }
    ProgramController* program_controller() { return _program_controller; }
    ParameterController* parameter_controller() { return _parameter_controller; }
    MidiController* midi_controller() { return _midi_controller; }
    AudioRoutingController* audio_routing_controller() { return _audio_routing_controller; }
    CvGateController* cv_gate_controller() { return _cv_gate_controller; }
    OscController* osc_controller() { return _osc_controller; }
    NotificationController* notification_controller() { return _notification_controller; }

protected:
    SushiController(SystemController* system_controller,
                    TransportController* transport_controller,
                    TimingController* timing_controller,
                    KeyboardController* keyboard_controller,
                    AudioGraphController* audio_graph_controller,
                    ProgramController* program_controller,
                    ParameterController* parameter_controller,
                    MidiController* midi_controller,
                    AudioRoutingController* audio_routing_controller,
                    CvGateController* cv_gate_controller,
                    OscController* osc_controller,
                    NotificationController* notification_controller) :
                        _system_controller(system_controller),
                        _transport_controller(transport_controller),
                        _timing_controller(timing_controller),
                        _keyboard_controller(keyboard_controller),
                        _audio_graph_controller(audio_graph_controller),
                        _program_controller(program_controller),
                        _parameter_controller(parameter_controller),
                        _midi_controller(midi_controller),
                        _audio_routing_controller(audio_routing_controller),
                        _cv_gate_controller(cv_gate_controller),
                        _osc_controller(osc_controller),
                        _notification_controller(notification_controller) {}

private:
    SystemController* _system_controller;
    TransportController* _transport_controller;
    TimingController* _timing_controller;
    KeyboardController* _keyboard_controller;
    AudioGraphController* _audio_graph_controller;
    ProgramController* _program_controller;
    ParameterController* _parameter_controller;
    MidiController* _midi_controller;
    AudioRoutingController* _audio_routing_controller;
    CvGateController* _cv_gate_controller;
    OscController* _osc_controller;
    NotificationController* _notification_controller;
};

} // sushi_controller


#endif //SUSHI_CONTROL_INTERFACE_H
