# pSTL-Bench

pSTL-Bench is a benchmark suite designed to assist developers in evaluating the most suitable parallel
STL (Standard Template Library) backend for their needs.
This tool allows developers to benchmark a wide variety of parallel primitives and offers the flexibility to choose the
desired backend for execution during compile time.

## Table of Contents

- [Fork Overview](#fork-overview)
  - [Ansible Playbooks](#ansible-playbooks)
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)

# Fork Overview

This repository is a fork of [pSTL-Bench by parlab-tuwien](https://github.com/parlab-tuwien/pSTL-Bench), originally introduced in the paper:

> Ruben Laso, Diego Krupitza, and Sascha Hunold. 2024,
> **Exploring Scalability in C++ Parallel STL Implementations**,
> *In Proceedings of the 53rd International Conference on Parallel Processing (ICPP '24)*.
> [DOI: 10.1145/3673038.3673065](https://doi.org/10.1145/3673038.3673065)

This fork introduces support for **oneDPL** backend and several enhancements to improve the reproducibility of the benchmark suite:

* **Ansible playbooks** for automating the setup of dependencies, builds, and benchmark execution across different systems.
* **R scripts** for automated generation of plots and analysis of benchmark results.
* **Docs** for comprehensive documentation of the benchmarking process, including setup, execution, and analysis.

These additions aim to streamline the benchmarking workflow and ensure consistent, reproducible results across diverse environments.

## Ansible Playbooks
There are three Ansible playbooks available in the `ansible/playbooks` directory:
- `install_dependencies.yml`: Installs the necessary dependencies for the benchmark suite.
- `cmake_builds.yml`: Builds the benchmark suite using CMake with the specified backend and compiler.
- `benchmark.yml`: Executes the benchmark suite and collects results.

The playbooks were tested on Ubuntu 24.04 and 25.04 and should work on any Debian-based distribution.

The original fork used CSV files for results, but this fork has been modified to use JSON files because Google Benchmark deprecated CSV output in favor of JSON output.

You can run the playbooks using the CLI or by using [Semaphore UI](https://semaphoreui.com/). There is a Semaphore UI project available at [ansible/semaphore_ui_project.json](ansible/semaphore_ui_project.json)

The Semaphore UI project also shows every needed variable for Ansible playbooks, so you can easily set them up in the UI. There are some task denominated as *debug* that will print commands to the console, so you can see what is being executed in the background when a playbook is ran and how to run it manually if you prefer not to use the UI.

### Semaphore UI screenshots
| ![ Benchmark tab ](/docs/images/semaphore_ui/benchmark_tab.png) | ![ Debug cmake output ](/docs/images/semaphore_ui/debug_cmake_output.png) |
|:--:| :--:|
| [*Semaphore UI - Benchmark tab*](/docs/images/semaphore_ui/benchmark_tab.png) | [*Semaphore UI - Debug CMake output*](/docs/images/semaphore_ui/debug_cmake_output.png) |

## Introduction

pSTL-Bench is a resource for developers seeking to assess the performance and suitability of different
parallel STL backends.
By providing a rich benchmark suite, it facilitates the evaluation of parallel primitives across various
implementations, aiding in the selection of the optimal backend for specific requirements.

## Features

- Comprehensive benchmark suite for parallel STL backends
- Benchmarks a wide variety of parallel primitives
- Flexibility to choose the desired backend at compile time
- Facilitates performance comparison and evaluation of different implementations

## Getting Started

To run pSTL-Bench, follow these steps:

1. Clone the repository:

```shell
git clone https://github.com/parlab-tuwien/pSTL-Bench.git
```

2. Build the project with the desired parallel STL Backend

```shell
cmake -DCMAKE_BUILD_TYPE=Release -DPSTL_BENCH_BACKEND=TBB -DCMAKE_CXX_COMPILER=g++ -S . -B ./cmake-build-gcc
cmake --build cmake-build-gcc/ --target pSTL-Bench
```

One must define which backend to be used and which compiler.
You can define the backend with `-DPSTL_BENCH_BACKEND=...` and the compiler with `-DCMAKE_CXX_COMPILER=...`.
In the example above we will use g++ with TBB.
A list of supported backends can be seen in `./cmake/`.

Other options are:

* `-DPSTL_BENCH_DATA_TYPE=...` to define the data type (`int`, `float`, `double`...).
* `-DPSTL_BENCH_MIN_INPUT_SIZE=...` and `-DPSTL_BENCH_MAX_INPUT_SIZE=...` to define the range of input sizes.
* `-DPSTL_BENCH_USE_PAR_ALLOC=ON|OFF` to use a parallel allocator designed for NUMA systems.
* `-DPSTL_BENCH_USE_LIKWID=ON|OFF` and `-DPSTL_BENCH_USE_PAPI=ON|OFF` to use performance counters
  with [LIKWID](https://github.com/RRZE-HPC/likwid) or [PAPI](https://github.com/icl-utk-edu/papi).
* `-DPSTL_BENCH_GPU_CONTINUOUS_TRANSFERS=ON|OFF` to enable continuous transfers between the CPU and GPU so will be
  transferred between host and device before and after each kernel. When OFF, data will be transferred only once before
  the first call.

_Note_: we recommend to use `ccmake` to see all the possible flags and options.

## USAGE

After building the binary for a desired backend compiler pairing, you can simply call it.
Since we are using [Google benchmark](https://github.com/google/benchmark) under the hood, you can use all the possible
command line parameters.
For example:

```shell
./build/pSTL-Bench --benchmark_filter="std::sort"
```

The full set of options can be printed with `./pSTL-Bench --help`.

To get the full list of benchmarks, you can use the `--benchmark_list_tests` flag.

By default, `pSTL-Bench` will capture the `OMP_NUM_THREADS` environment variable to set the number of threads.
However, for [HPX](https://github.com/STEllAR-GROUP/hpx) argument `--hpx:threads` must be used.

Other environment variables that can be used are:

* `PSTL_BENCH_ABS_TOL` and `PSTL_BENCH_REL_TOL` to define the absolute and relative tolerance when asserting the results
  of floating point operations.

## Citation

If you use pSTL-Bench in your research, please cite the following papers:

```bibtex
@inproceedings{
  pstlbench-icpp24,
  title={Exploring Scalability in {C++} Parallel {STL} Implementations},
  author={Ruben Laso and Diego Krupitza and Sascha Hunold},
  booktitle={Proceedings of the 2024 International Conference on Parallel Processing},
  year={2024},
  doi={10.1145/3673038.3673065}
}

@misc{
  pstlbench2024,
  title={{pSTL-Bench}: A Micro-Benchmark Suite for Assessing Scalability of {C++} Parallel {STL} Implementations},
  author={Ruben Laso and Diego Krupitza and Sascha Hunold},
  year={2024},
  eprint={2402.06384},
  archivePrefix={arXiv},
  primaryClass={cs.DC}
}
```

## Dependencies

Some parallel STL backends have dependencies:

- TBB can be found on their [GitHub](https://github.com/oneapi-src/oneTBB) or
  their [website](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb.html).
- HPX can be found on their [GitHub](https://github.com/STEllAR-GROUP/hpx) or
  their [website](https://hpx.stellar-group.org/).
- NVHPC can be found on their [website](https://developer.nvidia.com/hpc-sdk).