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

echo "::set-output name=hw_path::./${1%%-*}/${1##*-}"