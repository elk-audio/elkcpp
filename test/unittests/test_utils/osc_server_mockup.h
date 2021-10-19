#ifndef ELKCPP_OSC_SERVER_MOCKUP_H
#define ELKCPP_OSC_SERVER_MOCKUP_H

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
    constexpr int SEND_PORT = 24024;
    constexpr int RECV_PORT = 24023;

    const std::vector<std::string> OSC_PATHS = {"/test/path/no1", "/test/path/no2", "/test/path/no3"};

    constexpr int PARAMETER_ID = 2;
    constexpr int PROCESSOR_ID = 3;
} // namespace expected_results


class OscServiceMockup : public sushi_rpc::OscController::Service
{

    grpc::Status GetSendPort(grpc::ServerContext* /* context */,
                             const sushi_rpc::GenericVoidValue* /* request */,
                             sushi_rpc::GenericIntValue* response)
    {
        response->set_value(expected_results::SEND_PORT);
        return grpc::Status::OK;
    }

    grpc::Status GetReceivePort(grpc::ServerContext* /* context */,
                             const sushi_rpc::GenericVoidValue* /* request */,
                             sushi_rpc::GenericIntValue* response)
    {
        response->set_value(expected_results::RECV_PORT);
        return grpc::Status::OK;
    }

    grpc::Status GetEnabledParameterOutputs(grpc::ServerContext* /* context */,
                                            const sushi_rpc::GenericVoidValue* /* request */,
                                            sushi_rpc::OscParameterOutputList* response)
    {
        for (auto& path : expected_results::OSC_PATHS)
        {
            auto response_path = response->add_path();
            *response_path = path;
        }
        return grpc::Status::OK;
    }

    grpc::Status EnableOutputForParameter(grpc::ServerContext* /* context */,
                                          const sushi_rpc::ParameterIdentifier* request,
                                          sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->parameter_id() == expected_results::PARAMETER_ID &&
            request->processor_id() == expected_results::PROCESSOR_ID)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "ids don't match");
        }
    }

    grpc::Status DisableOutputForParameter(grpc::ServerContext* /* context */,
                                           const sushi_rpc::ParameterIdentifier* request,
                                           sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->parameter_id() == expected_results::PARAMETER_ID &&
            request->processor_id() == expected_results::PROCESSOR_ID)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "ids don't match");
        }
    }

    grpc::Status EnableAllOutput(grpc::ServerContext* /* context */,
                                 const sushi_rpc::GenericVoidValue* /* request */,
                                 sushi_rpc::GenericVoidValue* /* response */)
    {
        return grpc::Status::OK;
    }

    grpc::Status DisableAllOutput(grpc::ServerContext* /* context */,
                                  const sushi_rpc::GenericVoidValue* /* request */,
                                  sushi_rpc::GenericVoidValue* /* response */)
    {
        return grpc::Status::OK;
    }
};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class OscServerMockup
{
public:
    OscServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~OscServerMockup()
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
    OscServiceMockup service;

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


#endif // ELKCPP_OSC_SERVER_MOCKUP_H
