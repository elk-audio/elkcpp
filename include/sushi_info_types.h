/**
 * @brief The different data structures necessary for the gRPC messages
 * 
 * @copyright MIND Music Labs AB, Stockholm, Sweden
 */

#ifndef SUSHI_INFO_TYPES_H
#define SUSHI_INFO_TYPES_H

#include<string>

namespace sushi_controller
{
    
/**
 * @brief Enum mapping parameter type to ints.
 */
enum class PARAMETER_TYPE
{
    BOOL = 1,
    INT,
    FLOAT,
    STRING_PROPERTY,
    DATA_PROPERTY
};

/**
 * @brief The different playing modes available to sushi
 */
enum class PLAYING_MODE
{
    STOPPED = 1,
    PLAYING,
    RECORDING
};

/**
 * @brief The different sync modes available to sushi
 */
enum class SYNC_MODE
{
    INTERNAL = 1,
    MIDI,
    LINK
};

/**
 * @brief Structure to hold time signature
 */
struct TimeSignature
{
    int numerator;
    int denominator;
};

/**
 * @brief Structure to hold timings
 */
struct CpuTimings
{
    float average;
    float min;
    float max;
};

/**
 * @brief Object to hold info about a track
 */
struct TrackInfo
{
    int id;
    std::string label;
    std::string name;
    int input_channels;
    int input_busses;
    int output_channels;
    int output_busses;
    int processor_count;
};

/**
 * @brief Object to hold info about a processor
 */
struct ProcessorInfo
{
    int id;
    std::string label;
    std::string name;
    int parameter_count;
    int program_count;
};

/**
 * @brief Object to hold info about a parameter
 */
struct ParameterInfo
{
    int id;
    std::string type;
    std::string label;
    std::string name;
    std::string unit;
    bool automatable;
    float min_range;
    float max_range;
};

}

#endif // SUSHI_INFO_TYPES_H