#include <iostream>
#include <unistd.h>

#include "sushi_client.h"

/**
 * @brief Simple example of parameter notification subscription from Sushi.
 *        When the transport starts / stops, a transport notification is received.
 *        If you also use this with e.g. the example configuration that has a step-sequencer running,
 *        you will also receive notifications of when the steps trigger.
 * @return int
 */

void print_transport_notification(sushi_controller::TransportUpdate update,
                                  sushi_controller::TransportUpdateType type)
{
    if (type == sushi_controller::TransportUpdateType::PLAYING_MODE)
    {
        auto playing_mode = std::get<sushi_controller::PlayingMode>(update);

        switch (playing_mode)
        {
            case sushi_controller::PlayingMode::PLAYING:
                std::cout << "Transport Update: Playing" << std::endl;
                break;
            case sushi_controller::PlayingMode::RECORDING:
                std::cout << "Transport Update: Recording" << std::endl;
                break;
            case sushi_controller::PlayingMode::STOPPED:
                std::cout << "Transport Update: Stopped" << std::endl;
                break;
            default:
                break;
        }
    }
}

void print_parameter_notification(int processor_id, int parameter_id, float normalized_value,
                                  float domain_value, const std::string& formatted_value)
{
    std::cout << "param_id " << parameter_id << " proc_id " << processor_id << " val " << normalized_value
        << ", " << domain_value << ", " << formatted_value << std::endl;
}

int main()
{
    // Create a controller object to connect to sushi
    std::shared_ptr<sushi_controller::SushiController> controller = sushi_controller::CreateSushiController();

    controller->notification_controller()->subscribe_to_transport_changes(print_transport_notification);

    std::vector<std::pair<int, int>> blocklist;
    controller->notification_controller()->subscribe_to_parameter_updates(print_parameter_notification, blocklist);

    for (int i = 0; i < 3; ++i)
    {
        controller->transport_controller()->set_playing_mode(sushi_controller::PlayingMode::PLAYING);
        std::cout << "Started playback" << std::endl;
        sleep(2);

        controller->transport_controller()->set_playing_mode(sushi_controller::PlayingMode::STOPPED);
        std::cout << "Stopped playback" << std::endl;
        sleep(1);
    }
}
