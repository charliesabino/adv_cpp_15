#include <algorithm>
#include <benchmark/benchmark.h>
#include <execution>
#include <iostream>
#include <random>
#include <vector>

auto get_random_vec(size_t n) -> std::vector<double> {
  double lower = 0.0, upper = 1.0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(lower, upper);

  std::vector<double> vec(n);
  for (auto &x : vec) {
    x = dis(gen);
  }

  return vec;
}

void benchmark_par_unseq(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto vec = get_random_vec(1 << 16);
    state.ResumeTiming();
    std::sort(std::execution::par_unseq, begin(vec), end(vec));
  }
}

void benchmark_par(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto vec = get_random_vec(1 << 16);
    state.ResumeTiming();
    std::sort(std::execution::par, begin(vec), end(vec));
  }
}

void benchmark_seq(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto vec = get_random_vec(1 << 16);
    state.ResumeTiming();
    std::sort(begin(vec), end(vec));
  }
}

BENCHMARK(benchmark_par_unseq);
BENCHMARK(benchmark_par);
BENCHMARK(benchmark_seq);

BENCHMARK_MAIN();
