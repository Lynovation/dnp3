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
#ifndef SECAUTH_IOUTSTATIONUSERDATABASE_H
#define SECAUTH_IOUTSTATIONUSERDATABASE_H

#include "secauth/User.h"

#include <opendnp3/gen/UpdateKeyMode.h>
#include <opendnp3/gen/FunctionCode.h>

#include <openpal/container/ReadBufferView.h>

#include <functional>

namespace secauth
{	

/** 
	An interface for retrieving info about users

	This interface may be given out to multiple outstation instances on multiple threads, 
	and therefore should be thread-safe.
*/
class IOutstationUserDatabase
{
	public:		

		virtual bool GetUpdateKeyType(const User& user, opendnp3::UpdateKeyMode& type) const = 0;

		virtual bool IsAuthorized(const User& user, opendnp3::FunctionCode code) const = 0;
		
		virtual bool GetUpdateKey(const User& user, opendnp3::UpdateKeyMode& type, openpal::ReadBufferView& key) const = 0;

		virtual bool UserExists(const User& user) const = 0;
};

}

#endif

