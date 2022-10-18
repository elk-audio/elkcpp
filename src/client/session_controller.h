#ifndef ELKCPP_SESSION_CONTROLLER_H
#define ELKCPP_SESSION_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller {

class SessionControllerClient : public SessionController
{
public:
    SessionControllerClient(const std::string& address);

    /**
     * @brief Save the entire sushi session.
     * @return An std::pair<ControlStatus, std::string> string containing the Sushi session
     *         in a serialized format if ControlStatus == OK, empty string otherwise.
     */
    std::pair<ControlStatus, std::string> save_binary_session() const override;

    /**
     * @brief Restore the sushi session from a previously save session state.
     *        This will clear all track and loaded plugins
     * @param binary_session An std::string string containing the serialised Sushi session
     * @return ControlStatus::OK if operation was successful.
     */
    ControlStatus restore_binary_session(const std::string& binary_session) override;


protected:
    std::unique_ptr<sushi_rpc::SessionController::Stub> _stub;
};
} // namespace sushi_controller

#endif //ELKCPP_SESSION_CONTROLLER_H
