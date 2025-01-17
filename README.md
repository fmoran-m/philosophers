# Philosophers

## Overview

The Philosophers Problem is a classic concurrency challenge that explores the synchronization and resource-sharing issues between multiple threads. In this project, philosophers represent threads that alternate between three states: eating, thinking, and sleeping. They sit at a circular table with a shared bowl of spaghetti and a limited number of forks, where each philosopher needs two forks to eat. The simulation adheres to strict rules about timing and resource management, with a focus on preventing starvation and ensuring thread safety using mutexes.

This program, implemented in C, utilizes threads and mutexes to simulate and manage the philosophers' behavior, ensuring proper synchronization and avoiding undefined behavior like deadlocks or race conditions.

## The Problem

One or more philosophers are sitting at a round table with a large bowl of spaghetti in the center.
Each philosopher can perform only one of three actions: eating, thinking, or sleeping. While they are:

Eating: they cannot think or sleep.
Thinking: they cannot sleep or eat.
Sleeping: they cannot eat or think.
There are as many forks on the table as philosophers. To eat, a philosopher must take the fork on their right and the fork on their left, one in each hand. Once they finish eating, they will put both forks back on the table and immediately start sleeping. After waking up, they will begin thinking again.

The simulation stops if a philosopher dies of starvation. To avoid this:

All philosophers must eat and should never starve.
Philosophers do not communicate with each other and cannot predict if another philosopher is about to die.
The main challenge is to ensure that all philosophers eat in time and that no one dies!
