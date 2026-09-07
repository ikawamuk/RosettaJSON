#!/bin/bash
TEST_RUNNER="${TEST_RUNNER:-./build/rosetta_json_generate}"
SUITE_DIR="../JSONTestSuite/test_parsing"

GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
RESET="\033[0m"

# 実行ファイルとテストディレクトリの存在確認
if [ ! -x "$TEST_RUNNER" ]; then
	echo -e "${RED}Error: Test runner '$TEST_RUNNER' not found or not executable.${RESET}"
	echo "Please build your test runner first."
	exit 1
fi

if [ ! -d "$SUITE_DIR" ]; then
	echo -e "${RED}Error: Test suite directory '$SUITE_DIR' not found.${RESET}"
	echo "Please clone JSONTestSuite first."
	exit 1
fi

passed=0
failed=0
crashes=0
total=0

echo "=== Running generate round-trip tests (parse -> generate -> parse) ==="
echo "Suite directory: $SUITE_DIR (y_*.json only)"
echo "---------------------------------------------------------"

for file in "$SUITE_DIR"/y_*.json; do
    [ -e "$file" ] || continue

    filename=$(basename "$file")

    output=$($TEST_RUNNER "$file" 2>&1)
    exit_code=$?

    ((total++))

    if [ $exit_code -gt 1 ]; then
        echo -e "${RED}[CRASH/ERROR]${RESET} $filename (exit code: $exit_code)"
        echo "$output" | sed 's/^/    /'
        ((crashes++))
        ((failed++))
        continue
    fi

    if [ $exit_code -eq 0 ]; then
        ((passed++))
    else
        echo -e "${RED}[FAIL]${RESET} Round-trip mismatch: $filename"
        ((failed++))
    fi
done

echo "---------------------------------------------------------"
echo " Summary"
echo "---------------------------------------------------------"
echo " Total       : $total"
echo -e " Passed      : ${GREEN}$passed${RESET}"
echo -e " Failed      : ${RED}$failed${RESET}"
echo -e " Crashes/ASan: ${YELLOW}$crashes${RESET}"
echo "---------------------------------------------------------"

if [ $failed -eq 0 ]; then
    echo -e "${GREEN}ALL TESTS PASSED!${RESET}"
    exit 0
else
    echo -e "${RED}SOME TESTS FAILED.${RESET}"
    exit 1
fi
