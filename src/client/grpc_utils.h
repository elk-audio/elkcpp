#ifndef ELKCPP_GRPC_UTILS_H
#define ELKCPP_GRPC_UTILS_H

#include "sushi_rpc.grpc.pb.h"
#include "control_interface.h"

namespace sushi_controller
{

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
