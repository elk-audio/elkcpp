/**
 * @brief gRPC client to control sushi
 *
 * @copyright MIND Music Labs AB, Stockholm, Sweden
 */

#ifndef SUSHI_GRPC_CLIENT_H
#define SUSHI_GRPC_CLIENT_H

#include <grpc++/grpc++.h>
#include <thread>
#include <atomic>

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"
#include "system_controller.h"
#include "transport_controller.h"
#include "timing_controller.h"
#include "keyboard_controller.h"
#include "audio_graph_controller.h"
#include "program_controller.h"
#include "parameter_controller.h"
#include "midi_controller.h"
#include "audio_routing_controller.h"
#include "cv_gate_controller.h"
#include "osc_controller.h"
#include "notification_controller.h"

namespace sushi_controller
{

/**
 * @brief A class to control sushi via gRPC
 *
 */

class SushiControllerClient : public SushiController
{
public:
    SushiControllerClient(const std::string& address);

private:
    SystemControllerClient _system_controller_client;
    TransportControllerClient _transport_controller_client;
    TimingControllerClient _timing_controller_client;
    KeyboardControllerClient _keyboard_controller_client;
    AudioGraphControllerClient _audio_graph_controller_client;
    ProgramControllerClient _program_controller_client;
    ParameterControllerClient _parameter_controller_client;
    MidiControllerClient _midi_controller_client;
    AudioRoutingControllerClient _audio_routing_controller_client;
    CvGateControllerClient _cv_gate_controller_client;
    OscControllerClient _osc_controller_client;
    NotificationControllerClient _notification_controller_client;
};

}

#endif // SUSHI_GRPC_CLIENT_H
