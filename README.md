# ECommerceBackend

[![Build Status](https://github.com/yourusername/ECommerceBackend/workflows/CI/badge.svg)](https://github.com/yourusername/ECommerceBackend/actions)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

A production‑ready, modular C++ backend for a simple e‑commerce platform. 
Features include:

- **Cart management** – add/remove products, calculate totals.
- **Payment integration** – strategy pattern with Credit Card and PayPal processors.
- **Configuration handling** – loads environment variables from a `.env` file (singleton).
- **Thread‑safe logging** – lightweight logger with timestamps.
- **Unit tests** – Catch2 based test suite.
- **Modern C++** – C++20, RAII, smart pointers, `std::optional`, and more.

## Table of Contents

- [Installation](#installation)
- [Running the Application](#running-the-application)
- [Configuration](#configuration)
- [API Overview](#api-overview)
- [Testing](#testing)
- [License](#license)

## Installation

### Prerequisites

- C++20 compatible compiler (GCC 11+, Clang 14+, MSVC 19.30+)
- CMake ≥ 3.15
- Git

### Steps