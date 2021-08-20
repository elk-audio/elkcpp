#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "timing_controller.h"

namespace sushi_controller
{

TimingControllerClient::TimingControllerClient(const std::string& address)
    : _stub(sushi_rpc::TimingController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        ))) {}

std::pair<ControlStatus, bool> TimingControllerClient::get_timings_enabled() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericBoolValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetTimingsEnabled(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, bool>(to_ext(status), response.value());
}

ControlStatus TimingControllerClient::set_timings_enabled(bool enabled)
{
    sushi_rpc::GenericBoolValue request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_value(enabled);

    grpc::Status status = _stub.get()->SetTimingsEnabled(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::pair<ControlStatus, CpuTimings> TimingControllerClient::get_engine_timings() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::CpuTimings response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetEngineTimings(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, CpuTimings>(to_ext(status),CpuTimings{response.average(),response.min(),response.max()});
}

std::pair<ControlStatus, CpuTimings> TimingControllerClient::get_track_timings(int track_id) const
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::CpuTimings response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub.get()->GetTrackTimings(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, CpuTimings>(to_ext(status),CpuTimings{response.average(),response.min(),response.max()});
}

std::pair<ControlStatus, CpuTimings> TimingControllerClient::get_processor_timings(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::CpuTimings response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorTimings(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, CpuTimings>(to_ext(status),CpuTimings{response.average(),response.min(),response.max()});
}

ControlStatus TimingControllerClient::reset_all_timings()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->ResetAllTimings(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus TimingControllerClient::reset_track_timings(int track_id)
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub.get()->ResetTrackTimings(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus TimingControllerClient::reset_processor_timings(int processor_id)
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->ResetProcessorTimings(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::shared_ptr<TimingController> CreateTimingController(const std::string& server_address)
{
    return std::move(std::make_shared<TimingControllerClient>(server_address));
}

} // namespace sushi_controller

