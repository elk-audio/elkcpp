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
 * @brief maker for the sushi client
 * @version 0.1
 * @date 2019-09-27
 *
 * @copyright MIND Music Labs AB, Stockholm, Sweden 2019
 *
 */

#ifndef SUSHI_CLIENT_H
#define SUSHI_CLIENT_H

#include <memory>
#include <string>

#include "control_interface.h"

namespace sushi_controller
{
constexpr char DEFAULT_ADDRESS[] = "localhost:51051";
std::shared_ptr<SushiController> CreateSushiController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<SystemController> CreateSystemController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<TransportController> CreateTransportController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<TimingController> CreateTimingController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<KeyboardController> CreateKeyboardController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<AudioGraphController> CreateAudioGraphController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<ProgramController> CreateProgramController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<ParameterController> CreateParameterController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<MidiController> CreateMidiController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<AudioRoutingController> CreateAudioRoutingController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<CvGateController> CreateCvGateController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<OscController> CreateOscController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<NotificationController> CreateNotificationController(const std::string& server_address = DEFAULT_ADDRESS);
} //sushi_controller

#endif //SUSHI_CLIENT_H
