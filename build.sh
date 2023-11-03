#!/usr/bin/env zsh

# Build docs
/opt/homebrew/bin/doxygen Doxyfile
open extras/html/index.html
