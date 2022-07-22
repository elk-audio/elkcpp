#ifndef ELKCPP_AUDIO_GRAPH_CONTROLLER_H
#define ELKCPP_AUDIO_GRAPH_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller
{

class AudioGraphControllerClient : public AudioGraphController
{
public:
    AudioGraphControllerClient(const std::string& address);

    /**
     * @brief Get the info for all available processors
     *
     * @return std::pair<ControlStatus, std::vector<ProcessorInfo>>
     * Vector containing the info of each processor
     */
    std::pair<ControlStatus, std::vector<ProcessorInfo>> get_all_processors() const override;

    /**
     * @brief Get the info for all avilable tracks
     *
     * @return std::vector<TrackInfo> Vector containing the info of each track
     */
    std::pair<ControlStatus, std::vector<TrackInfo>> get_all_tracks() const override;

    /**
     * @brief Get the track id from a name
     *
     * @param track_name The name of the track to get the id from
     * @return std::pair<ControlStatus, int>
     */
    std::pair<ControlStatus, int> get_track_id(const std::string& track_name) const override;

    /**
     * @brief Get the info from a track
     *
     * @param track_id The id of the track to get the info from
     * @return std::pair<ControlStatus, TrackInfo>
     */
    std::pair<ControlStatus, TrackInfo> get_track_info(int track_id) const override;

    /**
     * @brief Get the info of avilable processors on a track
     *
     * @param track_id The id of the track to get the available processors from
     * @return std::pair<ControlStatus, std::vector<ProcessorInfo>>
     */
    std::pair<ControlStatus, std::vector<ProcessorInfo>> get_track_processors(int track_id) const override;

     /**
     * @brief Get the id of a processor from its name
     *
     * @param processor_name The name of the processor to get the id from
     * @return std::pair<ControlStatus, int>
     */
    std::pair<ControlStatus, int> get_processor_id(const std::string& processor_name) const override;

    /**
     * @brief Get the info about a processor
     *
     * @param processor_id The id of the processor to get the info from
     * @return std::pair<ControlStatus, ProcessorInfo>
     */
    std::pair<ControlStatus, ProcessorInfo> get_processor_info(int processor_id) const override;

    /**
     * @brief Get the bypass state of a processor
     *
     * @param processor_id The id of the processor to get the bypass state from
     * @return std::pair<ControlStatus, bool>
     */
    std::pair<ControlStatus, bool> get_processor_bypass_state(int processor_id) const override;

    /**
     * @brief Get the full state of a processor
     *
     * @param processor_id The id of the processor to get the state from
     * @return std::pair<ControlStatus, ProcessorState>
     */
    std::pair<ControlStatus, ProcessorState> get_processor_state(int processor_id) const override;

    /**
     * @brief Set the bypass state of a processor
     *
     * @param processor_id The id of the processor to set the bypass state of
     * @param bypass_enabled True to bypass processor, False to enable processor
     * @return ControlStatus
     */
    ControlStatus set_processor_bypass_state(int processor_id, bool bypass_enabled) override;

    /**
     * @brief Set the full or partial state of a processor
     *
     * @param processor_id The id of the processor to set the state of
     * @param state A ProcessorState object that will be applied to the chosen processor
     * @return ControlStatus
     */
    ControlStatus set_processor_state(int processor_id, const ProcessorState& state) override;

    /**
     * @brief Create a new track in sushi
     *
     * @param name The name of the new track
     * @param channels The number of channels to assign the new track
     * @return ControlStatus
     */
    ControlStatus create_track(const std::string& name, int channels) override;

    /**
     * @brief Create a new multibus track in sushi
     *
     * @param name The name of the the new track
     * @param buses The number of audio buses in the new track
     * @return ControlStatus
     */
    ControlStatus create_multibus_track(const std::string& name, int buses) override;

    /**
     * @brief Create a pre track in sushi
     *
     * @param name The name of the the new track
     * @return ControlStatus
     */
    ControlStatus create_pre_track(const std::string& name) override;

    /**
     * @brief Create a post track in sushi to
     *
     * @param name The name of the the new track
     * @return ControlStatus
     */
    ControlStatus create_post_track(const std::string& name) override;

    /**
     * @brief Create a new processor on an existing track
     *
     * @param name The name to assign the processor. Must be unique
     * @param uid The uid of an internal sushi processor or the URI of an LV2
     *            processor. Not applicable for vst2x and vst3x
     * @param path The path to the processor library. Only for vst2x and vst3x
     * @param type The type of processor to create
     * @param track_id The id of the track to add the processor to
     * @param before_processor Which existing processor to create the new
     * processor in front of
     * @param add_to_back Set to true to add the processor to the back of the
     * processing chain on the track. Overrides the `before_processor` parameter
     * @return ControlStatus
     */
    ControlStatus create_processor_on_track(const std::string& name,
                                            const std::string& uid,
                                            const std::string& path,
                                            PluginType type,
                                            int track_id,
                                            int before_processor,
                                            bool add_to_back) override;

    /**
     * @brief Move an existing processor
     *
     * @param processor The id of the processor to move
     * @param source_track The id of the track to move the processor from
     * @param destination_track The id of the track to move the processor to
     * @param before_processor The id of another processor to move this processor
     * in front of
     * @param add_to_back Set to true to move the processor the end of the processing
     * chain on the destination track. Overrides the `before_processor` parameter
     * @return ControlStatus
     */
    ControlStatus move_processor_on_track(int processor,
                                          int source_track,
                                          int destination_track,
                                          int before_processor,
                                          bool add_to_back) override;

    /**
     * @brief Delete an existing processor from a track
     *
     * @param processor The id of the processor to delete
     * @param track The id of the track that has the processor
     * @return ControlStatus
     */
    ControlStatus delete_processor_from_track(int processor, int track) override;

    /**
     * @brief Delete a track an all processors on it
     *
     * @param track_id The id of the track to delete
     * @return ControlStatus
     */
    ControlStatus delete_track(int track_id) override;

private:
    std::unique_ptr<sushi_rpc::AudioGraphController::Stub> _stub;
};

} // namespace sushi_controller


#endif // ELKCPP_AUDIO_GRAPH_CONTROLLER_H
