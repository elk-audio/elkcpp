/**
 * @brief Mockup of the server running in sushi for testing purposes
 */

#ifndef SUSHI_SERVER_MOCKUP_H
#define SUSHI_SERVER_MOCKUP_H

#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <unistd.h>

#include <grpc++/grpc++.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "sushi_rpc.grpc.pb.h"
#pragma GCC diagnostic pop



namespace sushi_controller
{

namespace expected_results
{

    // Track test values
    const TrackInfo TRACK_WITH_ID_1 = TrackInfo{ 1, "synth", "synth", 2, 2, 2, 2, 10};
    const TrackInfo TRACK_WITH_ID_2 = TrackInfo{ 2, "guitar", "guitar", 2, 2, 2, 2, 10};
    const std::vector<TrackInfo> TRACK_INFO_LIST = {TRACK_WITH_ID_1, TRACK_WITH_ID_2};

    // Processor test values
    const ProcessorInfo PROCESSOR_WITH_ID_1 = ProcessorInfo{1, "synth1", "synth1", 2, 2};
    const ProcessorInfo PROCESSOR_WITH_ID_2 = ProcessorInfo{2, "delay1", "delay1", 2, 2};
    const std::vector<ProcessorInfo> PROCESSOR_INFO_LIST = {PROCESSOR_WITH_ID_1, PROCESSOR_WITH_ID_2};
    constexpr bool PROCESSOR_BYPASS_STATE = true;

    // Program test values
    constexpr int PROGRAM_ID{1};
    const std::string PROGRAM_NAME{"Program1"};

    // Parameter test values
    constexpr ParameterType PARAMETER_TYPE{ParameterType::FLOAT};
    constexpr float PARAMETER_VALUE{5.34f};
    constexpr float PARAMETER_NORMALISED_VALUE{0.87f};
    const std::string PARAMETER_STRING_VALUE{"5.34"};
    const ParameterInfo PARAMETER_WITH_ID_1 = ParameterInfo{1, PARAMETER_TYPE, "param1", "param1", "Hz", true, 0.0f, 1.0f};
    const ParameterInfo PARAMETER_WITH_ID_2 = ParameterInfo{2, PARAMETER_TYPE, "param2", "param2", "Hz", true, 0.0f, 1.0f};
    const std::vector<ParameterInfo> PARAMETER_INFO_LIST = {PARAMETER_WITH_ID_1, PARAMETER_WITH_ID_2};

    // Notification test values
    constexpr std::array<float, 3> PARAMETER_CHANGE_VALUES = {0.0f, 0.5f, 1.0f};

} //expected_results

std::thread server_thread;
std::unique_ptr<grpc::Server> server;

void RunServerMockup();
void KillServerMockup();

class SushiServiceMockup final : public sushi_rpc::SushiController::Service
{


    //====================//
    //  Keyboard Control  //
    //====================//


    //==============//
    //  Cpu Timings //
    //==============//



    //=================//
    //  Track control  //
    //=================//



    //=====================//
    //  Processor control  //
    //=====================//


    //=====================//
    //  Parameter control  //
    //=====================//


    grpc::Status SubscribeToParameterUpdates(grpc::ServerContext* /* context*/,
                                             const sushi_rpc::ParameterNotificationRequest* request,
                                             grpc::ServerWriter<sushi_rpc::ParameterSetRequest>* response)
    {
        grpc::Status status;
        for (int i = 0; i < request->parameters_size(); ++i)
        {
            auto& parameter = request->parameters(i);
            if (parameter.processor_id() == expected_results::PROCESSOR_WITH_ID_1.id &&
                parameter.parameter_id() == expected_results::PARAMETER_WITH_ID_1.id)
            {
                status = grpc::Status::OK;
            }
        }
        sushi_rpc::ParameterSetRequest response_message;
        response_message.mutable_parameter()->set_parameter_id(expected_results::PROCESSOR_WITH_ID_2.id);
        response_message.mutable_parameter()->set_processor_id(expected_results::PARAMETER_WITH_ID_2.id);
        response_message.set_value(expected_results::PARAMETER_CHANGE_VALUES[0]);
        if (response->Write(response_message) == false)
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "First write to server failed!");
        }
        response_message.set_value(expected_results::PARAMETER_CHANGE_VALUES[1]);
        if (response->Write(response_message) == false)
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "First write to server failed!");
        }
        response_message.set_value(expected_results::PARAMETER_CHANGE_VALUES[2]);
        if (response->Write(response_message) == false)
        {
            return grpc::Status(grpc::StatusCode::UNKNOWN, "First write to server failed!");
        }
        return status;
    }

    bool _processor_bypass_state{expected_results::PROCESSOR_BYPASS_STATE};

public:
    void setUp()
    {
        // Set up time signature
        // _time_signature.set_numerator(expeceted_results::TIME_SIGNATURE.numerator);
        // _time_signature.set_denominator(expected_results::TIME_SIGNATURE.denominator);
    }
};

class SushiServerMockup
{
public:
    SushiServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~SushiServerMockup()
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
    SushiServiceMockup service;

    grpc::ServerBuilder builder;

    service.setUp();

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

}


#endif // SUSHI_SERVER_MOCKUP_H
