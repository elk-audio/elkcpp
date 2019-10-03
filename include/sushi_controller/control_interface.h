/**
 * @brief Abstract interface for external control of sushi over rpc, osc or similar
 * @copyright MIND Music Labs AB, Stockholm
 */


#ifndef SUSHI_CONTROL_INTERFACE_H
#define SUSHI_CONTROL_INTERFACE_H

#include <utility>
#include <optional>
#include <vector>

namespace sushi_controller {

enum class ControlStatus
{
    OK,
    ERROR,
    UNSUPPORTED_OPERATION,
    NOT_FOUND,
    OUT_OF_RANGE,
    INVALID_ARGUMENTS,
    UNAVAILABLE,
    UNAUTHENTICATED
};

enum class PlayingMode
{
    STOPPED,
    PLAYING,
    RECORDING
};

enum class SyncMode
{
    INTERNAL,
    MIDI,
    LINK
};

struct TimeSignature
{
    int numerator;
    int denominator;
};

struct CpuTimings
{
    float avg;
    float min;
    float max;
};

enum class ParameterType
{
    BOOL,
    INT,
    FLOAT,
    STRING_PROPERTY,
    DATA_PROPERTY,
};

struct ParameterInfo
{
    int             id;
    ParameterType   type;
    std::string     label;
    std::string     name;
    std::string     unit;
    bool            automatable;
    float           min_range;
    float           max_range;
};

struct ProcessorInfo
{
    int         id;
    std::string label;
    std::string name;
    int         parameter_count;
    int         program_count;
};

struct ProgramInfo
{
    int         id;
    std::string name;
};

struct TrackInfo
{
    int         id;
    std::string label;
    std::string name;
    int         input_channels;
    int         input_busses;
    int         output_channels;
    int         output_busses;
    int         processor_count;
};

/**
 * @brief A class to control sushi
 * 
 */

class SushiControl
{
public:
    virtual ~SushiControl() = default;

    //========================//
    //  Main engine controls  //
    //========================//
    
    /**
     * @brief Get the current samplerate
     * 
     * @return float The current samplerate
     */
    virtual std::pair<ControlStatus, float> get_samplerate() const = 0;

    /**
     * @brief Get the current playing mode
     * 
     * @return PlayingMode The current playing mode
     */
    virtual std::pair<ControlStatus, PlayingMode> get_playing_mode() const = 0;

    /**
     * @brief Set the playing mode
     * 
     * @param playing_mode The playing mode to set
     */
    virtual ControlStatus set_playing_mode(PlayingMode playing_mode) = 0;

    /**
     * @brief Get the sync mode
     * 
     * @return SyncMode The current sync mode
     */
    virtual std::pair<ControlStatus, SyncMode> get_sync_mode() const = 0;

    /**
     * @brief Set the sync mode
     * 
     * @param sync_mode The sync mode to set
     */
    virtual ControlStatus set_sync_mode(SyncMode sync_mode) = 0;

    /**
     * @brief Get the tempo
     * 
     * @return float The current tempo
     */
    virtual std::pair<ControlStatus, float> get_tempo() const = 0;

    /**
     * @brief Set the tempo
     * 
     * @param tempo The tempo to set
     * @return ControlStatus 
     */
    virtual ControlStatus set_tempo(float tempo) = 0;

    /**
     * @brief Get the time signature
     * 
     * @return TimeSignature The current time signature
     */
    virtual std::pair<ControlStatus, TimeSignature> get_time_signature() const = 0;

    /**
     * @brief Set the time signature
     * 
     * @param signature The time signature to set
     * @return ControlStatus 
     */
    virtual ControlStatus set_time_signature(TimeSignature signature) = 0;
    // virtual bool                                get_timing_statistics_enabled() = 0;
    // virtual void                                set_timing_statistics_enabled(bool enabled) const = 0;
    
    /**
     * @brief Get the info of the avilable tracks
     * 
     * @return std::vector<TrackInfo> Vector containing the info of each track
     */
    virtual std::pair<ControlStatus, std::vector<TrackInfo>> get_tracks() const = 0;

    //====================//
    //  Keyboard control  //
    //====================//

    /**
     * @brief Send note on message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param channel The channel on which the message should be sent 
     * @param note The note to send. Follows the MIDI standard where middle c = 60 
     * @param velocity The velocity of the note. Should be in range (0.0-1.0) 
     * @return ControlStatus 
     */
    virtual ControlStatus send_note_on(int track_id, int channel, int note, float velocity) = 0;
    
    /**
     * @brief Send note off message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param note The note to send. Follows the MIDI standard where middle c = 60 
     * @param channel The channel on which the message should be sent 
     * @param velocity The velocity of the note. Should be in range (0.0-1.0) 
     * @return ControlStatus 
     */
    virtual ControlStatus send_note_off(int track_id, int channel, int note, float velocity) = 0;
    
    /**
     * @brief Send note aftertouch message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param channel The channel on which the message should be sent 
     * @param note The note to send. Follows the MIDI standard where middle c = 60 
     * @param value 
     * @return ControlStatus 
     */
    virtual ControlStatus send_note_aftertouch(int track_id, int channel, int note, float value) = 0;
    
    /**
     * @brief Send aftertouch message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param channel The channel on which the message should be sent 
     * @param value 
     * @return ControlStatus 
     */
    virtual ControlStatus send_aftertouch(int track_id, int channel, float value) = 0;
    
     /**
     * @brief Send pitch bend message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param channel The channel on which the message should be sent 
     * @param value 
     * @return ControlStatus 
     */
    virtual ControlStatus send_pitch_bend(int track_id, int channel, float value) = 0;
    
    /**
     * @brief Send modulation message to a track
     * 
     * @param track_id The id of the track that should receive the message 
     * @param channel The channel on which the message should be sent 
     * @param value 
     * @return ControlStatus 
     */
    virtual ControlStatus send_modulation(int track_id, int channel, float value) = 0;

    //===============//
    //  Cpu Timings  //
    //===============//

    /**
     * @brief Get the engine timings
     * 
     * @return std::pair<ControlStatus, CpuTimings> 
     */
    virtual std::pair<ControlStatus, CpuTimings> get_engine_timings() const = 0;
    
    /**
     * @brief Get the track timings
     * 
     * @param track_id The id of the track to get the timings from
     * @return std::pair<ControlStatus, CpuTimings> 
     */
    virtual std::pair<ControlStatus, CpuTimings> get_track_timings(int track_id) const = 0;
    
    /**
     * @brief Get the processor timings
     * 
     * @param processor_id The id of the processor to get the timings from 
     * @return std::pair<ControlStatus, CpuTimings> 
     */
    virtual std::pair<ControlStatus, CpuTimings> get_processor_timings(int processor_id) const = 0;
    
    /**
     * @brief Reset all the timings measurements
     * 
     * @return ControlStatus 
     */
    virtual ControlStatus reset_all_timings() = 0;
    
    /**
     * @brief Reset the timings measurements of a track
     * 
     * @param track_id The id of the track to reset the timings of
     * @return ControlStatus 
     */
    virtual ControlStatus reset_track_timings(int track_id) = 0;
    
    /**
     * @brief Reset the timings measurements of a processor
     * 
     * @param processor_id The id of the processor to reset the timings of
     * @return ControlStatus 
     */
    virtual ControlStatus reset_processor_timings(int processor_id) = 0;

    //=================//
    //  Track control  //
    //=================//

    /**
     * @brief Get the track id from a name
     * 
     * @param track_name The name of the track to get the id from
     * @return std::pair<ControlStatus, int> 
     */
    virtual std::pair<ControlStatus, int> get_track_id(const std::string& track_name) const = 0;
    
    /**
     * @brief Get the info from a track
     * 
     * @param track_id The id of the track to get the info from
     * @return std::pair<ControlStatus, TrackInfo> 
     */
    virtual std::pair<ControlStatus, TrackInfo> get_track_info(int track_id) const = 0;

    /**
     * @brief Get the info of avilable processors on a track
     * 
     * @param track_id The id of the track to get the available processors from
     * @return std::pair<ControlStatus, std::vector<ProcessorInfo>> 
     */
    virtual std::pair<ControlStatus, std::vector<ProcessorInfo>> get_track_processors(int track_id) const = 0;
    
    /**
     * @brief Get the avilable parameters on a track
     * 
     * @param track_id The id of the track to get the parameter info from
     * @return std::pair<ControlStatus, std::vector<ParameterInfo>> 
     */
    virtual std::pair<ControlStatus, std::vector<ParameterInfo>> get_track_parameters(int track_id) const = 0;

    //=====================//
    //  Processor control  //
    //=====================//

    /**
     * @brief Get the id of a processor from its name
     * 
     * @param processor_name The name of the processor to get the id from
     * @return std::pair<ControlStatus, int> 
     */
    virtual std::pair<ControlStatus, int> get_processor_id(const std::string& processor_name) const = 0;
    
    /**
     * @brief Get the info about a processor
     * 
     * @param processor_id The id of the processor to get the info from
     * @return std::pair<ControlStatus, ProcessorInfo> 
     */
    virtual std::pair<ControlStatus, ProcessorInfo> get_processor_info(int processor_id) const = 0;
    
    /**
     * @brief Get the bypass state of a processor
     * 
     * @param processor_id The id of the processor to get the bypass state from 
     * @return std::pair<ControlStatus, bool> 
     */
    virtual std::pair<ControlStatus, bool> get_processor_bypass_state(int processor_id) const = 0;
    
    /**
     * @brief Set the bypass state of a processor
     * 
     * @param processor_id The id of the processor to set the bypass state of
     * @param bypass_enabled True to bypass processor, False to enable processor
     * @return ControlStatus 
     */
    virtual ControlStatus set_processor_bypass_state(int processor_id, bool bypass_enabled) = 0;
    
    /**
     * @brief Get the id of the current program of a processor
     * 
     * @param processor_id The id of the processor to get the current program id from
     * @return std::pair<ControlStatus, int> 
     */
    virtual std::pair<ControlStatus, int> get_processor_current_program(int processor_id) const = 0;
    
    /**
     * @brief Get the name of the current program of a processor
     * 
     * @param processor_id The id of the processor to get the current program name from
     * @return std::pair<ControlStatus, std::string> 
     */
    virtual std::pair<ControlStatus, std::string> get_processor_current_program_name(int processor_id) const = 0;
    
    /**
     * @brief Get the name of a program from a processor
     * 
     * @param processor_id The id of the processor containing the program
     * @param program_id The id of program to get the name from
     * @return std::pair<ControlStatus, std::string> 
     */
    virtual std::pair<ControlStatus, std::string> get_processor_program_name(int processor_id, int program_id) const = 0;
    
    /**
     * @brief Get the names of the programs available to a processor
     * 
     * @param processor_id The id of the processor to get the program names from
     * @return std::pair<ControlStatus, std::vector<std::string>> 
     */
    virtual std::pair<ControlStatus, std::vector<std::string>> get_processor_programs(int processor_id) const = 0;
    
    /**
     * @brief Set the current program of a processor
     * 
     * @param processor_id The id of the processor to set the program on
     * @param program_id The id of the program to set on the processor
     * @return ControlStatus 
     */
    virtual ControlStatus set_processor_program(int processor_id, int program_id)= 0;
    
    /**
     * @brief Get the parameters available to a processor
     * 
     * @param processor_id The id of the processor to get the parameters from
     * @return std::pair<ControlStatus, std::vector<ParameterInfo>> 
     */
    virtual std::pair<ControlStatus, std::vector<ParameterInfo>> get_processor_parameters(int processor_id) const = 0;

    //=====================//
    //  Parameter control  //
    //=====================//

    /**
     * @brief Get the id of a parameter from its name
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter The name of the parameter to get the id from
     * @return std::pair<ControlStatus, int> 
     */
    virtual std::pair<ControlStatus, int> get_parameter_id(int processor_id, const std::string& parameter) const = 0;
    
    /**
     * @brief Get the info of a parameter
     * 
     * @param processor_id The id of the processors containing the parameter
     * @param parameter_id The id of the parameter to get the info from
     * @return std::pair<ControlStatus, ParameterInfo> 
     */
    virtual std::pair<ControlStatus, ParameterInfo> get_parameter_info(int processor_id, int parameter_id) const = 0;
    
    /**
     * @brief Get the current value of a parameter
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of parameter to get the value from
     * @return std::pair<ControlStatus, float> 
     */
    virtual std::pair<ControlStatus, float> get_parameter_value(int processor_id, int parameter_id) const = 0;
    
    /**
     * @brief Get the normalised current value of a parameter
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to get the normalised value from
     * @return std::pair<ControlStatus, float> 
     */
    virtual std::pair<ControlStatus, float> get_parameter_value_normalised(int processor_id, int parameter_id) const = 0;
    
    /**
     * @brief Get the current value of a parameter as a string
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to get value as a string from
     * @return std::pair<ControlStatus, std::string> 
     */
    virtual std::pair<ControlStatus, std::string> get_parameter_value_as_string(int processor_id, int parameter_id) const = 0;
    // virtual std::pair<ControlStatus, std::string>      get_string_property_value(int processor_id, int parameter_id) const = 0;
    
    /**
     * @brief Set the value of a parameter
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to set the value of
     * @param value The value to set the parameter to
     * @return ControlStatus 
     */
    virtual ControlStatus set_parameter_value(int processor_id, int parameter_id, float value) = 0;
    
    /**
     * @brief Set the normalised value of a parameter
     * 
     * @param processor_id The id of the processor containing the parameter
     * @param parameter_id The id of the parameter to set the normalised value of
     * @param value The normalised value to set the parameter to
     * @return ControlStatus 
     */
    virtual ControlStatus                              set_parameter_value_normalised(int processor_id, int parameter_id, float value) = 0;
    // virtual ControlStatus                              set_string_property_value(int processor_id, int parameter_id, const std::string& value) = 0;


protected:
    SushiControl() = default;

};

class SushiControllerClient;


} // sushi_controller


#endif //SUSHI_CONTROL_INTERFACE_H
