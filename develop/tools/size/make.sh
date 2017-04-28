#!/bin/bash

# =============================================================================
# Description: 
#   size is a little application that shows you the size of C++ data
#   in the current platform.
# =============================================================================

# Compilation instructions for Linux / Mac OS:

  g++ ./size.cpp -Wno-write-strings -o ./size
  chmod +x ./size

# Compilation instructions for Windows:

#  g++ size.cpp -o size.exe


# 
# Notes:
# 
# https://software.intel.com/en-us/articles/size-of-long-integer-type-on-different-architecture-and-os
# 
# OS            arch                      size
# Windows       IA-32                     4 bytes
# Windows       Intel® 64 or IA-64        4 bytes
# Linux         IA-32                     4 bytes
# Linux         Intel® 64 or IA-64        8 bytes
# Mac OS X      IA-32                     4 bytes
# Mac OS X      Intel® 64 or IA-64        8 bytes 
# 
