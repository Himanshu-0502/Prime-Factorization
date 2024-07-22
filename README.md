# Prime Factorization

## Overview

This repository contains C++ implementations for prime checking and factorization using advanced mathematical algorithms. The primary functionalities include checking if a number is prime and factorizing a given number into its prime factors. The algorithm used for prime checking is the Miller-Rabin primality test, and the algorithm used for factorization is Pollard's Rho algorithm. The implementations are optimized for performance and can handle numbers upto 64-bit integers.

## Files

- `Prime.cpp`: Contains the implementation for checking if a number is prime. It can check upto 400,000 numbers in less than 1 second.
- `Factorization.cpp`: Contains the implementation for factorizing a given number into its prime factors. It can factorize upto 400 numbers in less than 1 second.

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/Himanshu-0502/Prime-Factorization.git
    cd Prime-Factorization
    ```

2. Compile the programs:
    ```sh
    g++ Prime.cpp -o prime
    g++ Factorization.cpp -o factorize
    ```

3. Run the programs:
    ```sh
    ./prime
    ./factorize
    ```

## Usage

- To check if a number is prime, run the `prime` program and enter the number.
- To factorize a number into its prime factors, run the `factorize` program and enter the number.

## Acknowledgements

Special thanks to the developers and researchers who created and documented the Montgomery multiplication, Miller-Rabin primality test, Pollard's Rho algorithm, and Stein's algorithm.