#ifndef ELKCPP_TRANSPORT_SERVER_MOCKUP
#define ELKCPP_TRANSPORT_SERVER_MOCKUP

#include <thread>
#include <array>

#include <grpcpp/grpcpp.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "sushi_rpc.grpc.pb.h"
#pragma GCC diagnostic pop

namespace sushi_controller
{

namespace expected_results
{

    // Processor test values
    const ProcessorInfo PROCESSOR_WITH_ID_1 = ProcessorInfo{1, "synth1", "synth1", 2, 2};
    const ProcessorInfo PROCESSOR_WITH_ID_2 = ProcessorInfo{2, "delay1", "delay1", 2, 2};
    const std::vector<ProcessorInfo> PROCESSOR_INFO_LIST = {PROCESSOR_WITH_ID_1, PROCESSOR_WITH_ID_2};
    constexpr bool PROCESSOR_BYPASS_STATE = true;

    // Parameter test values
    constexpr ParameterType PARAMETER_TYPE{ParameterType::FLOAT};
    constexpr float PARAMETER_VALUE{5.34f};
    constexpr float PARAMETER_NORMALISED_VALUE{0.87f};
    const std::string PARAMETER_STRING_VALUE{"5.34"};
    const ParameterInfo PARAMETER_WITH_ID_1 = ParameterInfo{1, PARAMETER_TYPE, "param1", "param1", "Hz", true, 0.0f, 1.0f};
    const ParameterInfo PARAMETER_WITH_ID_2 = ParameterInfo{2, PARAMETER_TYPE, "param2", "param2", "Hz", true, 0.0f, 1.0f};
    const std::vector<ParameterInfo> PARAMETER_INFO_LIST = {PARAMETER_WITH_ID_1, PARAMETER_WITH_ID_2};

    // Notification test values
    constexpr std::array<TransportUpdateType, 4> TRANSPORT_UPDATE_TYPES = {TransportUpdateType::TEMPO,
                                                                           TransportUpdateType::PLAYING_MODE,
                                                                           TransportUpdateType::SYNC_MODE,
                                                                           TransportUpdateType::TIME_SIGNATURE};
    constexpr TransportUpdate TEMPO_UPDATE = 120.0f;
    constexpr TransportUpdate PLAYING_UPDATE = PlayingMode::PLAYING;
    constexpr TransportUpdate SYNC_UPDATE = SyncMode::LINK;
    constexpr TransportUpdate TIME_SIG_UPDATE = TimeSignature{6,8};
    constexpr std::array<TransportUpdate, 4> TRANSPORT_UPDATE_CHANGES = {TEMPO_UPDATE, PLAYING_UPDATE, SYNC_UPDATE, TIME_SIG_UPDATE};
    constexpr std::array<CpuTimings, 2> TIMING_UPDATES = {CpuTimings{1.0f,2.0f,3.0f}, CpuTimings{4.0f,5.0f,6.0f}};
    constexpr std::array<float, 3> PARAMETER_CHANGE_VALUES = {0.0f, 0.5f, 1.0f};

} // namespace expected_results


class NotificationServiceMockup : public sushi_rpc::NotificationController::Service
{
    grpc::Status SubscribeToTransportChanges(grpc::ServerContext* /* context */,
                                             const sushi_rpc::GenericVoidValue* /* request */,
                                             grpc::ServerWriter<sushi_rpc::TransportUpdate>* response)
    {
        grpc::Status status;
        sushi_rpc::TransportUpdate response_message;
        response_message.set_tempo(std::get<float>(expected_results::TRANSPORT_UPDATE_CHANGES[0]));
        if (response->Write(response_message) == false)
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Failed to write float");
        }
        response_message.mutable_playing_mode()->set_mode(to_grpc(std::get<PlayingMode>(expected_results::TRANSPORT_UPDATE_CHANGES[1])));
        if (response->Write(response_message) == false)
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Failed to write playing mode");
        }
        response_message.mutable_sync_mode()->set_mode(to_grpc(std::get<SyncMode>(expected_results::TRANSPORT_UPDATE_CHANGES[2])));
        if (response->Write(response_message) == false)
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Failed to write sync mode");
        }
        response_message.mutable_time_signature()->set_numerator(std::get<TimeSignature>(expected_results::TRANSPORT_UPDATE_CHANGES[3]).numerator);
        response_message.mutable_time_signature()->set_denominator(std::get<TimeSignature>(expected_results::TRANSPORT_UPDATE_CHANGES[3]).denominator);
        if (response->Write(response_message) == false)
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Failed to write time signature");
        }
        return grpc::Status::OK;
    }

    grpc::Status SubscribeToEngineCpuTimingUpdates(grpc::ServerContext* /* context */,
                                                   const sushi_rpc::GenericVoidValue* /* request */,
                                                   grpc::ServerWriter<sushi_rpc::CpuTimings>* response)
    {
        grpc::Status status;
        sushi_rpc::CpuTimings response_message;
        for (auto& timings : expected_results::TIMING_UPDATES)
        {
            response_message.set_average(timings.avg);
            response_message.set_max(timings.max);
            response_message.set_min(timings.min);
            if (response->Write(response_message) == false)
            {
                return grpc::Status(grpc::StatusCode::UNKNOWN, "Write failed");
            }
        }
        return grpc::Status::OK;
    }

    grpc::Status SubscribeToParameterUpdates(grpc::ServerContext* /* context*/,
                                             const sushi_rpc::ParameterNotificationBlocklist* request,
                                             grpc::ServerWriter<sushi_rpc::ParameterValue>* response)
    {
        grpc::Status status;
        for (int i = 0; i < request->parameters_size(); ++i)
        {
            auto& parameter = request->parameters(i);
            if (parameter.processor_id() == expected_results::PROCESSOR_WITH_ID_1.id &&
                parameter.parameter_id() == expected_results::PARAMETER_WITH_ID_1.id)
            {
                status = grpc::Status::OK;
            }
        }
        sushi_rpc::ParameterValue response_message;
        response_message.mutable_parameter()->set_parameter_id(expected_results::PROCESSOR_WITH_ID_2.id);
        response_message.mutable_parameter()->set_processor_id(expected_results::PARAMETER_WITH_ID_2.id);
        response_message.set_value(expected_results::PARAMETER_CHANGE_VALUES[0]);
        if (response->Write(response_message) == false)
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "First write to server failed!");
        }
        response_message.set_value(expected_results::PARAMETER_CHANGE_VALUES[1]);
        if (response->Write(response_message) == false)
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "First write to server failed!");
        }
        response_message.set_value(expected_results::PARAMETER_CHANGE_VALUES[2]);
        if (response->Write(response_message) == false)
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "First write to server failed!");
        }
        return status;
    }

};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class NotificationServerMockup
{
public:
    NotificationServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~NotificationServerMockup()
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
    NotificationServiceMockup service;

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


#endif // ELKCPP_TRANSPORT_SERVER_MOCKUP
