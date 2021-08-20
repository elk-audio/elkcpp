#include <gtest/gtest.h>

#include "sushi_client.h"
#include "keyboard_controller.cpp"
#include "test_utils/keyboard_server_mockup.h"
#define private public


class KeyboardControllerTest : public ::testing::Test
{
    protected:
    KeyboardControllerTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    sushi_controller::KeyboardServerMockup server;
    std::shared_ptr<sushi_controller::KeyboardController> controller = sushi_controller::CreateKeyboardController("localhost:51051");
};

TEST_F(KeyboardControllerTest, SendNoteOn)
{
    sushi_controller::ControlStatus status = controller->send_note_on(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                     sushi_controller::expected_results::MIDI_CHANNEL,
                                                                     sushi_controller::expected_results::MIDI_NOTE,
                                                                     sushi_controller::expected_results::MIDI_VELOCITY);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}


TEST_F(KeyboardControllerTest, SendNoteOff)
{
    sushi_controller::ControlStatus status = controller->send_note_off(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                      sushi_controller::expected_results::MIDI_CHANNEL,
                                                                      sushi_controller::expected_results::MIDI_NOTE,
                                                                      sushi_controller::expected_results::MIDI_VELOCITY);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(KeyboardControllerTest, SendNoteAftertouch)
{
    sushi_controller::ControlStatus status = controller->send_note_aftertouch(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                             sushi_controller::expected_results::MIDI_CHANNEL,
                                                                             sushi_controller::expected_results::MIDI_NOTE,
                                                                             sushi_controller::expected_results::MIDI_AFTERTOUCH);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(KeyboardControllerTest, SendAftertouch)
{
    sushi_controller::ControlStatus status = controller->send_aftertouch(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                        sushi_controller::expected_results::MIDI_CHANNEL,
                                                                        sushi_controller::expected_results::MIDI_AFTERTOUCH);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(KeyboardControllerTest, SendPitchBend)
{
    sushi_controller::ControlStatus status = controller->send_pitch_bend(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                        sushi_controller::expected_results::MIDI_CHANNEL,
                                                                        sushi_controller::expected_results::MIDI_PITCH_BEND);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(KeyboardControllerTest, SendModulation)
{
    sushi_controller::ControlStatus status = controller->send_modulation(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                        sushi_controller::expected_results::MIDI_CHANNEL,
                                                                        sushi_controller::expected_results::MIDI_MODULATION);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

