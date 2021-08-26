#ifndef ELKCPP_AUDIOROUTING_SERVER_MOCKUP_H
#define ELKCPP_AUDIOROUTING_SERVER_MOCKUP_H

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
    constexpr AudioConnection AUDIO_CONNECTION = {4, 0, 1};
    const std::vector<AudioConnection> AUDIO_CONNECTIONS = {AUDIO_CONNECTION, AUDIO_CONNECTION};
} // namespace expected_results


class AudioRoutingServiceMockup : public sushi_rpc::AudioRoutingController::Service
{

    grpc::Status GetAllInputConnections(grpc::ServerContext* /* context */,
                                        const sushi_rpc::GenericVoidValue* /* request */,
                                        sushi_rpc::AudioConnectionList* response)
    {
        for (auto& connection : expected_results::AUDIO_CONNECTIONS)
        {
            auto response_connection = response->add_connections();
            response_connection->mutable_track()->set_id(connection.track_id);
            response_connection->set_track_channel(connection.track_channel);
            response_connection->set_engine_channel(connection.engine_channel);
        }

        return grpc::Status::OK;
    }

    grpc::Status GetAllOutputConnections(grpc::ServerContext* /* context */,
                                         const sushi_rpc::GenericVoidValue* /* request */,
                                         sushi_rpc::AudioConnectionList* response)
    {
        for (auto& connection : expected_results::AUDIO_CONNECTIONS)
        {
            auto response_connection = response->add_connections();
            response_connection->mutable_track()->set_id(connection.track_id);
            response_connection->set_track_channel(connection.track_channel);
            response_connection->set_engine_channel(connection.engine_channel);
        }

        return grpc::Status::OK;
    }

    grpc::Status GetInputConnectionsForTrack(grpc::ServerContext* /* context */,
                                             const sushi_rpc::TrackIdentifier* request,
                                             sushi_rpc::AudioConnectionList* response)
    {
        if (request->id() == expected_results::AUDIO_CONNECTION.track_id)
        {
            for (auto& connection : expected_results::AUDIO_CONNECTIONS)
            {
                auto response_connection = response->add_connections();
                response_connection->mutable_track()->set_id(connection.track_id);
                response_connection->set_track_channel(connection.track_channel);
                response_connection->set_engine_channel(connection.engine_channel);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Track id doesn't match");
        }
    }

    grpc::Status GetOutputConnectionsForTrack(grpc::ServerContext* /* context */,
                                              const sushi_rpc::TrackIdentifier* request,
                                              sushi_rpc::AudioConnectionList* response)
    {
        if (request->id() == expected_results::AUDIO_CONNECTION.track_id)
        {
            for (auto& connection : expected_results::AUDIO_CONNECTIONS)
            {
                auto response_connection = response->add_connections();
                response_connection->mutable_track()->set_id(connection.track_id);
                response_connection->set_track_channel(connection.track_channel);
                response_connection->set_engine_channel(connection.engine_channel);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Track id doesn't match");
        }
    }

    grpc::Status ConnectInputChannelToTrack(grpc::ServerContext* /* context */,
                                            const sushi_rpc::AudioConnection* request,
                                            sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::AUDIO_CONNECTION.track_id &&
            request->track_channel() == expected_results::AUDIO_CONNECTION.track_channel &&
            request->engine_channel() == expected_results::AUDIO_CONNECTION.engine_channel)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arguments don't match expected");
        }
    }

    grpc::Status ConnectOutputChannelFromTrack(grpc::ServerContext* /* context */,
                                             const sushi_rpc::AudioConnection* request,
                                             sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::AUDIO_CONNECTION.track_id &&
            request->track_channel() == expected_results::AUDIO_CONNECTION.track_channel &&
            request->engine_channel() == expected_results::AUDIO_CONNECTION.engine_channel)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arguments don't match expected");
        }
    }

    grpc::Status DisconnectInput(grpc::ServerContext* /* context */,
                                 const sushi_rpc::AudioConnection* request,
                                 sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::AUDIO_CONNECTION.track_id &&
            request->track_channel() == expected_results::AUDIO_CONNECTION.track_channel &&
            request->engine_channel() == expected_results::AUDIO_CONNECTION.engine_channel)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arguments don't match expected");
        }
    }

    grpc::Status DisconnectOutput(grpc::ServerContext* /* context */,
                                  const sushi_rpc::AudioConnection* request,
                                  sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::AUDIO_CONNECTION.track_id &&
            request->track_channel() == expected_results::AUDIO_CONNECTION.track_channel &&
            request->engine_channel() == expected_results::AUDIO_CONNECTION.engine_channel)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arguments don't match expected");
        }
    }

    grpc::Status DisconnectAllInputsFromTrack(grpc::ServerContext* /* context */,
                                              const sushi_rpc::TrackIdentifier* request,
                                              sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->id() == expected_results::AUDIO_CONNECTION.track_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Wrong track id");
        }
    }

    grpc::Status DisconnectAllOutputFromTrack(grpc::ServerContext* /* context */,
                                               const sushi_rpc::TrackIdentifier* request,
                                               sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->id() == expected_results::AUDIO_CONNECTION.track_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Wrong track id");
        }
    }

};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class AudioRoutingServerMockup
{
public:
    AudioRoutingServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~AudioRoutingServerMockup()
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
    AudioRoutingServiceMockup service;

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


#endif // ELKCPP_AUDIOROUTING_SERVER_MOCKUP_H
