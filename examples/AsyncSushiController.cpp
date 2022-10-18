#include <iostream>
#include <unistd.h>

#include "sushi_client.h"

/**
 * @brief Simple example program. Controls an instance of sushi with obxd and plays some notes and does parameter changes
 *
 * @return int
 */

void print_notification(int processor_id, int parameter_id, float normalized_value,
                        float domain_value, const std::string& formatted_value)
{
    std::cout << "param_id " << parameter_id << " proc_id " << processor_id << " val " << normalized_value
        << ", " << domain_value << ", " << formatted_value << std::endl;
}

int main()
{
    // Create a controller object to connect to sushi
    std::shared_ptr<sushi_controller::SushiController> controller = sushi_controller::CreateSushiController();
    std::vector<std::pair<int, int>> blocklist;
    controller->notification_controller()->subscribe_to_parameter_updates(print_notification, blocklist);
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
