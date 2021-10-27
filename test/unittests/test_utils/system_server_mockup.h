#ifndef ELKCPP_SYSTEM_SERVER_MOCKUP_H
#define ELKCPP_SYSTEM_SERVER_MOCKUP_H

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
    constexpr char VERSION_STRING[] = "0.8.1";
    const BuildInfo BUILD_INFO = {VERSION_STRING,
                                  {"-DBUFFER_SIZE=32", "-DWITH_XENOMAI=TRUE"},
                                  32,
                                  "kad65fc",
                                  "07-01-2021"};
    constexpr int INPUT_AUDIO_CHANNELS = 4;
    constexpr int OUTPUT_AUDIO_CHANNELS = 8;

} // namespace expected_results


class SystemServiceMockup : public sushi_rpc::SystemController::Service
{

    grpc::Status GetSushiVersion(grpc::ServerContext* /* context */,
                                 const sushi_rpc::GenericVoidValue* /* request */,
                                 sushi_rpc::GenericStringValue* response)
    {
        response->set_value(expected_results::VERSION_STRING);
        return grpc::Status::OK;
    }

    grpc::Status GetBuildInfo(grpc::ServerContext* /* context */,
                              const sushi_rpc::GenericVoidValue* /* request  */,
                              sushi_rpc::SushiBuildInfo* response)
    {
        response->set_version(expected_results::BUILD_INFO.version);
        for (auto& option : expected_results::BUILD_INFO.build_options)
        {
            auto build_options = response->add_build_options();
            *build_options = option;
        }
        response->set_audio_buffer_size(expected_results::BUILD_INFO.audio_buffer_size);
        response->set_commit_hash(expected_results::BUILD_INFO.commit_hash);
        response->set_build_date(expected_results::BUILD_INFO.build_date);
        return grpc::Status::OK;
    }

    grpc::Status GetInputAudioChannelCount(grpc::ServerContext* /* context */,
                                           const sushi_rpc::GenericVoidValue* /* request */,
                                           sushi_rpc::GenericIntValue* response)
    {
        response->set_value(expected_results::INPUT_AUDIO_CHANNELS);
        return grpc::Status::OK;
    }

    grpc::Status GetOutputAudioChannelCount(grpc::ServerContext* /* context */,
                                            const sushi_rpc::GenericVoidValue* /* request */,
                                            sushi_rpc::GenericIntValue* response)
    {
        response->set_value(expected_results::OUTPUT_AUDIO_CHANNELS);
        return grpc::Status::OK;
    }
};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class SystemServerMockup
{
public:
    SystemServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~SystemServerMockup()
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
    SystemServiceMockup service;

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


#endif // ELKCPP_SYSTEM_SERVER_MOCKUP_H
