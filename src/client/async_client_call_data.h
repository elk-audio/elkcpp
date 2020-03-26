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

#include "sushi_grpc_client.h"

namespace sushi_controller {

class CallData
{
public:
    CallData(sushi_rpc::SushiController::Stub* stub, grpc::CompletionQueue* cq)
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
    sushi_rpc::SushiController::Stub* _stub;

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

class SubscribeToParameterUpdatesCallData : public CallData
{
public:
    SubscribeToParameterUpdatesCallData(sushi_rpc::SushiController::Stub* stub,
                                        grpc::CompletionQueue* cq,
                                        void (*callback)(int,int,float),
                                        std::vector<std::pair<int,int>> parameter_blacklist)
    : CallData(stub, cq),
      _callback(callback),
      _parameter_blacklist(parameter_blacklist),
      _first_iteration(true)
    {
        proceed();
    }

    void proceed() override;

private:
    std::unique_ptr<grpc::ClientAsyncReader<sushi_rpc::ParameterSetRequest>> _reader;
    sushi_rpc::ParameterSetRequest _response;

    void (*_callback)(int,int,float);
    std::vector<std::pair<int,int>> _parameter_blacklist;

    bool _first_iteration;
};

} // sushi_controller
#endif // SUSHI_ASYNCCLIENTCALLDATA_H
