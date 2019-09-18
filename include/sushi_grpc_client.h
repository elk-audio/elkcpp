/**
 * @brief gRPC client to control sushi
 * 
 * @copyright MIND Music Labs AB, Stockholm, Sweden
 */

#ifndef SUSHI_GRPC_CLIENT_H
#define SUSHI_GRPC_CLIENT_H

#include "sushi_info_types.h"
#include "sushi_rpc.grpc.pb.h"

namespace sushi_controller
{

/**
 * @class A class to control sushi via gRPC
 */

class SushiControllerClient
{
public:
    /** The constructor for the SushiControllerClient class.
     * 
     * @param address: "ip-addres:port" The ip-addres and port at which to connect to sushi.
     * 
     */
    SushiControllerClient(std::string address = "localhost:51051");

    ~SushiControllerClient() = default;

    /**
     * @brief Get the current samplerate.
     * 
     * @param[out] 
     */
    float GetSampleRate();
    sushi_controller::PLAYING_MODE GetPlayingMode();
    void SetPlayingMode(sushi_controller::PLAYING_MODE playing_mode);
    sushi_controller::SYNC_MODE GetSyncMode();
    void SetSyncMode(sushi_controller::SYNC_MODE sync_mode);
    float GetTempo();
    void SetTempo(float tempo);
    sushi_controller::TimeSignature GetTimeSignature();
    void SetTimeSignature(sushi_controller::TimeSignature time_signature);
    std::vector<sushi_controller::TrackInfo> GetTracks();

    // Keyboard control
    void SendNoteOn(int track_id, int channel, int note, float velocity);
    void SendNoteOff(int track_id, int channel, int note, float velocity);
    void SendNoteAftertouch(int track_id, int channel, int note, float value);
    void SendAftertouch(int track_id, int channel, float value);
    void SendPitchBend(int track_id, int channel, float value);
    void SendModulation(int track_id, int channel, float value);

    // Cpu timings
    sushi_controller::CpuTimings GetEngineTimings();
    sushi_controller::CpuTimings GetTrackTimings(int track_id);
    sushi_controller::CpuTimings GetProcessorTimings(int processor_id);
    void ResetAllTimings();
    void ResetTrackTimings(int track_id);
    void ResetProcessorTimings(int processor_id);

    // Track control
    int GetTrackId(std::string track_name);
    sushi_controller::TrackInfo GetTrackInfo(int track_id);
    std::vector<sushi_controller::ProcessorInfo> GetTrackProcessors(int track_id);
    std::vector<sushi_controller::ParameterInfo> GetTrackParameters(int track_id);

    // Processor control
    int GetProcessorId(std::string processor_name);
    sushi_controller::ProcessorInfo GetProcessorInfo(int processor_id);
    bool GetProcessorBypassState(int processor_id);
    void SetProcessorBypassState(bool bypass_state);
    int GetProcessorCurrentProgram(int processor_id);
    std::string GetProcessorCurrentProgramName(int processor_id);
    std::string GetProcessorProgramName(int processor_id, int program_id);
    std::vector<sushi_controller::ProcessorInfo> GetProcessorPrograms(int processor_id);
    void SetProcessorProgram(int processor_id, int program_id);
    std::vector<sushi_controller::ParameterInfo> GetProcessorParameters(int processor_id);

    // Parameter control
    int GetParameterId(int processor_id, std::string parameter_name);
    sushi_controller::ParameterInfo GetParameterInfo(int processor_id, int parameter_id);
    float GetParameterValue(int processor_id, int parameter_id);
    float GetParameterValueNormalised(int processor_id, int parameter_id);
    std::string GetParameterValueAsString(int processor_id, int parameter_id);
    std::string GetStringPropertyValue(int processor_id, int parameter_id);
    void SetParameterValue(int processor_id, int parameter_id, float value);
    void SetParameterValueNormalised(int processor_id, int parameter_id, float value);
    void SetStringPropertyValue(int processor_id, int parameter_id, std::string value);

private:
    std::unique_ptr<sushi_rpc::SushiController::Stub> _stub;
};

}

#endif // SUSHI_GRPC_CLIENT_H