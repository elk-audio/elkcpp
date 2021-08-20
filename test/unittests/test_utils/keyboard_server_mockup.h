#ifndef ELKCPP_KEYBOARD_SERVER_MOCKUP
#define ELKCPP_KEYBOARD_SERVER_MOCKUP

#include <thread>

#include <grpcpp/grpcpp.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "sushi_rpc.grpc.pb.h"
#pragma GCC diagnostic pop

namespace sushi_controller
{

namespace expected_results
{
    // MIDI test values
    constexpr int MIDI_TRACK_ID = 1;
    constexpr int MIDI_CHANNEL = 3;
    constexpr int MIDI_NOTE = 63;
    constexpr float MIDI_VELOCITY = 0.89f;
    constexpr float MIDI_AFTERTOUCH = 0.46f;
    constexpr float MIDI_MODULATION = 0.78f;
    constexpr float MIDI_PITCH_BEND = 0.5f;
} // namespace expected_results


class KeyboardServiceMockup : public sushi_rpc::KeyboardController::Service
{
    grpc::Status SendNoteOn(grpc::ServerContext* /* context */,
                            const sushi_rpc::NoteOnRequest* request,
                            sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->note() == expected_results::MIDI_NOTE &&
            request->velocity() == expected_results::MIDI_VELOCITY)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    grpc::Status SendNoteOff(grpc::ServerContext* /* context */,
                            const sushi_rpc::NoteOffRequest* request,
                            sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->note() == expected_results::MIDI_NOTE &&
            request->velocity() == expected_results::MIDI_VELOCITY)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    grpc::Status SendNoteAftertouch(grpc::ServerContext* /* context */,
                                    const sushi_rpc::NoteAftertouchRequest* request,
                                    sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->note() == expected_results::MIDI_NOTE &&
            request->value() == expected_results::MIDI_AFTERTOUCH)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    grpc::Status SendAftertouch(grpc::ServerContext* /* context */,
                                const sushi_rpc::NoteModulationRequest* request,
                                sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->value() == expected_results::MIDI_AFTERTOUCH)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    grpc::Status SendPitchBend(grpc::ServerContext* /* context */,
                               const sushi_rpc::NoteModulationRequest* request,
                               sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->value() == expected_results::MIDI_PITCH_BEND)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

    grpc::Status SendModulation(grpc::ServerContext* /* context */,
                                const sushi_rpc::NoteModulationRequest* request,
                                sushi_rpc::GenericVoidValue* /* response */)
    {
        if (request->track().id() == expected_results::MIDI_TRACK_ID &&
            request->channel() == expected_results::MIDI_CHANNEL &&
            request->value() == expected_results::MIDI_MODULATION)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "Midi message did not match expected message");
        }
    }

};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class KeyboardServerMockup
{
public:
    KeyboardServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~KeyboardServerMockup()
    {
        KillServerMockup();
        server_thread.join();
    }

private:
    std::thread server_thread;
};

void RunServerMockup()
{
    std::string server_address("localhost:51051");
    KeyboardServiceMockup service;

    grpc::ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    server = builder.BuildAndStart();
    // std::cout << "Mockup server listening on " << server_address << std::endl;

    server->Wait();
}

void KillServerMockup()
{
    server->Shutdown();
}

} // namespace sushi_controller


#endif // ELKCPP_KEYBOARD_SERVER_MOCKUP
