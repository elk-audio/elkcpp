#include "sushi_grpc_client.h"

inline void print_status(grpc::Status status)
{
    std::cout << status.error_code() << ": " << status.error_message() << std::endl;
}

inline sushi_controller::ParameterType to_ext(const sushi_rpc::ParameterType::Type type)
{
    switch (type)
    {
        case sushi_rpc::ParameterType::INT:             return sushi_controller::ParameterType::INT;
        case sushi_rpc::ParameterType::FLOAT:           return sushi_controller::ParameterType::FLOAT;
        case sushi_rpc::ParameterType::BOOL:            return sushi_controller::ParameterType::BOOL;
        case sushi_rpc::ParameterType::STRING_PROPERTY: return sushi_controller::ParameterType::STRING_PROPERTY;
        case sushi_rpc::ParameterType::DATA_PROPERTY:   return sushi_controller::ParameterType::DATA_PROPERTY;
        default:                                        return sushi_controller::ParameterType::INT;
    }
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
        return to_ext(status);
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
        return to_ext(status);
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
        return to_ext(status);
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
        return to_ext(status);
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
        return to_ext(status);
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
        return to_ext(status);
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
        return to_ext(status);
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
        return to_ext(status);
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
}

//===============//
//  CPU Timings  //
//===============//

std::pair<ControlStatus, CpuTimings> SushiControllerClient::get_engine_timings() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::CpuTimings response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetEngineTimings(&context, request, &response);

    if(status.ok())
    {
        return std::pair<ControlStatus, CpuTimings>(to_ext(status),CpuTimings{response.average(),response.min(),response.max()});
    }
    else
    {
        return std::pair<ControlStatus, CpuTimings>(to_ext(status),CpuTimings{-1.0f,-1.0f,-1.0f});
    }  
}

std::pair<ControlStatus, CpuTimings> SushiControllerClient::get_track_timings(int track_id) const
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::CpuTimings response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub.get()->GetTrackTimings(&context, request, &response);

    if(status.ok())
    {
        return std::pair<ControlStatus, CpuTimings>(to_ext(status),CpuTimings{response.average(),response.min(),response.max()});
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, CpuTimings>(to_ext(status),CpuTimings{-1.0f,-1.0f,-1.0f});
    }  
}

std::pair<ControlStatus, CpuTimings> SushiControllerClient::get_processor_timings(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::CpuTimings response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorTimings(&context, request, &response);

    if(status.ok())
    {
        return std::pair<ControlStatus, CpuTimings>(to_ext(status),CpuTimings{response.average(),response.min(),response.max()});
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, CpuTimings>(to_ext(status),CpuTimings{-1.0f,-1.0f,-1.0f});
    }  
}

ControlStatus SushiControllerClient::reset_all_timings()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->ResetAllTimings(&context, request, &response);

    if(status.ok())
    {
        return to_ext(status);
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
    
}

ControlStatus SushiControllerClient::reset_track_timings(int track_id)
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub.get()->ResetTrackTimings(&context, request, &response);

    if(status.ok())
    {
        return to_ext(status);
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
    
}

ControlStatus SushiControllerClient::reset_processor_timings(int processor_id)
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->ResetProcessorTimings(&context, request, &response);

    if(status.ok())
    {
        return to_ext(status);
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
    
}

//=================//
//  Track control  //
//=================//

std::pair<ControlStatus, int> SushiControllerClient::get_track_id(const std::string& track_name) const
{
    sushi_rpc::GenericStringValue request;
    sushi_rpc::TrackIdentifier response;
    grpc::ClientContext context;

    request.set_value(track_name);

    grpc::Status status = _stub.get()->GetTrackId(&context, request, &response);

    if(status.ok())
    {
        return std::pair<ControlStatus, int>(to_ext(status), response.id());
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, int>(to_ext(status), -1);
    }
}

std::pair<ControlStatus, TrackInfo> SushiControllerClient::get_track_info(int track_id) const
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::TrackInfo response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub.get()->GetTrackInfo(&context, request, &response);

    if(status.ok())
    {
        return std::pair<ControlStatus, TrackInfo>(to_ext(status), TrackInfo{response.id(), 
                                                                             response.label(), 
                                                                             response.name(),
                                                                             response.input_channels(),
                                                                             response.input_busses(),
                                                                             response.output_channels(),
                                                                             response.output_busses(),
                                                                             response.processor_count()});
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, TrackInfo>(to_ext(status), TrackInfo());
    }
    
}

std::pair<ControlStatus, std::vector<ProcessorInfo>> SushiControllerClient::get_track_processors(int track_id) const
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::ProcessorInfoList response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub.get()->GetTrackProcessors(&context, request, &response);

    if(status.ok())
    {
        std::vector<ProcessorInfo> output;
        for (int i = 0; i < response.processors_size(); ++i)
        {
            output.push_back(ProcessorInfo{
                response.processors(i).id(),
                response.processors(i).label(),
                response.processors(i).name(),
                response.processors(i).parameter_count(),
                response.processors(i).program_count()
            });
        }
        return std::pair<ControlStatus, std::vector<ProcessorInfo>>(to_ext(status),output);
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, std::vector<ProcessorInfo>>(to_ext(status),std::vector<ProcessorInfo>());
    }
}

std::pair<ControlStatus, std::vector<ParameterInfo>> SushiControllerClient::get_track_parameters(int track_id) const
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::ParameterInfoList response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub.get()->GetTrackParameters(&context, request, &response);

    if(status.ok())
    {
        std::vector<ParameterInfo> output;
        for (int i = 0; i < response.parameters_size(); ++i)
        {
            output.push_back(ParameterInfo{
                response.parameters(i).id(),
                to_ext(response.parameters(i).type().type()),
                response.parameters(i).label(),
                response.parameters(i).name(),
                response.parameters(i).unit(),
                response.parameters(i).automatable(),
                response.parameters(i).min_range(),
                response.parameters(i).max_range()
            });
        }
        return std::pair<ControlStatus, std::vector<ParameterInfo>>(to_ext(status), output);
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, std::vector<ParameterInfo>>(to_ext(status), std::vector<ParameterInfo>());
    }
    
}

//=====================//
//  Processor control  //
//=====================//

std::pair<ControlStatus, int> SushiControllerClient::get_processor_id(const std::string& processor_name) const
{
    sushi_rpc::GenericStringValue request;
    sushi_rpc::ProcessorIdentifier response;
    grpc::ClientContext context;

    request.set_value(processor_name);

    grpc::Status status = _stub.get()->GetProcessorId(&context, request, &response);

    if (status.ok())
    {
        return std::pair<ControlStatus, int>(to_ext(status), response.id());
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, int>(to_ext(status),-1);
    }
}

std::pair<ControlStatus, ProcessorInfo> SushiControllerClient::get_processor_info(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::ProcessorInfo response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorInfo(&context, request, &response);

    if(status.ok())
    {
        ProcessorInfo output;
        output.id = response.id();
        output.label = response.label();
        output.name = response.name();
        output.parameter_count = response.parameter_count();
        output.program_count = response.program_count();
        return std::pair<ControlStatus, ProcessorInfo>(to_ext(status), output);
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, ProcessorInfo>(to_ext(status), ProcessorInfo());
    }
    
}

std::pair<ControlStatus, bool> SushiControllerClient::get_processor_bypass_state(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericBoolValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorBypassState(&context, request, &response);

    if(status.ok())
    {
        return std::pair<ControlStatus, bool>(to_ext(status), response.value());
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, bool>(to_ext(status), false);
    }
}

ControlStatus SushiControllerClient::set_processor_bypass_state(int processor_id, bool bypass_enabled)
{
    sushi_rpc::ProcessorBypassStateSetRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.set_value(bypass_enabled);

    grpc::Status status = _stub.get()->SetProcessorBypassState(&context, request, &response);

    if(status.ok())
    {
        return to_ext(status);
    }
    else
    {
        return to_ext(status);
    }
}

std::pair<ControlStatus, int> SushiControllerClient::get_processor_current_program(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::ProgramIdentifier response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorCurrentProgram(&context, request, &response);

    if(status.ok())
    {
        return std::pair<ControlStatus, int>(to_ext(status), response.program());
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, int>(to_ext(status), -1);
    }
    
}

std::pair<ControlStatus, std::string> SushiControllerClient::get_processor_current_program_name(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericStringValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorCurrentProgramName(&context, request, &response);

    if(status.ok())
    {
        return std::pair<ControlStatus, std::string>(to_ext(status), response.value());
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, std::string>(to_ext(status), "");
    }
    
}

std::pair<ControlStatus, std::string> SushiControllerClient::get_processor_program_name(int processor_id, int program_id) const
{
    sushi_rpc::ProcessorProgramIdentifier request;
    sushi_rpc::GenericStringValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.set_program(program_id);

    grpc::Status status = _stub.get()->GetProcessorProgramName(&context, request, &response);

    if(status.ok())
    {
        return std::pair<ControlStatus, std::string>(to_ext(status), response.value());
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, std::string>(to_ext(status), "");
    }
    
}

std::pair<ControlStatus, std::vector<std::string>> SushiControllerClient::get_processor_programs(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::ProgramInfoList response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorPrograms(&context, request, &response);

    if(status.ok())
    {
        std::vector<std::string> output;
        for (int i = 0; i < response.programs_size(); ++i)
        {
            output.push_back(response.programs(i).name());
        }
        return std::pair<ControlStatus, std::vector<std::string>>(to_ext(status), output);
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, std::vector<std::string>>(to_ext(status), std::vector<std::string>());
    }
    
}

ControlStatus SushiControllerClient::set_processor_program(int processor_id, int program_id)
{
    sushi_rpc::ProcessorProgramSetRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.mutable_program()->set_program(program_id);

    grpc::Status status = _stub.get()->SetProcessorProgram(&context, request, &response);

    if(status.ok())
    {
        return to_ext(status);
    }
    else
    {
        print_status(status);
        return to_ext(status);
    }
   
}

std::pair<ControlStatus, std::vector<ParameterInfo>> SushiControllerClient::get_processor_parameters(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::ParameterInfoList response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorParameters(&context, request, &response);

    if(status.ok())
    {
        std::vector<ParameterInfo> output;
        for(int i = 0; i < response.parameters_size(); ++i)
        {
            output.push_back(
                ParameterInfo{
                    response.parameters(i).id(),
                    to_ext(response.parameters(i).type().type()),
                    response.parameters(i).label(),
                    response.parameters(i).name(),
                    response.parameters(i).unit(),
                    response.parameters(i).automatable(),
                    response.parameters(i).min_range(),
                    response.parameters(i).max_range()
                }
            );
        }
        return std::pair<ControlStatus, std::vector<ParameterInfo>>(to_ext(status), output);
    }
    else
    {
        print_status(status);
        return std::pair<ControlStatus, std::vector<ParameterInfo>>(to_ext(status), std::vector<ParameterInfo>());
    }
    
}

} //sushi_controller