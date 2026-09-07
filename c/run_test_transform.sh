#!/bin/bash
# test_transform には「正しい」accept/reject は定義されていない
# (巨大な数値、重複キー、不正なコードポイント等、実装依存の挙動を観察するためのディレクトリ)
# そのためここでは「クラッシュしないこと」だけを合否判定に使い、
# 各ファイルに対する実際の挙動 (accept/reject, generate結果とのラウンドトリップ) は
# 参考情報としてログ出力するだけに留める。
TEST_RUNNER="./rosetta_json"
GEN_RUNNER="./rosetta_json_generate"
SUITE_DIR="../JSONTestSuite/test_transform"

GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
CYAN="\033[36m"
RESET="\033[0m"

if [ ! -x "$TEST_RUNNER" ] || [ ! -x "$GEN_RUNNER" ]; then
	echo -e "${RED}Error: Test runner(s) not found or not executable.${RESET}"
	echo "Please build your test runners first (make test-transform builds them for you)."
	exit 1
fi

if [ ! -d "$SUITE_DIR" ]; then
	echo -e "${RED}Error: Test suite directory '$SUITE_DIR' not found.${RESET}"
	echo "Please clone JSONTestSuite first."
	exit 1
fi

total=0
ok=0
crashes=0

echo "=== Running JSONTestSuite test_transform (behavior report, no pass/fail) ==="
echo "Suite directory: $SUITE_DIR"
echo "---------------------------------------------------------"

for file in "$SUITE_DIR"/*.json; do
    [ -e "$file" ] || continue

    filename=$(basename "$file")

    output=$($TEST_RUNNER "$file" 2>&1)
    exit_code=$?

    ((total++))

    if [ $exit_code -gt 1 ]; then
        echo -e "${RED}[CRASH]${RESET} $filename (parse exit code: $exit_code)"
        echo "$output" | sed 's/^/    /'
        ((crashes++))
        continue
    fi

    if [ $exit_code -eq 0 ]; then
        gen_output=$($GEN_RUNNER "$file" 2>&1)
        gen_exit=$?
        if [ $gen_exit -gt 1 ]; then
            echo -e "${RED}[CRASH]${RESET} $filename (generate exit code: $gen_exit)"
            echo "$gen_output" | sed 's/^/    /'
            ((crashes++))
            continue
        elif [ $gen_exit -eq 0 ]; then
            echo -e "${CYAN}[ACCEPT]${RESET} $filename (round-trip: OK)"
        else
            echo -e "${CYAN}[ACCEPT]${RESET} $filename (round-trip: DIFF)"
        fi
    else
        echo -e "${CYAN}[REJECT]${RESET} $filename"
    fi
    ((ok++))
done

echo "---------------------------------------------------------"
echo " Summary"
echo "---------------------------------------------------------"
echo " Total          : $total"
echo -e " No crash       : ${GREEN}$ok${RESET}"
echo -e " Crashes/ASan   : ${YELLOW}$crashes${RESET}"
echo "---------------------------------------------------------"
echo "Note: ACCEPT/REJECT and round-trip results above are observations,"
echo "not pass/fail judgments (test_transform has no defined correct answer)."

if [ $crashes -eq 0 ]; then
    echo -e "${GREEN}NO CRASHES.${RESET}"
    exit 0
else
    echo -e "${RED}SOME FILES CAUSED A CRASH.${RESET}"
    exit 1
fi
