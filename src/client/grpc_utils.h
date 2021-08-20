#ifndef ELKCPP_GRPC_UTILS_H
#define ELKCPP_GRPC_UTILS_H

#include "sushi_rpc.grpc.pb.h"
#include "control_interface.h"

namespace sushi_controller
{

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
