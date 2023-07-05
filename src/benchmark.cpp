#include "benchmark.h"
// Starting point: StartBenchmark("id");
// Stopping point: StopBenchmark("id");
// Showing Results: ShowBenchmark();
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

std::vector<cBenchmark> benchmarks = {cBenchmark("NULL")};

cBenchmark::cBenchmark(std::string id)
    : id_(id)
    , iterations_(0)
{
}

void StartBenchmark(std::string id)
{
    benchmarks.push_back(cBenchmark(id));

    benchmarks.back().startTime_ = std::chrono::steady_clock::now();
}


void StopBenchmark(std::string id)
{
    cBenchmark& benchmark = selectBenchmark(id);

    benchmark.stopTime_ = std::chrono::steady_clock::now();
    benchmark.latestTime_ = std::chrono::duration_cast<std::chrono::nanoseconds>(benchmark.stopTime_ - benchmark.startTime_);

    benchmark.iterations_ += 1;
    // new_average = (old_average * (n-1) + new_value) / n
    benchmark.avgTime_ = (benchmark.avgTime_ * (benchmark.iterations_ - 1) + benchmark.latestTime_) / benchmark.iterations_;
}

cBenchmark& selectBenchmark(std::vector<cBenchmark>& benchmarks&, std::string id)
{
    for (auto& benchmark : benchmarks)
    {
        if (benchmark.id_ == id)
        {
            return benchmark;
        }
    }
    std::cout << "No benchmark " << id << " found!\n";
}

void ShowBenchmarks(std::vector<cBenchmark>& benchmarks)
{
    for (auto& benchmark : benchmarks)
    {
        if (benchmark.id_ != "NULL")
        {
            std::cout << benchmark.id_ << " (Lst|Avg|Itr): " << benchmark.latestTime_.count() << " ns | " << benchmark.avgTime_.count() << " ns | " << benchmark.iterations_ << "\n";
        }
    }
    std::cout << "\n";
}
