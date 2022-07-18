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
    case MidiChannel::MIDI_CH_2:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_2;
    case MidiChannel::MIDI_CH_3:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_3;
    case MidiChannel::MIDI_CH_4:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_4;
    case MidiChannel::MIDI_CH_5:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_5;
    case MidiChannel::MIDI_CH_6:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_6;
    case MidiChannel::MIDI_CH_7:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_7;
    case MidiChannel::MIDI_CH_8:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_8;
    case MidiChannel::MIDI_CH_9:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_9;
    case MidiChannel::MIDI_CH_10:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_10;
    case MidiChannel::MIDI_CH_11:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_11;
    case MidiChannel::MIDI_CH_12:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_12;
    case MidiChannel::MIDI_CH_13:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_13;
    case MidiChannel::MIDI_CH_14:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_14;
    case MidiChannel::MIDI_CH_15:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_15;
    case MidiChannel::MIDI_CH_16:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_16;
    case MidiChannel::MIDI_CH_OMNI:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_OMNI;
    default:
        return sushi_rpc::MidiChannel_Channel_MIDI_CH_OMNI;
    }
}

inline MidiChannel to_ext(sushi_rpc::MidiChannel_Channel channel)
{
    switch (channel)
    {
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_1:
        return MidiChannel::MIDI_CH_1;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_2:
        return MidiChannel::MIDI_CH_2;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_3:
        return MidiChannel::MIDI_CH_3;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_4:
        return MidiChannel::MIDI_CH_4;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_5:
        return MidiChannel::MIDI_CH_5;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_6:
        return MidiChannel::MIDI_CH_6;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_7:
        return MidiChannel::MIDI_CH_7;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_8:
        return MidiChannel::MIDI_CH_8;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_9:
        return MidiChannel::MIDI_CH_9;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_10:
        return MidiChannel::MIDI_CH_10;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_11:
        return MidiChannel::MIDI_CH_11;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_12:
        return MidiChannel::MIDI_CH_12;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_13:
        return MidiChannel::MIDI_CH_13;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_14:
        return MidiChannel::MIDI_CH_14;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_15:
        return MidiChannel::MIDI_CH_15;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_16:
        return MidiChannel::MIDI_CH_16;
    case sushi_rpc::MidiChannel_Channel_MIDI_CH_OMNI:
        return MidiChannel::MIDI_CH_OMNI;
    default:
        return MidiChannel::MIDI_CH_OMNI;
    }
}

inline sushi_rpc::PluginType_Type to_grpc(PluginType type)
{
    switch (type)
    {
    case PluginType::INTERNAL:
        return sushi_rpc::PluginType_Type_INTERNAL;
    case PluginType::LV2:
        return sushi_rpc::PluginType_Type_LV2;
    case PluginType::VST2X:
        return sushi_rpc::PluginType_Type_VST2X;
    case PluginType::VST3X:
        return sushi_rpc::PluginType_Type_VST3X;
    default:
        return sushi_rpc::PluginType_Type_DUMMY;
    }
}

inline TrackUpdate::Action to_ext(sushi_rpc::TrackUpdate_Action action)
{
    switch (action)
    {
    case sushi_rpc::TrackUpdate_Action_TRACK_ADDED:
        return TrackUpdate::Action::TRACK_ADDED;
    case sushi_rpc::TrackUpdate_Action_TRACK_DELETED:
        return TrackUpdate::Action::TRACK_DELETED;
    default:
        return TrackUpdate::Action::TRACK_ADDED;
    }
}

inline sushi_rpc::TrackUpdate_Action to_grpc(TrackUpdate::Action action)
{
    switch (action)
    {
    case TrackUpdate::Action::TRACK_ADDED:
        return sushi_rpc::TrackUpdate_Action_TRACK_ADDED;
    case TrackUpdate::Action::TRACK_DELETED:
        return sushi_rpc::TrackUpdate_Action_TRACK_DELETED;
    default:
        return sushi_rpc::TrackUpdate_Action_DUMMY;
    }
}

inline ProcessorUpdate::Action to_ext(sushi_rpc::ProcessorUpdate_Action action)
{
    switch (action)
    {
    case sushi_rpc::ProcessorUpdate_Action_PROCESSOR_ADDED:
        return ProcessorUpdate::Action::PROCESSOR_ADDED;
    case sushi_rpc::ProcessorUpdate_Action_PROCESSOR_DELETED:
        return ProcessorUpdate::Action::PROCESSOR_DELETED;
    default:
        return ProcessorUpdate::Action::PROCESSOR_ADDED;
    }
}

inline sushi_rpc::ProcessorUpdate_Action to_grpc(ProcessorUpdate::Action action)
{
    switch (action)
    {
    case ProcessorUpdate::Action::PROCESSOR_ADDED:
        return sushi_rpc::ProcessorUpdate_Action_PROCESSOR_ADDED;
    case ProcessorUpdate::Action::PROCESSOR_DELETED:
        return sushi_rpc::ProcessorUpdate_Action_PROCESSOR_DELETED;
    default:
        return sushi_rpc::ProcessorUpdate_Action_DUMMY;
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

inline sushi_controller::TrackType to_ext(const sushi_rpc::TrackType::Type& type)
{
    switch(type)
    {
        case sushi_rpc::TrackType::REGULAR: return sushi_controller::TrackType::REGULAR;
        case sushi_rpc::TrackType::PRE:     return sushi_controller::TrackType::PRE;
        case sushi_rpc::TrackType::POST:    return sushi_controller::TrackType::POST;
        default:                            return sushi_controller::TrackType::REGULAR;
    }
}

inline sushi_rpc::TrackType::Type to_grpc(const sushi_controller::TrackType type)
{
    switch(type)
    {
        case sushi_controller::TrackType::REGULAR:  return sushi_rpc::TrackType::REGULAR;
        case sushi_controller::TrackType::PRE:      return sushi_rpc::TrackType::PRE;
        case sushi_controller::TrackType::POST:     return sushi_rpc::TrackType::POST;
        default:                                    return sushi_rpc::TrackType::REGULAR;
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
