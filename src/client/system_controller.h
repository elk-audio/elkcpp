#ifndef ELKCPP_SYSTEM_CONTROLLER_H
#define ELKCPP_SYSTEM_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller
{

class SystemControllerClient : public SystemController
{
public:
    SystemControllerClient(const std::string& address);

    /**
     * @brief Get the sushi version as a string
     *
     * @return std::pair<ControlStatus, std::string>
     */
    std::pair<ControlStatus, std::string> get_sushi_version() override;

    /**
     * @brief Get the info used for building sushi
     *
     * @return std::pair<ControlStatus, BuildInfo>
     */
    std::pair<ControlStatus, BuildInfo> get_build_info() override;

    /**
     * @brief Get the number of input channels available to sushi
     *
     * @return std::pair<ControlStatus, int>
     */
    std::pair<ControlStatus, int> get_input_audio_channel_count() override;

    /**
     * @brief Get the number of output channels available to sushi
     *
     * @return std::pair<ControlStatus, int>
     */
    std::pair<ControlStatus, int> get_output_audio_channel_count() override;

private:
    std::unique_ptr<sushi_rpc::SystemController::Stub> _stub;
};
} // namespace sushi_controller


#endif // ELKCPP_SYSTEM_CONTROLLER_H
