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
    constexpr float SAMPLERATE = 48000.0f;
    constexpr PlayingMode PLAYING_MODE = PlayingMode::STOPPED;
    constexpr SyncMode SYNC_MODE = SyncMode::INTERNAL;
    constexpr float TEMPO = 120.0f;
    constexpr TimeSignature TIME_SIGNATURE{4,4};
    const TrackInfo TRACK_WITH_ID_1 = TrackInfo{ 1, "synth", "synth", 2, 2, 2, 2, 10};
    const TrackInfo TRACK_WITH_ID_2 = TrackInfo{ 1, "guitar", "guitar", 2, 2, 2, 2, 10};
    const std::vector<TrackInfo> TRACK_INFO_LIST = {TRACK_WITH_ID_1, TRACK_WITH_ID_2};
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
                                sushi_rpc::GenericVoidValue* /* response */)
    {
        _playing_mode = request->mode();
        return grpc::Status::OK;
    }

    grpc::Status GetSyncMode(grpc::ServerContext* /* context */,
                             const sushi_rpc::GenericVoidValue* /* request */,
                             sushi_rpc::SyncMode* response)
    {
        response->set_mode(_sync_mode);
        return grpc::Status::OK;
    }

    sushi_rpc::PlayingMode::Mode _playing_mode{startup_values::PLAYING_MODE};
    sushi_rpc::SyncMode::Mode _sync_mode{startup_values::SYNC_MODE};
};

class SushiServerMockup
{
public:
    SushiServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(1000); //Wait for server to start
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