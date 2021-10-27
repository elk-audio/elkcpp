#ifndef ELKCPP_PROGRAM_CONTROLLER_H
#define ELKCPP_PROGRAM_CONTROLLER_H

#include "sushi_rpc.grpc.pb.h"

#include "control_interface.h"

namespace sushi_controller
{

class ProgramControllerClient : public ProgramController
{
public:
    ProgramControllerClient(const std::string& address);

    /**
     * @brief Get the id of the current program of a processor
     *
     * @param processor_id The id of the processor to get the current program id from
     * @return std::pair<ControlStatus, int>
     */
    virtual std::pair<ControlStatus, int> get_processor_current_program(int processor_id) const  override;

    /**
     * @brief Get the name of the current program of a processor
     *
     * @param processor_id The id of the processor to get the current program name from
     * @return std::pair<ControlStatus, std::string>
     */
    virtual std::pair<ControlStatus, std::string> get_processor_current_program_name(int processor_id) const  override;

    /**
     * @brief Get the name of a program from a processor
     *
     * @param processor_id The id of the processor containing the program
     * @param program_id The id of program to get the name from
     * @return std::pair<ControlStatus, std::string>
     */
    virtual std::pair<ControlStatus, std::string> get_processor_program_name(int processor_id,
                                                                             int program_id) const  override;

    /**
     * @brief Get the names of the programs available to a processor
     *
     * @param processor_id The id of the processor to get the program names from
     * @return std::pair<ControlStatus, std::vector<std::string>>
     */
    virtual std::pair<ControlStatus, std::vector<std::string>> get_processor_programs(int processor_id) const  override;

    /**
     * @brief Set the current program of a processor
     *
     * @param processor_id The id of the processor to set the program on
     * @param program_id The id of the program to set on the processor
     * @return ControlStatus
     */
    virtual ControlStatus set_processor_program(int processor_id,
                                                int program_id) override;

private:
    std::unique_ptr<sushi_rpc::ProgramController::Stub> _stub;
};

} // namespace sushi_controller


#endif // ELKCPP_PROGRAM_CONTROLLER_H
