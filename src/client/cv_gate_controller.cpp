#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "cv_gate_controller.h"

namespace sushi_controller
{

CvGateControllerClient::CvGateControllerClient(const std::string& address)
    : _stub(sushi_rpc::CvGateController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        ))) {}

std::pair<ControlStatus, int> CvGateControllerClient::get_cv_input_channel_count() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericIntValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetCvInputChannelCount(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, int>(to_ext(status), response.value());
}

std::pair<ControlStatus, int> CvGateControllerClient::get_cv_output_channel_count() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericIntValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetCvOutputChannelCount(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, int>(to_ext(status), response.value());
}

std::pair<ControlStatus, std::vector<CvConnection>> CvGateControllerClient::get_all_cv_input_connections() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::CvConnectionList response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetAllCvInputConnections(&context, request, &response);

    std::vector<CvConnection> output;
    for(auto& connection : response.connections())
    {
        output.push_back({connection.parameter().processor_id(),
                          connection.parameter().parameter_id(),
                          connection.cv_port_id()});
    }

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<CvConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<CvConnection>> CvGateControllerClient::get_all_cv_output_connections() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::CvConnectionList response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetAllCvOutputConnections(&context, request, &response);

    std::vector<CvConnection> output;
    for(auto& connection : response.connections())
    {
        output.push_back({connection.parameter().processor_id(),
                          connection.parameter().parameter_id(),
                          connection.cv_port_id()});
    }

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<CvConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<GateConnection>> CvGateControllerClient::get_all_gate_input_connections() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GateConnectionList response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetAllGateInputConnections(&context, request, &response);

    std::vector<GateConnection> output;
    for(auto& connection : response.connections())
    {
        output.push_back({connection.processor().id(),
                          connection.gate_port_id(),
                          connection.channel(),
                          connection.note_no()});
    }

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<GateConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<GateConnection>> CvGateControllerClient::get_all_gate_output_connections() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GateConnectionList response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetAllGateOutputConnections(&context, request, &response);

    std::vector<GateConnection> output;
    for(auto& connection : response.connections())
    {
        output.push_back({connection.processor().id(),
                          connection.gate_port_id(),
                          connection.channel(),
                          connection.note_no()});
    }

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<GateConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<CvConnection>> CvGateControllerClient::get_cv_input_connections_for_processor(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::CvConnectionList response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->GetCvInputConnectionsForProcessor(&context, request, &response);

    std::vector<CvConnection> output;
    for(auto& connection : response.connections())
    {
        output.push_back({connection.parameter().processor_id(),
                          connection.parameter().parameter_id(),
                          connection.cv_port_id()});
    }

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<CvConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<CvConnection>> CvGateControllerClient::get_cv_output_connections_for_processor(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::CvConnectionList response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->GetCvOutputConnectionsForProcessor(&context, request, &response);

    std::vector<CvConnection> output;
    for(auto& connection : response.connections())
    {
        output.push_back({connection.parameter().processor_id(),
                          connection.parameter().parameter_id(),
                          connection.cv_port_id()});
    }

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<CvConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<GateConnection>> CvGateControllerClient::get_gate_input_connections_for_processor(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GateConnectionList response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->GetGateInputConnectionsForProcessor(&context, request, &response);

    std::vector<GateConnection> output;
    for(auto& connection : response.connections())
    {
        output.push_back({connection.processor().id(),
                          connection.gate_port_id(),
                          connection.channel(),
                          connection.note_no()});
    }

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<GateConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<GateConnection>> CvGateControllerClient::get_gate_output_connections_for_processor(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GateConnectionList response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->GetGateOutputConnectionsForProcessor(&context, request, &response);

    std::vector<GateConnection> output;
    for(auto& connection : response.connections())
    {
        output.push_back({connection.processor().id(),
                          connection.gate_port_id(),
                          connection.channel(),
                          connection.note_no()});
    }

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<GateConnection>>(to_ext(status), output);
}

ControlStatus CvGateControllerClient::connect_cv_input_to_parameter(int processor_id, int parameter_id, int cv_input_id)
{
    sushi_rpc::CvConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_parameter()->set_processor_id(processor_id);
    request.mutable_parameter()->set_parameter_id(parameter_id);
    request.set_cv_port_id(cv_input_id);

    grpc::Status status = _stub->ConnectCvInputToParameter(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::connect_cv_output_from_parameter(int processor_id, int parameter_id, int cv_output_id)
{
    sushi_rpc::CvConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_parameter()->set_processor_id(processor_id);
    request.mutable_parameter()->set_parameter_id(parameter_id);
    request.set_cv_port_id(cv_output_id);

    grpc::Status status = _stub->ConnectCvOutputFromParameter(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::connect_gate_input_to_processor(int processor_id, int gate_input_id, int channel, int note_no)
{
    sushi_rpc::GateConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.set_gate_port_id(gate_input_id);
    request.set_channel(channel);
    request.set_note_no(note_no);

    grpc::Status status = _stub->ConnectGateInputToProcessor(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::connect_gate_output_from_processor(int processor_id, int gate_output_id, int channel, int note_no)
{
    sushi_rpc::GateConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.set_gate_port_id(gate_output_id);
    request.set_channel(channel);
    request.set_note_no(note_no);

    grpc::Status status = _stub->ConnectGateOutputFromProcessor(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::disconnect_cv_input(int processor_id, int parameter_id, int cv_input_id)
{
    sushi_rpc::CvConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_parameter()->set_processor_id(processor_id);
    request.mutable_parameter()->set_parameter_id(parameter_id);
    request.set_cv_port_id(cv_input_id);

    grpc::Status status = _stub->DisconnectCvInput(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::disconnect_cv_output(int processor_id, int parameter_id, int cv_output_id)
{
    sushi_rpc::CvConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_parameter()->set_processor_id(processor_id);
    request.mutable_parameter()->set_parameter_id(parameter_id);
    request.set_cv_port_id(cv_output_id);

    grpc::Status status = _stub->DisconnectCvOutput(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::disconnect_gate_input(int processor_id, int gate_input_id, int channel, int note_no)
{
    sushi_rpc::GateConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.set_gate_port_id(gate_input_id);
    request.set_channel(channel);
    request.set_note_no(note_no);

    grpc::Status status = _stub->DisconnectGateInput(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::disconnect_gate_output(int processor_id, int gate_output_id, int channel, int note_no)
{
    sushi_rpc::GateConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.set_gate_port_id(gate_output_id);
    request.set_channel(channel);
    request.set_note_no(note_no);

    grpc::Status status = _stub->DisconnectGateOutput(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::disconnect_all_cv_inputs_from_processor(int processor_id)
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);
    grpc::Status status = _stub->DisconnectAllCvInputsFromProcessor(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::disconnect_all_cv_outputs_from_processor(int processor_id)
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);
    grpc::Status status = _stub->DisconnectAllCvOutputsFromProcessor(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::disconnect_all_gate_inputs_from_processor(int processor_id)
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);
    grpc::Status status = _stub->DisconnectAllGateInputsFromProcessor(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus CvGateControllerClient::disconnect_all_gate_outputs_from_processor(int processor_id)
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);
    grpc::Status status = _stub->DisconnectAllGateOutputsFromProcessor(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::shared_ptr<CvGateController> CreateCvGateController(const std::string& address)
{
    return std::move(std::make_shared<CvGateControllerClient>(address));
}

} // namespace sushi_controller
