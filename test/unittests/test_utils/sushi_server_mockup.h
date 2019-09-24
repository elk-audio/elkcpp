/**
 * @brief Mockup of the server running in sushi for testing purposes
 */

#ifndef SUSHI_SERVER_MOCKUP_H
#define SUSHI_SERVER_MOCKUP_H

#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <unistd.h>

#include <grpc++/grpc++.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "sushi_rpc.grpc.pb.h"
#pragma GCC diagnostic pop



namespace sushi_controller
{

namespace startup_values
{
    constexpr sushi_rpc::PlayingMode::Mode PLAYING_MODE = sushi_rpc::PlayingMode::STOPPED;
    constexpr sushi_rpc::SyncMode::Mode SYNC_MODE = sushi_rpc::SyncMode::INTERNAL;
}

namespace expected_results
{
    // Engine test values
    constexpr float SAMPLERATE = 48000.0f;
    constexpr PlayingMode PLAYING_MODE = PlayingMode::STOPPED;
    constexpr SyncMode SYNC_MODE = SyncMode::INTERNAL;
    constexpr float TEMPO = 120.0f;
    constexpr TimeSignature TIME_SIGNATURE{4,4};
    
    // MIDI test values
    constexpr int MIDI_TRACK_ID = 1;
    constexpr int MIDI_CHANNEL = 3;
    constexpr int MIDI_NOTE = 63;
    constexpr float MIDI_VELOCITY = 0.89f;
    constexpr float MIDI_AFTERTOUCH = 0.46f;
    constexpr float MIDI_MODULATION = 0.78f;
    constexpr float MIDI_PITCH_BEND = 0.5f;

    // Cpu Timings test values
    constexpr CpuTimings ENGINE_TIMINGS{0.02f, 0.15f, 0.04f};
    constexpr CpuTimings TRACK_TIMINGS{0.015f, 0.10f, 0.035f};
    constexpr CpuTimings PROCESSOR_TIMINGS{0.009f, 0.01f, 0.005f};

    // Track test values
    const TrackInfo TRACK_WITH_ID_1 = TrackInfo{ 1, "synth", "synth", 2, 2, 2, 2, 10};
    const TrackInfo TRACK_WITH_ID_2 = TrackInfo{ 2, "guitar", "guitar", 2, 2, 2, 2, 10};
    const std::vector<TrackInfo> TRACK_INFO_LIST = {TRACK_WITH_ID_1, TRACK_WITH_ID_2};

    // Processor test values
    const ProcessorInfo PROCESSOR_WITH_ID_1 = ProcessorInfo{1, "synth1", "synth1", 2, 2};
    const ProcessorInfo PROCESSOR_WITH_ID_2 = ProcessorInfo{2, "delay1", "delay1", 2, 2};
    const std::vector<ProcessorInfo> PROCESSOR_INFO_LIST = {PROCESSOR_WITH_ID_1, PROCESSOR_WITH_ID_2}; 
} //expected_results

std::thread server_thread;
std::unique_ptr<grpc::Server> server;

void RunServerMockup();
void KillServerMockup();

class SushiServiceMockup final : public sushi_rpc::SushiController::Service
{

    grpc::Status GetSamplerate(grpc::ServerContext* /* context */, 
                               const sushi_rpc::GenericVoidValue* /* request */,
                               sushi_rpc::GenericFloatValue* response) override
    {
        response->set_value(expected_results::SAMPLERATE);
        return grpc::Status::OK;
    }

    grpc::Status GetPlayingMode(grpc::ServerContext* /* context */, 
                               const sushi_rpc::GenericVoidValue* /* context */,
                               sushi_rpc::PlayingMode* response) override
    {
        response->set_mode(_playing_mode);
        return grpc::Status::OK;
    }

    grpc::Status SetPlayingMode(grpc::ServerContext* /* context */,
                                const sushi_rpc::PlayingMode* request,
                                sushi_rpc::GenericVoidValue* /* response */) override
    {
        _playing_mode = request->mode();
        return grpc::Status::OK;
    }

    grpc::Status GetSyncMode(grpc::ServerContext* /* context */,
                             const sushi_rpc::GenericVoidValue* /* request */,
                             sushi_rpc::SyncMode* response) override
    {
        response->set_mode(_sync_mode);
        return grpc::Status::OK;
    }

    grpc::Status SetSyncMode(grpc::ServerContext* /* context */,
                             const sushi_rpc::SyncMode* request,
                             sushi_rpc::GenericVoidValue* /* response */) override
    {
        _sync_mode = request->mode();
        return grpc::Status::OK;
    }

    grpc::Status GetTempo(grpc::ServerContext* /* context */,
                          const sushi_rpc::GenericVoidValue* /* request */,
                          sushi_rpc::GenericFloatValue* response) override
    {
        response->set_value(_tempo);
        return grpc::Status::OK;
    }

    grpc::Status SetTempo(grpc::ServerContext* /* context */,
                         const sushi_rpc::GenericFloatValue* request,
                         sushi_rpc::GenericVoidValue* /* response */) override
    {
        _tempo = request->value();
        return grpc::Status::OK;
    }

    grpc::Status GetTimeSignature(grpc::ServerContext* /* context */,
                                  const sushi_rpc::GenericVoidValue* /* request */,
                                  sushi_rpc::TimeSignature* response) override
    {
        response->set_numerator(_time_signature.numerator);
        response->set_denominator(_time_signature.denominator);
        return grpc::Status::OK;
    }

    grpc::Status SetTimeSignature(grpc::ServerContext* /* context */,
                                  const sushi_rpc::TimeSignature* request, 
                                  sushi_rpc::GenericVoidValue* /* response */) override
    {
        _time_signature.numerator = request->numerator();
        _time_signature.denominator = request->denominator();
        return grpc::Status::OK;
    }

    grpc::Status GetTracks(grpc::ServerContext* /* context */,
                           const sushi_rpc::GenericVoidValue* /* request */,
                           sushi_rpc::TrackInfoList* response) override
    {
        sushi_rpc::TrackInfo* track1 = response->add_tracks();
        track1->set_id(expected_results::TRACK_WITH_ID_1.id);
        track1->set_label(expected_results::TRACK_WITH_ID_1.label);
        track1->set_name(expected_results::TRACK_WITH_ID_1.name);
        track1->set_input_channels(expected_results::TRACK_WITH_ID_1.input_channels);
        track1->set_input_busses(expected_results::TRACK_WITH_ID_1.input_busses);
        track1->set_output_channels(expected_results::TRACK_WITH_ID_1.output_channels);
        track1->set_output_busses(expected_results::TRACK_WITH_ID_1.output_busses);
        track1->set_processor_count(expected_results::TRACK_WITH_ID_1.processor_count);

        sushi_rpc::TrackInfo* track2 = response->add_tracks();
        track2->set_id(expected_results::TRACK_WITH_ID_2.id);
        track2->set_label(expected_results::TRACK_WITH_ID_2.label);
        track2->set_name(expected_results::TRACK_WITH_ID_2.name);
        track2->set_input_channels(expected_results::TRACK_WITH_ID_2.input_channels);
        track2->set_input_busses(expected_results::TRACK_WITH_ID_2.input_busses);
        track2->set_output_channels(expected_results::TRACK_WITH_ID_2.output_channels);
        track2->set_output_busses(expected_results::TRACK_WITH_ID_2.output_busses);
        track2->set_processor_count(expected_results::TRACK_WITH_ID_2.processor_count);

        return grpc::Status::OK;
    }

    //====================//
    //  Keyboard Control  //
    //====================//

    grpc::Status SendNoteOn(grpc::ServerContext* /* context */,
                            const sushi_rpc::NoteOnRequest* request,
                            sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->note() == expected_results::MIDI_NOTE &&
            request->velocity() == expected_results::MIDI_VELOCITY)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    grpc::Status SendNoteOff(grpc::ServerContext* /* context */,
                            const sushi_rpc::NoteOffRequest* request,
                            sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->note() == expected_results::MIDI_NOTE &&
            request->velocity() == expected_results::MIDI_VELOCITY)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    grpc::Status SendNoteAftertouch(grpc::ServerContext* /* context */,
                                    const sushi_rpc::NoteAftertouchRequest* request,
                                    sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->note() == expected_results::MIDI_NOTE &&
            request->value() == expected_results::MIDI_AFTERTOUCH)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    grpc::Status SendAftertouch(grpc::ServerContext* /* context */,
                                const sushi_rpc::NoteModulationRequest* request,
                                sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->value() == expected_results::MIDI_AFTERTOUCH)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    grpc::Status SendPitchBend(grpc::ServerContext* /* context */,
                               const sushi_rpc::NoteModulationRequest* request,
                               sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->value() == expected_results::MIDI_PITCH_BEND)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    grpc::Status SendModulation(grpc::ServerContext* /* context */,
                                const sushi_rpc::NoteModulationRequest* request,
                                sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->value() == expected_results::MIDI_MODULATION)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    //==============//
    //  Cpu Timings //
    //==============//

    grpc::Status GetEngineTimings(grpc::ServerContext* /* context */,
                                  const sushi_rpc::GenericVoidValue* /* request */,
                                  sushi_rpc::CpuTimings* response)
    {
        response->set_min(expected_results::ENGINE_TIMINGS.min);
        response->set_max(expected_results::ENGINE_TIMINGS.max);
        response->set_average(expected_results::ENGINE_TIMINGS.avg);
        return grpc::Status::OK;
    }

    grpc::Status GetTrackTimings(grpc::ServerContext* /* context */,
                                 const sushi_rpc::TrackIdentifier* request,
                                 sushi_rpc::CpuTimings* response)
    {
        if (request->id() == expected_results::TRACK_WITH_ID_1.id)
        {
            response->set_min(expected_results::TRACK_TIMINGS.min);
            response->set_max(expected_results::TRACK_TIMINGS.max);
            response->set_average(expected_results::TRACK_TIMINGS.avg);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "Track id not found");
        }

    }

    grpc::Status GetProcessorTimings(grpc::ServerContext* /* context */,
                                     const sushi_rpc::ProcessorIdentifier* request,
                                     sushi_rpc::CpuTimings* response)
    {
        if (request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_min(expected_results::PROCESSOR_TIMINGS.min);
            response->set_max(expected_results::PROCESSOR_TIMINGS.max);
            response->set_average(expected_results::PROCESSOR_TIMINGS.avg);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "Processor id not found");
        }

    }

    grpc::Status ResetAllTimings(grpc::ServerContext* /* context */,
                                 const sushi_rpc::GenericVoidValue* /* request */,
                                 sushi_rpc::GenericVoidValue* /* response */)
    {
        return grpc::Status::OK;
    }

    grpc::Status ResetTrackTimings(grpc::ServerContext* /* context */,
                                   const sushi_rpc::TrackIdentifier* request,
                                   sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->id() == expected_results::TRACK_WITH_ID_1.id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "Track id not found");
        }
    }

     grpc::Status ResetProcessorTimings(grpc::ServerContext* /* context */,
                                        const sushi_rpc::ProcessorIdentifier* request,
                                        sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "Processor id not found");
        }
    }

    sushi_rpc::PlayingMode::Mode _playing_mode{startup_values::PLAYING_MODE};
    sushi_rpc::SyncMode::Mode _sync_mode{startup_values::SYNC_MODE};
    float _tempo{expected_results::TEMPO};
    sushi_controller::TimeSignature _time_signature{expected_results::TIME_SIGNATURE};

public:
    void setUp()
    {
        // Set up time signature
        // _time_signature.set_numerator(expeceted_results::TIME_SIGNATURE.numerator);
        // _time_signature.set_denominator(expected_results::TIME_SIGNATURE.denominator);
    }
};

class SushiServerMockup
{
public:
    SushiServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~SushiServerMockup()
    {
        KillServerMockup();
        server_thread.join();
    }

private:
    std::thread server_thread;
};

void RunServerMockup()
{
    std::string server_address("localhost:51051");
    SushiServiceMockup service;

    grpc::ServerBuilder builder;

    service.setUp();

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    server = builder.BuildAndStart();
    // std::cout << "Mockup server listening on " << server_address << std::endl;

    server->Wait();
}

void KillServerMockup()
{
    server->Shutdown();
}

}


#endif // SUSHI_SERVER_MOCKUP_H