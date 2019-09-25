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
    constexpr bool PROCESSOR_BYPASS_STATE = true;

    // Program test values
    constexpr int PROGRAM_ID{1};
    const std::string PROGRAM_NAME{"Program1"};

    // Parameter test values
    constexpr ParameterType PARAMETER_TYPE{ParameterType::FLOAT};
    const ParameterInfo PARAMETER_WITH_ID_1 = ParameterInfo{1, PARAMETER_TYPE, "param1", "param1", "Hz", true, 0.0f, 1.0f};
    const ParameterInfo PARAMETER_WITH_ID_2 = ParameterInfo{2, PARAMETER_TYPE, "param2", "param2", "Hz", true, 0.0f, 1.0f};
    const std::vector<ParameterInfo> PARAMETER_INFO_LIST = {PARAMETER_WITH_ID_1, PARAMETER_WITH_ID_2}; 
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

    //=================//
    //  Track control  //
    //=================//

    grpc::Status GetTrackId(grpc::ServerContext* /* context */,
                            const sushi_rpc::GenericStringValue* request,
                            sushi_rpc::TrackIdentifier* response)
    {
        if (request->value() == expected_results::TRACK_WITH_ID_1.name)
        {
            response->set_id(expected_results::TRACK_WITH_ID_1.id);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No track with that name");
        }
        
    }

    grpc::Status GetTrackInfo(grpc::ServerContext* /* context */,
                              const sushi_rpc::TrackIdentifier* request,
                              sushi_rpc::TrackInfo* response)
    {
        if (request->id() == expected_results::TRACK_WITH_ID_1.id)
        {
            response->set_id(expected_results::TRACK_WITH_ID_1.id);
            response->set_label(expected_results::TRACK_WITH_ID_1.label);
            response->set_name(expected_results::TRACK_WITH_ID_1.name);
            response->set_input_channels(expected_results::TRACK_WITH_ID_1.input_channels);
            response->set_input_busses(expected_results::TRACK_WITH_ID_1.input_busses);
            response->set_output_channels(expected_results::TRACK_WITH_ID_1.output_channels);
            response->set_output_busses(expected_results::TRACK_WITH_ID_1.output_busses);
            response->set_processor_count(expected_results::TRACK_WITH_ID_1.processor_count);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No track with that id");
        }
    }

    grpc::Status GetTrackProcessors(grpc::ServerContext* /* context */,
                                    const sushi_rpc::TrackIdentifier* request,
                                    sushi_rpc::ProcessorInfoList* response)
    {
        if (request->id() == expected_results::TRACK_WITH_ID_1.id)
        {
            for(uint i = 0; i < expected_results::PROCESSOR_INFO_LIST.size(); ++i)
            {
                sushi_rpc::ProcessorInfo* processor = response->add_processors();
                processor->set_id(expected_results::PROCESSOR_INFO_LIST.at(i).id);
                processor->set_label(expected_results::PROCESSOR_INFO_LIST.at(i).label);
                processor->set_name(expected_results::PROCESSOR_INFO_LIST.at(i).name);
                processor->set_parameter_count(expected_results::PROCESSOR_INFO_LIST.at(i).parameter_count);
                processor->set_program_count(expected_results::PROCESSOR_INFO_LIST.at(i).program_count);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No track with that id");
        }
    }

    grpc::Status GetTrackParameters(grpc::ServerContext* /* context */,
                                    const sushi_rpc::TrackIdentifier* request,
                                    sushi_rpc::ParameterInfoList* response)
    {
        if (request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            for(uint i = 0; i < expected_results::PARAMETER_INFO_LIST.size(); ++i)
            {
                sushi_rpc::ParameterInfo* parameter = response->add_parameters();
                parameter->set_id(expected_results::PARAMETER_INFO_LIST.at(i).id);
                parameter->mutable_type()->set_type(sushi_rpc::ParameterType::FLOAT);
                parameter->set_label(expected_results::PARAMETER_INFO_LIST.at(i).label);
                parameter->set_name(expected_results::PARAMETER_INFO_LIST.at(i).name);
                parameter->set_unit(expected_results::PARAMETER_INFO_LIST.at(i).unit);
                parameter->set_automatable(expected_results::PARAMETER_INFO_LIST.at(i).automatable);
                parameter->set_min_range(expected_results::PARAMETER_INFO_LIST.at(i).min_range);
                parameter->set_max_range(expected_results::PARAMETER_INFO_LIST.at(i).max_range);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    //=====================//
    //  Processor control  //
    //=====================//

    grpc::Status GetProcessorId(grpc::ServerContext* /* context */,
                                const sushi_rpc::GenericStringValue* request,
                                sushi_rpc::ProcessorIdentifier* response)
    {
        if(request->value() == expected_results::PROCESSOR_WITH_ID_1.name)
        {
            response->set_id(expected_results::PROCESSOR_WITH_ID_1.id);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that name");
        }
    }

    grpc::Status GetProcessorInfo(grpc::ServerContext* /* context */,
                                  const sushi_rpc::ProcessorIdentifier* request,
                                  sushi_rpc::ProcessorInfo* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_id(expected_results::PROCESSOR_WITH_ID_1.id);
            response->set_label(expected_results::PROCESSOR_WITH_ID_1.label);
            response->set_name(expected_results::PROCESSOR_WITH_ID_1.name);
            response->set_parameter_count(expected_results::PROCESSOR_WITH_ID_1.parameter_count);
            response->set_program_count(expected_results::PROCESSOR_WITH_ID_1.program_count);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status GetProcessorBypassState(grpc::ServerContext* /* context */,
                                         const sushi_rpc::ProcessorIdentifier* request,
                                         sushi_rpc::GenericBoolValue* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_value(_processor_bypass_state);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status SetProcessorBypassState(grpc::ServerContext* /* context */,
                                         const sushi_rpc::ProcessorBypassStateSetRequest* request,
                                         sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            _processor_bypass_state = request->value();
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
        
    }

    grpc::Status GetProcessorCurrentProgram(grpc::ServerContext* /* context */,
                                            const sushi_rpc::ProcessorIdentifier* request,
                                            sushi_rpc::ProgramIdentifier* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_program(expected_results::PROGRAM_ID);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
        
    }

    grpc::Status GetProcessorCurrentProgramName(grpc::ServerContext* /* context */,
                                                const sushi_rpc::ProcessorIdentifier* request,
                                                sushi_rpc::GenericStringValue* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_value(expected_results::PROGRAM_NAME);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
        
    }

    grpc::Status GetProcessorProgramName(grpc::ServerContext* /* context */,
                                         const sushi_rpc::ProcessorProgramIdentifier* request,
                                         sushi_rpc::GenericStringValue* response)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id && request->program() == expected_results::PROGRAM_ID)
        {
            response->set_value(expected_results::PROGRAM_NAME);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor and/or program with that id");
        }
        
    }

    grpc::Status GetProcessorPrograms(grpc::ServerContext* /* context */,
                                      const sushi_rpc::ProcessorIdentifier* request,
                                      sushi_rpc::ProgramInfoList* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            sushi_rpc::ProgramInfo* program = response->add_programs();
            program->mutable_id()->set_program(expected_results::PROGRAM_ID);
            program->set_name(expected_results::PROGRAM_NAME);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
        
    }

    grpc::Status SetProcessorProgram(grpc::ServerContext* /* context */,
                                     const sushi_rpc::ProcessorProgramSetRequest* request,
                                     sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id && request->program().program() == expected_results::PROGRAM_ID)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor and/or program with that id");
        }
    }

    grpc::Status GetProcessorParameters(grpc::ServerContext* /* context */,
                                        const sushi_rpc::ProcessorIdentifier* request,
                                        sushi_rpc::ParameterInfoList* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            for(uint i = 0; i < expected_results::PARAMETER_INFO_LIST.size(); ++i)
            {
                sushi_rpc::ParameterInfo* parameter = response->add_parameters();
                parameter->set_id(expected_results::PARAMETER_INFO_LIST.at(i).id);
                parameter->mutable_type()->set_type(sushi_rpc::ParameterType::FLOAT);
                parameter->set_label(expected_results::PARAMETER_INFO_LIST.at(i).label);
                parameter->set_name(expected_results::PARAMETER_INFO_LIST.at(i).name);
                parameter->set_unit(expected_results::PARAMETER_INFO_LIST.at(i).unit);
                parameter->set_automatable(expected_results::PARAMETER_INFO_LIST.at(i).automatable);
                parameter->set_min_range(expected_results::PARAMETER_INFO_LIST.at(i).min_range);
                parameter->set_max_range(expected_results::PARAMETER_INFO_LIST.at(i).max_range);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
        
    }

    sushi_rpc::PlayingMode::Mode _playing_mode{startup_values::PLAYING_MODE};
    sushi_rpc::SyncMode::Mode _sync_mode{startup_values::SYNC_MODE};
    float _tempo{expected_results::TEMPO};
    sushi_controller::TimeSignature _time_signature{expected_results::TIME_SIGNATURE};
    bool _processor_bypass_state{expected_results::PROCESSOR_BYPASS_STATE};

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