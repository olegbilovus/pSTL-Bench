#ifdef PSTL_BENCH_USE_HPX
#include <hpx/hpx_main.hpp>
#endif

#include <thread>

#include <benchmark/benchmark.h>

#if defined(PSTL_BENCH_USE_TBB) or defined(PSTL_BENCH_USE_HPX)
#include "pstl/utils/thread_control.h"
#endif

#ifdef PSTL_BENCH_USE_LIKWID
#include <likwid-marker.h>
#endif

#include "pstl/benchmarks/pstl-benchmarks.h"


// Global variable to store the number of threads
int GLOBAL_NUM_THREADS;

// Run the benchmark
int main(int argc, char ** argv)
{
#if defined(PSTL_BENCH_USE_TBB)
	auto tbbThreadControl = init_tbb_thread_control();
	GLOBAL_NUM_THREADS    = tbb::global_control::active_value(tbb::global_control::max_allowed_parallelism);
	benchmark::AddCustomContext("tbb #threads", std::to_string(GLOBAL_NUM_THREADS));
#elif defined(PSTL_BENCH_USE_GNU) || defined(PSTL_BENCH_USE_PSTL)
	GLOBAL_NUM_THREADS = omp_get_max_threads();
	benchmark::AddCustomContext("omp #threads", std::to_string(GLOBAL_NUM_THREADS));
#elif defined(PSTL_BENCH_USE_HPX)
	GLOBAL_NUM_THREADS = hpx::get_num_worker_threads();
	benchmark::AddCustomContext("hpx #threads", std::to_string(GLOBAL_NUM_THREADS));
#else
	GLOBAL_NUM_THREADS = std::thread::hardware_concurrency();
	benchmark::AddCustomContext("std::threads #threads", std::to_string(GLOBAL_NUM_THREADS));
#endif

#ifdef PSTL_BENCH_USE_PAPI
	benchmark::AddCustomContext("PAPI", "enabled");
#endif

#ifdef PSTL_BENCH_USE_LIKWID
	benchmark::AddCustomContext("LIKWID", "enabled");
	LIKWID_MARKER_INIT;
#endif

	benchmark::Initialize(&argc, argv);
	if (benchmark::ReportUnrecognizedArguments(argc, argv)) { return 1; }
	benchmark::RunSpecifiedBenchmarks();
	benchmark::Shutdown();

#ifdef PSTL_BENCH_USE_LIKWID
	LIKWID_MARKER_CLOSE;
#endif

	return EXIT_SUCCESS;
}
