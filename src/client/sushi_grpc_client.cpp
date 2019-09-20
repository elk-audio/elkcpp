#include "sushi_grpc_client.h"

inline void print_status(grpc::Status status)
{
    std::cout << status.error_code() << ": " << status.error_message() << std::endl;
}

inline sushi_controller::PlayingMode to_ext(sushi_rpc::PlayingMode::Mode playing_mode)
{
    switch(playing_mode)
    {
        case sushi_rpc::PlayingMode::STOPPED:   return sushi_controller::PlayingMode::STOPPED;
        case sushi_rpc::PlayingMode::PLAYING:   return sushi_controller::PlayingMode::PLAYING;
        case sushi_rpc::PlayingMode::RECORDING: return sushi_controller::PlayingMode::RECORDING;
        default: return sushi_controller::PlayingMode::STOPPED;
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
        return sushi_controller::PlayingMode::STOPPED;
    }
    
    return PlayingMode::RECORDING;
}

} //sushi_controller