#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "program_controller.h"

namespace sushi_controller
{

ProgramControllerClient::ProgramControllerClient(const std::string& address)
    : _stub(sushi_rpc::ProgramController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        ))) {}

std::pair<ControlStatus, int> ProgramControllerClient::get_processor_current_program(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::ProgramIdentifier response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->GetProcessorCurrentProgram(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return {to_ext(status), response.program()};
}

std::pair<ControlStatus, std::string> ProgramControllerClient::get_processor_current_program_name(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericStringValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->GetProcessorCurrentProgramName(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return {to_ext(status), response.value()};
}

std::pair<ControlStatus, std::string> ProgramControllerClient::get_processor_program_name(int processor_id, int program_id) const
{
    sushi_rpc::ProcessorProgramIdentifier request;
    sushi_rpc::GenericStringValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.set_program(program_id);

    grpc::Status status = _stub->GetProcessorProgramName(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return {to_ext(status), response.value()};
}

std::pair<ControlStatus, std::vector<std::string>> ProgramControllerClient::get_processor_programs(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::ProgramInfoList response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->GetProcessorPrograms(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    std::vector<std::string> output;
    for (auto& program : response.programs())
    {
        output.push_back(program.name());
    }
    return {to_ext(status), output};
}

ControlStatus ProgramControllerClient::set_processor_program(int processor_id, int program_id)
{
    sushi_rpc::ProcessorProgramSetRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.mutable_program()->set_program(program_id);

    grpc::Status status = _stub->SetProcessorProgram(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::shared_ptr<ProgramController> CreateProgramController(const std::string& server_address)
{
    return std::make_shared<ProgramControllerClient>(server_address);
}

} // namespace sushi_controller

