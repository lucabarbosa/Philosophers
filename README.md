# Colorful Philosophers - Dining Philosophers Problem

A multithreaded simulation of the classic **Dining Philosophers Problem**, implemented in C using POSIX threads (pthreads) and mutexes. This project is part of the 42 School curriculum and explores concepts of concurrency, synchronization, and deadlock avoidance.

## 📋 Table of Contents

- [Overview](#overview)
- [The Problem](#the-problem)
- [Features](#features)
- [Compilation](#compilation)
- [Usage](#usage)
- [Testing Scenarios](#testing-scenarios)
- [Checking Leaks and Data Races](#checking-leak-and-data-races)
- [Project Structure](#project-structure)
- [Learning Resources](#learning-resources)

## 🎯 Overview

The Dining Philosophers Problem is a classic synchronization problem in computer science that illustrates the challenges of allocating limited resources among multiple processes while avoiding deadlock and starvation.

In this simulation:
- Philosophers sit at a round table with a bowl of spaghetti
- Each philosopher alternates between eating, sleeping, and thinking
- There's one fork between each pair of philosophers
- A philosopher needs two forks to eat
- The simulation ends when a philosopher dies of starvation or all philosophers have eaten a specified number of times

## 🍝 The Problem

Philosophers follow this routine:
1. **Think** - Philosopher contemplates life
2. **Take forks** - Attempt to pick up both left and right forks
3. **Eat** - Consume spaghetti for a specified duration (eat time)
4. **Sleep** - Rest after eating
5. **Repeat** - Continue until death or completion

    The philosopher dies if they don't start eating within `time_to_die` in milliseconds since their last meal.

## ✨ Features

- **Thread-safe operations** using mutexes
- **Deadlock prevention** through fork ordering strategy
- **Real-time monitoring** of philosopher states
- **Death detection** system
- **Meal tracking** for completion conditions
- **Color-coded output** for better visualization
- **Optimized thinking time** to reduce unnecessary CPU usage

## 🔨 Compilation

To compile the project, simply run:

```bash
make
```

This will generate the `philo` executable.

To clean object files:
```bash
make clean
```

To clean everything (objects and executable):
```bash
make fclean
```

To recompile from scratch:
```bash
make re
```

## 🚀 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] - optional
```

### Arguments

1. **number_of_philosophers** - Number of philosophers (and forks) [1-200]
2. **time_to_die** - Time in milliseconds until a philosopher dies without eating
3. **time_to_eat** - Time in milliseconds it takes to eat
4. **time_to_sleep** - Time in milliseconds spent sleeping
5. **[number_of_times_each_philosopher_must_eat]** - (Optional) Simulation stops when all philosophers have eaten this many times

### Example

```bash
./philo 5 310 200 200
```

This creates 5 philosophers who die after 310ms without eating, take 200ms to eat, and sleep for 200ms.

## 🧪 Testing Scenarios

### Scenario 1: Philosopher Should Die

Test cases where a philosopher should starve:

```bash
#Should die - impossible to survive
./philo 1 800 200 200
#Expected: Philosopher takes one fork and dies after 800ms

#Should die - not enough time
./philo 4 310 200 100
#Expected: At least one philosopher dies

#Edge case - dies right at the limit
./philo 4 200 205 200
#Expected: Should die as eating time exceeds survival time
```

### Scenario 2: No One Should Die (Infinite Eating)

Test cases where philosophers should survive indefinitely, depending of your computer config some philo can died because of the execution of process:

```bash
#Basic survival test
./philo 5 800 200 200
#Expected: All philosophers eat continuously, no deaths

#Stress test
./philo 50 800 200 200
#Expected: All 50 philosophers survive

#Very tight timing
./philo 4 310 100 100
#Expected: Should survive with optimized thinking time
```

### Scenario 3: Complete After N Meals

Test cases with meal limits:

```bash
#Complete after 5 meals each
./philo 5 800 200 200 5
#Expected: Simulation ends when all philosophers eat 5 times

#Quick completion
./philo 4 410 200 200 3
#Expected: All philosophers eat 3 times, then stop

#Many meals
./philo 2 400 100 100 10
#Expected: Both philosophers complete 10 meals

#Single meal test
./philo 7 310 100 100 5
#Expected: All 7 philosophers eat 5 times, then simulation ends
```
You can check the how many meals they eat using:
```bash
#Test with 5 meals each
./philo 7 800 200 200 5 | grep 'eating' | wc -l
#Expected: 35 (7 philos * 5 meals = 35)
```

### Additional Edge Cases

```bash
#Single philosopher (special case)
./philo 1 800 200 200
#Expected: Takes one fork, waits, and dies

#Minimum values
./philo 2 60 10 10
#Expected: Should handle very fast execution

#Large number of philosophers
./philo 200 800 200 200
#Expected: All 200 philosophers should function properly
```

## 🧪 Checking leak and data races

```bash
#Single philosopher (leak case)
valgrind --leak-check=full --show-leak-kinds=all ./philo 1 800 200 200
#Expected: All heap blocks were freed -- no leaks are possible

#Single philosopher (data race case)
valgrind --tool=helgrind ./philo 1 800 200 200
#Expected: ERROR SUMMARY: 0 errors from 0 contexts (suppressed: n from n)

#Single philosopher (leak case)
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 310 200 100
#Expected: All heap blocks were freed -- no leaks are possible

#Single philosopher (data race case)
valgrind --tool=helgrind ./philo 5 310 200 100
#Expected: ERROR SUMMARY: 0 errors from 0 contexts (suppressed: n from n)

#Single philosopher (leak case)
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200 5
#Expected: All heap blocks were freed -- no leaks are possible

#Single philosopher (data race case)
valgrind --tool=helgrind ./philo 5 800 200 200 5
#Expected: ERROR SUMMARY: 0 errors from 0 contexts (suppressed: n from n)
```

## 📁 Project Structure

```
philo/
├── main.c              # Entry point and initialization
├── threads.c           # Thread creation and management
├── routine.c           # Philosopher routine (eat, sleep, think)
├── monitor.c           # Death detection and meal tracking
├── philo_utils.c       # Utility functions (time, parsing, errors)
├── philo.h             # Header file with structures and prototypes
├── Makefile            # Compilation rules
└─────────────────────────────────────────────────────
├── LICENSE             # License of the project
└── README.md           # This file
```

### Key Components

- **Thread Management**: Each philosopher runs on a separate thread
- **Mutex Protection**: Forks, death status, and output are protected by mutexes
- **Monitoring System**: Main thread monitors for deaths and meal completion
- **Deadlock Prevention**: Even-numbered philosophers pick forks in reverse order
- **Optimized Thinking**: Thinking time is calculated to prevent unnecessary spinning

## 📚 Learning Resources

This project was developed using this resources:

### Articles & Guides
- [**Philosophers 42 Guide - The Dining Philosophers Problem**](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)  
  Comprehensive guide explaining the problem and implementation strategies specific to 42's version

- [**Philosophers 42 Guide - Gitbook**](https://42-cursus.gitbook.io/guide/3-rank-03/philosophers)  
  Easiest guide who explain the problem and the new tools that you'll use

### Video Tutorials
- [**CodeVault - Unix Threads in C**](https://www.youtube.com/watch?v=JbDHLaf1c5Y)  
  Excellent video series on pthread programming and synchronization concepts

### Additional Concepts
- POSIX Threads (pthreads)
- Mutex synchronization
- Race conditions and deadlocks
- Thread-safe programming
- Resource allocation strategies

## 🎨 Output Visualization

The program outputs philosopher actions with timestamps and color coding:

- 🍴 **White**: Fork taken
- 🍝 **Red**: Eating
- 😴 **Blue**: Sleeping
- 🧠 **Green**: Thinking
- 💀 **Yellow**: Death
- ✅ **Green**: All meals completed

Example output:
```
0 1 has taken a fork 🍴
0 1 has taken a fork 🍴
0 1 is eating 🍝
200 2 has taken a fork 🍴
200 2 has taken a fork 🍴
200 2 is eating 🍝
...
```

## ⚠️ Important Notes

- All timestamps are in milliseconds
- The simulation must not have data races
- Philosophers should die within 10ms of the actual death time
- Output from different philosophers should not be mixed
- The program handles up to 200 philosophers
- A philosopher can't eat with only one fork

## 🏆 Project Goals

- ✅ Learn about threads and mutexes
- ✅ Understand synchronization problems
- ✅ Implement deadlock prevention
- ✅ Practice concurrent programming
- ✅ Optimize resource allocation

---