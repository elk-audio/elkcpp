#ifndef ELKCPP_TIMING_CONTORLLER_H
#define ELKCPP_TIMING_CONTORLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller
{

class TimingControllerClient : public TimingController
{
public:
    TimingControllerClient(const std::string& address);

    /**
     * @brief Check if timings are enabled
     *
     * @return std::pair<ControlStatus, bool> true if enabled. false if not
     */
    std::pair<ControlStatus, bool> get_timings_enabled() const override;

    /**
     * @brief Set if timings should be enabled
     *
     * @param enabled true if timings should be enabled. false if not
     * @return ControlStatus
     */
    ControlStatus set_timings_enabled(bool enabled) override;

    /**
     * @brief Get the engine timings
     *
     * @return std::pair<ControlStatus, CpuTimings>
     */
    std::pair<ControlStatus, CpuTimings> get_engine_timings() const override;

    /**
     * @brief Get the track timings
     *
     * @param track_id The id of the track to get the timings from
     * @return std::pair<ControlStatus, CpuTimings>
     */
    std::pair<ControlStatus, CpuTimings> get_track_timings(int track_id) const override;

    /**
     * @brief Get the processor timings
     *
     * @param processor_id The id of the processor to get the timings from
     * @return std::pair<ControlStatus, CpuTimings>
     */
    std::pair<ControlStatus, CpuTimings> get_processor_timings(int processor_id) const override;

    /**
     * @brief Reset all the timings measurements
     *
     * @return ControlStatus
     */
    ControlStatus reset_all_timings() override;

    /**
     * @brief Reset the timings measurements of a track
     *
     * @param track_id The id of the track to reset the timings of
     * @return ControlStatus
     */
    ControlStatus reset_track_timings(int track_id) override;

    /**
     * @brief Reset the timings measurements of a processor
     *
     * @param processor_id The id of the processor to reset the timings of
     * @return ControlStatus
     */
    ControlStatus reset_processor_timings(int processor_id) override;

private:
    std::unique_ptr<sushi_rpc::TimingController::Stub> _stub;
};
} // namespace sushi_controller

#endif // ELKCPP_TIMING_CONTORLLER_H
