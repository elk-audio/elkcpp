/**
 * @brief The different data structures necessary for the gRPC messages
 * 
 * @copyright MIND Music Labs AB, Stockholm, Sweden
 */

#ifndef SUSHI_INFO_TYPES_H
#define SUSHI_INFO_TYPES_H

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
    TimeSignature(int numerator, int denominator) : numerator(numerator), denominator(denominator) {};

    int numerator;
    int denominator;
}

#endif // SUSHI_INFO_TYPES_H