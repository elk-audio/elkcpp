#ifndef ELKCPP_CV_GATE_SERVER_MOCKUP_H
#define ELKCPP_CV_GATE_SERVER_MOCKUP_H

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

    constexpr int N_INPUT_PORTS = 3;
    constexpr int N_OUTPUT_PORTS = 4;

    constexpr CvConnection CV_CONNECTION = {4, 7, 5};
    const std::vector<CvConnection> CV_CONNECTIONS = {CV_CONNECTION, CV_CONNECTION, CV_CONNECTION};

    constexpr GateConnection GATE_CONNECTION = {1, 11, 8, 15};
    const std::vector<GateConnection> GATE_CONNECTIONS = {GATE_CONNECTION, GATE_CONNECTION, GATE_CONNECTION, GATE_CONNECTION};

} // namespace expected_results


class CvGateServiceMockup : public sushi_rpc::CvGateController::Service
{

    grpc::Status GetCvInputChannelCount(grpc::ServerContext* /* context */,
                                 const sushi_rpc::GenericVoidValue* /* request */,
                                 sushi_rpc::GenericIntValue* response)
    {
        response->set_value(expected_results::N_INPUT_PORTS);
        return grpc::Status::OK;
    }

    grpc::Status GetCvOutputChannelCount(grpc::ServerContext* /* context */,
                                  const sushi_rpc::GenericVoidValue* /* request */,
                                  sushi_rpc::GenericIntValue* response)
    {
        response->set_value(expected_results::N_OUTPUT_PORTS);
        return grpc::Status::OK;
    }

    grpc::Status GetAllCvInputConnections(grpc::ServerContext* /* context */,
                                          const sushi_rpc::GenericVoidValue* /* request */,
                                          sushi_rpc::CvConnectionList* response)
    {
        for (auto& cv_connection : expected_results::CV_CONNECTIONS)
        {
            auto response_connection = response->add_connections();
            response_connection->mutable_parameter()->set_processor_id(cv_connection.processor_id);
            response_connection->mutable_parameter()->set_parameter_id(cv_connection.parameter_id);
            response_connection->set_cv_port_id(cv_connection.cv_port_id);
        }
        return grpc::Status::OK;
    }

    grpc::Status GetAllCvOutputConnections(grpc::ServerContext* /* context */,
                                           const sushi_rpc::GenericVoidValue* /* request */,
                                           sushi_rpc::CvConnectionList* response)
    {
        for (auto& cv_connection : expected_results::CV_CONNECTIONS)
        {
            auto response_connection = response->add_connections();
            response_connection->mutable_parameter()->set_processor_id(cv_connection.processor_id);
            response_connection->mutable_parameter()->set_parameter_id(cv_connection.parameter_id);
            response_connection->set_cv_port_id(cv_connection.cv_port_id);
        }
        return grpc::Status::OK;
    }

    grpc::Status GetAllGateInputConnections(grpc::ServerContext* /* context */,
                                            const sushi_rpc::GenericVoidValue* /* request */,
                                            sushi_rpc::GateConnectionList* response)
    {
        for (auto& gate_connection : expected_results::GATE_CONNECTIONS)
        {
            auto response_connection = response->add_connections();
            response_connection->mutable_processor()->set_id(gate_connection.processor_id);
            response_connection->set_gate_port_id(gate_connection.gate_port_id);
            response_connection->set_channel(gate_connection.channel);
            response_connection->set_note_no(gate_connection.note_no);
        }
        return grpc::Status::OK;
    }

    grpc::Status GetAllGateOutputConnections(grpc::ServerContext* /* context */,
                                             const sushi_rpc::GenericVoidValue* /* request */,
                                             sushi_rpc::GateConnectionList* response)
    {
        for (auto& gate_connection : expected_results::GATE_CONNECTIONS)
        {
            auto response_connection = response->add_connections();
            response_connection->mutable_processor()->set_id(gate_connection.processor_id);
            response_connection->set_gate_port_id(gate_connection.gate_port_id);
            response_connection->set_channel(gate_connection.channel);
            response_connection->set_note_no(gate_connection.note_no);
        }
        return grpc::Status::OK;
    }

    grpc::Status GetCvInputConnectionsForProcessor(grpc::ServerContext* /* context */,
                                                   const sushi_rpc::ProcessorIdentifier* request,
                                                   sushi_rpc::CvConnectionList* response)
    {
        if (request->id() == expected_results::CV_CONNECTION.processor_id)
        {
            for (auto& cv_connection : expected_results::CV_CONNECTIONS)
            {
                auto response_connection = response->add_connections();
                response_connection->mutable_parameter()->set_processor_id(cv_connection.processor_id);
                response_connection->mutable_parameter()->set_parameter_id(cv_connection.parameter_id);
                response_connection->set_cv_port_id(cv_connection.cv_port_id);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Processor id invalid");
        }
    }

    grpc::Status GetCvOutputConnectionsForProcessor(grpc::ServerContext* /* context */,
                                                    const sushi_rpc::ProcessorIdentifier* request,
                                                    sushi_rpc::CvConnectionList* response)
    {
        if (request->id() == expected_results::CV_CONNECTION.processor_id)
        {
            for (auto& cv_connection : expected_results::CV_CONNECTIONS)
            {
                auto response_connection = response->add_connections();
                response_connection->mutable_parameter()->set_processor_id(cv_connection.processor_id);
                response_connection->mutable_parameter()->set_parameter_id(cv_connection.parameter_id);
                response_connection->set_cv_port_id(cv_connection.cv_port_id);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Processor id invalid");
        }
    }

    grpc::Status GetGateInputConnectionsForProcessor(grpc::ServerContext* /* context */,
                                                     const sushi_rpc::ProcessorIdentifier* request,
                                                     sushi_rpc::GateConnectionList* response)
    {
        if (request->id() == expected_results::CV_CONNECTION.processor_id)
        {
            for (auto& gate_connection : expected_results::GATE_CONNECTIONS)
            {
                auto response_connection = response->add_connections();
                response_connection->mutable_processor()->set_id(gate_connection.processor_id);
                response_connection->set_gate_port_id(gate_connection.gate_port_id);
                response_connection->set_channel(gate_connection.channel);
                response_connection->set_note_no(gate_connection.note_no);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Processor id invalid");
        }
    }

    grpc::Status GetGateOutputConnectionsForProcessor(grpc::ServerContext* /* context */,
                                                      const sushi_rpc::ProcessorIdentifier* request,
                                                      sushi_rpc::GateConnectionList* response)
    {
        if (request->id() == expected_results::CV_CONNECTION.processor_id)
        {
            for (auto& gate_connection : expected_results::GATE_CONNECTIONS)
            {
                auto response_connection = response->add_connections();
                response_connection->mutable_processor()->set_id(gate_connection.processor_id);
                response_connection->set_gate_port_id(gate_connection.gate_port_id);
                response_connection->set_channel(gate_connection.channel);
                response_connection->set_note_no(gate_connection.note_no);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Processor id invalid");
        }
    }

    grpc::Status ConnectCvInputToParameter(grpc::ServerContext* /* context */,
                                           const sushi_rpc::CvConnection* request,
                                           sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->parameter().processor_id() == expected_results::CV_CONNECTION.processor_id &&
            request->parameter().parameter_id() == expected_results::CV_CONNECTION.parameter_id &&
            request->cv_port_id() == expected_results::CV_CONNECTION.cv_port_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Unexpected ids");
        }
    }

    grpc::Status ConnectCvOutputFromParameter(grpc::ServerContext* /* context */,
                                              const sushi_rpc::CvConnection* request,
                                              sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->parameter().processor_id() == expected_results::CV_CONNECTION.processor_id &&
            request->parameter().parameter_id() == expected_results::CV_CONNECTION.parameter_id &&
            request->cv_port_id() == expected_results::CV_CONNECTION.cv_port_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Unexpected ids");
        }
    }

    grpc::Status ConnectGateInputToProcessor(grpc::ServerContext* /* context */,
                                             const sushi_rpc::GateConnection* request,
                                             sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->processor().id() == expected_results::GATE_CONNECTION.processor_id &&
            request->gate_port_id() == expected_results::GATE_CONNECTION.gate_port_id &&
            request->channel() == expected_results::GATE_CONNECTION.channel &&
            request->note_no() == expected_results::GATE_CONNECTION.note_no)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Unexpected ids");
        }
    }

    grpc::Status ConnectGateOutputFromProcessor(grpc::ServerContext* /* context */,
                                                const sushi_rpc::GateConnection* request,
                                                sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->processor().id() == expected_results::GATE_CONNECTION.processor_id &&
            request->gate_port_id() == expected_results::GATE_CONNECTION.gate_port_id &&
            request->channel() == expected_results::GATE_CONNECTION.channel &&
            request->note_no() == expected_results::GATE_CONNECTION.note_no)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Unexpected ids");
        }
    }

    grpc::Status DisconnectCvInput(grpc::ServerContext* /* context */,
                                   const sushi_rpc::CvConnection* request,
                                   sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->parameter().processor_id() == expected_results::CV_CONNECTION.processor_id &&
            request->parameter().parameter_id() == expected_results::CV_CONNECTION.parameter_id &&
            request->cv_port_id() == expected_results::CV_CONNECTION.cv_port_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Unexpected ids");
        }
    }

    grpc::Status DisconnectCvOutput(grpc::ServerContext* /* context */,
                                    const sushi_rpc::CvConnection* request,
                                    sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->parameter().processor_id() == expected_results::CV_CONNECTION.processor_id &&
            request->parameter().parameter_id() == expected_results::CV_CONNECTION.parameter_id &&
            request->cv_port_id() == expected_results::CV_CONNECTION.cv_port_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Unexpected ids");
        }
    }

    grpc::Status DisconnectGateInput(grpc::ServerContext* /* context */,
                                     const sushi_rpc::GateConnection* request,
                                     sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->processor().id() == expected_results::GATE_CONNECTION.processor_id &&
            request->gate_port_id() == expected_results::GATE_CONNECTION.gate_port_id &&
            request->channel() == expected_results::GATE_CONNECTION.channel &&
            request->note_no() == expected_results::GATE_CONNECTION.note_no)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Unexpected ids");
        }
    }

    grpc::Status DisconnectGateOutput(grpc::ServerContext* /* context */,
                                      const sushi_rpc::GateConnection* request,
                                      sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->processor().id() == expected_results::GATE_CONNECTION.processor_id &&
            request->gate_port_id() == expected_results::GATE_CONNECTION.gate_port_id &&
            request->channel() == expected_results::GATE_CONNECTION.channel &&
            request->note_no() == expected_results::GATE_CONNECTION.note_no)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Unexpected ids");
        }
    }

    grpc::Status DisconnectAllCvInputsFromProcessor(grpc::ServerContext* /* context */,
                                                    const sushi_rpc::ProcessorIdentifier* request,
                                                    sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->id() == expected_results::CV_CONNECTION.processor_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Processor id invalid");
        }
    }


    grpc::Status DisconnectAllCvOutputsFromProcessor(grpc::ServerContext* /* context */,
                                                     const sushi_rpc::ProcessorIdentifier* request,
                                                     sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->id() == expected_results::CV_CONNECTION.processor_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Processor id invalid");
        }
    }


    grpc::Status DisconnectAllGateInputsFromProcessor(grpc::ServerContext* /* context */,
                                                      const sushi_rpc::ProcessorIdentifier* request,
                                                      sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->id() == expected_results::GATE_CONNECTION.processor_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Processor id invalid");
        }
    }

    grpc::Status DisconnectAllGateOutputsFromProcessor(grpc::ServerContext* /* context */,
                                                       const sushi_rpc::ProcessorIdentifier* request,
                                                       sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->id() == expected_results::GATE_CONNECTION.processor_id)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Processor id invalid");
        }
    }
};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class CvGateServerMockup
{
public:
    CvGateServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~CvGateServerMockup()
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
    CvGateServiceMockup service;

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


#endif // ELKCPP_CV_GATE_SERVER_MOCKUP_H
