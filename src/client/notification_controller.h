#ifndef ELKCPP_NOTIFICATION_CONTROLLER_H
#define ELKCPP_NOTIFICATION_CONTROLLER_H

#include <atomic>
#include <thread>
#include <vector>

#include "sushi_rpc.grpc.pb.h"

#include "async_client_call_data.h"
#include "control_interface.h"

namespace sushi_controller
{

class CallData;

class NotificationControllerClient : public NotificationController
{
public:
    NotificationControllerClient(const std::string& address);
    ~NotificationControllerClient();

    /**
     * @brief Subscribe to changes on the transport
     *
     * @param callback The callback to run when a change is made to the transport
     */
    virtual void subscribe_to_transport_changes(std::function<void(TransportUpdate update)> callback) override;

    /**
     * @brief Subscribe to timing updates
     *
     * @param callback The callback to run when the timings are updated
     */
    virtual void subscribe_to_engine_cpu_timing_updates(std::function<void(CpuTimings timings)> callback) override;

    /**
     * @brief Subscribe to track changes
     *
     * @param callback The callback to run when the tracks are changed
     */
    virtual void subscribe_to_track_changes(std::function<void(TrackUpdate update)> callback) override;

    /**
     * @brief Subscribe to processor changes
     *
     * @param callback The callback to run when the processors are changed
     */
    virtual void subscribe_to_processor_changes(std::function<void(ProcessorUpdate update)> callback) override;

    /**
     * @brief Subscribe callback to parameter change updates
     *
     * @param callback The callback to run when a parameter update is received
     * @param parameter_blocklist Parameters to blocklist. The first int in the
     * pair is a processor id. The second int is a processor id
     */
    virtual void subscribe_to_parameter_updates(std::function<void(int parameter_id, int processor_id, float value)> callback,
                                                std::vector<std::pair<int,int>> parameter_blocklist) override;

    void notification_loop();

private:
    std::unique_ptr<sushi_rpc::NotificationController::Stub> _stub;
    grpc::CompletionQueue _cq;
    std::thread _worker;
    std::atomic<bool> _running;
    std::vector<CallData*> _active_call_datas;
};

} // namespace sushi_controller

#endif // ELKCPP_NOTIFICATION_CONTROLLER_H
