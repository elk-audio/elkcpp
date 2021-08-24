#ifndef ELKCPP_GRPC_UTILS_H
#define ELKCPP_GRPC_UTILS_H

#include "sushi_rpc.grpc.pb.h"
#include "control_interface.h"

namespace sushi_controller
{

inline sushi_rpc::MidiChannel_Channel to_grpc(MidiChannel channel)
{
    switch (channel)
    {
    case MidiChannel::MIDI_CH_1:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_1;
        break;
    case MidiChannel::MIDI_CH_2:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_2;
        break;
    case MidiChannel::MIDI_CH_3:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_3;
        break;
    case MidiChannel::MIDI_CH_4:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_4;
        break;
    case MidiChannel::MIDI_CH_5:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_5;
        break;
    case MidiChannel::MIDI_CH_6:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_6;
        break;
    case MidiChannel::MIDI_CH_7:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_7;
        break;
    case MidiChannel::MIDI_CH_8:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_8;
        break;
    case MidiChannel::MIDI_CH_9:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_9;
        break;
    case MidiChannel::MIDI_CH_10:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_10;
        break;
    case MidiChannel::MIDI_CH_11:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_11;
        break;
    case MidiChannel::MIDI_CH_12:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_12;
        break;
    case MidiChannel::MIDI_CH_13:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_13;
        break;
    case MidiChannel::MIDI_CH_14:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_14;
        break;
    case MidiChannel::MIDI_CH_15:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_15;
        break;
    case MidiChannel::MIDI_CH_16:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_16;
        break;
    case MidiChannel::MIDI_CH_OMNI:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_OMNI;
        break;
    default:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_OMNI;
        break;
    }
}

inline MidiChannel to_ext(sushi_rpc::MidiChannel_Channel channel)
{
    switch (channel)
    {
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_1:
        return MidiChannel::MIDI_CH_1;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_2:
        return MidiChannel::MIDI_CH_2;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_3:
        return MidiChannel::MIDI_CH_3;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_4:
        return MidiChannel::MIDI_CH_4;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_5:
        return MidiChannel::MIDI_CH_5;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_6:
        return MidiChannel::MIDI_CH_6;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_7:
        return MidiChannel::MIDI_CH_7;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_8:
        return MidiChannel::MIDI_CH_8;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_9:
        return MidiChannel::MIDI_CH_9;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_10:
        return MidiChannel::MIDI_CH_10;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_11:
        return MidiChannel::MIDI_CH_11;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_12:
        return MidiChannel::MIDI_CH_12;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_13:
        return MidiChannel::MIDI_CH_13;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_14:
        return MidiChannel::MIDI_CH_14;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_15:
        return MidiChannel::MIDI_CH_15;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_16:
        return MidiChannel::MIDI_CH_16;
        break;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_OMNI:
        return MidiChannel::MIDI_CH_OMNI;
        break;
    default:
        return MidiChannel::MIDI_CH_OMNI;
        break;
    }
}

inline sushi_rpc::PluginType_Type to_grpc(PluginType type)
{
    switch (type)
    {
    case PluginType::INTERNAL:
        return sushi_rpc::PluginType_Type_INTERNAL;
        break;
    case PluginType::LV2:
        return sushi_rpc::PluginType_Type_LV2;
        break;
    case PluginType::VST2X:
        return sushi_rpc::PluginType_Type_VST2X;
        break;
    case PluginType::VST3X:
        return sushi_rpc::PluginType_Type_VST3X;
        break;
    default:
        return sushi_rpc::PluginType_Type_DUMMY;
        break;
    }
}

inline TrackUpdate::Action to_ext(sushi_rpc::TrackUpdate_Action action)
{
    switch (action)
    {
    case sushi_rpc::TrackUpdate_Action_TRACK_ADDED:
        return TrackUpdate::Action::TRACK_ADDED;
        break;
    case sushi_rpc::TrackUpdate_Action_TRACK_DELETED:
        return TrackUpdate::Action::TRACK_DELETED;
        break;
    default:
        return TrackUpdate::Action::TRACK_ADDED;
        break;
    }
}

inline sushi_rpc::TrackUpdate_Action to_grpc(TrackUpdate::Action action)
{
    switch (action)
    {
    case TrackUpdate::Action::TRACK_ADDED:
        return sushi_rpc::TrackUpdate_Action_TRACK_ADDED;
        break;
    case TrackUpdate::Action::TRACK_DELETED:
        return sushi_rpc::TrackUpdate_Action_TRACK_DELETED;
        break;
    default:
        return sushi_rpc::TrackUpdate_Action_DUMMY;
        break;
    }
}

inline ProcessorUpdate::Action to_ext(sushi_rpc::ProcessorUpdate_Action action)
{
    switch (action)
    {
    case sushi_rpc::ProcessorUpdate_Action_PROCESSOR_ADDED:
        return ProcessorUpdate::Action::PROCESSOR_ADDED;
        break;
    case sushi_rpc::ProcessorUpdate_Action_PROCESSOR_DELETED:
        return ProcessorUpdate::Action::PROCESSOR_DELETED;
        break;
    default:
        return ProcessorUpdate::Action::PROCESSOR_ADDED;
        break;
    }
}

inline sushi_rpc::ProcessorUpdate_Action to_grpc(ProcessorUpdate::Action action)
{
    switch (action)
    {
    case ProcessorUpdate::Action::PROCESSOR_ADDED:
        return sushi_rpc::ProcessorUpdate_Action_PROCESSOR_ADDED;
        break;
    case ProcessorUpdate::Action::PROCESSOR_DELETED:
        return sushi_rpc::ProcessorUpdate_Action_PROCESSOR_DELETED;
        break;
    default:
        return sushi_rpc::ProcessorUpdate_Action_DUMMY;
        break;
    }
}

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

inline sushi_controller::ControlStatus to_ext(const grpc::Status& status)
{
    switch(status.error_code())
    {
        case grpc::StatusCode::OK:                  return sushi_controller::ControlStatus::OK;
        case grpc::StatusCode::UNKNOWN:             return sushi_controller::ControlStatus::ERROR;
        case grpc::StatusCode::FAILED_PRECONDITION: return sushi_controller::ControlStatus::UNSUPPORTED_OPERATION;
        case grpc::StatusCode::NOT_FOUND:           return sushi_controller::ControlStatus::NOT_FOUND;
        case grpc::StatusCode::OUT_OF_RANGE:        return sushi_controller::ControlStatus::OUT_OF_RANGE;
        case grpc::StatusCode::INVALID_ARGUMENT:    return sushi_controller::ControlStatus::INVALID_ARGUMENTS;
        case grpc::StatusCode::UNAVAILABLE:         return sushi_controller::ControlStatus::UNAVAILABLE;
        case grpc::StatusCode::UNAUTHENTICATED:     return sushi_controller::ControlStatus::UNAUTHENTICATED;
        default:                                    return sushi_controller::ControlStatus::ERROR;
    }
}

inline std::string to_str(const sushi_controller::ControlStatus& code)
{
    switch(code)
    {
        case sushi_controller::ControlStatus::OK: return "OK";
        case sushi_controller::ControlStatus::ERROR: return "ERROR";
        case sushi_controller::ControlStatus::UNSUPPORTED_OPERATION: return "UNSUPPORTED OPERATION";
        case sushi_controller::ControlStatus::NOT_FOUND: return "NOT FOUND";
        case sushi_controller::ControlStatus::OUT_OF_RANGE: return "OUT OF RANGE";
        case sushi_controller::ControlStatus::INVALID_ARGUMENTS: return "INVALID ARGUMENTS";
        case sushi_controller::ControlStatus::UNAVAILABLE: return "UNAVAILABLE";
        case sushi_controller::ControlStatus::UNAUTHENTICATED: return "UNAUTHENTICATED";
        default: return "ERROR";
    }
}

inline void handle_error([[maybe_unused]] grpc::Status status)
{
#ifdef SUSHI_CONTROLLER_PRINT_ERRORS
    std::cout << "Sushi controller error: " << to_str(to_ext(status)) << ", " << status.error_message() << std::endl;
#endif
}

} // namespace sushi_controller



#endif // ELKCPP_GRPC_UTILS_H
