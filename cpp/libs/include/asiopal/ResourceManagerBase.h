/*
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
#ifndef ASIOPAL_RESOURCEMANAGERBASE_H
#define ASIOPAL_RESOURCEMANAGERBASE_H

#include "IResourceManager.h"

#include <mutex>
#include <vector>
#include <algorithm>

namespace asiopal
{

class ResourceManagerBase : public IResourceManager
{

public:

	virtual bool Attach(std::shared_ptr<IResource> resource) override final
	{
		std::lock_guard <std::mutex> lock(this->resource_mutex);

		if (this->is_shutting_down)
		{
			return false;
		}

		this->resources.push_back(resource);

		return true;
	}

	virtual void Detach(std::shared_ptr<IResource> resource)  override final
	{
		std::lock_guard <std::mutex> lock(this->resource_mutex);

		auto is_match = [resource](const std::shared_ptr<asiopal::IResource>& other) -> bool
		{
			return resource == other;
		};

		this->resources.erase(std::remove_if(this->resources.begin(), this->resources.end(), is_match), this->resources.end());
	}

protected:

	void ShutdownResources()
	{
		std::lock_guard <std::mutex> lock(this->resource_mutex);

		this->is_shutting_down = true;

		for (auto& resource : this->resources)
		{
			resource->BeginShutdown();
		}
	}

	template <class R, class T>
	std::shared_ptr<R> BindResource(const T& create)
	{
		std::lock_guard <std::mutex> lock(this->resource_mutex);
		if (this->is_shutting_down)
		{
			return nullptr;
		}
		else
		{
			auto item = create();
			auto shutdown = [item, this]()
			{
				this->Detach(item);
			};
			item->SetShutdownAction(shutdown);
			this->resources.push_back(item);
			return item;
		}
	}

private:

	bool is_shutting_down = false;
	std::mutex resource_mutex;
	std::vector<std::shared_ptr<asiopal::IResource>> resources;

};

}

#endif
