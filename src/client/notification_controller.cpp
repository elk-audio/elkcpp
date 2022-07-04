#include <grpcpp/grpcpp.h>

#include "grpc_utils.h"
#include "sushi_client.h"
#include "notification_controller.h"

namespace sushi_controller
{

NotificationControllerClient::NotificationControllerClient(const std::string& address)
    : _stub(sushi_rpc::NotificationController::NewStub(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        )))
{
    _worker = std::thread(&NotificationControllerClient::notification_loop, this);
}

NotificationControllerClient::~NotificationControllerClient()
{
    for (auto& call_data : _active_call_datas)
    {
        call_data->stop();
        call_data->alert();
    }
    _cq.Shutdown();

    if (_worker.joinable())
    {
        _worker.join();
    }
}

void NotificationControllerClient::subscribe_to_transport_changes(std::function<void(TransportUpdate update, TransportUpdateType type)> callback)
{
    _active_call_datas.push_back(
        std::make_unique<SubscribeToTransportChangesCallData>(_stub.get(),
                                                              &_cq,
                                                              callback)
    );
}

void NotificationControllerClient::subscribe_to_engine_cpu_timing_updates(std::function<void(CpuTimings timings)> callback)
{
    _active_call_datas.push_back(
        std::make_unique<SubscribeToEngineCpuTimingUpdatesCallData>(_stub.get(),
                                                                    &_cq,
                                                                    callback)
    );
}

void NotificationControllerClient::subscribe_to_track_changes(std::function<void(TrackUpdate update)> callback)
{
    _active_call_datas.push_back(
        std::make_unique<SubscribeToTrackChangesCallData>(_stub.get(),
                                                          &_cq,
                                                          callback)
    );
}

void NotificationControllerClient::subscribe_to_processor_changes(std::function<void(ProcessorUpdate update)> callback)
{
    _active_call_datas.push_back(
        std::make_unique<SubscribeToProcessorChangesCallData>(_stub.get(),
                                                              &_cq,
                                                              callback)
    );
}

void NotificationControllerClient::subscribe_to_parameter_updates(std::function<void(int parameter_id, int processor_id, float value)> callback,
                                                                  const std::vector<std::pair<int, int>>& blocklist)
{
    _active_call_datas.push_back(
        std::make_unique<SubscribeToParameterUpdatesCallData>(_stub.get(),
                                                              &_cq,
                                                              callback,
                                                              blocklist)
    );
}

void NotificationControllerClient::subscribe_to_property_updates(std::function<void(int parameter_id, int processor_id, const std::string& value)> callback,
                                                                 const std::vector<std::pair<int, int>>& blocklist)
{
    _active_call_datas.push_back(
        std::make_unique<SubscribeToPropertyUpdatesCallData>(_stub.get(),
                                                             &_cq,
                                                             callback,
                                                             blocklist)
    );
}

void NotificationControllerClient::notification_loop()
{
    void* tag;
    bool ok;
    while(_cq.Next(&tag, &ok))
    {
        if (ok == false)
        {
            static_cast<CallData*>(tag)->stop();
        }
        static_cast<CallData*>(tag)->proceed();
    }
}

std::shared_ptr<NotificationController> CreateNotificationController(const std::string& server_address)
{
    return std::make_shared<NotificationControllerClient>(server_address);
}

} // namespace sushi_controller

