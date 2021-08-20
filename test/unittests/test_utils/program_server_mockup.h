#ifndef ELKCPP_TRANSPORT_SERVER_MOCKUP
#define ELKCPP_TRANSPORT_SERVER_MOCKUP

#include <thread>

#include <grpcpp/grpcpp.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "sushi_rpc.grpc.pb.h"
#pragma GCC diagnostic pop

namespace sushi_controller
{

namespace expected_results
{
    // Processor test values
    const ProcessorInfo PROCESSOR_WITH_ID_1 = ProcessorInfo{1, "synth1", "synth1", 2, 2};
    const ProcessorInfo PROCESSOR_WITH_ID_2 = ProcessorInfo{2, "delay1", "delay1", 2, 2};
    const std::vector<ProcessorInfo> PROCESSOR_INFO_LIST = {PROCESSOR_WITH_ID_1, PROCESSOR_WITH_ID_2};
    constexpr bool PROCESSOR_BYPASS_STATE = true;

    // Program test values
    constexpr int PROGRAM_ID{1};
    const std::string PROGRAM_NAME{"Program1"};
} // namespace expected_results


class ProgramServiceMockup : public sushi_rpc::ProgramController::Service
{

    grpc::Status GetProcessorCurrentProgram(grpc::ServerContext* /* context */,
                                            const sushi_rpc::ProcessorIdentifier* request,
                                            sushi_rpc::ProgramIdentifier* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_program(expected_results::PROGRAM_ID);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status GetProcessorCurrentProgramName(grpc::ServerContext* /* context */,
                                                const sushi_rpc::ProcessorIdentifier* request,
                                                sushi_rpc::GenericStringValue* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            response->set_value(expected_results::PROGRAM_NAME);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status GetProcessorProgramName(grpc::ServerContext* /* context */,
                                         const sushi_rpc::ProcessorProgramIdentifier* request,
                                         sushi_rpc::GenericStringValue* response)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id
        && request->program() == expected_results::PROGRAM_ID)
        {
            response->set_value(expected_results::PROGRAM_NAME);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor and/or program with that id");
        }
    }

    grpc::Status GetProcessorPrograms(grpc::ServerContext* /* context */,
                                      const sushi_rpc::ProcessorIdentifier* request,
                                      sushi_rpc::ProgramInfoList* response)
    {
        if(request->id() == expected_results::PROCESSOR_WITH_ID_1.id)
        {
            sushi_rpc::ProgramInfo* program = response->add_programs();
            program->mutable_id()->set_program(expected_results::PROGRAM_ID);
            program->set_name(expected_results::PROGRAM_NAME);
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor with that id");
        }
    }

    grpc::Status SetProcessorProgram(grpc::ServerContext* /* context */,
                                     const sushi_rpc::ProcessorProgramSetRequest* request,
                                     sushi_rpc::GenericVoidValue* /* response */)
    {
        if(request->processor().id() == expected_results::PROCESSOR_WITH_ID_1.id
        && request->program().program() == expected_results::PROGRAM_ID)
        {
            return grpc::Status::OK;
        }
        else
        {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "No processor and/or program with that id");
        }
    }

};

static std::thread server_thread;
static std::unique_ptr<grpc::Server> server;

static void RunServerMockup();
static void KillServerMockup();

class ProgramServerMockup
{
public:
    ProgramServerMockup()
    {
        server_thread = std::thread(RunServerMockup);
        usleep(5000); //Wait for server to start
    }

    ~ProgramServerMockup()
    {
        KillServerMockup();
        server_thread.join();
    }

private:
    std::thread server_thread;
};

void RunServerMockup()
{
    std::string server_address("localhost:51051");
    ProgramServiceMockup service;

    grpc::ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    server = builder.BuildAndStart();
    // std::cout << "Mockup server listening on " << server_address << std::endl;

    server->Wait();
}

void KillServerMockup()
{
    server->Shutdown();
}

} // namespace sushi_controller


#endif // ELKCPP_TRANSPORT_SERVER_MOCKUP
