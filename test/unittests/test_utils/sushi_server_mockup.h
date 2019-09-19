/**
 * @brief Mockup of the server running in sushi for testing purposes
 */

#ifndef SUSHI_SERVER_MOCKUP_H
#define SUSHI_SERVER_MOCKUP_H

#include <grpc++/grpc++.h>
#include "sushi_rpc.grpc.pb.h"

namespace sushi_controller
{

class SushiServerMockup final : public sushi_rpc::SushiController::Service
{
    grpc::Status GetSamplerate(grpc::ServerContext* context, 
                               const sushi_rpc::GenericVoidValue* request,
                               sushi_rpc::GenericFloatValue* response) override
    {
        response->set_value(48000.0f);
        return grpc::Status::OK;
    }
};

}

#endif // SUSHI_SERVER_MOCKUP_H