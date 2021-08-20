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

    for (auto& call_data : _active_call_datas)
    {
        delete call_data;
    }
}

void NotificationControllerClient::subscribe_to_parameter_updates(std::function<void(int parameter_id, int processor_id, float value)> callback,
                                                                  std::vector<std::pair<int, int>> parameter_blocklist)
{
    auto call_data = new SubscribeToParameterUpdatesCallData(_stub.get(),
                                                             &_cq,
                                                             callback,
                                                             parameter_blocklist);
    _active_call_datas.push_back(call_data);
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
    return std::move(std::make_shared<NotificationControllerClient>(server_address));
}

} // namespace sushi_controller

