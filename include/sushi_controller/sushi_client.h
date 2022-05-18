/**
 * @file sushi_client.h
 * @author Ruben Svensson (therubething@gmail.com)
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
std::shared_ptr<SessionController> CreateSessionController(const std::string& server_address = DEFAULT_ADDRESS);
std::shared_ptr<NotificationController> CreateNotificationController(const std::string& server_address = DEFAULT_ADDRESS);
} //sushi_controller

#endif //SUSHI_CLIENT_H
