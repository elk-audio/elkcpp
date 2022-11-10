#include <iostream>
#include <unistd.h>

#include "sushi_client.h"

/**
 * @brief Simple example program.
 *        Controls an instance of sushi with MDA JX10.
 *        Plays some notes, and does parameter changes.
 *
 * @return int
 */

int main()
{
    // Create a controller object to connect to sushi
    std::shared_ptr<sushi_controller::SushiController> controller = sushi_controller::CreateSushiController();

    // "Fun" message
    std::cout << "Listen to the music!" << std::endl;

    // Set the name of the processor to control
    std::string processor_name = "mda JX10";

    // Initialize status variable
    sushi_controller::ControlStatus status;

    // Initialize variable to hold the id of the processor
    int processor_id;

    // Get the id of the processor matching the processor name
    std::tie(status, processor_id) = controller->audio_graph_controller()->get_processor_id(processor_name);

    // Check if the call was successful and print an error if not
    if (status != sushi_controller::ControlStatus::OK)
    {
        std::cerr << processor_name << " not found" << std::endl;
        return 1;
    }

    // Set the name of a parameter to control
    std::string parameter_name = "VCF Freq";

    // Initialize variable to hold the id of the parameter
    int parameter_id;

    // Get the id of the parameter matching the parameter name
    std::tie(status, parameter_id) = controller->parameter_controller()->get_parameter_id(processor_id, parameter_name);

    // Check if the call was successful and print an error if not
    if (status != sushi_controller::ControlStatus::OK)
    {
        std::cerr << parameter_name << " not found" << std::endl;
        return 1;
    }

    // Start a Cmaj7 chord
    controller->keyboard_controller()->send_note_on(0, 0, 60, 1.0f);
    controller->keyboard_controller()->send_note_on(0, 0, 64, 1.0f);
    controller->keyboard_controller()->send_note_on(0, 0, 67, 1.0f);
    controller->keyboard_controller()->send_note_on(0, 0, 71, 1.0f);

    // Initialize variables for the command sequence
    float cutoff = 0.0f;
    float pitch_bend = 0.0f;
    float duration = 3.0f;
    int number_of_steps = 1000;

    for (int i = 0; i < number_of_steps; ++i)
    {
        // Set the cutoff parameter
        controller->parameter_controller()->set_parameter_value(processor_id, parameter_id, cutoff);

        // Set the pitch bend
        controller->keyboard_controller()->send_pitch_bend(0, 0, pitch_bend);

        // Increment the cutoff
        cutoff += duration/(float)number_of_steps;

        // Increment the pitch bend value
        pitch_bend += duration/(float)number_of_steps;

        // Pause
        usleep((int)(duration * 1000000 / number_of_steps));
    }

    // Stop the notes that were started
    controller->keyboard_controller()->send_note_off(0, 0, 60, 1.0f);
    controller->keyboard_controller()->send_note_off(0, 0, 64, 1.0f);
    controller->keyboard_controller()->send_note_off(0, 0, 67, 1.0f);
    controller->keyboard_controller()->send_note_off(0, 0, 71, 1.0f);

    return 0;
}
