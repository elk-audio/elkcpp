#ifndef ELKCPP_AUDIO_GRAPH_SERVER_MOCKUP_H
#define ELKCPP_AUDIO_GRAPH_SERVER_MOCKUP_H

#include <thread>

#include <grpcpp/grpcpp.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "sushi_rpc.grpc.pb.h"
#pragma GCC diagnostic pop

namespace sushi_controller
{

namespace expected_results
{
    // Track test values
    const TrackInfo TRACK_WITH_ID_1 = TrackInfo{ 1, "synth", "synth", 2, 2, 2, 2, {10, 11}};
    const TrackInfo TRACK_WITH_ID_2 = TrackInfo{ 2, "guitar", "guitar", 2, 2, 2, 2, {10, 11}};
    const std::vector<TrackInfo> TRACK_INFO_LIST = {TRACK_WITH_ID_1, TRACK_WITH_ID_2};

    // Processor test values
    const ProcessorInfo PROCESSOR_WITH_ID_1 = ProcessorInfo{1, "synth1", "synth1", 2, 2};
    const ProcessorInfo PROCESSOR_WITH_ID_2 = ProcessorInfo{2, "delay1", "delay1", 2, 2};
    const std::vector<ProcessorInfo> PROCESSOR_INFO_LIST = {PROCESSOR_WITH_ID_1, PROCESSOR_WITH_ID_2};
    constexpr bool PROCESSOR_BYPASS_STATE = true;
    const int PROCESSOR_PROGRAM_ID = 3;
    const float PROCESSOR_PARAMETER_VALUE = 0.5f;

    // Dynamic track values
    constexpr char DYN_TRACK_NAME[] = "New track";
    constexpr int DYN_TRACK_CHANNELS = 2;
    constexpr int DYN_TRACK_OUTPUT_BUSSES = 10;
    constexpr int DYN_TRACK_INPUT_BUSSES = 4;

    // Dynamic processor values
    constexpr char DYN_PROC_NAME[] = "New processor";
    constexpr char DYN_PROC_UID[] = "test.dyn.processor";
    constexpr char DYN_PROC_PATH[] = "/path/to/proc";
    constexpr PluginType DYN_PROC_TYPE = PluginType::INTERNAL;
    constexpr int DYN_PROC_DST_TRACK = 1;
    constexpr int DYN_PROC_SRC_TRACK = 2;
    constexpr int DYN_PROC_BEFORE_PROC = 7;
    constexpr bool DYN_PROC_ADD_TO_BACK = true;

} // namespace expected_results


class AudioGraphServiceMockup : public sushi_rpc::AudioGraphController::Service
{

    grpc::Status GetAllTracks(grpc::ServerContext* /* context */,
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
        for (auto& processor_id : expected_results::TRACK_WITH_ID_1.processors)
        {
            auto grpc_processor = track1->add_processors();
            grpc_processor->set_id(processor_id);
        }

        sushi_rpc::TrackInfo* track2 = response->add_tracks();
        track2->set_id(expected_results::TRACK_WITH_ID_2.id);
        track2->set_label(expected_results::TRACK_WITH_ID_2.label);
        track2->set_name(expected_results::TRACK_WITH_ID_2.name);
        track2->set_input_channels(expected_results::TRACK_WITH_ID_2.input_channels);
        track2->set_input_busses(expected_results::TRACK_WITH_ID_2.input_busses);
        track2->set_output_channels(expected_results::TRACK_WITH_ID_2.output_channels);
        track2->set_output_busses(expected_results::TRACK_WITH_ID_2.output_busses);
        for (auto& processor_id : expected_results::TRACK_WITH_ID_2.processors)
        {
            auto grpc_processor = track2->add_processors();
            grpc_processor->set_id(processor_id);
        }

        return grpc::Status::OK;
    }

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
            for (auto& processor_id : expected_results::TRACK_WITH_ID_1.processors)
            {
                auto grpc_processor = response->add_processors();
                grpc_processor->set_id(processor_id);
            }
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

    grpc::Status GetProcessorState(grpc::ServerContext* /* context */,
                                   const sushi_rpc::ProcessorIdentifier* request,
                                   sushi_rpc::ProcessorState* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id ||
           request->id() == expected_results::PROCESSOR_WITH_ID_2.id)
        {
            response->mutable_program_id()->set_value(expected_results::PROCESSOR_PROGRAM_ID);
            response->mutable_program_id()->set_has_value(true);
            response->mutable_bypassed()->set_value(_processor_bypass_state);
            response->mutable_bypassed()->set_has_value(true);
            auto parameter = response->mutable_parameters()->Add();
            parameter->mutable_parameter()->set_parameter_id(0);
            parameter->set_value(expected_results::PROCESSOR_PARAMETER_VALUE);
            parameter = response->mutable_parameters()->Add();
            parameter->mutable_parameter()->set_parameter_id(1);
            parameter->set_value(expected_results::PROCESSOR_PARAMETER_VALUE);
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

    grpc::Status SetProcessorState(grpc::ServerContext* /* context */,
                                   const sushi_rpc::ProcessorStateSetRequest* request,
                                   sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id ||
           request->processor().id() == expected_results::PROCESSOR_WITH_ID_2.id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status CreateTrack(grpc::ServerContext* /* context */,
                             const sushi_rpc::CreateTrackRequest* request,
                             sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->name() == expected_results::DYN_TRACK_NAME &&
           request->channels() == expected_results::DYN_TRACK_CHANNELS)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arguments don't match expected test values");
        }
    }

    grpc::Status CreateMultibusTrack(grpc::ServerContext* /* context */,
                                     const sushi_rpc::CreateMultibusTrackRequest* request,
                                     sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->name() == expected_results::DYN_TRACK_NAME &&
           request->output_busses() == expected_results::DYN_TRACK_OUTPUT_BUSSES &&
           request->input_busses() == expected_results::DYN_TRACK_INPUT_BUSSES)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arguments don't match expected test values");
        }
    }

    grpc::Status CreateProcessorOnTrack(grpc::ServerContext* /* context */,
                                        const sushi_rpc::CreateProcessorRequest* request,
                                        sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->name() == expected_results::DYN_PROC_NAME &&
           request->uid() == expected_results::DYN_PROC_UID &&
           request->path() == expected_results::DYN_PROC_PATH &&
           request->type().type() == to_grpc(expected_results::DYN_PROC_TYPE) &&
           request->position().before_processor().id() == expected_results::DYN_PROC_BEFORE_PROC &&
           request->position().add_to_back() == expected_results::DYN_PROC_ADD_TO_BACK)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arguments don't match expected test values");
        }
    }

    grpc::Status MoveProcessorOnTrack(grpc::ServerContext* /* context */,
                                      const sushi_rpc::MoveProcessorRequest* request,
                                      sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id &&
           request->dest_track().id() == expected_results::DYN_PROC_DST_TRACK &&
           request->source_track().id() == expected_results::DYN_PROC_SRC_TRACK)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arguments don't match expected test values");
        }
    }

    grpc::Status DeleteProcessorFromTrack(grpc::ServerContext* /* context */,
                                         const sushi_rpc::DeleteProcessorRequest* request,
                                         sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id &&
           request->track().id() == expected_results::TRACK_WITH_ID_1.id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arguments don't match expected test values");
        }
    }

    grpc::Status DeleteTrack(grpc::ServerContext* /* context */,
                             const sushi_rpc::TrackIdentifier* request,
                             sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->id() == expected_results::TRACK_WITH_ID_1.id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arguments don't match expected test values");
        }
    }



    bool _processor_bypass_state{expected_results::PROCESSOR_BYPASS_STATE};
};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class AudioGraphServerMockup
{
public:
    AudioGraphServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~AudioGraphServerMockup()
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
    AudioGraphServiceMockup service;

    grpc::ServerBuilder builder;

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

} // namespace sushi_controller


#endif // ELKCPP_AUDIO_GRAPH_SERVER_MOCKUP_H
