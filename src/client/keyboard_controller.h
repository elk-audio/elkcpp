#ifndef ELKCPP_KEYBOARD_CONTROLLER_H
#define ELKCPP_KEYBOARD_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller
{

class KeyboardControllerClient : public KeyboardController
{
public:
    KeyboardControllerClient(const std::string& address);

    /**
     * @brief Send note on message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param channel The channel on which the message should be sent
     * @param note The note to send. Follows the MIDI standard where middle c = 60
     * @param velocity The velocity of the note. Should be in range (0.0-1.0)
     * @return ControlStatus
     */
    virtual ControlStatus send_note_on(int track_id, int channel, int note, float velocity) override;

    /**
     * @brief Send note off message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param note The note to send. Follows the MIDI standard where middle c = 60
     * @param channel The channel on which the message should be sent
     * @param velocity The velocity of the note. Should be in range (0.0-1.0)
     * @return ControlStatus
     */
    virtual ControlStatus send_note_off(int track_id, int channel, int note, float velocity) override;

    /**
     * @brief Send note aftertouch message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param channel The channel on which the message should be sent
     * @param note The note to send. Follows the MIDI standard where middle c = 60
     * @param value
     * @return ControlStatus
     */
    virtual ControlStatus send_note_aftertouch(int track_id, int channel, int note, float value) override;

    /**
     * @brief Send aftertouch message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param channel The channel on which the message should be sent
     * @param value
     * @return ControlStatus
     */
    virtual ControlStatus send_aftertouch(int track_id, int channel, float value) override;

     /**
     * @brief Send pitch bend message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param channel The channel on which the message should be sent
     * @param value
     * @return ControlStatus
     */
    virtual ControlStatus send_pitch_bend(int track_id, int channel, float value) override;

    /**
     * @brief Send modulation message to a track
     *
     * @param track_id The id of the track that should receive the message
     * @param channel The channel on which the message should be sent
     * @param value
     * @return ControlStatus
     */
    virtual ControlStatus send_modulation(int track_id, int channel, float value) override;

private:
    std::unique_ptr<sushi_rpc::KeyboardController::Stub> _stub;
};

} // namespace sushi_controller


#endif // ELKCPP_KEYBOARD_CONTROLLER_H
