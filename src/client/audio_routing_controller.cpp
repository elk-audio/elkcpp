#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "audio_routing_controller.h"

namespace sushi_controller
{

AudioRoutingControllerClient::AudioRoutingControllerClient(const std::string& address)
    : _stub(sushi_rpc::AudioRoutingController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        ))) {}


    std::pair<ControlStatus, std::vector<AudioConnection>> AudioRoutingControllerClient::get_all_input_connections() const
    {
        sushi_rpc::GenericVoidValue request;
        sushi_rpc::AudioConnectionList response;
        grpc::ClientContext context;

        grpc::Status status = _stub->GetAllInputConnections(&context, request, &response);

        std::vector<AudioConnection> output;
        for (auto& response_connection : response.connections())
        {
            output.push_back({response_connection.track().id(),
                              response_connection.track_channel(),
                              response_connection.engine_channel()});
        }

        if(!status.ok())
        {
            handle_error(status);
        }
        return std::pair<ControlStatus, std::vector<AudioConnection>>(to_ext(status), output);
    }

    std::pair<ControlStatus, std::vector<AudioConnection>> AudioRoutingControllerClient::get_all_output_connections() const
    {
        sushi_rpc::GenericVoidValue request;
        sushi_rpc::AudioConnectionList response;
        grpc::ClientContext context;

        grpc::Status status = _stub->GetAllOutputConnections(&context, request, &response);

        std::vector<AudioConnection> output;
        for (auto& response_connection : response.connections())
        {
            output.push_back({response_connection.track().id(),
                              response_connection.track_channel(),
                              response_connection.engine_channel()});
        }

        if(!status.ok())
        {
            handle_error(status);
        }
        return std::pair<ControlStatus, std::vector<AudioConnection>>(to_ext(status), output);
    }

    std::pair<ControlStatus, std::vector<AudioConnection>> AudioRoutingControllerClient::get_input_connections_for_track(int track_id) const
    {
        sushi_rpc::TrackIdentifier request;
        sushi_rpc::AudioConnectionList response;
        grpc::ClientContext context;

        request.set_id(track_id);

        grpc::Status status = _stub->GetInputConnectionsForTrack(&context, request, &response);

        std::vector<AudioConnection> output;
        for (auto& response_connection : response.connections())
        {
            output.push_back({response_connection.track().id(),
                              response_connection.track_channel(),
                              response_connection.engine_channel()});
        }

        if(!status.ok())
        {
            handle_error(status);
        }
        return std::pair<ControlStatus, std::vector<AudioConnection>>(to_ext(status), output);
    }

    std::pair<ControlStatus, std::vector<AudioConnection>> AudioRoutingControllerClient::get_output_connections_for_track(int track_id) const
    {
        sushi_rpc::TrackIdentifier request;
        sushi_rpc::AudioConnectionList response;
        grpc::ClientContext context;

        request.set_id(track_id);

        grpc::Status status = _stub->GetOutputConnectionsForTrack(&context, request, &response);

        std::vector<AudioConnection> output;
        for (auto& response_connection : response.connections())
        {
            output.push_back({response_connection.track().id(),
                              response_connection.track_channel(),
                              response_connection.engine_channel()});
        }

        if(!status.ok())
        {
            handle_error(status);
        }
        return std::pair<ControlStatus, std::vector<AudioConnection>>(to_ext(status), output);
    }

    ControlStatus AudioRoutingControllerClient::connect_input_channel_to_track(int track_id, int track_channel, int input_channel)
    {
        sushi_rpc::AudioConnection request;
        sushi_rpc::GenericVoidValue response;
        grpc::ClientContext context;

        request.mutable_track()->set_id(track_id);
        request.set_track_channel(track_channel);
        request.set_engine_channel(input_channel);

        grpc::Status status = _stub->ConnectInputChannelToTrack(&context, request, &response);

        if(!status.ok())
        {
            handle_error(status);
        }
        return to_ext(status);
    }

    ControlStatus AudioRoutingControllerClient::connect_output_channel_from_track(int track_id, int track_channel, int output_channel)
    {
        sushi_rpc::AudioConnection request;
        sushi_rpc::GenericVoidValue response;
        grpc::ClientContext context;

        request.mutable_track()->set_id(track_id);
        request.set_track_channel(track_channel);
        request.set_engine_channel(output_channel);

        grpc::Status status = _stub->ConnectOutputChannelFromTrack(&context, request, &response);

        if(!status.ok())
        {
            handle_error(status);
        }
        return to_ext(status);
    }

    ControlStatus AudioRoutingControllerClient::disconnect_input(int track_id, int track_channel, int input_channel)
    {
        sushi_rpc::AudioConnection request;
        sushi_rpc::GenericVoidValue response;
        grpc::ClientContext context;

        request.mutable_track()->set_id(track_id);
        request.set_track_channel(track_channel);
        request.set_engine_channel(input_channel);

        grpc::Status status = _stub->DisconnectInput(&context, request, &response);

        if(!status.ok())
        {
            handle_error(status);
        }
        return to_ext(status);
    }

    ControlStatus AudioRoutingControllerClient::disconnect_output(int track_id, int track_channel, int output_channel)
    {
        sushi_rpc::AudioConnection request;
        sushi_rpc::GenericVoidValue response;
        grpc::ClientContext context;

        request.mutable_track()->set_id(track_id);
        request.set_track_channel(track_channel);
        request.set_engine_channel(output_channel);

        grpc::Status status = _stub->DisconnectOutput(&context, request, &response);

        if(!status.ok())
        {
            handle_error(status);
        }
        return to_ext(status);
    }

    ControlStatus AudioRoutingControllerClient::disconnect_all_inputs_from_track(int track_id)
    {
        sushi_rpc::TrackIdentifier request;
        sushi_rpc::GenericVoidValue response;
        grpc::ClientContext context;

        request.set_id(track_id);

        grpc::Status status = _stub->DisconnectAllInputsFromTrack(&context, request, &response);

        if(!status.ok())
        {
            handle_error(status);
        }
        return to_ext(status);
    }

    ControlStatus AudioRoutingControllerClient::disconnect_all_outputs_from_track(int track_id)
    {
        sushi_rpc::TrackIdentifier request;
        sushi_rpc::GenericVoidValue response;
        grpc::ClientContext context;

        request.set_id(track_id);

        grpc::Status status = _stub->DisconnectAllOutputsFromTrack(&context, request, &response);

        if(!status.ok())
        {
            handle_error(status);
        }
        return to_ext(status);    }

std::shared_ptr<AudioRoutingController> CreateAudioRoutingController(const std::string& address)
{
    return std::make_shared<AudioRoutingControllerClient>(address);
}

} // namespace sushi_controller
