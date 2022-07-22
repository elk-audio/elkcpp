#ifndef ELKCPP_AUDIO_ROUTING_CONTROLLER_H
#define ELKCPP_AUDIO_ROUTING_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"
namespace sushi_controller
{

class AudioRoutingControllerClient : public AudioRoutingController
{
public:
    AudioRoutingControllerClient(const std::string& address);

    /**
     * @brief Get all the current input connections
     *
     * @return std::vector<AudioConnection>
     */
    std::pair<ControlStatus, std::vector<AudioConnection>> get_all_input_connections() const override;

    /**
     * @brief Get all the current output connections
     *
     * @return std::vector<AudioConnection>
     */
    std::pair<ControlStatus, std::vector<AudioConnection>> get_all_output_connections() const override;

    /**
     * @brief Get the input connections for a track
     *
     * @param track_id Id of the track to get the connections from
     * @return std::vector<AudioConnection>
     */
    std::pair<ControlStatus, std::vector<AudioConnection>> get_input_connections_for_track(int track_id) const override;

    /**
     * @brief Get the output connections for a track
     *
     * @param track_id Id of the track to get the connections from
     * @return std::vector<AudioConnection>
     */
    std::pair<ControlStatus, std::vector<AudioConnection>> get_output_connections_for_track(int track_id) const override;

    /**
     * @brief Connect an input channel to a track
     *
     * @param track_id The id of the track to connect
     * @param track_channel The index of the track channel to connect
     * @param input_channel The index of the engine input channel to connect
     * @return ControlStatus
     */
    ControlStatus connect_input_channel_to_track(int track_id, int track_channel, int input_channel) override;

    /**
     * @brief Connect an output channel from a track
     *
     * @param track_id The id of the track to connect
     * @param track_channel The index of the track channel to connect
     * @param output_channel The index of the engine output channel to connect
     * @return ControlStatus
     */
    ControlStatus connect_output_channel_from_track(int track_id, int track_channel, int output_channel) override;

    /**
     * @brief Disconnect an input channel from a track
     *
     * @param track_id The id of the track to disconnect
     * @param track_channel The index of the track channel to disconnect
     * @param input_channel The index of the engine input channel to disconnect
     * @return ControlStatus
     */
    ControlStatus disconnect_input(int track_id, int track_channel, int input_channel) override;

    /**
     * @brief Disconnect an output channel from a track
     *
     * @param track_id The id of the track to disconnect
     * @param track_channel The index of the track channel to disconnect
     * @param output_channel The index of the engine output channel to disconnect
     * @return ControlStatus
     */
    ControlStatus disconnect_output(int track_id, int track_channel, int output_channel) override;

    /**
     * @brief Disconnect all input channels from a track
     *
     * @param track_id The id of the track to disconnect from
     * @return ControlStatus
     */
    ControlStatus disconnect_all_inputs_from_track(int track_id) override;

    /**
     * @brief Disconnect all output channels from a track
     *
     * @param track_id The id of the track to disconnect from
     * @return ControlStatus
     */
    ControlStatus disconnect_all_outputs_from_track(int track_id) override;


private:
    std::unique_ptr<sushi_rpc::AudioRoutingController::Stub> _stub;
};

} // namespace sushi_controller


#endif // ELKCPP_AUDIO_ROUTING_CONTROLLER_H