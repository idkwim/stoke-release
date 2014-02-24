#ifndef STOKE_SRC_SEARCH_STATISTICS_CALLBACK_H
#define STOKE_SRC_SEARCH_STATISTICS_CALLBACK_H

#include <chrono>
#include <vector>

#include "src/search/statistics.h"

namespace stoke {

/** POD-datatype passed to callbacks by search */
struct StatisticsCallbackData {
	const size_t iterations;
	const time_t elapsed; // @todo what should this be?
	const std::vector<Statistics>& move_statistics;
};

/** Callback signature */
typedef void (*StatisticsCallback)(const StatisticsCallbackData& data, void* arg);

} // namespace stoke

#endif