### The Dining Philosophers Problem
The dining philosophers problem is a famous problem in computer science used to illustrate common issues in concurrent programming. The problem was originally formulated in 1965 by Edsger Dijkstra, and is stated as follows:

      X amount of philosophers sit at a round table with bowls of food.
      Forks are placed in front of each philosopher.
      There are as many forks as philosophers.
      All day the philosophers take turns eating, sleeping, and thinking.
      A philosopher must have two forks in order to eat, and each fork
      may only be used by one philosopher at a time. At any time a
      philosopher can pick up or set down a fork,
      but cannot start eating until picking up both forks.
      The philosophers alternatively eat, sleep, or think.
      While they are eating, they are not thinking nor sleeping,
      while thinking, they are not eating nor sleeping,
      and, of course, while sleeping, they are not eating nor thinking.
      
  ![Image Description](https://github.com/iobba/philosophers/blob/master/philo/zphilo_img.png)

## Overview

This project simulates the classic dining philosophers problem, featuring both a mandatory and a bonus part. It's a hands-on exploration of threading and process management, ensuring all philosophers can eat without starving.

## Key Concepts Explained

### Threading & Mutexes (Mandatory Part)

- **Threading**: Threads allow us to run multiple operations concurrently within a single process. Each philosopher is modeled as a thread, enabling simultaneous actions like eating, thinking, and sleeping.

- **Mutexes**: Mutexes are used to protect shared resources (forks) from being accessed simultaneously by multiple threads. This prevents race conditions and ensures fair access to resources.

### Processes & Semaphores (Bonus Part)

- **Processes**: Unlike threads, processes run independently and have their own memory space. The bonus part introduces processes for philosophers, enhancing scalability and isolation.

- **Semaphores**: Semaphores are used to represent the availability of resources (forks) in a synchronized manner. They allow for efficient management of shared resources across multiple processes.

### Data Races (Race Conditions) — What Are They?
Data races are a common problem in multithreaded programming. Data races occur when multiple tasks or threads access a shared resource without sufficient protections, leading to undefined or unpredictable behavior.

- two or more threads concurrently accessing a location of memory
- one of them is a write
- one of them is unsynchronized
  
In simpler words a race condition can happen when 2 or more threads are trying to access and modify the same variable at the same time, it can lead to an error in the final value of the variable, it doesn’t mean it will for sure happen though. For an example let’s think of a function that deposits the amount you insert to your bank account, If we use multithreading and use 2 threads and want to deposit 300 using the first thread and 200 using the second you will think our bank account will have a total of 500, but that’s not particularly the case.

## Project Structure

### Mandatory Part: `philo`

- **Objective**: Implement a simulation where philosophers eat, think, and sleep, with forks as shared resources.
- **Implementation**: Each philosopher is a thread, with forks protected by mutexes.

### Bonus Part: `philo_bonus`

- **Objective**: Extend the simulation to use processes and semaphores for managing forks.
- **Implementation**: Centralize forks with semaphore representation for availability, with each philosopher as a process.
