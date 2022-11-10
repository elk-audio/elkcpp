#include <iostream>
#include <array>

#include "sushi_client.h"

/**
 * @brief Simple example program mirroring the sushi_control_example.py, in ElkPy.
 *        Controls an instance of sushi with MDA JX10, a step sequencer, and DubDelay.
 *        Subscribes to notifications.
 *        Sets parameters.
 *
 * @return int
 */

constexpr auto TRACK_NAME = "main";
constexpr auto SYNTH_NAME = "mda JX10";
constexpr auto SEQUENCER_NAME = "step_sequencer";
constexpr auto EFFECT_NAME = "mda DubDelay";

constexpr auto OSC_MIX_NAME = "OSC Mix";
constexpr auto ENV_REL_NAME = "ENV Rel";
constexpr auto VFC_VEL_NAME = "VCF Vel";
constexpr auto VFC_FREQ_NAME = "VCF Freq";
constexpr auto VFC_RESO_NAME = "VCF Reso";

constexpr auto PITCH_0_NAME = "pitch_0";
constexpr auto PITCH_1_NAME = "pitch_1";
constexpr auto PITCH_2_NAME = "pitch_2";
constexpr auto PITCH_3_NAME = "pitch_3";
constexpr auto PITCH_4_NAME = "pitch_4";
constexpr auto PITCH_5_NAME = "pitch_5";
constexpr auto PITCH_6_NAME = "pitch_6";
constexpr auto PITCH_7_NAME = "pitch_7";

//// TODO: Can this be constexpr?
//std::array<const char *const, 4> SUSHI_PROCESSORS {TRACK_NAME,
//                                                   SYNTH_NAME,
//                                                   SEQUENCER_NAME,
//                                                   EFFECT_NAME};
//
//std::array<const char *const, 5> MDA_JX10_PARAMETERS {OSC_MIX_NAME,
//                                                      ENV_REL_NAME,
//                                                      VFC_VEL_NAME,
//                                                      VFC_FREQ_NAME,
//                                                      VFC_RESO_NAME};
//
// std::array<int, 5> MDA_JX10_PARAMETER_IDS;
//
//std::array<const char *const, 8> SEQ_PARAMETERS {PITCH_0_NAME,
//                                                 PITCH_1_NAME,
//                                                 PITCH_2_NAME,
//                                                 PITCH_3_NAME,
//                                                 PITCH_4_NAME,
//                                                 PITCH_5_NAME,
//                                                 PITCH_6_NAME,
//                                                 PITCH_7_NAME};
//
// std::array<int, 8> SEQ_PARAMETER_IDS;

struct plugin
{
    std::string path;
    std::string name;
    std::string uid;
    sushi_controller::PluginType type;
};

std::array<plugin, 3> plugins;

int processor_notification_count = 0;

std::shared_ptr<sushi_controller::SushiController> controller;

sushi_controller::ControlStatus set_parameter(const char* const parameter_name, const char* const processor_name, float value)
{
    sushi_controller::ControlStatus status;
    int parameter_id;
    int processor_id;

    std::tie(status, processor_id) = controller->audio_graph_controller()->get_processor_id(processor_name);

    if (status != sushi_controller::ControlStatus::OK)
    {
        std::cerr << processor_name << " not found" << std::endl;
        return status;
    }

    std::tie(status, parameter_id) = controller->parameter_controller()->get_parameter_id(processor_id,
                                                                                          parameter_name);

    if (status != sushi_controller::ControlStatus::OK)
    {
        std::cerr << parameter_name << " not found" << std::endl;
        return status;
    }

    status = controller->parameter_controller()->set_parameter_value(processor_id, parameter_id, value);

    return status;
}

void set_parameters_for_theme_tune()
{
    set_parameter(OSC_MIX_NAME, SYNTH_NAME, 0.2f);
    set_parameter(ENV_REL_NAME, SYNTH_NAME, 0.3f);
    set_parameter(VFC_VEL_NAME, SYNTH_NAME, 0.6f);
    set_parameter(VFC_FREQ_NAME, SYNTH_NAME, 0.5f);
    set_parameter(VFC_RESO_NAME, SYNTH_NAME, 0.1f);

    set_parameter(PITCH_0_NAME, SYNTH_NAME, 0.4166666666666667);
    set_parameter(PITCH_1_NAME, SYNTH_NAME, 0.5);
    set_parameter(PITCH_2_NAME, SYNTH_NAME, 0.5625);
    set_parameter(PITCH_3_NAME, SYNTH_NAME, 0.6458333333333334);
    set_parameter(PITCH_4_NAME, SYNTH_NAME, 0.6666666666666666);
    set_parameter(PITCH_5_NAME, SYNTH_NAME, 0.6458333333333334);
    set_parameter(PITCH_6_NAME, SYNTH_NAME, 0.5625);
    set_parameter(PITCH_7_NAME, SYNTH_NAME, 0.5);
}

void set_parameters_when_processors_are_ready(sushi_controller::ProcessorUpdate update)
{
    if (update.action == sushi_controller::ProcessorUpdate::Action::PROCESSOR_ADDED)
    {
        std::cout << "Processor created with ID: " << update.processor_id << std::endl;
        processor_notification_count += 1;
    }

    if (processor_notification_count == plugins.size())
    {
        set_parameters_for_theme_tune();
    }
}

void load_plugin_on_track(sushi_controller::SushiController* controller, const plugin& p, int track_id)
{
    auto status = controller->audio_graph_controller()->create_processor_on_track(p.name,
                                                                                  p.uid,
                                                                                  p.path,
                                                                                  p.type,
                                                                                   track_id,
                                                                                  0,
                                                                                  true);

    if (status != sushi_controller::ControlStatus::OK)
    {
        std::cerr << "Creating Processor: " << p.name << " on track: " << TRACK_NAME << " failed" << std::endl;
    }
}

int main()
{
    // Create a controller object to connect to sushi
    controller = sushi_controller::CreateSushiController();

    // Initialize status variable
    sushi_controller::ControlStatus status;

    controller->notification_controller()->subscribe_to_processor_changes(set_parameters_when_processors_are_ready);

    int track_id;

    // Get the id of the processor matching the processor name
    std::tie(status, track_id) = controller->audio_graph_controller()->get_track_id(TRACK_NAME);

    // Check if the call was successful and print an error if not
    if (status != sushi_controller::ControlStatus::OK)
    {
        std::cerr << TRACK_NAME << " not found" << std::endl;
        return 1;
    }

    int sequencer_index = 0;
    plugins[sequencer_index].path = "";
    plugins[sequencer_index].name = SEQUENCER_NAME;
    plugins[sequencer_index].uid = "sushi.testing.step_sequencer";
    plugins[sequencer_index].type = sushi_controller::PluginType::INTERNAL;

    int synth_index = 1;
    plugins[synth_index].path = "mda-vst3.vst3";
    plugins[synth_index].name = SYNTH_NAME;
    plugins[synth_index].uid = SYNTH_NAME;
    plugins[synth_index].type = sushi_controller::PluginType::VST3X;

    int effect_index = 2;
    plugins[effect_index].path = "mda-vst3.vst3";
    plugins[effect_index].name = EFFECT_NAME;
    plugins[effect_index].uid = EFFECT_NAME;
    plugins[effect_index].type = sushi_controller::PluginType::VST3X;

    for (auto p : plugins)
    {
        load_plugin_on_track(controller.get(), p, track_id);
    }

    return 0;
}
