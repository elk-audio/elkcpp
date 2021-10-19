#ifndef ELKCPP_OSC_CONTROLLER_H
#define ELKCPP_OSC_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller
{

class OscControllerClient : public OscController
{
public:
    OscControllerClient(const std::string& address);

    /**
     * @brief Get the port osc is sent to
     *
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_send_port() const override;

    /**
     * @brief Get the port osc is received on
     *
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_receive_port() const override;

    /**
     * @brief Get the enabled parameter output osc addresses
     *
     * @return std::pair<ControlStatus, std::vector<std::string>>
     */
    virtual std::pair<ControlStatus, std::vector<std::string>> get_enabled_parameter_outputs() const override;

    /**
     * @brief Enable osc output for a parameter
     *
     * @param processor_id The id of the processor the parameter belongs to
     * @param parameter_id The id of the parameter to output as osc
     * @return ControlStatus
     */
    virtual ControlStatus enable_output_for_parameter(int processor_id, int parameter_id) override;

    /**
     * @brief Disable osc output for a parameter
     *
     * @param processor_id The id of the processor the parameter belongs to
     * @param parameter_id The id of the parameter to output as osc
     * @return ControlStatus
     */
    virtual ControlStatus disable_output_for_parameter(int processor_id, int parameter_id) override;

    /**
     * @brief Enable osc output for all parameters
     *
     * @return ControlStatus
     */
    virtual ControlStatus enable_all_output() override;

    /**
     * @brief Disable osc output for all parameters
     *
     * @return ControlStatus
     */
    virtual ControlStatus disable_all_output() override;

private:
    std::unique_ptr<sushi_rpc::OscController::Stub> _stub;
};

} // namespace sushi_controller


#endif // ELKCPP_OSC_CONTROLLER_H