#ifndef ELKCPP_TRANSPORT_CONTROLLER_H
#define ELKCPP_TRANSPORT_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller {

class TransportControllerClient : public TransportController
{
public:
    TransportControllerClient(const std::string& address);

    /**
     * @brief Get the current samplerate
     *
     * @return float The current samplerate
     */
    std::pair<ControlStatus, float> get_samplerate() const override;

    /**
     * @brief Get the current playing mode
     *
     * @return PlayingMode The current playing mode
     */
    std::pair<ControlStatus, PlayingMode> get_playing_mode() const override;

    /**
     * @brief Set the playing mode
     *
     * @param playing_mode The playing mode to set
     */
    ControlStatus set_playing_mode(PlayingMode playing_mode) override;

    /**
     * @brief Get the sync mode
     *
     * @return SyncMode The current sync mode
     */
    std::pair<ControlStatus, SyncMode> get_sync_mode() const override;

    /**
     * @brief Set the sync mode
     *
     * @param sync_mode The sync mode to set
     */
    ControlStatus set_sync_mode(SyncMode sync_mode) override;

    /**
     * @brief Get the tempo
     *
     * @return float The current tempo
     */
    std::pair<ControlStatus, float> get_tempo() const override;

    /**
     * @brief Set the tempo
     *
     * @param tempo The tempo to set
     * @return ControlStatus
     */
    ControlStatus set_tempo(float tempo) override;

    /**
     * @brief Get the time signature
     *
     * @return TimeSignature The current time signature
     */
    std::pair<ControlStatus, TimeSignature> get_time_signature() const override;

    /**
     * @brief Set the time signature
     *
     * @param signature The time signature to set
     * @return ControlStatus
     */
    ControlStatus set_time_signature(TimeSignature signature) override;

private:
    std::unique_ptr<sushi_rpc::TransportController::Stub> _stub;
};

}

#endif // ELKCPP_TRANSPORT_CONTROLLER_H
