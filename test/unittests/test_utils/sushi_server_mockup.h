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

std::unique_ptr<grpc::Server> server;

class SushiServerMockup final : public sushi_rpc::SushiController::Service
{
    grpc::Status GetSamplerate(grpc::ServerContext* context, 
                               const sushi_rpc::GenericVoidValue* request,
                               sushi_rpc::GenericFloatValue* response) override
    {
        response->set_value(48000.0f);
        return grpc::Status::OK;
    }

    grpc::Status GetPlayingMode(grpc::ServerContext* context, 
                               const sushi_rpc::GenericVoidValue* request,
                               sushi_rpc::PlayingMode* response) override
    {
        response->set_mode(_playing_mode);
        return grpc::Status::OK;
    }

    sushi_rpc::PlayingMode::Mode _playing_mode{sushi_rpc::PlayingMode::STOPPED};
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