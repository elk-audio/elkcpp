#include "sushi_grpc_client.h"

inline void print_status(grpc::Status status)
{
    std::cout << status.error_code() << ": " << status.error_message() << std::endl;
}

inline sushi_controller::PlayingMode to_ext(const sushi_rpc::PlayingMode::Mode mode)
{
    switch(mode)
    {
        case sushi_rpc::PlayingMode::STOPPED:   return sushi_controller::PlayingMode::STOPPED;
        case sushi_rpc::PlayingMode::PLAYING:   return sushi_controller::PlayingMode::PLAYING;
        case sushi_rpc::PlayingMode::RECORDING: return sushi_controller::PlayingMode::RECORDING;
        default:                                return sushi_controller::PlayingMode::PLAYING;
    }
}

inline sushi_rpc::PlayingMode::Mode to_grpc(const sushi_controller::PlayingMode mode)
{
    switch(mode)
    {
        case sushi_controller::PlayingMode::STOPPED:   return sushi_rpc::PlayingMode::STOPPED;
        case sushi_controller::PlayingMode::PLAYING:   return sushi_rpc::PlayingMode::PLAYING;
        case sushi_controller::PlayingMode::RECORDING: return sushi_rpc::PlayingMode::RECORDING;
        default:                                       return sushi_rpc::PlayingMode::PLAYING;
    }
}


inline sushi_controller::SyncMode to_ext(const sushi_rpc::SyncMode::Mode mode)
{
    switch(mode)
    {
        case sushi_rpc::SyncMode::INTERNAL:   return sushi_controller::SyncMode::INTERNAL;
        case sushi_rpc::SyncMode::MIDI:       return sushi_controller::SyncMode::MIDI;
        case sushi_rpc::SyncMode::LINK:       return sushi_controller::SyncMode::LINK;
        default:                              return sushi_controller::SyncMode::INTERNAL;
    }
}

namespace sushi_controller
{

SushiControllerClient::SushiControllerClient(std::string address)
    : _stub(sushi_rpc::SushiController::NewStub(
        grpc::CreateChannel(
            address, 
            grpc::InsecureChannelCredentials()
        )))
{
}

float SushiControllerClient::get_samplerate() const
{   
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericFloatValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetSamplerate(&context, request, &response);
    
    if (status.ok())
    {
        return response.value();
    }
    else
    {
        print_status(status);
        return -1;
    }
    
}

PlayingMode SushiControllerClient::get_playing_mode() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::PlayingMode response;
    grpc::ClientContext context;
    
    grpc::Status status = _stub.get()->GetPlayingMode(&context, request, &response);

    if (status.ok())
    {
        return to_ext(response.mode());
    }
    else
    {
        print_status(status);
        return PlayingMode::STOPPED;
    }
}

void SushiControllerClient::set_playing_mode(PlayingMode playing_mode)
{
    sushi_rpc::PlayingMode request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_mode(to_grpc(playing_mode));

    grpc::Status status = _stub.get()->SetPlayingMode(&context, request, &response);

    if (!status.ok())
    {
        print_status(status);
    }
}

SyncMode SushiControllerClient::get_sync_mode() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::SyncMode response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetSyncMode(&context, request, &response);

    if (status.ok())
    {
        return to_ext(response.mode());
    }
    else
    {
        print_status(status);
        return SyncMode::INTERNAL;
    }
}

} //sushi_controller