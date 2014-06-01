#include <gtest/gtest.h>

#include <handystats/rapidjson/allocators.h>

#include <handystats/chrono.hpp>
#include <handystats/metrics/gauge.hpp>

#include <handystats/json/gauge_json_writer.hpp>

using namespace handystats::metrics;

TEST(GaugeTest, TestGaugeConstruction) {
	gauge sample_gauge(-10, handystats::chrono::default_clock::now());

	ASSERT_NEAR(sample_gauge.value, -10, 1E-9);

	std::cout << handystats::json::write_to_json_string<rapidjson::MemoryPoolAllocator<>>(&sample_gauge) << std::endl;
}

TEST(GaugeTest, TestGaugeSetMethod) {
	gauge sample_gauge;

	for (int test_value = -1E3; test_value < 1E3; ++test_value) {
		sample_gauge.set(test_value, handystats::chrono::default_clock::now());

		ASSERT_NEAR(sample_gauge.value, test_value, 1E-9);
	}

	std::cout << handystats::json::write_to_json_string<rapidjson::MemoryPoolAllocator<>>(&sample_gauge) << std::endl;
}

TEST(GaugeTest, TestGaugeInternalStats) {
	gauge sample_gauge;

	const int min_test_value = -1E3;
	const int max_test_value = 1E3;

	for (int test_value = min_test_value; test_value <= max_test_value; ++test_value) {
		sample_gauge.set(test_value, handystats::chrono::default_clock::now());
	}


	auto stats = sample_gauge.values;
	ASSERT_NEAR(stats.min(), min_test_value, 1E-9);
	ASSERT_NEAR(stats.max(), max_test_value, 1E-9);

	ASSERT_EQ(stats.count(), max_test_value - min_test_value + 1);
	ASSERT_NEAR(stats.sum(), 0, 1E-9);
	ASSERT_NEAR(stats.mean(), 0, 1E-9);

	std::cout << handystats::json::write_to_json_string<rapidjson::MemoryPoolAllocator<>>(&sample_gauge) << std::endl;
}
