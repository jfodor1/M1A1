cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(m1a1-superloop-combo-lock)

target_sources(app PRIVATE src/main.c)
