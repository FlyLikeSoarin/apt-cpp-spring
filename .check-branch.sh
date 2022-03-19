#! /bin/bash

# Check if student exists
if ! grep -Fxq "${1%%-*}" .students.txt; then
    echo "::set-output name=hw_path::error"
    echo "::set-output name=reason::Incorrect branch name: student ${1%%-*} not found is .students.txt"
    exit
fi

# Check if task exists
if ! grep -Fxq "${1##*-}" .tasks.txt; then
    echo "::set-output name=hw_path::error"
    echo "::set-output name=reason::Incorrect branch name: task ${1##*-} not found is .tasks.txt"
    exit
fi

# Check for code
if ! ls "./${1%%-*}/${1##*-}/*.cpp" 1> /dev/null 2>&1; then
    echo "::set-output name=hw_path::error"
    echo "::set-output name=reason::No code found in task directory ./${1%%-*}/${1##*-}"
    exit
fi

echo "::set-output name=hw_path::./${1%%-*}/${1##*-}"