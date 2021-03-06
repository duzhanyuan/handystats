/*
* Copyright (c) YANDEX LLC. All rights reserved.
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 3.0 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library.
*/

#ifndef HANDYSTATS_MEASURING_POINTS_TIMER_PROXY_HPP_
#define HANDYSTATS_MEASURING_POINTS_TIMER_PROXY_HPP_

#include <string>

#include <handystats/metrics/timer.hpp>

#include <handystats/measuring_points/timer.hpp>

namespace handystats { namespace measuring_points {

class timer_proxy {
public:
	/*
	 * Ctors without sending init event
	 */
	timer_proxy(const std::string& name,
			const metrics::timer::instance_id_type& instance_id = metrics::timer::DEFAULT_INSTANCE_ID
		)
		: name(name)
		, instance_id(instance_id)
	{}

	timer_proxy(const char* name,
			const metrics::timer::instance_id_type& instance_id = metrics::timer::DEFAULT_INSTANCE_ID
		)
		: name(name)
		, instance_id(instance_id)
	{}

	/*
	 * Proxy init event
	 */
	void init(
			const metrics::timer::instance_id_type& instance_id = metrics::timer::DEFAULT_INSTANCE_ID,
			const metrics::timer::time_point& timestamp = metrics::timer::clock::now()
		)
	{
		HANDY_TIMER_INIT(name.substr(), choose_instance_id(instance_id), timestamp);
	}

	/*
	 * Proxy start event
	 */
	void start(
			const metrics::timer::instance_id_type& instance_id = metrics::timer::DEFAULT_INSTANCE_ID,
			const metrics::timer::time_point& timestamp = metrics::timer::clock::now()
		)
	{
		HANDY_TIMER_START(name.substr(), choose_instance_id(instance_id), timestamp);
	}

	/*
	 * Proxy stop event
	 */
	void stop(
			const metrics::timer::instance_id_type& instance_id = metrics::timer::DEFAULT_INSTANCE_ID,
			const metrics::timer::time_point& timestamp = metrics::timer::clock::now()
		)
	{
		HANDY_TIMER_STOP(name.substr(), choose_instance_id(instance_id), timestamp);
	}

	/*
	 * Proxy discard event
	 */
	void discard(
			const metrics::timer::instance_id_type& instance_id = metrics::timer::DEFAULT_INSTANCE_ID,
			const metrics::timer::time_point& timestamp = metrics::timer::clock::now()
		)
	{
		HANDY_TIMER_DISCARD(name.substr(), choose_instance_id(instance_id), timestamp);
	}

	/*
	 * Proxy heartbeat event
	 */
	void heartbeat(
			const metrics::timer::instance_id_type& instance_id = metrics::timer::DEFAULT_INSTANCE_ID,
			const metrics::timer::time_point& timestamp = metrics::timer::clock::now()
		)
	{
		HANDY_TIMER_HEARTBEAT(name.substr(), choose_instance_id(instance_id), timestamp);
	}

	/*
	 * Proxy set event
	 */
	void set(
			const metrics::timer::value_type& measurement,
			const metrics::timer::time_point& timestamp = metrics::timer::clock::now()
		)
	{
		HANDY_TIMER_SET(name.substr(), measurement, timestamp);
	}

private:
	const std::string name;
	const metrics::timer::instance_id_type instance_id;

	metrics::timer::instance_id_type choose_instance_id(const metrics::timer::instance_id_type& instance_id) {
		if (this->instance_id != metrics::timer::DEFAULT_INSTANCE_ID) {
			return this->instance_id;
		}
		else {
			return instance_id;
		}
	}
};

}} // namespace handystats::measuring_points

#endif // HANDYSTATS_MEASURING_POINTS_TIMER_PROXY_HPP_
