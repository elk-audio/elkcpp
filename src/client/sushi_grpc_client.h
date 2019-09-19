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
 * @class A class to control sushi via gRPC
 */


class SushiControllerClient : public SushiControl
{
public:
    /** The constructor for the SushiControllerClient class.
     * 
     * @param address: "ip-addres:port" The ip-addres and port at which to connect to sushi.
     * 
     */
    SushiControllerClient(std::string address = "localhost:51051");

    ~SushiControllerClient() = default;

    // Main engine controls
    float                               get_samplerate() const override;
    PlayingMode                         get_playing_mode() const override;
    // void                                set_playing_mode(PlayingMode playing_mode) override;
    // SyncMode                            get_sync_mode() const override;
    // void                                set_sync_mode(SyncMode sync_mode) override;
    // float                               get_tempo() const override;
    // ControlStatus                       set_tempo(float tempo) override;
    // TimeSignature                       get_time_signature() const override;
    // ControlStatus                       set_time_signature(TimeSignature signature) override;
    // bool                                get_timing_statistics_enabled() override;
    // void                                set_timing_statistics_enabled(bool enabled) const override;
    // std::vector<TrackInfo>              get_tracks() const override;

    // // Keyboard control
    // ControlStatus                       send_note_on(int track_id, int note, int channel, float velocity) override;
    // ControlStatus                       send_note_off(int track_id, int note, int channel, float velocity) override;
    // ControlStatus                       send_note_aftertouch(int track_id, int channel, int note, float value) override;
    // ControlStatus                       send_aftertouch(int track_id, int channel, float value) override;
    // ControlStatus                       send_pitch_bend(int track_id, int channel, float value) override;
    // ControlStatus                       send_modulation(int track_id, int channel, float value) override;

    // // Cpu Timings
    // std::pair<ControlStatus, CpuTimings>    get_engine_timings() const override;
    // std::pair<ControlStatus, CpuTimings>    get_track_timings(int track_id) const override;
    // std::pair<ControlStatus, CpuTimings>    get_processor_timings(int processor_id) const override;
    // ControlStatus                           reset_all_timings() override;
    // ControlStatus                           reset_track_timings(int track_id) override;
    // ControlStatus                           reset_processor_timings(int processor_id) override;

    // // Track control
    // std::pair<ControlStatus, int>           get_track_id(const std::string& track_name) const override;
    // std::pair<ControlStatus, TrackInfo>     get_track_info(int track_id) const override;
    // std::pair<ControlStatus, std::vector<ProcessorInfo>> get_track_processors(int track_id) const override;
    // std::pair<ControlStatus, std::vector<ParameterInfo>> get_track_parameters(int processor_id) const override;

    // // Processor control
    // std::pair<ControlStatus, int>              get_processor_id(const std::string& processor_name) const override;
    // std::pair<ControlStatus, ProcessorInfo>    get_processor_info(int processor_id) const override;
    // std::pair<ControlStatus, bool>             get_processor_bypass_state(int processor_id) const override;
    // ControlStatus                              set_processor_bypass_state(int processor_id, bool bypass_enabled) override;
    // std::pair<ControlStatus, int>              get_processor_current_program(int processor_id) const override;
    // std::pair<ControlStatus, std::string>      get_processor_current_program_name(int processor_id) const override;
    // std::pair<ControlStatus, std::string>      get_processor_program_name(int processor_id, int program_id) const override;
    // std::pair<ControlStatus, std::vector<std::string>>   get_processor_programs(int processor_id) const override;
    // ControlStatus                              set_processor_program(int processor_id, int program_id) override;
    // std::pair<ControlStatus, std::vector<ParameterInfo>> get_processor_parameters(int processor_id) const override;

    // // Parameter control
    // std::pair<ControlStatus, int>              get_parameter_id(int processor_id, const std::string& parameter) const override;
    // std::pair<ControlStatus, ParameterInfo>    get_parameter_info(int processor_id, int parameter_id) const override;
    // std::pair<ControlStatus, float>            get_parameter_value(int processor_id, int parameter_id) const override;
    // std::pair<ControlStatus, float>            get_parameter_value_normalised(int processor_id, int parameter_id) const override;
    // std::pair<ControlStatus, std::string>      get_parameter_value_as_string(int processor_id, int parameter_id) const override;
    // std::pair<ControlStatus, std::string>      get_string_property_value(int processor_id, int parameter_id) const override;
    // ControlStatus                              set_parameter_value(int processor_id, int parameter_id, float value) override;
    // ControlStatus                              set_parameter_value_normalised(int processor_id, int parameter_id, float value) override;
    // ControlStatus                              set_string_property_value(int processor_id, int parameter_id, const std::string& value) override;

private:
    std::unique_ptr<sushi_rpc::SushiController::Stub> _stub;
};

}

#endif // SUSHI_GRPC_CLIENT_H