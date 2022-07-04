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
    virtual void subscribe_to_transport_changes(std::function<void(TransportUpdate update, TransportUpdateType type)> callback) override;

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
     * @brief Subscribe to parameter changes
     *
     * @param callback The callback to run when a parameter update is received
     * @param blocklist A vector of pairs of <parameter id, processor is> for which the
     *                  callback will not be called. If empty, the callback will be
     *                  called for all parameter changes.
     */
    virtual void subscribe_to_parameter_updates(std::function<void(int parameter_id, int processor_id, float normalized_value, float domain_value, const std::string& formatted_value)> callback,
                                                const std::vector<std::pair<int,int>>& blocklist) override;

    /**
     * @brief Subscribe to property changes
     *
     * @param callback The callback to run when a property update is received
     * @param blocklist A vector of pairs of <property id, processor is> for which the
     *                  callback will not be called. If empty, the callback will be
     *                  called for all property changes.
     */
    virtual void subscribe_to_property_updates(std::function<void(int property_id, int processor_id, const std::string& value)> callback,
                                               const std::vector<std::pair<int,int>>& blocklist) override;

    void notification_loop();

private:
    std::unique_ptr<sushi_rpc::NotificationController::Stub> _stub;
    grpc::CompletionQueue _cq;
    std::thread _worker;
    std::vector<std::unique_ptr<CallData>> _active_call_datas;
};

} // namespace sushi_controller

#endif // ELKCPP_NOTIFICATION_CONTROLLER_H
