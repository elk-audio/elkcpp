#ifndef ELKCPP_MIDI_SERVER_MOCKUP_H
#define ELKCPP_MIDI_SERVER_MOCKUP_H

#include <thread>

#include <grpcpp/grpcpp.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "sushi_rpc.grpc.pb.h"
#pragma GCC diagnostic pop

#include "controller_types.h"
#include "grpc_utils.h"

namespace sushi_controller
{

namespace expected_results
{
    constexpr int MIDI_INPUT_PORTS = 6;
    constexpr int MIDI_OUTPUT_PORTS = 8;

    constexpr MidiKbdConnection KBD_CONNECTION = {1, MidiChannel::MIDI_CH_10, 5, true};
    const std::vector<MidiKbdConnection> KBD_CONNECTIONS = {KBD_CONNECTION, KBD_CONNECTION, KBD_CONNECTION, KBD_CONNECTION};

    constexpr MidiCCConnection CC_CONNECTION = {4, 7, MidiChannel::MIDI_CH_15, 2, 63, 0.1f, 0.9f, false};
    const std::vector<MidiCCConnection> CC_CONNECTIONS = {CC_CONNECTION, CC_CONNECTION};

    constexpr MidiPCConnection PC_CONNECTION = {5, MidiChannel::MIDI_CH_2, 6};
    const std::vector<MidiPCConnection> PC_CONNECTIONS = {PC_CONNECTION, PC_CONNECTION, PC_CONNECTION};
} // namespace expected_results


class MidiServiceMockup : public sushi_rpc::MidiController::Service
{

    grpc::Status GetInputPorts(grpc::ServerContext* /* context */,
                               const sushi_rpc::GenericVoidValue* /* request */,
                               sushi_rpc::GenericIntValue* response)
    {
        response->set_value(expected_results::MIDI_INPUT_PORTS);
        return grpc::Status::OK;
    }

    grpc::Status GetOutputPorts(grpc::ServerContext* /* context */,
                                const sushi_rpc::GenericVoidValue* /* request */,
                                sushi_rpc::GenericIntValue* response)
    {
        response->set_value(expected_results::MIDI_OUTPUT_PORTS);
        return grpc::Status::OK;
    }

    grpc::Status GetAllKbdInputConnections(grpc::ServerContext* /* context */,
                                           const sushi_rpc::GenericVoidValue* /* request */,
                                           sushi_rpc::MidiKbdConnectionList* response)
    {
        for (auto& connection : expected_results::KBD_CONNECTIONS)
        {
            auto response_connection = response->add_connections();
            response_connection->mutable_track()->set_id(connection.track_id);
            response_connection->mutable_channel()->set_channel(to_grpc(connection.channel));
            response_connection->set_port(connection.port);
            response_connection->set_raw_midi(connection.raw_midi);
        }
        return grpc::Status::OK;
    }

    grpc::Status GetAllKbdOutputConnections(grpc::ServerContext* /* context */,
                                            const sushi_rpc::GenericVoidValue* /* request */,
                                            sushi_rpc::MidiKbdConnectionList* response)
    {
        for (auto& connection : expected_results::KBD_CONNECTIONS)
        {
            auto response_connection = response->add_connections();
            response_connection->mutable_track()->set_id(connection.track_id);
            response_connection->mutable_channel()->set_channel(to_grpc(connection.channel));
            response_connection->set_port(connection.port);
            response_connection->set_raw_midi(connection.raw_midi);
        }
        return grpc::Status::OK;
    }

    grpc::Status GetAllCCInputConnections(grpc::ServerContext* /* context */,
                                          const sushi_rpc::GenericVoidValue* /* request */,
                                          sushi_rpc::MidiCCConnectionList* response)
    {
        for (auto& connection : expected_results::CC_CONNECTIONS)
        {
            auto response_connection = response->add_connections();
            response_connection->mutable_parameter()->set_parameter_id(connection.parameter_id);
            response_connection->mutable_parameter()->set_processor_id(connection.processor_id);
            response_connection->mutable_channel()->set_channel(to_grpc(connection.channel));
            response_connection->set_port(connection.port);
            response_connection->set_cc_number(connection.cc_number);
            response_connection->set_min_range(connection.min_range);
            response_connection->set_max_range(connection.max_range);
            response_connection->set_relative_mode(connection.relative_mode);
        }
        return grpc::Status::OK;
    }

    grpc::Status GetAllPCInputConnections(grpc::ServerContext* /* context */,
                                          const sushi_rpc::GenericVoidValue* /* request */,
                                          sushi_rpc::MidiPCConnectionList* response)
    {
        for (auto& connection : expected_results::PC_CONNECTIONS)
        {
            auto response_connection = response->add_connections();
            response_connection->mutable_processor()->set_id(connection.processor_id);
            response_connection->mutable_channel()->set_channel(to_grpc(connection.channel));
            response_connection->set_port(connection.port);
        }
        return grpc::Status::OK;
    }

    grpc::Status GetCCInputConnectionsForProcessor(grpc::ServerContext* /* context */,
                                                   const sushi_rpc::ProcessorIdentifier* request,
                                                   sushi_rpc::MidiCCConnectionList* response)
    {
        if (request->id() == expected_results::CC_CONNECTION.processor_id)
        {
            for (auto& connection : expected_results::CC_CONNECTIONS)
            {
                auto response_connection = response->add_connections();
                response_connection->mutable_parameter()->set_parameter_id(connection.parameter_id);
                response_connection->mutable_parameter()->set_processor_id(connection.processor_id);
                response_connection->mutable_channel()->set_channel(to_grpc(connection.channel));
                response_connection->set_port(connection.port);
                response_connection->set_cc_number(connection.cc_number);
                response_connection->set_min_range(connection.min_range);
                response_connection->set_max_range(connection.max_range);
                response_connection->set_relative_mode(connection.relative_mode);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Processor id does not match");
        }
    }

    grpc::Status GetPCInputConnectionsForProcessor(grpc::ServerContext* /* context */,
                                                   const sushi_rpc::ProcessorIdentifier* request,
                                                   sushi_rpc::MidiPCConnectionList* response)
    {
        if (request->id() == expected_results::PC_CONNECTION.processor_id)
        {
            for (auto& connection : expected_results::PC_CONNECTIONS)
            {
                auto response_connection = response->add_connections();
                response_connection->mutable_processor()->set_id(connection.processor_id);
                response_connection->mutable_channel()->set_channel(to_grpc(connection.channel));
                response_connection->set_port(connection.port);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Processor id does not match");
        }
    }

    grpc::Status ConnectKbdInputToTrack(grpc::ServerContext* /* context */,
                                        const sushi_rpc::MidiKbdConnection* request,
                                        sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::KBD_CONNECTION.track_id &&
            to_ext(request->channel().channel()) == expected_results::KBD_CONNECTION.channel &&
            request->port() == expected_results::KBD_CONNECTION.port &&
            request->raw_midi() == expected_results::KBD_CONNECTION.raw_midi)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arugment doesn't match expected");
        }
    }

    grpc::Status ConnectKbdOutputFromTrack(grpc::ServerContext* /* context */,
                                           const sushi_rpc::MidiKbdConnection* request,
                                           sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::KBD_CONNECTION.track_id &&
            to_ext(request->channel().channel()) == expected_results::KBD_CONNECTION.channel &&
            request->port() == expected_results::KBD_CONNECTION.port &&
            request->raw_midi() == expected_results::KBD_CONNECTION.raw_midi)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arugment doesn't match expected");
        }
    }

    grpc::Status ConnectCCToParameter(grpc::ServerContext* /* context */,
                                      const sushi_rpc::MidiCCConnection* request,
                                      sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->parameter().parameter_id() == expected_results::CC_CONNECTION.parameter_id &&
            request->parameter().processor_id() == expected_results::CC_CONNECTION.processor_id &&
            to_ext(request->channel().channel()) == expected_results::CC_CONNECTION.channel &&
            request->port() == expected_results::CC_CONNECTION.port &&
            request->cc_number() == expected_results::CC_CONNECTION.cc_number &&
            request->min_range() == expected_results::CC_CONNECTION.min_range &&
            request->max_range() == expected_results::CC_CONNECTION.max_range &&
            request->relative_mode() == expected_results::CC_CONNECTION.relative_mode)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arugment doesn't match expected");
        }
    }

    grpc::Status ConnectPCToProcessor(grpc::ServerContext* /* context */,
                                      const sushi_rpc::MidiPCConnection* request,
                                      sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->processor().id() == expected_results::PC_CONNECTION.processor_id &&
            to_ext(request->channel().channel()) == expected_results::PC_CONNECTION.channel &&
            request->port() == expected_results::PC_CONNECTION.port)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arugment doesn't match expected");
        }
    }

    grpc::Status DisconnectKbdInput(grpc::ServerContext* /* context */,
                                    const sushi_rpc::MidiKbdConnection* request,
                                    sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::KBD_CONNECTION.track_id &&
            to_ext(request->channel().channel()) == expected_results::KBD_CONNECTION.channel &&
            request->port() == expected_results::KBD_CONNECTION.port &&
            request->raw_midi() == expected_results::KBD_CONNECTION.raw_midi)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arugment doesn't match expected");
        }
    }

    grpc::Status DisconnectKbdOutput(grpc::ServerContext* /* context */,
                                     const sushi_rpc::MidiKbdConnection* request,
                                     sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::KBD_CONNECTION.track_id &&
            to_ext(request->channel().channel()) == expected_results::KBD_CONNECTION.channel &&
            request->port() == expected_results::KBD_CONNECTION.port &&
            request->raw_midi() == expected_results::KBD_CONNECTION.raw_midi)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arugment doesn't match expected");
        }
    }

    grpc::Status DisconnectCC(grpc::ServerContext* /* context */,
                              const sushi_rpc::MidiCCConnection* request,
                              sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->parameter().parameter_id() == expected_results::CC_CONNECTION.parameter_id &&
            request->parameter().processor_id() == expected_results::CC_CONNECTION.processor_id &&
            to_ext(request->channel().channel()) == expected_results::CC_CONNECTION.channel &&
            request->port() == expected_results::CC_CONNECTION.port &&
            request->cc_number() == expected_results::CC_CONNECTION.cc_number &&
            request->min_range() == expected_results::CC_CONNECTION.min_range &&
            request->max_range() == expected_results::CC_CONNECTION.max_range &&
            request->relative_mode() == expected_results::CC_CONNECTION.relative_mode)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arugment doesn't match expected");
        }
    }

    grpc::Status DisconnectPC(grpc::ServerContext* /* context */,
                              const sushi_rpc::MidiPCConnection* request,
                              sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->processor().id() == expected_results::PC_CONNECTION.processor_id &&
            to_ext(request->channel().channel()) == expected_results::PC_CONNECTION.channel &&
            request->port() == expected_results::PC_CONNECTION.port)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arugment doesn't match expected");
        }
    }

    grpc::Status DisconnectAllCCFromProcessor(grpc::ServerContext* /* context */,
                                              const sushi_rpc::ProcessorIdentifier* request,
                                              sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->id() == expected_results::CC_CONNECTION.processor_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arugment doesn't match expected");
        }
    }

    grpc::Status DisconnectAllPCFromProcessor(grpc::ServerContext* /* context */,
                                              const sushi_rpc::ProcessorIdentifier* request,
                                              sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->id() == expected_results::PC_CONNECTION.processor_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Arugment doesn't match expected");
        }
    }
};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class MidiServerMockup
{
public:
    MidiServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~MidiServerMockup()
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
    MidiServiceMockup service;

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


#endif // ELKCPP_MIDI_SERVER_MOCKUP_H
