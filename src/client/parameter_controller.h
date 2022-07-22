#ifndef ELKCPP_PARAMETER_CONTROLLER_H
#define ELKCPP_PARAMETER_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller
{

class ParameterControllerClient : public ParameterController
{
public:
    ParameterControllerClient(const std::string& address);

    /**
     * @brief Get the parameters available to a track
     *
     * @param track_id The id of the track to get the parameters from
     * @return std::pair<ControlStatus, std::vector<ParameterInfo>>
     */
    std::pair<ControlStatus, std::vector<ParameterInfo>> get_track_parameters(int track_id) const override;

    /**
     * @brief Get the parameters available to a processor
     *
     * @param processor_id The id of the processor to get the parameters from
     * @return std::pair<ControlStatus, std::vector<ParameterInfo>>
     */
    std::pair<ControlStatus, std::vector<ParameterInfo>> get_processor_parameters(int processor_id) const override;

    /**
     * @brief Get the id of a parameter from its name
     *
     * @param processor_id The id of the processor containing the parameter
     * @param parameter The name of the parameter to get the id from
     * @return std::pair<ControlStatus, int>
     */
    std::pair<ControlStatus, int> get_parameter_id(int processor_id, const std::string& parameter) const override;

    /**
     * @brief Get the info of a parameter
     *
     * @param processor_id The id of the processors containing the parameter
     * @param parameter_id The id of the parameter to get the info from
     * @return std::pair<ControlStatus, ParameterInfo>
     */
    std::pair<ControlStatus, ParameterInfo> get_parameter_info(int processor_id, int parameter_id) const override;

    /**
     * @brief Get the current value of a parameter
     *
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of parameter to get the value from
     * @return std::pair<ControlStatus, float>
     */
    std::pair<ControlStatus, float> get_parameter_value(int processor_id, int parameter_id) const override;

    /**
     * @brief Get the normalised current value of a parameter
     *
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to get the normalised value from
     * @return std::pair<ControlStatus, float>
     */
    std::pair<ControlStatus, float> get_parameter_value_in_domain(int processor_id, int parameter_id) const override;

    /**
     * @brief Get the current value of a parameter as a string
     *
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to get value as a string from
     * @return std::pair<ControlStatus, std::string>
     */
    std::pair<ControlStatus, std::string> get_parameter_value_as_string(int processor_id, int parameter_id) const override;

    /**
     * @brief Set the value of a parameter
     *
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to set the value of
     * @param value The value to set the parameter to
     * @return ControlStatus
     */
    ControlStatus set_parameter_value(int processor_id, int parameter_id, float value) override;

    /**
     * @brief Get the properties available to a track
     *
     * @param track_id The id of the track to get the properties from
     * @return std::pair<ControlStatus, std::vector<ParameterInfo>>
     */
    std::pair<ControlStatus, std::vector<PropertyInfo>> get_track_properties(int track_id) const override;

    /**
     * @brief Get the properties available to a processor
     *
     * @param processor_id The id of the processor to get the properties from
     * @return std::pair<ControlStatus, std::vector<ParameterInfo>>
     */
    std::pair<ControlStatus, std::vector<PropertyInfo>> get_processor_properties(int processor_id) const override;

    /**
     * @brief Get the id of a property from its name
     *
     * @param processor_id The id of the processor containing the property
     * @param property The name of the property to get the id from
     * @return std::pair<ControlStatus, int>
     */
    std::pair<ControlStatus, int> get_property_id(int processor_id, const std::string& property) const override;

    /**
     * @brief Get the info of a property
     *
     * @param processor_id The id of the processors containing the property
     * @param property_id The id of the property to get the info from
     * @return std::pair<ControlStatus, ParameterInfo>
     */
    std::pair<ControlStatus, PropertyInfo> get_property_info(int processor_id, int property_id) const override;

    /**
     * @brief Get the current value of a property
     *
     * @param processor_id The id of the processor containing the property
     * @param property_id The id of the property to get value as a string from
     * @return std::pair<ControlStatus, std::string>
     */
    std::pair<ControlStatus, std::string> get_property_value(int processor_id, int property_id) const override;

    /**
     * @brief Set the value of a property
     *
     * @param processor_id The id of the processor containing the property
     * @param property_id The id of the property to set the value of
     * @param value The value to set the property to
     * @return ControlStatus
     */
    ControlStatus set_property_value(int processor_id, int property_id, std::string value) override;

private:
    std::unique_ptr<sushi_rpc::ParameterController::Stub> _stub;
};

} // namespace sushi_controller


#endif // ELKCPP_PARAMETER_CONTROLLER_H
