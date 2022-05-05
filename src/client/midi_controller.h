#ifndef ELKCPP_MIDI_CONTROLLER_H
#define ELKCPP_MIDI_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller
{

class MidiControllerClient : public MidiController
{
public:
    MidiControllerClient(const std::string& address);

    /**
     * @brief Get number of available midi input ports
     *
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_input_ports() override;

    /**
     * @brief Get number of available midi output ports
     *
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_output_ports() override;

    /**
     * @brief Get all midi keyboard input connections
     *
     * @return std::pair<ControlStatus, std::vector<MidiKbdConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiKbdConnection>> get_all_kbd_input_connections() override;

    /**
     * @brief Get all midi keyboard output connections
     *
     * @return std::pair<ControlStatus, std::vector<MidiKbdConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiKbdConnection>> get_all_kbd_output_connections() override;

    /**
     * @brief Get all midi CC input connections
     *
     * @return std::pair<ControlStatus, std::vector<MidiCCConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiCCConnection>> get_all_cc_input_connections() override;

    /**
     * @brief Get all midi PC input input connections
     *
     * @return std::pair<ControlStatus, std::vector<MidiPCConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiPCConnection>> get_all_pc_input_connections() override;

    /**
     * @brief Get the CC input connections for a processor
     *
     * @param processor_id The processor to get the CC input connections from
     * @return std::pair<ControlStatus, std::vector<MidiCCConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiCCConnection>> get_cc_input_connections_for_processor(int processor_id) override;

    /**
     * @brief Get the PC input connections for a processor
     *
     * @param processor_id The processor to get the PC input connections from
     * @return std::pair<ControlStatus, std::vector<MidiPCConnection>>
     */
    virtual std::pair<ControlStatus, std::vector<MidiPCConnection>> get_pc_input_connections_for_processor(int processor_id) override;

    /**
     * @brief Get whether midi clock is enabled for a given midi output port
     *
     * @param port Id of the port to query
     * @return If ControlStatus == Ok, then true if enabled, false if disabled
     */
    virtual std::pair<ControlStatus, bool> get_midi_clock_output_enabled(int port) const override;

    /**
     * @brief Enable or disable midi clock output for a given output port
     *
     * @param enabled true to enable, false to disable
     * @param port Id of the port to set
     * @return ControlStatus
     */
    virtual ControlStatus set_midi_clock_output_enabled(bool enabled, int port) override;

    /**
     * @brief Connect keyboard input to a track
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus connect_kbd_input_to_track(MidiKbdConnection connection_data) override;

    /**
     * @brief Connection keyboard from a track
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus connect_kbd_output_from_track(MidiKbdConnection connection_data) override;

    /**
     * @brief Connect CC messages to a parmeter
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus connect_cc_to_parameter(MidiCCConnection connection_data) override;

    /**
     * @brief Connect PC messages to a processor
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus connect_pc_to_processor(MidiPCConnection connection_data) override;

    /**
     * @brief Disconnect an existing keyboard input connection
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_kbd_input(MidiKbdConnection connection_data) override;

    /**
     * @brief Disconnect an existing keyboard output connection
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_kbd_output(MidiKbdConnection connection_data) override;

    /**
     * @brief Disconnect an existing CC connection
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_cc(MidiCCConnection connection_data) override;

    /**
     * @brief Disconnect an existing PC connection
     *
     * @param connection_data
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_pc(MidiPCConnection connection_data) override;

    /**
     * @brief Disconnect all CC connections from a processor
     *
     * @param processor_id
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_cc_from_processor(int processor_id) override;

    /**
     * @brief Disconnect all PC connection from a processor
     *
     * @param processor_id
     * @return ControlStatus
     */
    virtual ControlStatus disconnect_all_pc_from_processor(int processor_id) override;

private:
    std::unique_ptr<sushi_rpc::MidiController::Stub> _stub;
};

} // namespace sushi_controller


#endif // ELKCPP_MIDI_CONTROLLER_H
