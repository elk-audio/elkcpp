#ifndef ELKCPP_SESSION_SERVER_MOCKUP_H
#define ELKCPP_SESSION_SERVER_MOCKUP_H

#include <thread>

#include <grpcpp/grpcpp.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "sushi_rpc.grpc.pb.h"

#pragma GCC diagnostic pop

namespace sushi_controller {

class SessionServiceMockup : public sushi_rpc::SessionController::Service
{

    grpc::Status SaveSession(grpc::ServerContext* /* context */,
                             const sushi_rpc::GenericVoidValue* /* request */,
                             sushi_rpc::SessionState* /* response */)
    {
        return grpc::Status::OK;
    }

    grpc::Status RestoreSession(grpc::ServerContext* /* context */,
                                const sushi_rpc::SessionState* /* request */,
                                sushi_rpc::GenericVoidValue* /* response */)
    {
        return grpc::Status::OK;
    }
};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();

static void KillServerMockup();

class SessionServerMockup
{
public:
    SessionServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~SessionServerMockup()
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
    SessionServiceMockup service;

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

#endif //ELKCPP_SESSION_SERVER_MOCKUP_H
