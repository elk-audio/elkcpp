/**
 * @brief Mockup of the server running in sushi for testing purposes
 */

#ifndef SUSHI_SERVER_MOCKUP_H
#define SUSHI_SERVER_MOCKUP_H

#include <iostream>
#include <string>
#include <memory>

#include <grpc++/grpc++.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "sushi_rpc.grpc.pb.h"
#pragma GCC diagnostic pop



namespace sushi_controller
{

namespace expected_results
{
    constexpr float SAMPLERATE = 48000.0f;
    constexpr sushi_rpc::PlayingMode::Mode PLAYING_MODE = sushi_rpc::PlayingMode::STOPPED;
    constexpr sushi_rpc::SyncMode::Mode SYNC_MODE = sushi_rpc::SyncMode::INTERNAL; 
} //expected_results

std::unique_ptr<grpc::Server> server;

class SushiServerMockup final : public sushi_rpc::SushiController::Service
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

    sushi_rpc::PlayingMode::Mode _playing_mode{expected_results::PLAYING_MODE};
};

void RunServerMockup()
{
    std::string server_address("localhost:51051");
    SushiServerMockup service;

    grpc::ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    server = builder.BuildAndStart();
    std::cout << "Mockup server listening on " << server_address << std::endl;

    server->Wait();
}

void KillServerMockup()
{
    server->Shutdown();
}

}

#endif // SUSHI_SERVER_MOCKUP_H