#include "async_client_call_data.h"

namespace sushi_controller {

void SubscribeToParameterUpdatesCallData::proceed()
{
    if (_status == CREATE)
    {
        // Format blacklist
        auto request = sushi_rpc::ParameterNotificationBlocklist();
        for (auto parameter : _parameter_blocklist)
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
