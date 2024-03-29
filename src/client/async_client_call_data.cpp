#include "async_client_call_data.h"
#include "grpc_utils.h"

namespace sushi_controller {

void SubscribeToTransportChangesCallData::proceed()
{
    if (_status == CREATE)
    {
        // Format blocklist
        auto request = sushi_rpc::GenericVoidValue();
        // Request response from server
        _reader = _stub->AsyncSubscribeToTransportChanges(&_ctx, request, _cq, this);
        _status = PROCESS;
    }
    else if (_status == PROCESS)
    {
        // Read one notification
        _reader->Read(&_response, this);

        // first iteration returns an empty message so we discard it.
        if (_first_iteration)
        {
            _first_iteration = false;
        }
        else
        {
            TransportUpdate update;
            TransportUpdateType type;
            if (_response.has_playing_mode())
            {
                update = to_ext(_response.playing_mode().mode());
                type = TransportUpdateType::PLAYING_MODE;
            }
            else if (_response.has_sync_mode())
            {
                update = to_ext(_response.sync_mode().mode());
                type = TransportUpdateType::SYNC_MODE;
            }
            else if (_response.has_time_signature())
            {
                TimeSignature time_signature;
                time_signature.numerator = _response.time_signature().numerator();
                time_signature.denominator = _response.time_signature().denominator();
                update = time_signature;
                type = TransportUpdateType::TIME_SIGNATURE;
            }
            else
            {
                update = _response.tempo();
                type = TransportUpdateType::TEMPO;
            }
            // Call callback
            _callback(update, type);
        }
    }
    else
    {
        assert(_status == FINISH);
        _ctx.TryCancel();
    }
}

void SubscribeToEngineCpuTimingUpdatesCallData::proceed()
{
    if (_status == CREATE)
    {
        // Format blocklist
        auto request = sushi_rpc::GenericVoidValue();
        // Request response from server
        _reader = _stub->AsyncSubscribeToEngineCpuTimingUpdates(&_ctx, request, _cq, this);
        _status = PROCESS;
    }
    else if (_status == PROCESS)
    {
        // Read one notification
        _reader->Read(&_response, this);

        // first iteration returns an empty message so we discard it.
        if (_first_iteration)
        {
            _first_iteration = false;
        }
        else
        {
            // Call callback
            _callback({_response.average(), _response.min(), _response.max()});
        }
    }
    else
    {
        assert(_status == FINISH);
        _ctx.TryCancel();
    }
}

void SubscribeToTrackChangesCallData::proceed()
{
    if (_status == CREATE)
    {
        // Format blocklist
        auto request = sushi_rpc::GenericVoidValue();
        // Request response from server
        _reader = _stub->AsyncSubscribeToTrackChanges(&_ctx, request, _cq, this);
        _status = PROCESS;
    }
    else if (_status == PROCESS)
    {
        // Read one notification
        _reader->Read(&_response, this);

        // first iteration returns an empty message so we discard it.
        if (_first_iteration)
        {
            _first_iteration = false;
        }
        else
        {
            // Call callback
            _callback({to_ext(_response.action()), _response.track().id()});
        }
    }
    else
    {
        assert(_status == FINISH);
        _ctx.TryCancel();
    }
}

void SubscribeToProcessorChangesCallData::proceed()
{
    if (_status == CREATE)
    {
        // Format blocklist
        auto request = sushi_rpc::GenericVoidValue();
        // Request response from server
        _reader = _stub->AsyncSubscribeToProcessorChanges(&_ctx, request, _cq, this);
        _status = PROCESS;
    }
    else if (_status == PROCESS)
    {
        // Read one notification
        _reader->Read(&_response, this);

        // first iteration returns an empty message so we discard it.
        if (_first_iteration)
        {
            _first_iteration = false;
        }
        else
        {
            // Call callback
            _callback({to_ext(_response.action()),
                      _response.processor().id(),
                      _response.parent_track().id()});
        }
    }
    else
    {
        assert(_status == FINISH);
        _ctx.TryCancel();
    }
}

void SubscribeToParameterUpdatesCallData::proceed()
{
    if (_status == CREATE)
    {
        // Format blocklist
        auto request = sushi_rpc::ParameterNotificationBlocklist();
        for (const auto& parameter : _parameter_blocklist)
        {
            auto parameter_to_add = request.add_parameters();
            parameter_to_add->set_parameter_id(parameter.first);
            parameter_to_add->set_processor_id(parameter.second);
        }
        // Request response from server
        _reader = _stub->AsyncSubscribeToParameterUpdates(&_ctx, request, _cq, this);
        _status = PROCESS;
    }
    else if (_status == PROCESS)
    {
        // Read one notification
        _reader->Read(&_response, this);

        // first iteration returns an empty message so we discard it.
        if (_first_iteration)
        {
            _first_iteration = false;
        }
        else
        {
            // Call callback
            _callback(_response.parameter().processor_id(),
                      _response.parameter().parameter_id(),
                      _response.normalized_value(),
                      _response.domain_value(),
                      _response.formatted_value());
        }
    }
    else
    {
        assert(_status == FINISH);
        _ctx.TryCancel();
    }
}

void SubscribeToPropertyUpdatesCallData::proceed()
{
    if (_status == CREATE)
    {
        // Format blocklist
        auto request = sushi_rpc::PropertyNotificationBlocklist();
        for (const auto& property : _blocklist)
        {
            auto property_to_add = request.add_properties();
            property_to_add->set_property_id(property.first);
            property_to_add->set_processor_id(property.second);
        }
        // Request response from server
        _reader = _stub->AsyncSubscribeToPropertyUpdates(&_ctx, request, _cq, this);
        _status = PROCESS;
    }
    else if (_status == PROCESS)
    {
        // Read one notification
        _reader->Read(&_response, this);

        // first iteration returns an empty message so we discard it.
        if (_first_iteration)
        {
            _first_iteration = false;
        }
        else
        {
            // Call callback
            _callback(_response.property().processor_id(),
                      _response.property().property_id(),
                      _response.value());
        }
    }
    else
    {
        assert(_status == FINISH);
        _ctx.TryCancel();
    }
}

} // sushi_controller
