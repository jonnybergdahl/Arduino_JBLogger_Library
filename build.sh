#!/usr/bin/env zsh

# Build docs
/opt/homebrew/bin/doxygen Doxyfile
open docs/index.html
