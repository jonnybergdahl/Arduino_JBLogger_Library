#!/usr/bin/env zsh

# Check for uncommitted changes
if [ -n "$(git status --porcelain)" ]; then
  echo "There are uncommitted changes in the Git repository. Aborting."
  exit 1
fi

# Build docs
start_path=$(pwd)
/opt/homebrew/bin/doxygen Doxyfile
rm -r ~/Developer/jonnybergdahl/jonnybergdahl.github.io/docs
cp -r docs ~/Developer/jonnybergdahl/jonnybergdahl.github.io/docs

# Commit and push docs
cd ~/Developer/jonnybergdahl/jonnybergdahl.github.io
git checkout gh-pages
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
cd "$start_path"
