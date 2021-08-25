#ifndef ELKCPP_TRANSPORT_SERVER_MOCKUP_H
#define ELKCPP_TRANSPORT_SERVER_MOCKUP_H

#include <thread>

#include <grpcpp/grpcpp.h>

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

}

class TransportServiceMockup : public sushi_rpc::TransportController::Service
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

    sushi_rpc::PlayingMode::Mode _playing_mode{startup_values::PLAYING_MODE};
    sushi_rpc::SyncMode::Mode _sync_mode{startup_values::SYNC_MODE};
    float _tempo{expected_results::TEMPO};
    sushi_controller::TimeSignature _time_signature{expected_results::TIME_SIGNATURE};
};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class TransportServerMockup
{
public:
    TransportServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~TransportServerMockup()
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
    TransportServiceMockup service;

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


#endif // ELKCPP_TRANSPORT_SERVER_MOCKUP_H
