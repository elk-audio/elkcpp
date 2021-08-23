#ifndef ELKCPP_CONTROLLER_TYPES_H
#define ELKCPP_CONTROLLER_TYPES_H

#include <string>
#include <variant>
#include <vector>

namespace sushi_controller
{

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

struct BuildInfo
{
    std::string version;
    std::vector<std::string> build_options;
    int audio_buffer_size;
    std::string commit_hash;
    std::string build_date;
};

inline bool operator==(const BuildInfo& lhs, const BuildInfo& rhs)
{
    return (lhs.version == rhs.version) &&
           (lhs.build_options == rhs.build_options) &&
           (lhs.audio_buffer_size == rhs.audio_buffer_size) &&
           (lhs.commit_hash == rhs.commit_hash) &&
           (lhs.build_date == rhs.build_date);
}

struct TimeSignature
{
    int numerator;
    int denominator;
};

inline bool operator==(const TimeSignature& lhs, const TimeSignature& rhs)
{
    return (lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator);
}

struct CpuTimings
{
    float avg;
    float min;
    float max;
};

inline bool operator==(const CpuTimings& lhs, const CpuTimings& rhs)
{
    return (lhs.avg == rhs.avg) && (lhs.max == rhs.max) && (lhs.min == rhs.min);
}

enum class ParameterType
{
    BOOL,
    INT,
    FLOAT,
};

enum class PluginType
{
   INTERNAL,
   VST2X,
   VST3X,
   LV2
};

struct ParameterInfo
{
    int             id;
    ParameterType   type;
    std::string     label;
    std::string     name;
    std::string     unit;
    bool            automatable;
    float           min_domain_value;
    float           max_domain_value;
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
    int              id;
    std::string      label;
    std::string      name;
    int              input_channels;
    int              input_busses;
    int              output_channels;
    int              output_busses;
    std::vector<int> processors;
};

enum class TransportUpdateType
{
    TEMPO,
    PLAYING_MODE,
    SYNC_MODE,
    TIME_SIGNATURE
};
using TransportUpdate = std::variant<float, PlayingMode, SyncMode, TimeSignature>;

struct TrackUpdate
{
    enum class Action
    {
        TRACK_ADDED,
        TRACK_DELETED
    };
    Action action;
    int track_id;
};

inline bool operator==(const TrackUpdate& lhs, const TrackUpdate& rhs)
{
    return (lhs.action == rhs.action) && (lhs.track_id && rhs.track_id);
}

struct ProcessorUpdate
{
    enum class Action
    {
        PROCESSOR_ADDED,
        PROCESSOR_DELETED
    };
    Action action;
    int processor_id;
    int parent_track_id;
};

inline bool operator==(const ProcessorUpdate& lhs, const ProcessorUpdate& rhs)
{
    return (lhs.action == rhs.action) &&
           (lhs.processor_id == rhs.processor_id) &&
           (lhs.parent_track_id == rhs.parent_track_id);
}

} // namespace sushi_controller


#endif // ELKCPP_CONTROLLER_TYPES_H
