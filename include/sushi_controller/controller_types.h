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

} // namespace sushi_controller


#endif // ELKCPP_CONTROLLER_TYPES_H
