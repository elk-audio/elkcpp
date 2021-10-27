#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "osc_controller.h"

namespace sushi_controller
{

OscControllerClient::OscControllerClient(const std::string& address)
    : _stub(sushi_rpc::OscController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        ))) {}


std::pair<ControlStatus, int> OscControllerClient::get_send_port() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericIntValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetSendPort(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, int>(to_ext(status), response.value());
}

std::pair<ControlStatus, int> OscControllerClient::get_receive_port() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericIntValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetReceivePort(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, int>(to_ext(status), response.value());
}

std::pair<ControlStatus, std::vector<std::string>> OscControllerClient::get_enabled_parameter_outputs() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::OscParameterOutputList response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetEnabledParameterOutputs(&context, request, &response);

    std::vector<std::string> output;
    for (auto& path : response.path())
    {
        output.push_back(path);
    }

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<std::string>>(to_ext(status), output);
}

ControlStatus OscControllerClient::enable_output_for_parameter(int processor_id, int parameter_id)
{
    sushi_rpc::ParameterIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_processor_id(processor_id);
    request.set_parameter_id(parameter_id);

    grpc::Status status = _stub->EnableOutputForParameter(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus OscControllerClient::disable_output_for_parameter(int processor_id, int parameter_id)
{
    sushi_rpc::ParameterIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_processor_id(processor_id);
    request.set_parameter_id(parameter_id);

    grpc::Status status = _stub->DisableOutputForParameter(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus OscControllerClient::enable_all_output()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->EnableAllOutput(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus OscControllerClient::disable_all_output()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->DisableAllOutput(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::shared_ptr<OscController> CreateOscController(const std::string& address)
{
    return std::make_shared<OscControllerClient>(address);
}

} // namespace sushi_controller
