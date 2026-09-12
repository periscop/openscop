#!/bin/sh
# Reconfigure the current build, preserving its original configure arguments.
set -eu
configure_script=$1
configure_args=$(./config.status --config)
# config.status --config emits shell-quoted arguments, including user flags.
eval "set -- $configure_args"
exec "${CONFIG_SHELL:-/bin/sh}" "$configure_script" "$@" --enable-asan
