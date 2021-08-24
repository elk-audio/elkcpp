#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "midi_controller.h"

namespace sushi_controller
{

MidiControllerClient::MidiControllerClient(const std::string& address)
    : _stub(sushi_rpc::MidiController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        ))) {}


std::pair<ControlStatus, int> MidiControllerClient::get_input_ports()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericIntValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetInputPorts(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, int>(to_ext(status), response.value());
}

std::pair<ControlStatus, int> MidiControllerClient::get_output_ports()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::GenericIntValue response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetOutputPorts(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, int>(to_ext(status), response.value());
}

std::pair<ControlStatus, std::vector<MidiKbdConnection>> MidiControllerClient::get_all_kbd_input_connections()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::MidiKbdConnectionList response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetAllKbdInputConnections(&context, request, &response);

    std::vector<MidiKbdConnection> output;
    for (auto& connection : response.connections())
    {
        output.push_back({
            connection.track().id(),
            to_ext(connection.channel().channel()),
            connection.port(),
            connection.raw_midi()
        });
    }
    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<MidiKbdConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<MidiKbdConnection>> MidiControllerClient::get_all_kbd_output_connections()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::MidiKbdConnectionList response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetAllKbdOutputConnections(&context, request, &response);

    std::vector<MidiKbdConnection> output;
    for (auto& connection : response.connections())
    {
        output.push_back({
            connection.track().id(),
            to_ext(connection.channel().channel()),
            connection.port(),
            connection.raw_midi()
        });
    }
    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<MidiKbdConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<MidiCCConnection>> MidiControllerClient::get_all_cc_input_connections()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::MidiCCConnectionList response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetAllCCInputConnections(&context, request, &response);

    std::vector<MidiCCConnection> output;
    for (auto& connection : response.connections())
    {
        output.push_back({
            connection.parameter().parameter_id(),
            connection.parameter().processor_id(),
            to_ext(connection.channel().channel()),
            connection.port(),
            connection.cc_number(),
            connection.min_range(),
            connection.max_range(),
            connection.relative_mode()
        });
    }
    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<MidiCCConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<MidiPCConnection>> MidiControllerClient::get_all_pc_input_connections()
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::MidiPCConnectionList response;
    grpc::ClientContext context;

    grpc::Status status = _stub->GetAllPCInputConnections(&context, request, &response);

    std::vector<MidiPCConnection> output;
    for (auto& connection : response.connections())
    {
        output.push_back({
            connection.processor().id(),
            to_ext(connection.channel().channel()),
            connection.port()
        });
    }
    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<MidiPCConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<MidiCCConnection>> MidiControllerClient::get_cc_input_connections_for_processor(int processor_id)
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::MidiCCConnectionList response;
    grpc::ClientContext context;

    request.set_id(processor_id);
    grpc::Status status = _stub->GetCCInputConnectionsForProcessor(&context, request, &response);

    std::vector<MidiCCConnection> output;
    for (auto& connection : response.connections())
    {
        output.push_back({
            connection.parameter().parameter_id(),
            connection.parameter().processor_id(),
            to_ext(connection.channel().channel()),
            connection.port(),
            connection.cc_number(),
            connection.min_range(),
            connection.max_range(),
            connection.relative_mode()
        });
    }
    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<MidiCCConnection>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<MidiPCConnection>> MidiControllerClient::get_pc_input_connections_for_processor(int processor_id)
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::MidiPCConnectionList response;
    grpc::ClientContext context;

    request.set_id(processor_id);
    grpc::Status status = _stub->GetPCInputConnectionsForProcessor(&context, request, &response);

    std::vector<MidiPCConnection> output;
    for (auto& connection : response.connections())
    {
        output.push_back({
            connection.processor().id(),
            to_ext(connection.channel().channel()),
            connection.port()
        });
    }
    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, std::vector<MidiPCConnection>>(to_ext(status), output);
}

ControlStatus MidiControllerClient::connect_kbd_input_to_track(MidiKbdConnection connection_data)
{
    sushi_rpc::MidiKbdConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_track()->set_id(connection_data.track_id);
    request.mutable_channel()->set_channel(to_grpc(connection_data.channel));
    request.set_port(connection_data.port);
    request.set_raw_midi(connection_data.raw_midi);

    grpc::Status status = _stub->ConnectKbdInputToTrack(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus MidiControllerClient::connect_kbd_output_from_track(MidiKbdConnection connection_data)
{
    sushi_rpc::MidiKbdConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_track()->set_id(connection_data.track_id);
    request.mutable_channel()->set_channel(to_grpc(connection_data.channel));
    request.set_port(connection_data.port);
    request.set_raw_midi(connection_data.raw_midi);

    grpc::Status status = _stub->ConnectKbdOutputFromTrack(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus MidiControllerClient::connect_cc_to_parameter(MidiCCConnection connection_data)
{
    sushi_rpc::MidiCCConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_parameter()->set_parameter_id(connection_data.parameter_id);
    request.mutable_parameter()->set_processor_id(connection_data.processor_id);
    request.mutable_channel()->set_channel(to_grpc(connection_data.channel));
    request.set_port(connection_data.port);
    request.set_cc_number(connection_data.cc_number);
    request.set_min_range(connection_data.min_range);
    request.set_max_range(connection_data.max_range);
    request.set_relative_mode(connection_data.relative_mode);

    grpc::Status status = _stub->ConnectCCToParameter(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus MidiControllerClient::connect_pc_to_processor(MidiPCConnection connection_data)
{
    sushi_rpc::MidiPCConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(connection_data.processor_id);
    request.mutable_channel()->set_channel(to_grpc(connection_data.channel));
    request.set_port(connection_data.port);

    grpc::Status status = _stub->ConnectPCToProcessor(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus MidiControllerClient::disconnect_kbd_input(MidiKbdConnection connection_data)
{
    sushi_rpc::MidiKbdConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_track()->set_id(connection_data.track_id);
    request.mutable_channel()->set_channel(to_grpc(connection_data.channel));
    request.set_port(connection_data.port);
    request.set_raw_midi(connection_data.raw_midi);

    grpc::Status status = _stub->DisconnectKbdInput(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus MidiControllerClient::disconnect_kbd_output(MidiKbdConnection connection_data)
{
    sushi_rpc::MidiKbdConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_track()->set_id(connection_data.track_id);
    request.mutable_channel()->set_channel(to_grpc(connection_data.channel));
    request.set_port(connection_data.port);
    request.set_raw_midi(connection_data.raw_midi);

    grpc::Status status = _stub->DisconnectKbdOutput(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus MidiControllerClient::disconnect_cc(MidiCCConnection connection_data)
{
    sushi_rpc::MidiCCConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_parameter()->set_parameter_id(connection_data.parameter_id);
    request.mutable_parameter()->set_processor_id(connection_data.processor_id);
    request.mutable_channel()->set_channel(to_grpc(connection_data.channel));
    request.set_port(connection_data.port);
    request.set_cc_number(connection_data.cc_number);
    request.set_min_range(connection_data.min_range);
    request.set_max_range(connection_data.max_range);
    request.set_relative_mode(connection_data.relative_mode);

    grpc::Status status = _stub->DisconnectCC(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus MidiControllerClient::disconnect_pc(MidiPCConnection connection_data)
{
    sushi_rpc::MidiPCConnection request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(connection_data.processor_id);
    request.mutable_channel()->set_channel(to_grpc(connection_data.channel));
    request.set_port(connection_data.port);

    grpc::Status status = _stub->DisconnectPC(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus MidiControllerClient::disconnect_all_cc_from_processor(int processor_id)
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->DisconnectAllCCFromProcessor(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus MidiControllerClient::disconnect_all_pc_from_processor(int processor_id)
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub->DisconnectAllPCFromProcessor(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::shared_ptr<MidiController> CreateMidiController(const std::string& address)
{
    return std::move(std::make_unique<MidiControllerClient>(address));
}
} // namespace sushi_controller

