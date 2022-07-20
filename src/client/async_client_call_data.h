/*
 * Copyright 2017-2019 Modern Ancient Instruments Networked AB, dba Elk
 *
 * SUSHI is free software: you can redistribute it and/or modify it under the terms of
 * the GNU Affero General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * SUSHI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with
 * SUSHI.  If not, see http://www.gnu.org/licenses/
 */

/**
 * @brief Sushi Async gRPC Call Data. Objects to handle the async calls to sushi.
 * @copyright 2017-2019 Modern Ancient Instruments Networked AB, dba Elk, Stockholm
 */

#ifndef SUSHI_ASYNCCLIENTCALLDATA_H
#define SUSHI_ASYNCCLIENTCALLDATA_H

#include <grpcpp/alarm.h>
#include <functional>

#include "sushi_rpc.grpc.pb.h"
#include "controller_types.h"

namespace sushi_controller {

class CallData
{
public:
    CallData(sushi_rpc::NotificationController::Stub* stub, grpc::CompletionQueue* cq)
        : _cq(cq),
          _stub(stub),
          _status(CREATE) {}

    virtual ~CallData() = default;

    virtual void proceed() = 0;

    void stop()
    {
        _status = FINISH;
    }

    void alert()
    {
        _alarm.Set(_cq, gpr_now(gpr_clock_type::GPR_CLOCK_REALTIME), this);
    }

protected:
    grpc::CompletionQueue* _cq;
    grpc::ClientContext _ctx;
    sushi_rpc::NotificationController::Stub* _stub;

    grpc::Alarm _alarm;

    enum CallStatus
    {
        CREATE,
        PROCESS,
        FINISH,
        PUSH_TO_BACK
    };
    CallStatus _status;
};

class SubscribeToTransportChangesCallData : public CallData
{
public:
    SubscribeToTransportChangesCallData(sushi_rpc::NotificationController::Stub* stub,
                                        grpc::CompletionQueue* cq,
                                        std::function<void(TransportUpdate update, TransportUpdateType type)> callback)
    : CallData(stub, cq),
      _callback(callback),
      _first_iteration(true)
    {
        proceed();
    }

    void proceed() override;

private:
    std::unique_ptr<grpc::ClientAsyncReader<sushi_rpc::TransportUpdate>> _reader;
    sushi_rpc::TransportUpdate _response;

    std::function<void(TransportUpdate update, TransportUpdateType type)> _callback;

    bool _first_iteration;
};


class SubscribeToEngineCpuTimingUpdatesCallData : public CallData
{
public:
    SubscribeToEngineCpuTimingUpdatesCallData(sushi_rpc::NotificationController::Stub* stub,
                                               grpc::CompletionQueue* cq,
                                               std::function<void(CpuTimings timings)> callback)
    : CallData(stub, cq),
      _callback(callback),
      _first_iteration(true)
    {
        proceed();
    }

    void proceed() override;

private:
    std::unique_ptr<grpc::ClientAsyncReader<sushi_rpc::CpuTimings>> _reader;
    sushi_rpc::CpuTimings _response;

    std::function<void(CpuTimings timings)> _callback;

    bool _first_iteration;
};

class SubscribeToTrackChangesCallData : public CallData
{
public:
    SubscribeToTrackChangesCallData(sushi_rpc::NotificationController::Stub* stub,
                                    grpc::CompletionQueue* cq,
                                    std::function<void(TrackUpdate update)> callback)
    : CallData(stub, cq),
      _callback(callback),
      _first_iteration(true)
    {
        proceed();
    }

    void proceed() override;

private:
    std::unique_ptr<grpc::ClientAsyncReader<sushi_rpc::TrackUpdate>> _reader;
    sushi_rpc::TrackUpdate _response;

    std::function<void(TrackUpdate update)> _callback;

    bool _first_iteration;
};

class SubscribeToProcessorChangesCallData : public CallData
{
public:
    SubscribeToProcessorChangesCallData(sushi_rpc::NotificationController::Stub* stub,
                                    grpc::CompletionQueue* cq,
                                    std::function<void(ProcessorUpdate update)> callback)
    : CallData(stub, cq),
      _callback(callback),
      _first_iteration(true)
    {
        proceed();
    }

    void proceed() override;

private:
    std::unique_ptr<grpc::ClientAsyncReader<sushi_rpc::ProcessorUpdate>> _reader;
    sushi_rpc::ProcessorUpdate _response;

    std::function<void(ProcessorUpdate update)> _callback;

    bool _first_iteration;
};
class SubscribeToParameterUpdatesCallData : public CallData
{
public:
    SubscribeToParameterUpdatesCallData(sushi_rpc::NotificationController::Stub* stub,
                                        grpc::CompletionQueue* cq,
                                        std::function<void(int parameter_id, int processor_id, float normalized_value, float domain_value, const std::string& formatted_value)> callback,
                                        std::vector<std::pair<int,int>> parameter_blocklist)
    : CallData(stub, cq),
      _callback(callback),
      _parameter_blocklist(parameter_blocklist),
      _first_iteration(true)
    {
        proceed();
    }

    void proceed() override;

private:
    std::unique_ptr<grpc::ClientAsyncReader<sushi_rpc::ParameterUpdate>> _reader;
    sushi_rpc::ParameterUpdate _response;

    std::function<void(int parameter_id, int processor_id, float normalized_value, float domain_value, const std::string& formatted_value)> _callback;
    std::vector<std::pair<int,int>> _parameter_blocklist;

    bool _first_iteration;
};

class SubscribeToPropertyUpdatesCallData : public CallData
{
public:
    SubscribeToPropertyUpdatesCallData(sushi_rpc::NotificationController::Stub* stub,
                                       grpc::CompletionQueue* cq,
                                       std::function<void(int property_id, int processor_id, const std::string& value)> callback,
                                       std::vector<std::pair<int,int>> blocklist)
    : CallData(stub, cq),
      _callback(callback),
      _blocklist(blocklist),
      _first_iteration(true)
    {
        proceed();
    }

    void proceed() override;

private:
    std::unique_ptr<grpc::ClientAsyncReader<sushi_rpc::PropertyValue>> _reader;
    sushi_rpc::PropertyValue _response;

    std::function<void(int parameter_id, int processor_id, const std::string& value)> _callback;
    std::vector<std::pair<int,int>> _blocklist;

    bool _first_iteration;
};

} // sushi_controller
#endif // SUSHI_ASYNCCLIENTCALLDATA_H
