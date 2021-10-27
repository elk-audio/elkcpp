#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "system_controller.h"

namespace sushi_controller
{

SystemControllerClient::SystemControllerClient(const std::string& address)
    : _stub(sushi_rpc::SystemController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        )
    )) {}

std::pair<ControlStatus, std::string> SystemControllerClient::get_sushi_version()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericStringValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetSushiVersion(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::string>(to_ext(status), response.value());
}

std::pair<ControlStatus, BuildInfo> SystemControllerClient::get_build_info()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::SushiBuildInfo response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetBuildInfo(&context, request, &response);

    BuildInfo output;
    output.version = response.version();
    for (auto& build_option : response.build_options())
    {
        output.build_options.push_back(build_option);
    }
    output.audio_buffer_size = response.audio_buffer_size();
    output.commit_hash = response.commit_hash();
    output.build_date = response.build_date();

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, BuildInfo>(to_ext(status), output);
}

std::pair<ControlStatus, int> SystemControllerClient::get_input_audio_channel_count()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericIntValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetInputAudioChannelCount(&context, request, &response);
    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, int>(to_ext(status), response.value());
}

std::pair<ControlStatus, int> SystemControllerClient::get_output_audio_channel_count()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericIntValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetOutputAudioChannelCount(&context, request, &response);
    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, int>(to_ext(status), response.value());
}

std::shared_ptr<SystemController> CreateSystemController(const std::string& address)
{
    return std::make_shared<SystemControllerClient>(address);
}

} // namespace sushi_controller
