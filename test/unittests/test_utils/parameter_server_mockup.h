#ifndef ELKCPP_PARAMETER_SERVER_MOCKUP_H
#define ELKCPP_PARAMETER_SERVER_MOCKUP_H

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
    // Processor test values
    const ProcessorInfo PROCESSOR_WITH_ID_1 = ProcessorInfo{1, "synth1", "synth1", 2, 2};
    const ProcessorInfo PROCESSOR_WITH_ID_2 = ProcessorInfo{2, "delay1", "delay1", 2, 2};
    const std::vector<ProcessorInfo> PROCESSOR_INFO_LIST = {PROCESSOR_WITH_ID_1, PROCESSOR_WITH_ID_2};
    constexpr bool PROCESSOR_BYPASS_STATE = true;

    // Parameter test values
    constexpr ParameterType PARAMETER_TYPE{ParameterType::FLOAT};
    constexpr float PARAMETER_VALUE{5.34f};
    constexpr float PARAMETER_NORMALISED_VALUE{0.87f};
    const std::string PARAMETER_STRING_VALUE{"5.34"};
    const ParameterInfo PARAMETER_WITH_ID_1 = ParameterInfo{1, PARAMETER_TYPE, "param1", "param1", "Hz", true, 0.0f, 1.0f};
    const ParameterInfo PARAMETER_WITH_ID_2 = ParameterInfo{2, PARAMETER_TYPE, "param2", "param2", "Hz", true, 0.0f, 1.0f};
    const std::vector<ParameterInfo> PARAMETER_INFO_LIST = {PARAMETER_WITH_ID_1, PARAMETER_WITH_ID_2};

    // Property test value
    constexpr auto PROPERTY_VALUE{"value"};
    const PropertyInfo PROPERTY_WITH_ID_3 = PropertyInfo{3, "property_1", "Property 1"};
    const PropertyInfo PROPERTY_WITH_ID_4 = PropertyInfo{4, "property_2", "Property 2"};
    const std::vector<PropertyInfo> PROPERTY_INFO_LIST = {PROPERTY_WITH_ID_3, PROPERTY_WITH_ID_4};

} // namespace expected_results


class ParameterServiceMockup : public sushi_rpc::ParameterController::Service
{

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
            response->set_value(expected_results::PARAMETER_VALUE);
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
            response->set_value(expected_results::PARAMETER_NORMALISED_VALUE);
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
                                   const sushi_rpc::ParameterValue* request,
                                   sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->parameter().processor_id() == expected_results::PROCESSOR_WITH_ID_1.id
        && request->parameter().parameter_id() == expected_results::PARAMETER_WITH_ID_1.id
        && request->value() == expected_results::PARAMETER_VALUE)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No procesor and/or parameter with that id");
        }
    }

    grpc::Status GetTrackProperties(grpc::ServerContext* /* context */,
                                    const sushi_rpc::TrackIdentifier* request,
                                    sushi_rpc::PropertyInfoList* response)
    {
        if (request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            for(uint i = 0; i < expected_results::PROPERTY_INFO_LIST.size(); ++i)
            {
                auto property = response->add_properties();
                property->set_id(expected_results::PROPERTY_INFO_LIST.at(i).id);
                property->set_label(expected_results::PROPERTY_INFO_LIST.at(i).label);
                property->set_name(expected_results::PROPERTY_INFO_LIST.at(i).name);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No track with that id");
        }
    }

    grpc::Status GetProcessorProperties(grpc::ServerContext* /* context */,
                                        const sushi_rpc::ProcessorIdentifier* request,
                                        sushi_rpc::PropertyInfoList* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            for(uint i = 0; i < expected_results::PROPERTY_INFO_LIST.size(); ++i)
            {
                auto property = response->add_properties();
                property->set_id(expected_results::PROPERTY_INFO_LIST.at(i).id);
                property->set_label(expected_results::PROPERTY_INFO_LIST.at(i).label);
                property->set_name(expected_results::PROPERTY_INFO_LIST.at(i).name);
            }
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status GetPropertyId(grpc::ServerContext* /* context */,
                               const sushi_rpc::PropertyIdRequest* request,
                               sushi_rpc::PropertyIdentifier* response)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id
           && request->property_name() == expected_results::PROPERTY_WITH_ID_3.name)
        {
            response->set_processor_id(expected_results::PROCESSOR_WITH_ID_1.id);
            response->set_property_id(expected_results::PROPERTY_WITH_ID_3.id);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id and/or property with that name");
        }

    }

    grpc::Status GetPropertyInfo(grpc::ServerContext* /* context */,
                                 const sushi_rpc::PropertyIdentifier* request,
                                 sushi_rpc::PropertyInfo* response)
    {
        if(request->processor_id() == expected_results::PROCESSOR_WITH_ID_1.id
           && request->property_id() == expected_results::PROPERTY_WITH_ID_3.id)
        {
            response->set_id(expected_results::PROPERTY_WITH_ID_3.id);
            response->set_name(expected_results::PROPERTY_WITH_ID_3.name);
            response->set_label(expected_results::PROPERTY_WITH_ID_3.label);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor and/or property with that id");
        }

    }

    grpc::Status GetPropertyValue(grpc::ServerContext* /* context */,
                                  const sushi_rpc::PropertyIdentifier* request,
                                  sushi_rpc::GenericStringValue* response)
    {
        if(request->processor_id() == expected_results::PROCESSOR_WITH_ID_1.id
           && request->property_id() == expected_results::PROPERTY_WITH_ID_4.id)
        {
            response->set_value(expected_results::PROPERTY_VALUE);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor and/or property with that id");
        }
    }

    grpc::Status SetPropertyValue(grpc::ServerContext* /* context */,
                                  const sushi_rpc::PropertyValue* request,
                                  sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->property().processor_id() == expected_results::PROCESSOR_WITH_ID_1.id
           && request->property().property_id() == expected_results::PROPERTY_WITH_ID_3.id
           && request->value() == expected_results::PROPERTY_VALUE)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No procesor and/or property with that id");
        }
    }


};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class ParameterServerMockup
{
public:
    ParameterServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~ParameterServerMockup()
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
    ParameterServiceMockup service;

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


#endif // ELKCPP_PARAMETER_SERVER_MOCKUP_H
