/**
 * @brief gRPC client to control sushi
 * 
 * @copyright MIND Music Labs AB, Stockholm, Sweden
 */

#ifndef SUSHI_GRPC_CLIENT_H
#define SUSHI_GRPC_CLIENT_H

#include "sushi_info_types.h"
#include "sushi_rpc.grpc.pb.h"

namespace sushi_controller
{

class SushiControllerClient
{
public:
    SushiController(std::string address = "localhost:51051");

    ~SushiController() = default;

    float GetSampleRate();

private:
    std::unique_ptr<sushi_rpc::SushiController::Stub> _stub;
};

}

#endif // SUSHI_GRPC_CLIENT_H