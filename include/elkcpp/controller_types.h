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

enum class TrackType
{
    REGULAR,
    PRE,
    POST
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

struct PropertyInfo
{
    int         id;
    std::string name;
    std::string label;
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
    int              channels;
    int              buses;
    TrackType        type;
    std::vector<int> processors;
};

struct ProcessorState
{
    std::optional<int>  program_id;
    std::optional<bool> bypassed;
    std::vector<std::pair<int, float>> parameters;
    std::vector<std::pair<int, std::string>> properties;
    std::string binary_data;
};

enum class MidiChannel
{
    MIDI_CH_1 = 1,
    MIDI_CH_2 = 2,
    MIDI_CH_3 = 3,
    MIDI_CH_4 = 4,
    MIDI_CH_5 = 5,
    MIDI_CH_6 = 6,
    MIDI_CH_7 = 7,
    MIDI_CH_8 = 8,
    MIDI_CH_9 = 9,
    MIDI_CH_10 = 10,
    MIDI_CH_11 = 11,
    MIDI_CH_12 = 12,
    MIDI_CH_13 = 13,
    MIDI_CH_14 = 14,
    MIDI_CH_15 = 15,
    MIDI_CH_16 = 16,
    MIDI_CH_OMNI = 17
};

struct MidiKbdConnection
{
    int track_id;
    MidiChannel channel;
    int port;
    bool raw_midi;
};

inline bool operator==(const MidiKbdConnection& lhs, const MidiKbdConnection& rhs)
{
    return (lhs.track_id == rhs.track_id) &&
           (lhs.channel == rhs.channel) &&
           (lhs.port == rhs.port) &&
           (lhs.raw_midi == rhs.raw_midi);
}

struct MidiCCConnection
{
    int parameter_id;
    int processor_id;
    MidiChannel channel;
    int port;
    int cc_number;
    float min_range;
    float max_range;
    bool relative_mode;
};

inline bool operator==(const MidiCCConnection& lhs, const MidiCCConnection& rhs)
{
    return (lhs.parameter_id == rhs.parameter_id) &&
           (lhs.channel == rhs.channel) &&
           (lhs.port == rhs.port) &&
           (lhs.cc_number == rhs.cc_number) &&
           (lhs.min_range == rhs.min_range) &&
           (lhs.max_range == rhs.max_range) &&
           (lhs.relative_mode == rhs.relative_mode);
}

struct MidiPCConnection
{
    int processor_id;
    MidiChannel channel;
    int port;
};

inline bool operator==(const MidiPCConnection& lhs, const MidiPCConnection& rhs)
{
    return (lhs.processor_id == rhs.processor_id) &&
           (lhs.channel == rhs.channel) &&
           (lhs.port == rhs.port);
}

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

struct AudioConnection
{
    int track_id;
    int track_channel;
    int engine_channel;
};

inline bool operator==(const AudioConnection& lhs, const AudioConnection& rhs)
{
    return (lhs.track_id == rhs.track_id) &&
           (lhs.track_channel == rhs.track_channel) &&
           (lhs.engine_channel == rhs.engine_channel);
}

struct CvConnection
{
    int processor_id;
    int parameter_id;
    int cv_port_id;
};

inline bool operator==(const CvConnection& lhs, const CvConnection& rhs)
{
    return (lhs.processor_id == rhs.processor_id) &&
           (lhs.parameter_id == rhs.parameter_id) &&
           (lhs.cv_port_id == rhs.cv_port_id);
}
struct GateConnection
{
    int processor_id;
    int gate_port_id;
    int channel;
    int note_no;
};

inline bool operator==(const GateConnection& lhs, const GateConnection& rhs)
{
    return (lhs.processor_id == rhs.processor_id) &&
           (lhs.gate_port_id == rhs.gate_port_id) &&
           (lhs.channel == rhs.channel) &&
           (lhs.note_no == rhs.note_no);
}

} // namespace sushi_controller


#endif // ELKCPP_CONTROLLER_TYPES_H
