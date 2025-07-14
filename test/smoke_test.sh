#!/bin/bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
CMD=${SCRIPT_DIR}/../minishell/minishell
if [ ! -f "$CMD" ]; then
    echo "Minishell executable not found at $CMD"
    exit 1
fi

PROMPT=$(echo -e "exit\n" | $CMD)


run_command () {
    echo -e "$1\nexit\n" | $CMD | sed "s/^$PROMPT//g" | sed "s/ $//g"
}

# Run the minishell command with a simple command

echo "Running smoke test for minishell..."
OUTPUT=$(run_command "echo Hello, World!")

if [ "$OUTPUT" == "Hello, World!" ]; then
    echo "Smoke test passed: Output is as expected."
else
    echo "Smoke test failed: Unexpected output."
    echo "Output was: $OUTPUT"
    exit 1
fi

OUTPUT=$(run_command "ls -l")
OUTPUT_ORIG=$(ls -l)
if [ "$OUTPUT" == "$OUTPUT_ORIG" ]; then
    echo "Smoke test passed: 'ls -l' command executed successfully."
else
    echo "Smoke test failed: 'ls -l' command did not execute as expected."
    echo "Output was: $OUTPUT"
    exit 1
fi

OUTPUT=$(run_command "pwd")
OUTPUT_ORIG=$(pwd)
if [ "$OUTPUT" == "$OUTPUT_ORIG" ]; then
    echo "Smoke test passed: 'pwd' command executed successfully."
else
    echo "Smoke test failed: 'pwd' command did not execute as expected."
    echo "Output was: $OUTPUT"
    exit 1
fi

OUTPUT=$(run_command "echo \$PATH")
OUTPUT_ORIG=$(echo $PATH)
if [ "$OUTPUT" == "$OUTPUT_ORIG" ]; then
    echo "Smoke test passed: 'echo \$PATH' command executed successfully."
else
    echo "Smoke test failed: 'echo \$PATH' command did not execute as expected."
    echo "Output was: $OUTPUT"
    exit 1
fi