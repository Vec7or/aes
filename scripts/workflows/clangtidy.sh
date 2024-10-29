#!/usr/bin/env bash
set -e

REPO_ROOT=$(git rev-parse --show-toplevel)

# Add here all folders to be included
DIRS_TO_CHECK=("$REPO_ROOT/src" "$REPO_ROOT/include")
FILES_TO_CHECK=$(find "${DIRS_TO_CHECK[@]}" -regex '.*\.\(cpp\|inl\|hpp\|cc\|c\)')

display_help() {
  cat << EOF
Usage: ${0##*/} [OPTION]

A script to format source code files using clang-format.

Options:
  --diff, -d         Dry-run format check. Show the proposed formatting changes without applying them.
  --apply, -a        Apply formatting changes to the files.
  --help, -h         Display this help message and exit.

Examples:
  ${0##*/} --diff
  ${0##*/} --apply
EOF
}

EXIT_CODE=0

case "$1" in
    --diff|-d)
    clang-tidy --version
    # shellcheck disable=SC2086
    clang-tidy $FILES_TO_CHECK -p "$REPO_ROOT/build"
    EXIT_CODE=$?
    ;;
    --apply|-a)
    clang-format --version
    # shellcheck disable=SC2086
    clang-tidy $FILES_TO_CHECK -p "$REPO_ROOT/build" --fix
    EXIT_CODE=$?
    ;;
    *)
    display_help
    EXIT_CODE=1
    ;;
esac

exit "$EXIT_CODE"