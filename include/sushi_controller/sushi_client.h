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
 * @copyright 2018-2019 Modern Ancient Instruments Networked AB, dba Elk, Stockholm
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
std::shared_ptr<sushi_controller::SushiControl> CreateSushiController(const std::string& server_address = DEFAULT_ADDRESS);
} //sushi_controller

#endif //SUSHI_CLIENT_H