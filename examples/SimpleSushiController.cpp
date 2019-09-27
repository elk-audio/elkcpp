#include <iostream>
#include <unistd.h>

#include "sushi_client.h"

/**
 * @brief Simple example program. Controls an instance of sushi with obxd and plays some notes and does parameter changes
 * 
 * @return int 
 */

int main()
{
    std::unique_ptr<sushi_controller::SushiControl> controller = sushi_controller::CreateSushiController();
    std::cout << "Listen to the music!" << std::endl;
    std::string processor_name = "obxd";
    auto get_id_result = controller.get()->get_processor_id(processor_name);
    int processor_id;
    if (get_id_result.first == sushi_controller::ControlStatus::OK)
    {
        processor_id = get_id_result.second;
    }
    else
    {
        std::cout << processor_name << " not found" << std::endl;
        return 1;
    }
    
    std::string parameter_name = "Cutoff";
    auto get_param_result = controller.get()->get_parameter_id(processor_id, parameter_name);
    int parameter_id;
    if (get_param_result.first == sushi_controller::ControlStatus::OK)
    {
        parameter_id = get_param_result.second;
    }
    else
    {
        std::cout << parameter_name << " not found" << std::endl;
        return 1;
    }

    controller.get()->send_note_on(0, 0, 60, 1.0f);
    controller.get()->send_note_on(0, 0, 64, 1.0f);
    controller.get()->send_note_on(0, 0, 67, 1.0f);
    controller.get()->send_note_on(0, 0, 71, 1.0f);
    
    float cutoff = 0.0f;
    float pitch_bend = 0.0f;
    float duration = 3.0f;
    int number_of_steps = 1000;
    
    for(int i = 0; i < number_of_steps; ++i)
    {
        controller.get()->set_parameter_value_normalised(processor_id, parameter_id, cutoff);
        controller.get()->send_pitch_bend(0, 0, pitch_bend);
        cutoff += duration/(float)number_of_steps;
        pitch_bend += duration/(float)number_of_steps;
        usleep((int)(duration*1000000/number_of_steps));
    }

    controller.get()->send_note_off(0, 0, 60, 1.0f);
    controller.get()->send_note_off(0, 0, 64, 1.0f);
    controller.get()->send_note_off(0, 0, 67, 1.0f);
    controller.get()->send_note_off(0, 0, 71, 1.0f);
    return 0;
}