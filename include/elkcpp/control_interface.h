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
public:
    virtual ~SystemController() = default;

    /**
     * @brief Get the sushi version as a string
     *
     * @return std::pair<ControlStatus, std::string>
     */
    virtual std::pair<ControlStatus, std::string> get_sushi_version() = 0;

    /**
     * @brief Get the info used for building sushi
     *
     * @return std::pair<ControlStatus, BuildInfo>
     */
    virtual std::pair<ControlStatus, BuildInfo> get_build_info() = 0;

    /**
     * @brief Get the number of input channels available to sushi
     *
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_input_audio_channel_count() = 0;

    /**
     * @brief Get the number of output channels available to sushi
     *
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_output_audio_channel_count() = 0;

protected:
    SystemController() = default;
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
     * @brief Get the full state of a processor
     *
     * @param processor_id The id of the processor to get the state from
     * @return std::pair<ControlStatus, ProcessorState>
     */
    virtual std::pair<ControlStatus, ProcessorState> get_processor_state(int processor_id) const = 0;

    /**
     * @brief Set the bypass state of a processor
     *
     * @param processor_id The id of the processor to set the bypass state of
     * @param bypass_enabled True to bypass processor, False to enable processor
     * @return ControlStatus
     */
    virtual ControlStatus set_processor_bypass_state(int processor_id, bool bypass_enabled) = 0;

    /**
     * @brief Set the full or partial state of a processor
     *
     * @param processor_id The id of the processor to set the state of
     * @param state A ProcessorState object that will be applied to the chosen processor
     * @return ControlStatus
     */
    virtual ControlStatus set_processor_state(int processor_id, const ProcessorState& state) = 0;

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
     * @param buses The number of audio buses in the new track
     * @return ControlStatus
     */
    virtual ControlStatus create_multibus_track(const std::string& name, int buses) = 0;

    /**
     * @brief Create a pre master track in sushi
     *
     * @param name The name of the the new track
     * @return ControlStatus
     */
    virtual ControlStatus create_pre_track(const std::string& name) = 0;

    /**
     * @brief Create a post master track in sushi to
     *
     * @param name The name of the the new track
     * @return ControlStatus
     */
    virtual ControlStatus create_post_track(const std::string& name) = 0;

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

    /**
     * @brief Get the properties available to a track
     *
     * @param track_id The id of the track to get the parameters from
     * @return std::pair<ControlStatus, std::vector<PropertyInfo>>
     */
    virtual std::pair<ControlStatus, std::vector<PropertyInfo>> get_track_properties(int track_id) const = 0;

    /**
     * @brief Get the properties available to a processor
     *
     * @param processor_id The id of the processor to get the properties from
     * @return std::pair<ControlStatus, std::vector<PropertyInfo>>
     */
    virtual std::pair<ControlStatus, std::vector<PropertyInfo>> get_processor_properties(int processor_id) const = 0;

    /**
     * @brief Get the id of a property from its name
     *
     * @param processor_id The id of the processor containing the property
     * @param property The name of the property to get the id from
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_property_id(int processor_id,
                                                         const std::string& property_name) const = 0;

    /**
     * @brief Get the info of a property
     *
     * @param processor_id The id of the processors containing the property
     * @param property_id The id of the property to get the info from
     * @return std::pair<ControlStatus, ParameterInfo>
     */
    virtual std::pair<ControlStatus, PropertyInfo> get_property_info(int processor_id,
                                                                     int property_id) const = 0;

    /**
     * @brief Get the current value of a property
     *
     * @param processor_id The id of the processor containing the property
     * @param property_id The id of property to get the value from
     * @return std::pair<ControlStatus, float>
     */
    virtual std::pair<ControlStatus, std::string> get_property_value(int processor_id,
                                                                     int property_id) const = 0;

    /**
     * @brief Set the value of a property
     *
     * @param processor_id The id of the processor containing the property
     * @param property_id The id of the property to set the value of
     * @param value The value to set the property to
     * @return ControlStatus
     */
    virtual ControlStatus set_property_value(int processor_id,
                                             int property_id,
                                             std::string value) = 0;

protected:
    ParameterController() = default;
};

class MidiController
{
public:
    virtual ~MidiController() = default;

    /**
     * @brief Get number of available MIDI input ports
     *
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_input_ports() = 0;

    /**
     * @brief Get number of available MIDI output ports
     *
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_output_ports() = 0;

    /**
     * @brief Get all MIDI keyboard input connections
     *
     * @return std::pair<ControlStatus, std::vector<MidiKbdConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiKbdConnection>> get_all_kbd_input_connections() = 0;

    /**
     * @brief Get all MIDI keyboard output connections
     *
     * @return std::pair<ControlStatus, std::vector<MidiKbdConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiKbdConnection>> get_all_kbd_output_connections() = 0;

    /**
     * @brief Get all MIDI Control Change input connections
     *
     * @return std::pair<ControlStatus, std::vector<MidiCCConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiCCConnection>> get_all_cc_input_connections() = 0;

    /**
     * @brief Get all MIDI Program Change input input connections
     *
     * @return std::pair<ControlStatus, std::vector<MidiPCConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiPCConnection>> get_all_pc_input_connections() = 0;

    /**
     * @brief Get the Control Change input connections for a processor
     *
     * @param processor_id The processor to get the Control Change input connections from
     * @return std::pair<ControlStatus, std::vector<MidiCCConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiCCConnection>> get_cc_input_connections_for_processor(int processor_id) = 0;

    /**
     * @brief Get the Program Change input connections for a processor
     *
     * @param processor_id The processor to get the Program Change input connections from
     * @return std::pair<ControlStatus, std::vector<MidiPCConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiPCConnection>> get_pc_input_connections_for_processor(int processor_id) = 0;

    /**
     * @brief Get whether MIDI clock is enabled for a given MIDI output port
     *
     * @param port Id of the port to query
     * @return If ControlStatus == Ok, then true if enabled, false if disabled
     */
    virtual std::pair<ControlStatus, bool> get_midi_clock_output_enabled(int port) const = 0;

    /**
     * @brief Enable or disable MIDI clock output for a given output port
     * @param enabled true to enable, false to disable
     * @param port Id of the port to set
     * @return ControlStatus
     */
    virtual ControlStatus set_midi_clock_output_enabled(bool enabled, int port) = 0;

    /**
     * @brief Connect keyboard input to a track
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus connect_kbd_input_to_track(MidiKbdConnection connection_data) = 0;

    /**
     * @brief Connection keyboard from a track
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus connect_kbd_output_from_track(MidiKbdConnection connection_data) = 0;

    /**
     * @brief Connect Control Change messages to a parameter
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus connect_cc_to_parameter(MidiCCConnection connection_data) = 0;

    /**
     * @brief Connect Program Change messages to a processor
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus connect_pc_to_processor(MidiPCConnection connection_data) = 0;

    /**
     * @brief Disconnect an existing keyboard input connection
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_kbd_input(MidiKbdConnection connection_data) = 0;

    /**
     * @brief Disconnect an existing keyboard output connection
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_kbd_output(MidiKbdConnection connection_data) = 0;

    /**
     * @brief Disconnect an existing Control Change connection
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_cc(MidiCCConnection connection_data) = 0;

    /**
     * @brief Disconnect an existing Program Change connection
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_pc(MidiPCConnection connection_data) = 0;

    /**
     * @brief Disconnect all Control Change connections from a processor
     *
     * @param processor_id
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_cc_from_processor(int processor_id) = 0;

    /**
     * @brief Disconnect all Program Change connection from a processor
     *
     * @param processor_id
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_pc_from_processor(int processor_id) = 0;

protected:
    MidiController() = default;
};

class AudioRoutingController
{
public:
    virtual ~AudioRoutingController() = default;

    /**
     * @brief Get all the current input connections
     *
     * @return std::vector<AudioConnection>
     */
    virtual std::pair<ControlStatus, std::vector<AudioConnection>> get_all_input_connections() const = 0;

    /**
     * @brief Get all the current output connections
     *
     * @return std::vector<AudioConnection>
     */
    virtual std::pair<ControlStatus, std::vector<AudioConnection>> get_all_output_connections() const = 0;

    /**
     * @brief Get the input connections for a track
     *
     * @param track_id Id of the track to get the connections from
     * @return std::vector<AudioConnection>
     */
    virtual std::pair<ControlStatus, std::vector<AudioConnection>> get_input_connections_for_track(int track_id) const = 0;

    /**
     * @brief Get the output connections for a track
     *
     * @param track_id Id of the track to get the connections from
     * @return std::vector<AudioConnection>
     */
    virtual std::pair<ControlStatus, std::vector<AudioConnection>> get_output_connections_for_track(int track_id) const = 0;

    /**
     * @brief Connect an input channel to a track
     *
     * @param track_id The id of the track to connect
     * @param track_channel The index of the track channel to connect
     * @param input_channel The index of the engine input channel to connect
     * @return ControlStatus
     */
    virtual ControlStatus connect_input_channel_to_track(int track_id, int track_channel, int input_channel) = 0;
    ControlStatus connect_input_channel_to_track(AudioConnection connection)
    {
        return connect_input_channel_to_track(connection.track_id, connection.track_channel, connection.engine_channel);
    }

    /**
     * @brief Connect an output channel from a track
     *
     * @param track_id The id of the track to connect
     * @param track_channel The index of the track channel to connect
     * @param output_channel The index of the engine output channel to connect
     * @return ControlStatus
     */
    virtual ControlStatus connect_output_channel_from_track(int track_id, int track_channel, int output_channel) = 0;
    ControlStatus connect_output_channel_from_track(AudioConnection connection)
    {
        return connect_output_channel_from_track(connection.track_id, connection.track_channel, connection.engine_channel);
    }

    /**
     * @brief Disconnect an input channel from a track
     *
     * @param track_id The id of the track to disconnect
     * @param track_channel The index of the track channel to disconnect
     * @param input_channel The index of the engine input channel to disconnect
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_input(int track_id, int track_channel, int input_channel) = 0;
    ControlStatus disconnect_input(AudioConnection connection)
    {
        return disconnect_input(connection.track_id, connection.track_channel, connection.engine_channel);
    }

    /**
     * @brief Disconnect an output channel from a track
     *
     * @param track_id The id of the track to disconnect
     * @param track_channel The index of the track channel to disconnect
     * @param output_channel The index of the engine output channel to disconnect
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_output(int track_id, int track_channel, int output_channel) = 0;
    ControlStatus disconnect_output(AudioConnection connection)
    {
        return disconnect_output(connection.track_id, connection.track_channel, connection.engine_channel);
    }

    /**
     * @brief Disconnect all input channels from a track
     *
     * @param track_id The id of the track to disconnect from
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_inputs_from_track(int track_id) = 0;

    /**
     * @brief Disconnect all output channels from a track
     *
     * @param track_id The id of the track to disconnect from
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_outputs_from_track(int track_id) = 0;

protected:
    AudioRoutingController() = default;
};

class CvGateController
{
public:
    virtual ~CvGateController() = default;

    /**
     * @brief Get number of cv input ports
     *
     * @return int
     */
    virtual std::pair<ControlStatus, int> get_cv_input_channel_count() const = 0;

    /**
     * @brief Get number of cv output ports
     *
     * @return int
     */
    virtual std::pair<ControlStatus, int> get_cv_output_channel_count() const = 0;

    /**
     * @brief Get a list of all cv input connections
     *
     * @return std::vector<CvConnection>
     */
    virtual std::pair<ControlStatus, std::vector<CvConnection>> get_all_cv_input_connections() const = 0;

    /**
     * @brief Get a list of all cv output connections
     *
     * @return std::vector<CvConnection>
     */
    virtual std::pair<ControlStatus, std::vector<CvConnection>> get_all_cv_output_connections() const = 0;

    /**
     * @brief Get a list of all gate input connections
     *
     * @return std::vector<GateConnection>
     */
    virtual std::pair<ControlStatus, std::vector<GateConnection>> get_all_gate_input_connections() const = 0;

    /**
     * @brief Get a list of all gate output connections
     *
     * @return std::vector<GateConnection>
     */
    virtual std::pair<ControlStatus, std::vector<GateConnection>> get_all_gate_output_connections() const = 0;

    /**
     * @brief Get the cv input connections for a processor
     *
     * @param processor_id Id of the processor to get connections for
     * @return std::pair<ControlStatus, std::vector<CvConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<CvConnection>> get_cv_input_connections_for_processor(int processor_id) const = 0;

    /**
     * @brief Get the cv output connections for a processor
     *
     * @param processor_id Id of the processor to get connections for
     * @return std::pair<ControlStatus, std::vector<CvConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<CvConnection>> get_cv_output_connections_for_processor(int processor_id) const = 0;

    /**
     * @brief Get the gate input connections for a processor
     *
     * @param processor_id Id of the processor to get connections for
     * @return std::pair<ControlStatus, std::vector<GateConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<GateConnection>> get_gate_input_connections_for_processor(int processor_id) const = 0;

    /**
     * @brief Get the gate output connections for a processor
     *
     * @param processor_id Id of the processor to get connections for
     * @return std::pair<ControlStatus, std::vector<GateConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<GateConnection>> get_gate_output_connections_for_processor(int processor_id) const = 0;

    /**
     * @brief Connect a cv input to a parameter
     *
     * @param processor_id Id of the processor that has the parameter
     * @param parameter_id Id of the parameter to connect the CV to
     * @param cv_input_id Id of the CV input to connect
     * @return ControlStatus
     */
    virtual ControlStatus connect_cv_input_to_parameter(int processor_id, int parameter_id, int cv_input_id) = 0;

    /**
     * @brief Connect a cv output from a parameter
     *
     * @param processor_id Id of the processor that has the parameter
     * @param parameter_id Id of the parameter to connect the CV to
     * @param cv_output_id Id of the CV output to connect
     * @return ControlStatus
     */
    virtual ControlStatus connect_cv_output_from_parameter(int processor_id, int parameter_id, int cv_output_id) = 0;

    /**
     * @brief Connect a gate input to a processor
     *
     * @param processor_id Id of the processor to connect to
     * @param gate_input_id Id of the gate input to connect
     * @param channel Midi channel to use for the gate trigger signal
     * @param note_no Note to play when the gate triggers
     * @return ControlStatus
     */
    virtual ControlStatus connect_gate_input_to_processor(int processor_id, int gate_input_id, int channel, int note_no) = 0;

    /**
     * @brief Connect a gate output to a processor
     *
     * @param processor_id Id of the processor to connect to
     * @param gate_output_id Id of the gate output to connect
     * @param channel Midi channel to use for the gate trigger signal
     * @param note_no Note to play when the gate triggers
     * @return ControlStatus
     */
    virtual ControlStatus connect_gate_output_from_processor(int processor_id, int gate_output_id, int channel, int note_no) = 0;

    /**
     * @brief Disconnect CV input
     *
     * @param processor_id Id of the processor the parameter belongs to
     * @param parameter_id Id of the parameter to disconnect from
     * @param cv_input_id Id of the CV input
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_cv_input(int processor_id, int parameter_id, int cv_input_id) = 0;

    /**
     * @brief Disconnect CV output
     *
     * @param processor_id Id of the processor the parameter belongs to
     * @param parameter_id Id of the parameter to disconnect from
     * @param cv_output_id Id of the CV output
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_cv_output(int processor_id, int parameter_id, int cv_output_id) = 0;

    /**
     * @brief Disconnect gate input
     *
     * @param processor_id Id of the processor to disconnect
     * @param gate_input_id Id of the gate input
     * @param channel Midi channel that is used for the gate trigger signal
     * @param note_no Note that is played when the gate triggers
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_gate_input(int processor_id, int gate_input_id, int channel, int note_no) = 0;

    /**
     * @brief Disconnect gate output
     *
     * @param processor_id Id of processor to disconnect
     * @param gate_output_id Id of the gate output
     * @param channel Midi channel that is used for the gate trigger signal
     * @param note_no Note that is played when the gate triggers
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_gate_output(int processor_id, int gate_output_id, int channel, int note_no) = 0;

    /**
     * @brief Disconnect all CV inputs from a processor
     *
     * @param processor_id Id of the processor to disconnect from
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_cv_inputs_from_processor(int processor_id) = 0;

    /**
     * @brief Disconnect all CV outputs from a processor
     *
     * @param processor_id Id of the processor to disconnect from
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_cv_outputs_from_processor(int processor_id) = 0;

    /**
     * @brief Disconnect all gate inputs from a processor
     *
     * @param processor_id Id of the processor to disconnect from
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_gate_inputs_from_processor(int processor_id) = 0;

    /**
     * @brief Disconnect all gate outputs from a processor
     *
     * @param processor_id Id of the processor to disconnect from
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_gate_outputs_from_processor(int processor_id) = 0;

protected:
    CvGateController() = default;
};

class OscController
{
public:
    virtual ~OscController() = default;

    /**
     * @brief Get the port osc is sent to
     *
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_send_port() const = 0;

    /**
     * @brief Get the port osc is received on
     *
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_receive_port() const = 0;

    /**
     * @brief Get the enabled parameter output osc addresses
     *
     * @return std::pair<ControlStatus, std::vector<std::string>>
     */
    virtual std::pair<ControlStatus, std::vector<std::string>> get_enabled_parameter_outputs() const = 0;

    /**
     * @brief Enable osc output for a parameter
     *
     * @param processor_id The id of the processor the parameter belongs to
     * @param parameter_id The id of the parameter to output as osc
     * @return ControlStatus
     */
    virtual ControlStatus enable_output_for_parameter(int processor_id, int parameter_id) = 0;

    /**
     * @brief Disable osc output for a parameter
     *
     * @param processor_id The id of the processor the parameter belongs to
     * @param parameter_id The id of the parameter to output as osc
     * @return ControlStatus
     */
    virtual ControlStatus disable_output_for_parameter(int processor_id, int parameter_id) = 0;

    /**
     * @brief Enable osc output for all parameters
     *
     * @return ControlStatus
     */
    virtual ControlStatus enable_all_output() = 0;

    /**
     * @brief Disable osc output for all parameters
     *
     * @return ControlStatus
     */
    virtual ControlStatus disable_all_output() = 0;

protected:
    OscController() = default;
};

class SessionController
{
public:
    virtual ~SessionController() = default;

    /**
     * @brief Save the entire sushi session.
     * @return An std::pair<ControlStatus, std::string> string containing the Sushi session
     *         in a serialized format if ControlStatus == OK, empty string otherwise.
     */
    virtual std::pair<ControlStatus, std::string> save_binary_session() const = 0;

    /**
     * @brief Restore the sushi session from a previously save session state.
     *        This will clear all track and loaded plugins
     * @param binary_session An std::string string containing the serialised Sushi session
     * @return ControlStatus::OK if operation was successful.
     */
    virtual ControlStatus restore_binary_session(const std::string& binary_session) = 0;


protected:
    SessionController() = default;
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
       * @brief Subscribe to parameter changes
       *
       * @param callback The callback to run when a parameter update is received
       * @param blocklist A vector of pairs of <parameter id, processor is> for which the
       *                  callback will not be called. If empty, the callback will be
       *                  called for all parameter changes.
       */
    virtual void subscribe_to_parameter_updates(std::function<void(int parameter_id, int processor_id, float normalized_value, float domain_value, const std::string& formatted_value)> callback,
                                                const std::vector<std::pair<int,int>>& blocklist) = 0;

    /**
     * @brief Subscribe to property changes
     *
     * @param callback The callback to run when a property update is received
     * @param blocklist A vector of pairs of <property id, processor is> for which the
     *                  callback will not be called. If empty, the callback will be
     *                  called for all property changes.
     */
    virtual void subscribe_to_property_updates(std::function<void(int property_id, int processor_id, const std::string& value)> callback,
                                               const std::vector<std::pair<int,int>>& blocklist) = 0;


protected:
    NotificationController() = default;
};

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunused-private-field"
#endif

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
                    SessionController* session_controller,
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
                        _session_controller(session_controller),
                        _notification_controller(notification_controller) {}

private:
    SystemController*       _system_controller;
    TransportController*    _transport_controller;
    TimingController*       _timing_controller;
    KeyboardController*     _keyboard_controller;
    AudioGraphController*   _audio_graph_controller;
    ProgramController*      _program_controller;
    ParameterController*    _parameter_controller;
    MidiController*         _midi_controller;
    AudioRoutingController* _audio_routing_controller;
    CvGateController*       _cv_gate_controller;
    OscController*          _osc_controller;
    SessionController*      _session_controller;
    NotificationController* _notification_controller;
};

} // sushi_controller

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif

#endif //SUSHI_CONTROL_INTERFACE_H
