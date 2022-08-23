#!/bin/bash

mpicc -o mpi_ping_pong mpi_ping_pong.c
mpirun -np 2 ./mpi_ping_pong