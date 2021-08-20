
#include "sushi_client.h"
#include "sushi_grpc_client.h"
#include "async_client_call_data.h"
namespace sushi_controller
{

SushiControllerClient::SushiControllerClient(const std::string& address)
    : SushiController(
        nullptr, // &_system_controller_client,
        &_transport_controller_client,
        &_timing_controller_client,
        &_keyboard_controller_client,
        &_audio_graph_controller_client,
        &_program_controller_client,
        &_parameter_controller_client,
        nullptr, // &_midi_controller_client,
        nullptr, // &_audio_routing_controller_client,
        nullptr, // &_cv_gate_controller_client,
        nullptr, // &_osc_controller_client,
        &_notification_controller_client
    ),
    // _system_controller_client(address),
    _transport_controller_client(address),
    _timing_controller_client(address),
    _keyboard_controller_client(address),
    _audio_graph_controller_client(address),
    _program_controller_client(address),
    _parameter_controller_client(address),
    // _midi_controller_client(address),
    // _audio_routing_controller_client(address),
    // _cv_gate_controller_client(address),
    // _osc_controller_client(address),
    _notification_controller_client(address) {}

std::shared_ptr<SushiController> CreateSushiController(const std::string& server_address)
{
    return std::move(std::make_shared<SushiControllerClient>(server_address));
}

} //sushi_controller
