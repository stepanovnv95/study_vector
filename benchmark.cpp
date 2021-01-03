#include <benchmark/benchmark.h>

#include <vector>
#include "Vector.h"


template<class ContainerType, class ItemType>
static void BM_PushBack(benchmark::State& state)
{
    for (auto _ : state)
    {
        ContainerType v;
        for (size_t i = 0; i < 10000; ++i) {
            v.push_back(ItemType());
        }
    }
}
BENCHMARK_TEMPLATE(BM_PushBack, std::vector<int>, int);
BENCHMARK_TEMPLATE(BM_PushBack, study::Vector<int>, int);

BENCHMARK_MAIN();
