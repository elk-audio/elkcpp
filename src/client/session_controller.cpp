#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "session_controller.h"

namespace sushi_controller
{
SessionControllerClient::SessionControllerClient(const std::string& address)
    : _stub(sushi_rpc::SessionController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        ))) {}

std::pair<ControlStatus, std::string> SessionControllerClient::save_binary_session() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::SessionState response;
    grpc::ClientContext context;

    std::string binary_state;

    grpc::Status status = _stub->SaveSession(&context, request, &response);
    if(status.ok())
    {
        binary_state = response.SerializeAsString();
    }
    else
    {
        handle_error(status);
    }

    return {to_ext(status), binary_state};
}

ControlStatus SessionControllerClient::restore_binary_session(const std::string& binary_session)
{
    sushi_rpc::SessionState request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.ParseFromString(binary_session);
    grpc::Status status = _stub->RestoreSession(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::shared_ptr<SessionController> CreateSessionController(const std::string& server_address)
{
    return std::make_shared<SessionControllerClient>(server_address);
}
} // namespace sushi_controller
