#include <thread>

#include <gtest/gtest.h>

#include <handystats/chrono.hpp>
#include <handystats/metrics/timer.hpp>

using namespace handystats::metrics;

TEST(TimerTest, CheckTimerCountsRunningTimeCorrectly) {
	timer inter;
	inter.start(timer::clock::now());

	std::this_thread::sleep_for(handystats::chrono::default_duration(100));

	inter.stop(timer::clock::now());

	ASSERT_GT(inter.get().first.count(), 100);
}

TEST(Timer, CheckNotStartedTimerHasNoDuration) {
	timer inter;

	std::this_thread::sleep_for(handystats::chrono::default_duration(100));

	ASSERT_EQ(inter.get().first.count(), 0);
}

TEST(TimerTest, CheckNotStoppedTimerHasNoDuration) {
	timer inter;
	inter.start(timer::clock::now());

	std::this_thread::sleep_for(handystats::chrono::default_duration(100));

	ASSERT_EQ(inter.get().first.count(), 0);
}
