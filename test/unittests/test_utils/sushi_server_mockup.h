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
    constexpr float PARAMETER_DOMAIN_VALUE{5.34f};
    constexpr float PARAMETER_NORMALISED_VALUE{0.87f};
    const std::string PARAMETER_STRING_VALUE{"5.34"};
    const ParameterInfo PARAMETER_WITH_ID_1 = ParameterInfo{1, PARAMETER_TYPE, "param1", "param1", "Hz", true, 0.0f, 1.0f};
    const ParameterInfo PARAMETER_WITH_ID_2 = ParameterInfo{2, PARAMETER_TYPE, "param2", "param2", "Hz", true, 0.0f, 1.0f};
    const std::vector<ParameterInfo> PARAMETER_INFO_LIST = {PARAMETER_WITH_ID_1, PARAMETER_WITH_ID_2};



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


<<<<<<< HEAD
    grpc::Status GetTrackParameters(grpc::ServerContext* /* context */,
                                    const sushi_rpc::TrackIdentifier* request,
                                    sushi_rpc::ParameterInfoList* response)
    {
        if (request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            for(uint i = 0; i < expected_results::PARAMETER_INFO_LIST.size(); ++i)
            {
                sushi_rpc::ParameterInfo* parameter = response->add_parameters();
                parameter->set_id(expected_results::PARAMETER_INFO_LIST.at(i).id);
                parameter->mutable_type()->set_type(sushi_rpc::ParameterType::FLOAT);
                parameter->set_label(expected_results::PARAMETER_INFO_LIST.at(i).label);
                parameter->set_name(expected_results::PARAMETER_INFO_LIST.at(i).name);
                parameter->set_unit(expected_results::PARAMETER_INFO_LIST.at(i).unit);
                parameter->set_automatable(expected_results::PARAMETER_INFO_LIST.at(i).automatable);
                parameter->set_min_domain_value(expected_results::PARAMETER_INFO_LIST.at(i).min_domain_value);
                parameter->set_max_domain_value(expected_results::PARAMETER_INFO_LIST.at(i).max_domain_value);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }
=======
>>>>>>> develop

    //=====================//
    //  Processor control  //
    //=====================//

<<<<<<< HEAD
    grpc::Status GetProcessorId(grpc::ServerContext* /* context */,
                                const sushi_rpc::GenericStringValue* request,
                                sushi_rpc::ProcessorIdentifier* response)
    {
        if(request->value() == expected_results::PROCESSOR_WITH_ID_1.name)
        {
            response->set_id(expected_results::PROCESSOR_WITH_ID_1.id);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that name");
        }
    }

    grpc::Status GetProcessorInfo(grpc::ServerContext* /* context */,
                                  const sushi_rpc::ProcessorIdentifier* request,
                                  sushi_rpc::ProcessorInfo* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_id(expected_results::PROCESSOR_WITH_ID_1.id);
            response->set_label(expected_results::PROCESSOR_WITH_ID_1.label);
            response->set_name(expected_results::PROCESSOR_WITH_ID_1.name);
            response->set_parameter_count(expected_results::PROCESSOR_WITH_ID_1.parameter_count);
            response->set_program_count(expected_results::PROCESSOR_WITH_ID_1.program_count);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status GetProcessorBypassState(grpc::ServerContext* /* context */,
                                         const sushi_rpc::ProcessorIdentifier* request,
                                         sushi_rpc::GenericBoolValue* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_value(_processor_bypass_state);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status SetProcessorBypassState(grpc::ServerContext* /* context */,
                                         const sushi_rpc::ProcessorBypassStateSetRequest* request,
                                         sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            _processor_bypass_state = request->value();
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status GetProcessorCurrentProgram(grpc::ServerContext* /* context */,
                                            const sushi_rpc::ProcessorIdentifier* request,
                                            sushi_rpc::ProgramIdentifier* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_program(expected_results::PROGRAM_ID);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status GetProcessorCurrentProgramName(grpc::ServerContext* /* context */,
                                                const sushi_rpc::ProcessorIdentifier* request,
                                                sushi_rpc::GenericStringValue* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_value(expected_results::PROGRAM_NAME);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status GetProcessorProgramName(grpc::ServerContext* /* context */,
                                         const sushi_rpc::ProcessorProgramIdentifier* request,
                                         sushi_rpc::GenericStringValue* response)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id 
        && request->program() == expected_results::PROGRAM_ID)
        {
            response->set_value(expected_results::PROGRAM_NAME);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor and/or program with that id");
        }
    }

    grpc::Status GetProcessorPrograms(grpc::ServerContext* /* context */,
                                      const sushi_rpc::ProcessorIdentifier* request,
                                      sushi_rpc::ProgramInfoList* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            sushi_rpc::ProgramInfo* program = response->add_programs();
            program->mutable_id()->set_program(expected_results::PROGRAM_ID);
            program->set_name(expected_results::PROGRAM_NAME);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status SetProcessorProgram(grpc::ServerContext* /* context */,
                                     const sushi_rpc::ProcessorProgramSetRequest* request,
                                     sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id 
        && request->program().program() == expected_results::PROGRAM_ID)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor and/or program with that id");
        }
    }

    grpc::Status GetProcessorParameters(grpc::ServerContext* /* context */,
                                        const sushi_rpc::ProcessorIdentifier* request,
                                        sushi_rpc::ParameterInfoList* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            for(uint i = 0; i < expected_results::PARAMETER_INFO_LIST.size(); ++i)
            {
                sushi_rpc::ParameterInfo* parameter = response->add_parameters();
                parameter->set_id(expected_results::PARAMETER_INFO_LIST.at(i).id);
                parameter->mutable_type()->set_type(sushi_rpc::ParameterType::FLOAT);
                parameter->set_label(expected_results::PARAMETER_INFO_LIST.at(i).label);
                parameter->set_name(expected_results::PARAMETER_INFO_LIST.at(i).name);
                parameter->set_unit(expected_results::PARAMETER_INFO_LIST.at(i).unit);
                parameter->set_automatable(expected_results::PARAMETER_INFO_LIST.at(i).automatable);
                parameter->set_min_domain_value(expected_results::PARAMETER_INFO_LIST.at(i).min_domain_value);
                parameter->set_max_domain_value(expected_results::PARAMETER_INFO_LIST.at(i).max_domain_value);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }
=======
>>>>>>> develop

    //=====================//
    //  Parameter control  //
    //=====================//

<<<<<<< HEAD
    grpc::Status GetParameterId(grpc::ServerContext* /* context */,
                                const sushi_rpc::ParameterIdRequest* request,
                                sushi_rpc::ParameterIdentifier* response)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id 
        && request->parametername() == expected_results::PARAMETER_WITH_ID_1.name)
        {
            response->set_processor_id(expected_results::PROCESSOR_WITH_ID_1.id);
            response->set_parameter_id(expected_results::PARAMETER_WITH_ID_1.id);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id and/or parameter with that name");
        }
        
    }

    grpc::Status GetParameterInfo(grpc::ServerContext* /* context */,
                                  const sushi_rpc::ParameterIdentifier* request,
                                  sushi_rpc::ParameterInfo* response)
    {
        if(request->processor_id() == expected_results::PROCESSOR_WITH_ID_1.id 
        && request->parameter_id() == expected_results::PARAMETER_WITH_ID_1.id)
        {
            response->set_id(expected_results::PARAMETER_WITH_ID_1.id);
            response->mutable_type()->set_type(sushi_rpc::ParameterType::FLOAT);
            response->set_name(expected_results::PARAMETER_WITH_ID_1.name);
            response->set_label(expected_results::PARAMETER_WITH_ID_1.label);
            response->set_unit(expected_results::PARAMETER_WITH_ID_1.unit);
            response->set_automatable(expected_results::PARAMETER_WITH_ID_1.automatable);
            response->set_min_domain_value(expected_results::PARAMETER_WITH_ID_1.min_domain_value);
            response->set_max_domain_value(expected_results::PARAMETER_WITH_ID_1.max_domain_value);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor and/or parameter with that id");
        }
        
    }

    grpc::Status GetParameterValue(grpc::ServerContext* /* context */,
                                   const sushi_rpc::ParameterIdentifier* request,
                                   sushi_rpc::GenericFloatValue* response)
    {
        if(request->processor_id() == expected_results::PROCESSOR_WITH_ID_1.id 
        && request->parameter_id() == expected_results::PARAMETER_WITH_ID_1.id)
        {
            response->set_value(expected_results::PARAMETER_NORMALISED_VALUE);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No procesor and/or parameter with that id");
        }
    }  

    grpc::Status GetParameterValueInDomain(grpc::ServerContext* /* context */,
                                           const sushi_rpc::ParameterIdentifier* request,
                                           sushi_rpc::GenericFloatValue* response)
    {
        if(request->processor_id() == expected_results::PROCESSOR_WITH_ID_1.id 
        && request->parameter_id() == expected_results::PARAMETER_WITH_ID_1.id)
        {
            response->set_value(expected_results::PARAMETER_DOMAIN_VALUE);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No procesor and/or parameter with that id");
        }
    }

    grpc::Status GetParameterValueAsString(grpc::ServerContext* /* context */,
                                   const sushi_rpc::ParameterIdentifier* request,
                                   sushi_rpc::GenericStringValue* response)
    {
        if(request->processor_id() == expected_results::PROCESSOR_WITH_ID_1.id 
        && request->parameter_id() == expected_results::PARAMETER_WITH_ID_1.id)
        {
            response->set_value(expected_results::PARAMETER_STRING_VALUE);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No procesor and/or parameter with that id");
        }
    }

    grpc::Status SetParameterValue(grpc::ServerContext* /* context */,
                                   const sushi_rpc::ParameterSetRequest* request,
                                   sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->parameter().processor_id() == expected_results::PROCESSOR_WITH_ID_1.id 
        && request->parameter().parameter_id() == expected_results::PARAMETER_WITH_ID_1.id 
        && request->value() == expected_results::PARAMETER_DOMAIN_VALUE)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No procesor and/or parameter with that id");
        }
    }

    grpc::Status SetParameterValueNormalised(grpc::ServerContext* /* context */,
                                   const sushi_rpc::ParameterSetRequest* request,
                                   sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->parameter().processor_id() == expected_results::PROCESSOR_WITH_ID_1.id 
        && request->parameter().parameter_id() == expected_results::PARAMETER_WITH_ID_1.id 
        && request->value() == expected_results::PARAMETER_NORMALISED_VALUE) 
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No procesor and/or parameter with that id");
        }
    }
=======


>>>>>>> develop

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
