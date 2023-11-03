#!/usr/bin/env zsh

# Check for uncommitted changes
if [ -n "$(git status --porcelain)" ]; then
  echo "There are uncommitted changes in the Git repository. Aborting."
  exit 1
fi

# Build docs
git checkout gh-pages
/opt/homebrew/bin/doxygen Doxyfile
git add docs
if [ -n "$(git status --porcelain)" ]; then
  echo "Branch gh-pages is up to date,nothing to do."
  exit 1
fi
if [ -n "$(git status --porcelain)" ]; then
   echo "Branch gh-pages is up to date,nothing to do."
else
  git commit -m "Update docs"
  git push origin gh-pages
fi
git checkout main
