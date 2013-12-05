/**
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#include "MockUpperLayer.h"

#include "BufferHelpers.h"

#include <openpal/ToHex.h>
#include <openpal/LoggableMacros.h>

#include <memory>

using namespace openpal;

namespace opendnp3
{

MockUpperLayer::MockUpperLayer(openpal::Logger aLogger) :
	Loggable(aLogger),
	IUpperLayer(aLogger)
{}

void MockUpperLayer::_OnReceive(const openpal::ReadOnlyBuffer& arBuffer)
{
	this->WriteToBuffer(arBuffer);
	if(mOnReceiveHandler) mOnReceiveHandler(arBuffer);
}

void MockUpperLayer::_OnSendSuccess()
{
	LOG_BLOCK(LogLevel::Debug, "OnSendSuccess");
	++mState.mSuccessCnt;
}

void MockUpperLayer::_OnSendFailure()
{
	LOG_BLOCK(LogLevel::Debug, "OnSendFailure");
	++mState.mFailureCnt;
}

void MockUpperLayer::_OnLowerLayerUp()
{
	LOG_BLOCK(LogLevel::Debug, "OnLowerLayerUp");
	++mState.mNumLayerUp;
}

void MockUpperLayer::_OnLowerLayerDown()
{
	LOG_BLOCK(LogLevel::Debug, "OnLowerLayerDown");
	++mState.mNumLayerDown;
}

void MockUpperLayer::SendDown(const openpal::ReadOnlyBuffer& arBuffer)
{
	if(this->mpLowerLayer) mpLowerLayer->Send(arBuffer);
}

void MockUpperLayer::SendDown(const std::string& arHexData)
{
	HexSequence hs(arHexData);	
	this->SendDown(hs.ToReadOnly());
}

}
