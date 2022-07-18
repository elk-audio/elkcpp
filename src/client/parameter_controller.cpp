#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "parameter_controller.h"


namespace sushi_controller
{

inline sushi_controller::ParameterType to_ext(const sushi_rpc::ParameterType::Type& type)
{
    switch (type)
    {
        case sushi_rpc::ParameterType::INT:             return sushi_controller::ParameterType::INT;
        case sushi_rpc::ParameterType::FLOAT:           return sushi_controller::ParameterType::FLOAT;
        case sushi_rpc::ParameterType::BOOL:            return sushi_controller::ParameterType::BOOL;
        default:                                        return sushi_controller::ParameterType::INT;
    }
}

ParameterControllerClient::ParameterControllerClient(const std::string& address)
    : _stub(sushi_rpc::ParameterController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        ))) {}

std::pair<ControlStatus, std::vector<ParameterInfo>> ParameterControllerClient::get_track_parameters(int track_id) const
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::ParameterInfoList response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub->GetTrackParameters(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    std::vector<ParameterInfo> output;
    for(int i = 0; i < response.parameters_size(); ++i)
    {
        output.push_back(
            ParameterInfo{
                response.parameters(i).id(),
                to_ext(response.parameters(i).type().type()),
                response.parameters(i).label(),
                response.parameters(i).name(),
                response.parameters(i).unit(),
                response.parameters(i).automatable(),
                response.parameters(i).min_domain_value(),
                response.parameters(i).max_domain_value()
            }
        );
    }
    return {to_ext(status), output};
}

std::pair<ControlStatus, std::vector<ParameterInfo>> ParameterControllerClient::get_processor_parameters(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::ParameterInfoList response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->GetProcessorParameters(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    std::vector<ParameterInfo> output;
    for(int i = 0; i < response.parameters_size(); ++i)
    {
        output.push_back(
            ParameterInfo{
                response.parameters(i).id(),
                to_ext(response.parameters(i).type().type()),
                response.parameters(i).label(),
                response.parameters(i).name(),
                response.parameters(i).unit(),
                response.parameters(i).automatable(),
                response.parameters(i).min_domain_value(),
                response.parameters(i).max_domain_value()
            }
        );
    }
    return {to_ext(status), output};
}

std::pair<ControlStatus, int> ParameterControllerClient::get_parameter_id(int processor_id, const std::string& parameter) const
{
    sushi_rpc::ParameterIdRequest request;
    sushi_rpc::ParameterIdentifier response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.set_parametername(parameter);

    grpc::Status status = _stub->GetParameterId(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return {to_ext(status), response.parameter_id()};
}

std::pair<ControlStatus, ParameterInfo> ParameterControllerClient::get_parameter_info(int processor_id, int parameter_id) const
{
    sushi_rpc::ParameterIdentifier request;
    sushi_rpc::ParameterInfo response;
    grpc::ClientContext context;

    request.set_processor_id(processor_id);
    request.set_parameter_id(parameter_id);

    grpc::Status status = _stub->GetParameterInfo(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    ParameterInfo output{
        response.id(),
        to_ext(response.type().type()),
        response.label(),
        response.name(),
        response.unit(),
        response.automatable(),
        response.min_domain_value(),
        response.max_domain_value()
    };
    return {to_ext(status), output};
}

std::pair<ControlStatus, float> ParameterControllerClient::get_parameter_value(int processor_id, int parameter_id) const
{
    sushi_rpc::ParameterIdentifier request;
    sushi_rpc::GenericFloatValue response;
    grpc::ClientContext context;

    request.set_processor_id(processor_id);
    request.set_parameter_id(parameter_id);

    grpc::Status status = _stub->GetParameterValue(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return {to_ext(status), response.value()};
}

std::pair<ControlStatus, float> ParameterControllerClient::get_parameter_value_in_domain(int processor_id, int parameter_id) const
{
    sushi_rpc::ParameterIdentifier request;
    sushi_rpc::GenericFloatValue response;
    grpc::ClientContext context;

    request.set_processor_id(processor_id);
    request.set_parameter_id(parameter_id);

    grpc::Status status = _stub->GetParameterValueInDomain(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return {to_ext(status), response.value()};
}

std::pair<ControlStatus, std::string> ParameterControllerClient::get_parameter_value_as_string(int processor_id, int parameter_id) const
{
    sushi_rpc::ParameterIdentifier request;
    sushi_rpc::GenericStringValue response;
    grpc::ClientContext context;

    request.set_processor_id(processor_id);
    request.set_parameter_id(parameter_id);

    grpc::Status status = _stub->GetParameterValueAsString(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return {to_ext(status), response.value()};
}

ControlStatus ParameterControllerClient::set_parameter_value(int processor_id, int parameter_id, float value)
{
    sushi_rpc::ParameterValue request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_parameter()->set_processor_id(processor_id);
    request.mutable_parameter()->set_parameter_id(parameter_id);
    request.set_value(value);

    grpc::Status status = _stub->SetParameterValue(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::pair<ControlStatus, std::vector<PropertyInfo>> ParameterControllerClient::get_track_properties(int track_id) const
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::PropertyInfoList response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub->GetTrackProperties(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    std::vector<PropertyInfo> output;
    for(int i = 0; i < response.properties_size(); ++i)
    {
        output.push_back(
                PropertyInfo{
                    response.properties(i).id(),
                    response.properties(i).name(),
                    response.properties(i).label(),
                }
        );
    }
    return {to_ext(status), output};
}

std::pair<ControlStatus, std::vector<PropertyInfo>> ParameterControllerClient::get_processor_properties(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::PropertyInfoList response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->GetProcessorProperties(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    std::vector<PropertyInfo> output;
    for(int i = 0; i < response.properties_size(); ++i)
    {
        output.push_back(
                PropertyInfo{
                        response.properties(i).id(),
                        response.properties(i).name(),
                        response.properties(i).label(),
                }
        );
    }
    return {to_ext(status), output};
}

std::pair<ControlStatus, int> ParameterControllerClient::get_property_id(int processor_id, const std::string& property_name) const
{
    sushi_rpc::PropertyIdRequest request;
    sushi_rpc::PropertyIdentifier response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.set_property_name(property_name);

    grpc::Status status = _stub->GetPropertyId(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return {to_ext(status), response.property_id()};
}

std::pair<ControlStatus, PropertyInfo> ParameterControllerClient::get_property_info(int processor_id, int property_id) const
{
    sushi_rpc::PropertyIdentifier request;
    sushi_rpc::PropertyInfo response;
    grpc::ClientContext context;

    request.set_processor_id(processor_id);
    request.set_property_id(property_id);

    grpc::Status status = _stub->GetPropertyInfo(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    PropertyInfo output{
            response.id(),
            response.name(),
            response.label(),
    };
    return {to_ext(status), output};
}

std::pair<ControlStatus, std::string> ParameterControllerClient::get_property_value(int processor_id, int property_id) const
{
    sushi_rpc::PropertyIdentifier request;
    sushi_rpc::GenericStringValue response;
    grpc::ClientContext context;

    request.set_processor_id(processor_id);
    request.set_property_id(property_id);

    grpc::Status status = _stub->GetPropertyValue(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return {to_ext(status), response.value()};
}

ControlStatus ParameterControllerClient::set_property_value(int processor_id, int property_id, std::string value)
{
    sushi_rpc::PropertyValue request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_property()->set_processor_id(processor_id);
    request.mutable_property()->set_property_id(property_id);
    request.set_value(value);

    grpc::Status status = _stub->SetPropertyValue(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::shared_ptr<ParameterController> CreateParameterController(const std::string& server_address)
{
    return std::make_shared<ParameterControllerClient>(server_address);
}

} // namespace sushi_controller

