#include <benchmark/benchmark.h>

#include <vector>
#include "Vector.h"


template<class ContainerType, class ValueType=typename ContainerType::value_type>
static void BM_PushBack(benchmark::State& state)
{
    for (auto _ : state)
    {
        ContainerType v;
        for (size_t i = 0; i < 10000; ++i) {
            v.push_back(ValueType());
        }
    }
}
BENCHMARK_TEMPLATE(BM_PushBack, std::vector<bool>);
BENCHMARK_TEMPLATE(BM_PushBack, study::Vector<bool>);
BENCHMARK_TEMPLATE(BM_PushBack, std::vector<int>);
BENCHMARK_TEMPLATE(BM_PushBack, study::Vector<int>);


template<class ContainerType>
static void BM_Iteration(benchmark::State& state)
{
    for (auto _ : state)
    {
        ContainerType v(10000);
        for (auto it = v.begin(); it != v.end(); ++it) {
            *it = 1;
        }
    }
}
BENCHMARK_TEMPLATE(BM_Iteration, std::vector<int>);
BENCHMARK_TEMPLATE(BM_Iteration, study::Vector<int>);


BENCHMARK_MAIN();
