#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "audio_graph_controller.h"

namespace sushi_controller
{

AudioGraphControllerClient::AudioGraphControllerClient(const std::string& address)
    : _stub(sushi_rpc::AudioGraphController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        ))) {}

std::pair<ControlStatus, std::vector<ProcessorInfo>> AudioGraphControllerClient::get_all_processors() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::ProcessorInfoList response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetAllProcessors(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    std::vector<ProcessorInfo> output;
    for (auto& processor : response.processors())
    {
        output.push_back(
            ProcessorInfo{
                processor.id(),
                processor.label(),
                processor.name(),
                processor.parameter_count(),
                processor.program_count()
            }
        );
    }
    return std::pair<ControlStatus, std::vector<ProcessorInfo>>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<TrackInfo>> AudioGraphControllerClient::get_all_tracks() const
{
    sushi_rpc::GenericVoidValue request;
    sushi_rpc::TrackInfoList response;
    grpc::ClientContext context;

    grpc::Status status = _stub.get()->GetAllTracks(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    std::vector<TrackInfo> output;
    for(auto& track : response.tracks())
    {
        std::vector<int> processor_ids;
        for (auto& processor : track.processors())
        {
            processor_ids.push_back(processor.id());
        }
        output.push_back(
            TrackInfo{
                track.id(),
                track.label(),
                track.name(),
                track.input_channels(),
                track.input_busses(),
                track.output_channels(),
                track.output_busses(),
                processor_ids
            }
        );
    }
    return std::pair<ControlStatus, std::vector<TrackInfo>>(to_ext(status), output);
}

std::pair<ControlStatus, int> AudioGraphControllerClient::get_track_id(const std::string& track_name) const
{
    sushi_rpc::GenericStringValue request;
    sushi_rpc::TrackIdentifier response;
    grpc::ClientContext context;

    request.set_value(track_name);

    grpc::Status status = _stub.get()->GetTrackId(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, int>(to_ext(status), response.id());
}

std::pair<ControlStatus, TrackInfo> AudioGraphControllerClient::get_track_info(int track_id) const
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::TrackInfo response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub.get()->GetTrackInfo(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    std::vector<int> processor_ids;
    for (auto& processor : response.processors())
    {
        processor_ids.push_back(processor.id());
    }
    TrackInfo output{
        response.id(),
        response.label(),
        response.name(),
        response.input_channels(),
        response.input_busses(),
        response.output_channels(),
        response.output_busses(),
        processor_ids
    };
    return std::pair<ControlStatus, TrackInfo>(to_ext(status), output);
}

std::pair<ControlStatus, std::vector<ProcessorInfo>> AudioGraphControllerClient::get_track_processors(int track_id) const
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::ProcessorInfoList response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub.get()->GetTrackProcessors(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    std::vector<ProcessorInfo> output;
    for (auto& processor : response.processors())
    {
        output.push_back(ProcessorInfo{
            processor.id(),
            processor.label(),
            processor.name(),
            processor.parameter_count(),
            processor.program_count()
        });
    }
    return std::pair<ControlStatus, std::vector<ProcessorInfo>>(to_ext(status),output);
}

std::pair<ControlStatus, int> AudioGraphControllerClient::get_processor_id(const std::string& processor_name) const
{
    sushi_rpc::GenericStringValue request;
    sushi_rpc::ProcessorIdentifier response;
    grpc::ClientContext context;

    request.set_value(processor_name);

    grpc::Status status = _stub.get()->GetProcessorId(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, int>(to_ext(status), response.id());
}

std::pair<ControlStatus, ProcessorInfo> AudioGraphControllerClient::get_processor_info(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::ProcessorInfo response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorInfo(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    ProcessorInfo output;
    output.id = response.id();
    output.label = response.label();
    output.name = response.name();
    output.parameter_count = response.parameter_count();
    output.program_count = response.program_count();
    return std::pair<ControlStatus, ProcessorInfo>(to_ext(status), output);
}

std::pair<ControlStatus, bool> AudioGraphControllerClient::get_processor_bypass_state(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::GenericBoolValue response;
    grpc::ClientContext context;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorBypassState(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return std::pair<ControlStatus, bool>(to_ext(status), response.value());
}

std::pair<ControlStatus, ProcessorState> AudioGraphControllerClient::get_processor_state(int processor_id) const
{
    sushi_rpc::ProcessorIdentifier request;
    sushi_rpc::ProcessorState response;
    grpc::ClientContext context;
    ProcessorState state;

    request.set_id(processor_id);

    grpc::Status status = _stub.get()->GetProcessorState(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    if (response.has_bypassed() && response.bypassed().has_value())
    {
        state.bypassed = response.bypassed().value();
    }
    if (response.has_program_id() && response.program_id().has_value())
    {
        state.program_id = response.program_id().value();
    }
    state.properties.reserve(response.properties_size());
    for (const auto& property : response.properties())
    {
        state.properties.emplace_back(property.property().property_id(), property.value());
    }
    state.parameters.reserve(response.parameters_size());
    for (const auto& parameter : response.parameters())
    {
        state.parameters.emplace_back(parameter.parameter().parameter_id(), parameter.value());
    }
    state.binary_data = response.binary_data();

    return std::pair<ControlStatus, ProcessorState>(to_ext(status), state);
}

ControlStatus AudioGraphControllerClient::set_processor_bypass_state(int processor_id, bool bypass_enabled)
{
    sushi_rpc::ProcessorBypassStateSetRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);
    request.set_value(bypass_enabled);

    grpc::Status status = _stub.get()->SetProcessorBypassState(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus AudioGraphControllerClient::set_processor_state(int processor_id, const ProcessorState state)
{
    sushi_rpc::ProcessorStateSetRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor_id);

    if (state.program_id.has_value())
    {
        request.mutable_state()->mutable_program_id()->set_value(state.program_id.value());
        request.mutable_state()->mutable_program_id()->set_has_value(true);
    }
    if (state.bypassed.has_value())
    {
        request.mutable_state()->mutable_bypassed()->set_value(state.bypassed.value());
        request.mutable_state()->mutable_bypassed()->set_has_value(true);
    }
    request.mutable_state()->mutable_properties()->Reserve(state.properties.size());
    for (const auto& property : state.properties)
    {
        auto target = request.mutable_state()->mutable_properties()->Add();
        target->mutable_property()->set_property_id(property.first);
        target->set_value(property.second);
    }
    request.mutable_state()->mutable_parameters()->Reserve(state.parameters.size());
    for (const auto& parameter : state.parameters)
    {
        auto target = request.mutable_state()->mutable_parameters()->Add();
        target->mutable_parameter()->set_parameter_id(parameter.first);
        target->set_value(parameter.second);
    }
    request.mutable_state()->set_binary_data(state.binary_data);

    grpc::Status status = _stub.get()->SetProcessorState(&context, request, &response);

    if (!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus AudioGraphControllerClient::create_track(const std::string& name, int channels)
{
    sushi_rpc::CreateTrackRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_name(name);
    request.set_channels(channels);

    grpc::Status status = _stub.get()->CreateTrack(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus AudioGraphControllerClient::create_multibus_track(const std::string& name,
                                                                int output_busses,
                                                                int input_busses)
{
    sushi_rpc::CreateMultibusTrackRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_name(name);
    request.set_output_busses(output_busses);
    request.set_input_busses(input_busses);

    grpc::Status status = _stub.get()->CreateMultibusTrack(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus AudioGraphControllerClient::create_processor_on_track(const std::string& name,
                                                                    const std::string& uid,
                                                                    const std::string& path,
                                                                    PluginType type,
                                                                    int track_id,
                                                                    int before_processor,
                                                                    bool add_to_back)
{
    sushi_rpc::CreateProcessorRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_name(name);
    request.set_uid(uid);
    request.set_path(path);
    request.mutable_type()->set_type(to_grpc(type));
    request.mutable_track()->set_id(track_id);
    request.mutable_position()->mutable_before_processor()->set_id(before_processor);
    request.mutable_position()->set_add_to_back(add_to_back);

    grpc::Status status = _stub.get()->CreateProcessorOnTrack(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus AudioGraphControllerClient::move_processor_on_track(int processor,
                                                                  int source_track,
                                                                  int destination_track,
                                                                  int before_processor,
                                                                  bool add_to_back)
{
    sushi_rpc::MoveProcessorRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor);
    request.mutable_source_track()->set_id(source_track);
    request.mutable_dest_track()->set_id(destination_track);
    request.mutable_position()->mutable_before_processor()->set_id(before_processor);
    request.mutable_position()->set_add_to_back(add_to_back);

    grpc::Status status = _stub.get()->MoveProcessorOnTrack(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus AudioGraphControllerClient::delete_processor_from_track(int processor,
                                                                      int track)
{
    sushi_rpc::DeleteProcessorRequest request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.mutable_processor()->set_id(processor);
    request.mutable_track()->set_id(track);

    grpc::Status status = _stub.get()->DeleteProcessorFromTrack(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

ControlStatus AudioGraphControllerClient::delete_track(int track_id)
{
    sushi_rpc::TrackIdentifier request;
    sushi_rpc::GenericVoidValue response;
    grpc::ClientContext context;

    request.set_id(track_id);

    grpc::Status status = _stub.get()->DeleteTrack(&context, request, &response);

    if(!status.ok())
    {
        handle_error(status);
    }
    return to_ext(status);
}

std::shared_ptr<AudioGraphController> CreateAudioGraphController(const std::string& server_address)
{
    return std::make_shared<AudioGraphControllerClient>(server_address);
}

} // namespace sushi_controller

