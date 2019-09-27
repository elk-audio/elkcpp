/**
 * @brief gRPC client to control sushi
 * 
 * @copyright MIND Music Labs AB, Stockholm, Sweden
 */

#ifndef SUSHI_GRPC_CLIENT_H
#define SUSHI_GRPC_CLIENT_H

#include <grpc++/grpc++.h>
#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller
{

/**
 * @brief A class to control sushi via gRPC
 * 
 */

class SushiControllerClient : public SushiControl
{
public:
    /**
     * @brief Construct a new Sushi Controller Client object
     * 
     * @param address, "ip-address:port" The ip-address and port at which to connect to sushi. 
     */
    SushiControllerClient(std::string address = "localhost:51051");

    ~SushiControllerClient() = default;

    //========================//
    //  Main engine controls  //
    //========================//

    /**
     * @brief Get the current samplerate
     * 
     * @return float The current samplerate
     */
    float get_samplerate() const override;

    /**
     * @brief Get the current playing mode
     * 
     * @return PlayingMode The current playing mode
     */
    PlayingMode get_playing_mode() const override;

    /**
     * @brief Set the playing mode
     * 
     * @param playing_mode The playing mode to set
     */
    void set_playing_mode(PlayingMode playing_mode) override;

    /**
     * @brief Get the sync mode
     * 
     * @return SyncMode The current sync mode
     */
    SyncMode get_sync_mode() const override;

    /**
     * @brief Set the sync mode
     * 
     * @param sync_mode The sync mode to set
     */
    void set_sync_mode(SyncMode sync_mode) override;

    /**
     * @brief Get the tempo
     * 
     * @return float The current tempo
     */
    float get_tempo() const override;

    /**
     * @brief Set the tempo
     * 
     * @param tempo The tempo to set
     * @return ControlStatus 
     */
    ControlStatus set_tempo(float tempo) override;

    /**
     * @brief Get the time signature
     * 
     * @return TimeSignature The current time signature
     */
    TimeSignature get_time_signature() const override;

    /**
     * @brief Set the time signature
     * 
     * @param signature The time signature to set
     * @return ControlStatus 
     */
    ControlStatus set_time_signature(TimeSignature signature) override;
    // bool                                get_timing_statistics_enabled() override;
    // void                                set_timing_statistics_enabled(bool enabled) const override;

    /**
     * @brief Get the info of the avilable tracks
     * 
     * @return std::vector<TrackInfo> Vector containing the info of each track
     */
    std::vector<TrackInfo> get_tracks() const override;

    //====================//
    //  Keyboard control  //
    //====================//

    /**
     * @brief Send note on message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param channel The channel on which the message should be sent 
     * @param note The note to send. Follows the MIDI standard where middle c = 60 
     * @param velocity The velocity of the note. Should be in range (0.0-1.0) 
     * @return ControlStatus 
     */
    ControlStatus send_note_on(int track_id, int channel, int note, float velocity) override;

    /**
     * @brief Send note off message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param note The note to send. Follows the MIDI standard where middle c = 60 
     * @param channel The channel on which the message should be sent 
     * @param velocity The velocity of the note. Should be in range (0.0-1.0) 
     * @return ControlStatus 
     */
    ControlStatus send_note_off(int track_id, int note, int channel, float velocity) override;

    /**
     * @brief Send note aftertouch message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param channel The channel on which the message should be sent 
     * @param note The note to send. Follows the MIDI standard where middle c = 60 
     * @param value 
     * @return ControlStatus 
     */
    ControlStatus send_note_aftertouch(int track_id, int channel, int note, float value) override;

    /**
     * @brief Send aftertouch message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param channel The channel on which the message should be sent 
     * @param value 
     * @return ControlStatus 
     */
    ControlStatus send_aftertouch(int track_id, int channel, float value) override;

    /**
     * @brief Send pitch bend message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param channel The channel on which the message should be sent 
     * @param value 
     * @return ControlStatus 
     */
    ControlStatus send_pitch_bend(int track_id, int channel, float value) override;

    /**
     * @brief Send modulation message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param channel The channel on which the message should be sent 
     * @param value 
     * @return ControlStatus 
     */
    ControlStatus send_modulation(int track_id, int channel, float value) override;

    //===============//
    //  Cpu Timings  //
    //===============//

    /**
     * @brief Get the engine timings
     * 
     * @return std::pair<ControlStatus, CpuTimings> 
     */
    std::pair<ControlStatus, CpuTimings> get_engine_timings() const override;

    /**
     * @brief Get the track timings
     * 
     * @param track_id The id of the track to get the timings from
     * @return std::pair<ControlStatus, CpuTimings> 
     */
    std::pair<ControlStatus, CpuTimings> get_track_timings(int track_id) const override;

    /**
     * @brief Get the processor timings
     * 
     * @param processor_id The id of the processor to get the timings from 
     * @return std::pair<ControlStatus, CpuTimings> 
     */
    std::pair<ControlStatus, CpuTimings> get_processor_timings(int processor_id) const override;

    /**
     * @brief Reset all the timings measurements
     * 
     * @return ControlStatus 
     */
    ControlStatus reset_all_timings() override;

    /**
     * @brief Reset the timings measurements of a track
     * 
     * @param track_id The id of the track to reset the timings of
     * @return ControlStatus 
     */
    ControlStatus reset_track_timings(int track_id) override;

    /**
     * @brief Reset the timings measurements of a processor
     * 
     * @param processor_id The id of the processor to reset the timings of
     * @return ControlStatus 
     */
    ControlStatus reset_processor_timings(int processor_id) override;

    //=================//
    //  Track control  //
    //=================//

    /**
     * @brief Get the track id from a name
     * 
     * @param track_name The name of the track to get the id from
     * @return std::pair<ControlStatus, int> 
     */
    std::pair<ControlStatus, int> get_track_id(const std::string& track_name) const override;

    /**
     * @brief Get the info from a track
     * 
     * @param track_id The id of the track to get the info from
     * @return std::pair<ControlStatus, TrackInfo> 
     */
    std::pair<ControlStatus, TrackInfo> get_track_info(int track_id) const override;

    /**
     * @brief Get the info of avilable processors on a track
     * 
     * @param track_id The id of the track to get the available processors from
     * @return std::pair<ControlStatus, std::vector<ProcessorInfo>> 
     */
    std::pair<ControlStatus, std::vector<ProcessorInfo>> get_track_processors(int track_id) const override;

    /**
     * @brief Get the avilable parameters on a track
     * 
     * @param track_id The id of the track to get the parameter info from
     * @return std::pair<ControlStatus, std::vector<ParameterInfo>> 
     */
    std::pair<ControlStatus, std::vector<ParameterInfo>> get_track_parameters(int track_id) const override;

    //=====================//
    //  Processor control  //
    //=====================//

    /**
     * @brief Get the id of a processor from its name
     * 
     * @param processor_name The name of the processor to get the id from
     * @return std::pair<ControlStatus, int> 
     */
    std::pair<ControlStatus, int> get_processor_id(const std::string& processor_name) const override;

    /**
     * @brief Get the info about a processor
     * 
     * @param processor_id The id of the processor to get the info from
     * @return std::pair<ControlStatus, ProcessorInfo> 
     */
    std::pair<ControlStatus, ProcessorInfo> get_processor_info(int processor_id) const override;

    /**
     * @brief Get the bypass state of a processor
     * 
     * @param processor_id The id of the processor to get the bypass state from 
     * @return std::pair<ControlStatus, bool> 
     */
    std::pair<ControlStatus, bool> get_processor_bypass_state(int processor_id) const override;

    /**
     * @brief Set the bypass state of a processor
     * 
     * @param processor_id The id of the processor to set the bypass state of
     * @param bypass_enabled True to bypass processor, False to enable processor
     * @return ControlStatus 
     */
    ControlStatus set_processor_bypass_state(int processor_id, bool bypass_enabled) override;

    /**
     * @brief Get the id of the current program of a processor
     * 
     * @param processor_id The id of the processor to get the current program id from
     * @return std::pair<ControlStatus, int> 
     */
    std::pair<ControlStatus, int> get_processor_current_program(int processor_id) const override;

    /**
     * @brief Get the name of the current program of a processor
     * 
     * @param processor_id The id of the processor to get the current program name from
     * @return std::pair<ControlStatus, std::string> 
     */
    std::pair<ControlStatus, std::string> get_processor_current_program_name(int processor_id) const override;

    /**
     * @brief Get the name of a program from a processor
     * 
     * @param processor_id The id of the processor containing the program
     * @param program_id The id of program to get the name from
     * @return std::pair<ControlStatus, std::string> 
     */
    std::pair<ControlStatus, std::string> get_processor_program_name(int processor_id, int program_id) const override;

    /**
     * @brief Get the names of the programs available to a processor
     * 
     * @param processor_id The id of the processor to get the program names from
     * @return std::pair<ControlStatus, std::vector<std::string>> 
     */
    std::pair<ControlStatus, std::vector<std::string>> get_processor_programs(int processor_id) const override;

    /**
     * @brief Set the current program of a processor
     * 
     * @param processor_id The id of the processor to set the program on
     * @param program_id The id of the program to set on the processor
     * @return ControlStatus 
     */
    ControlStatus set_processor_program(int processor_id, int program_id) override;

    /**
     * @brief Get the parameters available to a processor
     * 
     * @param processor_id The id of the processor to get the parameters from
     * @return std::pair<ControlStatus, std::vector<ParameterInfo>> 
     */
    std::pair<ControlStatus, std::vector<ParameterInfo>> get_processor_parameters(int processor_id) const override;

    //=====================//
    //  Parameter control  //
    //=====================//

    /**
     * @brief Get the id of a parameter from its name
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter The name of the parameter to get the id from
     * @return std::pair<ControlStatus, int> 
     */
    std::pair<ControlStatus, int> get_parameter_id(int processor_id, const std::string& parameter) const override;

    /**
     * @brief Get the info of a parameter
     * 
     * @param processor_id The id of the processors containing the parameter
     * @param parameter_id The id of the parameter to get the info from
     * @return std::pair<ControlStatus, ParameterInfo> 
     */
    std::pair<ControlStatus, ParameterInfo> get_parameter_info(int processor_id, int parameter_id) const override;

    /**
     * @brief Get the current value of a parameter
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of parameter to get the value from
     * @return std::pair<ControlStatus, float> 
     */
    std::pair<ControlStatus, float> get_parameter_value(int processor_id, int parameter_id) const override;

    /**
     * @brief Get the normalised current value of a parameter
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to get the normalised value from
     * @return std::pair<ControlStatus, float> 
     */
    std::pair<ControlStatus, float> get_parameter_value_normalised(int processor_id, int parameter_id) const override;

    /**
     * @brief Get the current value of a parameter as a string
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to get value as a string from
     * @return std::pair<ControlStatus, std::string> 
     */
    std::pair<ControlStatus, std::string> get_parameter_value_as_string(int processor_id, int parameter_id) const override;
    // std::pair<ControlStatus, std::string>      get_string_property_value(int processor_id, int parameter_id) const override;

    /**
     * @brief Set the value of a parameter
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to set the value of
     * @param value The value to set the parameter to
     * @return ControlStatus 
     */
    ControlStatus set_parameter_value(int processor_id, int parameter_id, float value) override;

    /**
     * @brief Set the normalised value of a parameter
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to set the normalised value of
     * @param value The normalised value to set the parameter to
     * @return ControlStatus 
     */
    ControlStatus set_parameter_value_normalised(int processor_id, int parameter_id, float value) override;
    // ControlStatus                              set_string_property_value(int processor_id, int parameter_id, const std::string& value) override;

private:
    std::unique_ptr<sushi_rpc::SushiController::Stub> _stub;
};

}

#endif // SUSHI_GRPC_CLIENT_H