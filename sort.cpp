#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
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

template <typename Func>
double run_benchmark(const std::string &name, size_t vector_size, int num_runs,
                     Func sort_func) {
  std::vector<double> durations_ms;
  durations_ms.reserve(num_runs);

  std::cout << "Running benchmark: " << name << " (" << num_runs << " runs)..."
            << std::flush;

  for (int i = 0; i < num_runs; ++i) {

    auto vec = get_random_vec(vector_size);

    auto start = std::chrono::high_resolution_clock::now();
    sort_func(vec);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
            end - start);
    durations_ms.push_back(duration.count());
  }

  double total_duration =
      std::accumulate(durations_ms.begin(), durations_ms.end(), 0.0);
  double average_duration = total_duration / num_runs;

  std::cout << " Done." << std::endl;
  return average_duration;
}

int main() {
  const size_t vector_size = 1 << 20;
  const int num_runs = 10;

  std::cout << "Vector size: " << vector_size << std::endl;
  std::cout << "Number of runs per benchmark: " << num_runs << std::endl
            << std::endl;

  double avg_par_unseq = run_benchmark("Parallel Unsequenced Sort", vector_size,
                                       num_runs, [](std::vector<double> &vec) {
                                         std::sort(std::execution::par_unseq,
                                                   vec.begin(), vec.end());
                                       });

  double avg_par = run_benchmark(
      "Parallel Sort", vector_size, num_runs, [](std::vector<double> &vec) {
        std::sort(std::execution::par, vec.begin(), vec.end());
      });

  double avg_seq = run_benchmark(
      "Sequential Sort", vector_size, num_runs,
      [](std::vector<double> &vec) { std::sort(vec.begin(), vec.end()); });

  std::cout << "\n--- Average Execution Times ---" << std::endl;
  std::cout << std::fixed << std::setprecision(3);
  std::cout << "Parallel Unsequenced: " << avg_par_unseq << " ms" << std::endl;
  std::cout << "Parallel            : " << avg_par << " ms" << std::endl;
  std::cout << "Sequential          : " << avg_seq << " ms" << std::endl;

  return 0;
}
