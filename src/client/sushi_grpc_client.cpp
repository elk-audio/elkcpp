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

inline sushi_controller::ControlStatus to_ext(const grpc::Status status)
{
    switch(status.error_code())
    {
        case grpc::StatusCode::OK:                  return sushi_controller::ControlStatus::OK;
        case grpc::StatusCode::UNKNOWN:             return sushi_controller::ControlStatus::ERROR;
        case grpc::StatusCode::FAILED_PRECONDITION: return sushi_controller::ControlStatus::UNSUPPORTED_OPERATION;
        case grpc::StatusCode::NOT_FOUND:           return sushi_controller::ControlStatus::NOT_FOUND;
        case grpc::StatusCode::OUT_OF_RANGE:        return sushi_controller::ControlStatus::OUT_OF_RANGE;
        case grpc::StatusCode::INVALID_ARGUMENT:    return sushi_controller::ControlStatus::INVALID_ARGUMENTS;
        default:                                    return sushi_controller::ControlStatus::ERROR;
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

void SushiControllerClient::set_sync_mode(SyncMode mode)
{
    sushi_rpc::SyncMode request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_mode(to_grpc(mode));

    grpc::Status status = _stub.get()->SetSyncMode(&context, request, &response);

    if (!status.ok())
    {
        print_status(status);
    }
}

float SushiControllerClient::get_tempo() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericFloatValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetTempo(&context, request, &response);

    if (status.ok())
    {
        return response.value();
    }
    else
    {
        print_status(status);
        return -1.0f;
    }
}

ControlStatus SushiControllerClient::set_tempo(float tempo)
{
    sushi_rpc::GenericFloatValue request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_value(tempo);

    grpc::Status status = _stub.get()->SetTempo(&context, request, &response);

    if (status.ok())
    {
        return ControlStatus::OK;
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
}

TimeSignature SushiControllerClient::get_time_signature() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::TimeSignature response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetTimeSignature(&context, request, &response);

    if (status.ok())
    {
        return TimeSignature{response.numerator(), response.denominator()};
    }
    else
    {
        print_status(status);
        return TimeSignature{-1,-1};
    }
}

ControlStatus SushiControllerClient::set_time_signature(TimeSignature time_signature)
{
    sushi_rpc::TimeSignature request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_numerator(time_signature.numerator);
    request.set_denominator(time_signature.denominator);

    grpc::Status status = _stub.get()->SetTimeSignature(&context, request, &response);

    if (status.ok())
    {
        return ControlStatus::OK;
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
}

std::vector<TrackInfo> SushiControllerClient::get_tracks() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::TrackInfoList response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetTracks(&context, request, &response);

    if(status.ok())
    {
        std::vector<TrackInfo> output;
        for(int i = 0; i < response.tracks_size(); ++i)
        {
            output.push_back(
                TrackInfo{
                    response.tracks(i).id(),
                    response.tracks(i).label(),
                    response.tracks(i).name(),
                    response.tracks(i).input_channels(),
                    response.tracks(i).input_busses(),
                    response.tracks(i).output_channels(),
                    response.tracks(i).output_busses(),
                    response.tracks(i).processor_count()
                }
            );
        }
        return output;
    }
    else
    {
        print_status(status);
        return std::vector<TrackInfo>();
    }    
}

//====================//
//  Keyboard Control  //
//====================//

ControlStatus SushiControllerClient::send_note_on(int track_id, int channel, int note, float velocity)
{
    sushi_rpc::NoteOnRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;
    
    request.mutable_track()->set_id(track_id);
    request.set_channel(channel);
    request.set_note(note);
    request.set_velocity(velocity);

    grpc::Status status = _stub.get()->SendNoteOn(&context, request, &response);

    if(status.ok())
    {
        return ControlStatus::OK;
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
}

ControlStatus SushiControllerClient::send_note_off(int track_id, int channel, int note, float velocity)
{
    sushi_rpc::NoteOffRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_track()->set_id(track_id);
    request.set_channel(channel);
    request.set_note(note);
    request.set_velocity(velocity);

    grpc::Status status = _stub.get()->SendNoteOff(&context, request, &response);

    if(status.ok())
    {
        return ControlStatus::OK;
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
}

ControlStatus SushiControllerClient::send_note_aftertouch(int track_id, int channel, int note, float value)
{
    sushi_rpc::NoteAftertouchRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_track()->set_id(track_id);
    request.set_channel(channel);
    request.set_note(note);
    request.set_value(value);

    grpc::Status status = _stub.get()->SendNoteAftertouch(&context, request, &response);

    if(status.ok())
    {
        return ControlStatus::OK;
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
}

ControlStatus SushiControllerClient::send_aftertouch(int track_id, int channel, float value)
{
    sushi_rpc::NoteModulationRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_track()->set_id(track_id);
    request.set_channel(channel);
    request.set_value(value);

    grpc::Status status = _stub.get()->SendAftertouch(&context, request, &response);

    if(status.ok())
    {
        return ControlStatus::OK;
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
}

ControlStatus SushiControllerClient::send_pitch_bend(int track_id, int channel, float value)
{
    sushi_rpc::NoteModulationRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_track()->set_id(track_id);
    request.set_channel(channel);
    request.set_value(value);

    grpc::Status status = _stub.get()->SendPitchBend(&context, request, &response);

    if(status.ok())
    {
        return ControlStatus::OK;
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
}

ControlStatus SushiControllerClient::send_modulation(int track_id, int channel, float value)
{
    sushi_rpc::NoteModulationRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_track()->set_id(track_id);
    request.set_channel(channel);
    request.set_value(value);

    grpc::Status status = _stub.get()->SendModulation(&context, request, &response);

    if(status.ok())
    {
        return ControlStatus::OK;
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
}

} //sushi_controller