/*
 * Copyright 2018-2019 Modern Ancient Instruments Networked AB, dba Elk
 * elkcpp is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * elkcpp is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with elkcpp.
 * If not, see http://www.gnu.org/licenses/ .
 */

/**
 * @brief Implementation of the grpc client for sushi.
 * @copyright 2018-2019 Modern Ancient Instruments Networked AB, dba Elk, Stockholm
 */

#include "sushi_client.h"
#include "sushi_grpc_client.h"
#include "async_client_call_data.h"
namespace sushi_controller
{

SushiControllerClient::SushiControllerClient(const std::string& address)
    : SushiController(
        &_system_controller_client,
        &_transport_controller_client,
        &_timing_controller_client,
        &_keyboard_controller_client,
        &_audio_graph_controller_client,
        &_program_controller_client,
        &_parameter_controller_client,
        &_midi_controller_client,
        &_audio_routing_controller_client,
        &_cv_gate_controller_client,
        &_osc_controller_client,
        &_session_controller_client,
        &_notification_controller_client
    ),
    _system_controller_client(address),
    _transport_controller_client(address),
    _timing_controller_client(address),
    _keyboard_controller_client(address),
    _audio_graph_controller_client(address),
    _program_controller_client(address),
    _parameter_controller_client(address),
    _midi_controller_client(address),
    _audio_routing_controller_client(address),
    _cv_gate_controller_client(address),
    _osc_controller_client(address),
    _session_controller_client(address),
    _notification_controller_client(address) {}

std::shared_ptr<SushiController> CreateSushiController(const std::string& server_address)
{
    return std::make_shared<SushiControllerClient>(server_address);
}

} //sushi_controller
