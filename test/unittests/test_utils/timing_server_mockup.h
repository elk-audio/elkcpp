#ifndef ELKCPP_TIMING_SERVER_MOCKUP
#define ELKCPP_TIMING_SERVER_MOCKUP

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
    // Cpu Timings test values
    constexpr bool TIMINGS_ENABLED = true;
    constexpr CpuTimings ENGINE_TIMINGS{0.02f, 0.15f, 0.04f};
    constexpr CpuTimings TRACK_TIMINGS{0.015f, 0.10f, 0.035f};
    constexpr CpuTimings PROCESSOR_TIMINGS{0.009f, 0.01f, 0.005f};

    // Track test values
    const TrackInfo TRACK_WITH_ID_1 = TrackInfo{ 1, "synth", "synth", 2, 2, 2, 2, {10, 11}};
    const TrackInfo TRACK_WITH_ID_2 = TrackInfo{ 2, "guitar", "guitar", 2, 2, 2, 2, {10, 11}};
    const std::vector<TrackInfo> TRACK_INFO_LIST = {TRACK_WITH_ID_1, TRACK_WITH_ID_2};

    // Processor test values
    const ProcessorInfo PROCESSOR_WITH_ID_1 = ProcessorInfo{1, "synth1", "synth1", 2, 2};
    const ProcessorInfo PROCESSOR_WITH_ID_2 = ProcessorInfo{2, "delay1", "delay1", 2, 2};
    const std::vector<ProcessorInfo> PROCESSOR_INFO_LIST = {PROCESSOR_WITH_ID_1, PROCESSOR_WITH_ID_2};
    constexpr bool PROCESSOR_BYPASS_STATE = true;
} // namespace expected_results


class TimingServiceMockup : public sushi_rpc::TimingController::Service
{

    grpc::Status GetTimingsEnabled(grpc::ServerContext* /* context */,
                                   const sushi_rpc::GenericVoidValue* /* request */,
                                   sushi_rpc::GenericBoolValue* response)
    {
        response->set_value(_timings_enabled);
        return grpc::Status::OK;
    }

    grpc::Status SetTimingsEnabled(grpc::ServerContext* /* context */,
                                   const sushi_rpc::GenericBoolValue* request,
                                   sushi_rpc::GenericVoidValue* /* response */)
    {
        _timings_enabled = request->value();
        return grpc::Status::OK;
    }

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

    bool _timings_enabled{expected_results::TIMINGS_ENABLED};
};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class TimingServerMockup
{
public:
    TimingServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~TimingServerMockup()
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
    TimingServiceMockup service;

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


#endif // ELKCPP_TIMING_SERVER_MOCKUP
