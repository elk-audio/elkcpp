#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "transport_controller.h"

namespace sushi_controller
{

inline sushi_controller::PlayingMode to_ext(const sushi_rpc::PlayingMode::Mode& mode)
{
    switch(mode)
    {
        case sushi_rpc::PlayingMode::STOPPED:   return sushi_controller::PlayingMode::STOPPED;
        case sushi_rpc::PlayingMode::PLAYING:   return sushi_controller::PlayingMode::PLAYING;
        case sushi_rpc::PlayingMode::RECORDING: return sushi_controller::PlayingMode::RECORDING;
        default:                                return sushi_controller::PlayingMode::PLAYING;
    }
}

inline sushi_rpc::PlayingMode::Mode to_grpc(const sushi_controller::PlayingMode& mode)
{
    switch(mode)
    {
        case sushi_controller::PlayingMode::STOPPED:   return sushi_rpc::PlayingMode::STOPPED;
        case sushi_controller::PlayingMode::PLAYING:   return sushi_rpc::PlayingMode::PLAYING;
        case sushi_controller::PlayingMode::RECORDING: return sushi_rpc::PlayingMode::RECORDING;
        default:                                       return sushi_rpc::PlayingMode::PLAYING;
    }
}

inline sushi_controller::SyncMode to_ext(const sushi_rpc::SyncMode::Mode& mode)
{
    switch(mode)
    {
        case sushi_rpc::SyncMode::INTERNAL:   return sushi_controller::SyncMode::INTERNAL;
        case sushi_rpc::SyncMode::MIDI:       return sushi_controller::SyncMode::MIDI;
        case sushi_rpc::SyncMode::LINK:       return sushi_controller::SyncMode::LINK;
        default:                              return sushi_controller::SyncMode::INTERNAL;
    }
}

inline sushi_rpc::SyncMode::Mode to_grpc(const sushi_controller::SyncMode mode)
{
    switch(mode)
    {
        case sushi_controller::SyncMode::INTERNAL:   return sushi_rpc::SyncMode::INTERNAL;
        case sushi_controller::SyncMode::MIDI:       return sushi_rpc::SyncMode::MIDI;
        case sushi_controller::SyncMode::LINK:       return sushi_rpc::SyncMode::LINK;
        default:                              return sushi_rpc::SyncMode::INTERNAL;
    }
}

TransportControllerClient::TransportControllerClient(const std::string& address)
    : _stub(sushi_rpc::TransportController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        ))) {}

std::pair<ControlStatus, float> TransportControllerClient::get_samplerate() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericFloatValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetSamplerate(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, float>(to_ext(status),response.value());
}

std::pair<ControlStatus, PlayingMode> TransportControllerClient::get_playing_mode() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::PlayingMode response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetPlayingMode(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, PlayingMode>(to_ext(status), to_ext(response.mode()));
}

ControlStatus TransportControllerClient::set_playing_mode(PlayingMode playing_mode)
{
    sushi_rpc::PlayingMode request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_mode(to_grpc(playing_mode));

    grpc::Status status = _stub.get()->SetPlayingMode(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::pair<ControlStatus, SyncMode> TransportControllerClient::get_sync_mode() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::SyncMode response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetSyncMode(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, SyncMode>(to_ext(status), to_ext(response.mode()));
}

ControlStatus TransportControllerClient::set_sync_mode(SyncMode mode)
{
    sushi_rpc::SyncMode request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_mode(to_grpc(mode));

    grpc::Status status = _stub.get()->SetSyncMode(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::pair<ControlStatus, float> TransportControllerClient::get_tempo() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericFloatValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetTempo(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, float>(to_ext(status), response.value());
}

ControlStatus TransportControllerClient::set_tempo(float tempo)
{
    sushi_rpc::GenericFloatValue request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_value(tempo);

    grpc::Status status = _stub.get()->SetTempo(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::pair<ControlStatus, TimeSignature> TransportControllerClient::get_time_signature() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::TimeSignature response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetTimeSignature(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, TimeSignature>(to_ext(status), TimeSignature{response.numerator(), response.denominator()});
}

ControlStatus TransportControllerClient::set_time_signature(TimeSignature time_signature)
{
    sushi_rpc::TimeSignature request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_numerator(time_signature.numerator);
    request.set_denominator(time_signature.denominator);

    grpc::Status status = _stub.get()->SetTimeSignature(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::shared_ptr<TransportController> CreateTransportController(const std::string& server_address)
{
    return std::move(std::make_shared<TransportControllerClient>(server_address));
}

} // namespace sushi_controller

