#ifndef ELKCPP_CV_GATE_CONTROLLER_H
#define ELKCPP_CV_GATE_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller
{

class CvGateControllerClient : public CvGateController
{
public:
    CvGateControllerClient(const std::string& address);

    /**
     * @brief Get number of cv input ports
     *
     * @return int
     */
    virtual std::pair<ControlStatus, int> get_cv_input_channel_count() const override;

    /**
     * @brief Get number of cv output ports
     *
     * @return int
     */
    virtual std::pair<ControlStatus, int> get_cv_output_channel_count() const override;

    /**
     * @brief Get a list of all cv input connections
     *
     * @return std::vector<CvConnection>
     */
    virtual std::pair<ControlStatus, std::vector<CvConnection>> get_all_cv_input_connections() const override;

    /**
     * @brief Get a list of all cv output connections
     *
     * @return std::vector<CvConnection>
     */
    virtual std::pair<ControlStatus, std::vector<CvConnection>> get_all_cv_output_connections() const override;

    /**
     * @brief Get a list of all gate input connections
     *
     * @return std::vector<GateConnection>
     */
    virtual std::pair<ControlStatus, std::vector<GateConnection>> get_all_gate_input_connections() const override;

    /**
     * @brief Get a list of all gate output connections
     *
     * @return std::vector<GateConnection>
     */
    virtual std::pair<ControlStatus, std::vector<GateConnection>> get_all_gate_output_connections() const override;

    /**
     * @brief Get the cv input connections for a processor
     *
     * @param processor_id Id of the processor to get connections for
     * @return std::pair<ControlStatus, std::vector<CvConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<CvConnection>> get_cv_input_connections_for_processor(int processor_id) const override;

    /**
     * @brief Get the cv output connections for a processor
     *
     * @param processor_id Id of the processor to get connections for
     * @return std::pair<ControlStatus, std::vector<CvConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<CvConnection>> get_cv_output_connections_for_processor(int processor_id) const override;

    /**
     * @brief Get the gate input connections for a processor
     *
     * @param processor_id Id of the processor to get connections for
     * @return std::pair<ControlStatus, std::vector<GateConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<GateConnection>> get_gate_input_connections_for_processor(int processor_id) const override;

    /**
     * @brief Get the gate output connections for a processor
     *
     * @param processor_id Id of the processor to get connections for
     * @return std::pair<ControlStatus, std::vector<GateConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<GateConnection>> get_gate_output_connections_for_processor(int processor_id) const override;

    /**
     * @brief Connect a cv input to a parameter
     *
     * @param processor_id Id of the processor that has the parameter
     * @param parameter_id Id of the parameter to connect the CV to
     * @param cv_input_id Id of the CV input to connect
     * @return ControlStatus
     */
    virtual ControlStatus connect_cv_input_to_parameter(int processor_id, int parameter_id, int cv_input_id) override;

    /**
     * @brief Connect a cv output from a parameter
     *
     * @param processor_id Id of the processor that has the parameter
     * @param parameter_id Id of the parameter to connect the CV to
     * @param cv_output_id Id of the CV output to connect
     * @return ControlStatus
     */
    virtual ControlStatus connect_cv_output_from_parameter(int processor_id, int parameter_id, int cv_output_id) override;

    /**
     * @brief Connect a gate input to a processor
     *
     * @param processor_id Id of the processor to connect to
     * @param gate_input_id Id of the gate input to connect
     * @param channel Midi channel to use for the gate trigger signal
     * @param note_no Note to play when the gate triggers
     * @return ControlStatus
     */
    virtual ControlStatus connect_gate_input_to_processor(int processor_id, int gate_input_id, int channel, int note_no) override;

    /**
     * @brief Connect a gate output to a processor
     *
     * @param processor_id Id of the processor to connect to
     * @param gate_output_id Id of the gate output to connect
     * @param channel Midi channel to use for the gate trigger signal
     * @param note_no Note to play when the gate triggers
     * @return ControlStatus
     */
    virtual ControlStatus connect_gate_output_from_processor(int processor_id, int gate_output_id, int channel, int note_no) override;

    /**
     * @brief Disconnect CV input
     *
     * @param processor_id Id of the processor the parameter belongs to
     * @param parameter_id Id of the parameter to disconnect from
     * @param cv_input_id Id of the CV input
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_cv_input(int processor_id, int parameter_id, int cv_input_id) override;

    /**
     * @brief Disconnect CV output
     *
     * @param processor_id Id of the processor the parameter belongs to
     * @param parameter_id Id of the parameter to disconnect from
     * @param cv_output_id Id of the CV output
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_cv_output(int processor_id, int parameter_id, int cv_output_id) override;

    /**
     * @brief Disconnect gate input
     *
     * @param processor_id Id of the processor to disconnect
     * @param gate_input_id Id of the gate input
     * @param channel Midi channel that is used for the gate trigger signal
     * @param note_no Note that is played when the gate triggers
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_gate_input(int processor_id, int gate_input_id, int channel, int note_no) override;

    /**
     * @brief Disconnect gate output
     *
     * @param processor_id Id of processor to disconnect
     * @param gate_output_id Id of the gate output
     * @param channel Midi channel that is used for the gate trigger signal
     * @param note_no Note that is played when the gate triggers
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_gate_output(int processor_id, int gate_output_id, int channel, int note_no) override;

    /**
     * @brief Disconnect all CV inputs from a processor
     *
     * @param processor_id Id of the processor to disconnect from
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_cv_inputs_from_processor(int processor_id) override;

    /**
     * @brief Disconnect all CV outputs from a processor
     *
     * @param processor_id Id of the processor to disconnect from
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_cv_outputs_from_processor(int processor_id) override;

    /**
     * @brief Disconnect all gate inputs from a processor
     *
     * @param processor_id Id of the processor to disconnect from
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_gate_inputs_from_processor(int processor_id) override;

    /**
     * @brief Disconnect all gate outputs from a processor
     *
     * @param processor_id Id of the processor to disconnect from
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_gate_outputs_from_processor(int processor_id) override;

private:
    std::unique_ptr<sushi_rpc::CvGateController::Stub> _stub;
};

} // namespace sushi_controller


#endif // ELKCPP_CV_GATE_CONTROLLER_H