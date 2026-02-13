#!/bin/bash
#
# Edge-case test suite for vigenere_cypher
#
# How this works:
#   C doesn't have a built-in test runner like Python (pytest) or JS (jest).
#   For programs that do all their work through stdin/stdout/files, the
#   simplest approach is a shell script that:
#     1. Compiles the program
#     2. Runs it with various inputs
#     3. Checks exit codes and output for expected behavior
#
#   For larger C projects you'd use a framework like Unity, Check, or CUnit,
#   but those require extracting logic into testable functions. Since this
#   program is a single main(), shell tests are the practical choice.
#
# Usage:
#   cd vigenere_cypher
#   bash test.sh

set -e

PASS=0
FAIL=0
BINARY="./vigenere_cypher"
TMPDIR=$(mktemp -d)

# Clean up temp files on exit.
trap "rm -rf $TMPDIR" EXIT

# ---------- helpers ----------

compile() {
    echo "Compiling..."
    gcc -Wall -o "$BINARY" vigenere_cypher.c
    echo ""
}

# Run a single test case.
#   $1 = test name
#   $2 = expected exit code
#   $3... = program arguments
run_test() {
    local name="$1"
    local expected_exit="$2"
    shift 2

    # Run the program, capture output and exit code.
    local output
    output=$("$BINARY" "$@" 2>&1) && local actual_exit=0 || local actual_exit=$?

    if [ "$actual_exit" -eq "$expected_exit" ]; then
        echo "  PASS: $name"
        PASS=$((PASS + 1))
    else
        echo "  FAIL: $name"
        echo "        expected exit=$expected_exit, got exit=$actual_exit"
        echo "        output: $(echo "$output" | head -3)"
        FAIL=$((FAIL + 1))
    fi
}

# Run a test and check that stdout contains an expected string.
#   $1 = test name
#   $2 = expected substring in output
#   $3... = program arguments
run_test_grep() {
    local name="$1"
    local expected_str="$2"
    shift 2

    local output
    output=$("$BINARY" "$@" 2>&1) && true

    if echo "$output" | grep -q "$expected_str"; then
        echo "  PASS: $name"
        PASS=$((PASS + 1))
    else
        echo "  FAIL: $name"
        echo "        expected output to contain: $expected_str"
        echo "        output: $(echo "$output" | head -5)"
        FAIL=$((FAIL + 1))
    fi
}

# ---------- compile ----------

compile

# ---------- argument validation ----------

echo "=== Argument Validation ==="

run_test "No arguments" 1

run_test "Only one argument" 1 \
    "$TMPDIR/dummy.txt"

run_test "Only two arguments" 1 \
    "$TMPDIR/dummy.txt" "key"

run_test_grep "Usage message shown" "Usage:" \

# ---------- file handling ----------

echo ""
echo "=== File Handling ==="

run_test "Non-existent file" 1 \
    "$TMPDIR/nonexistent.txt" "key" "vec"

run_test_grep "File error message" "Error:" \
    "$TMPDIR/nonexistent.txt" "key" "vec"

# ---------- empty / minimal input ----------

echo ""
echo "=== Edge Case Inputs ==="

# Empty file -- the message will be empty, msgLen=0.
touch "$TMPDIR/empty.txt"
run_test_grep "Empty file produces output" "Original Message Length = 0" \
    "$TMPDIR/empty.txt" "key" "vec"

# Single character message.
echo -n "A" > "$TMPDIR/single.txt"
run_test_grep "Single character message" "Clean Message Length = 1" \
    "$TMPDIR/single.txt" "key" "vec"

# Message with only symbols/numbers -- all characters stripped.
echo '123!@#$%^&*()' > "$TMPDIR/symbols.txt"
run_test_grep "Symbols-only message, all stripped" "Clean Message Length = 0" \
    "$TMPDIR/symbols.txt" "key" "vec"

# Message with mixed content -- only letters survive.
# H3ll0 W0rld!!! -> H,l,l,W,r,l,d = 7 letters kept.
echo 'H3ll0 W0rld!!!' > "$TMPDIR/mixed.txt"
run_test_grep "Mixed content keeps only letters" "Clean Message Length = 7" \
    "$TMPDIR/mixed.txt" "key" "vec"

# ---------- padding edge cases ----------

echo ""
echo "=== Padding Edge Cases ==="

# Message length exactly equals keyword length (no padding needed in theory,
# but the current implementation adds a full block of padding).
echo -n "abcde" > "$TMPDIR/exact.txt"
run_test_grep "Message length == keyword length, pad = keyword length" \
    "Number of characters to be padded = 5" \
    "$TMPDIR/exact.txt" "abcde" "abcde"

# Message shorter than keyword.
echo -n "hi" > "$TMPDIR/short.txt"
run_test_grep "Message shorter than keyword" "Number of characters to be padded = 5" \
    "$TMPDIR/short.txt" "keyword" "keyword"

# Message length is a multiple of keyword length (3 * 2 = 6).
echo -n "abcdef" > "$TMPDIR/multiple.txt"
run_test_grep "Message multiple of keyword length" \
    "Number of characters to be padded = 2" \
    "$TMPDIR/multiple.txt" "ab" "ab"

# ---------- encryption produces output ----------

echo ""
echo "=== Encryption Output ==="

echo -n "hello" > "$TMPDIR/hello.txt"
run_test_grep "Encryption produces ciphertext section" \
    "Encrypted Vigenere Cypher:" \
    "$TMPDIR/hello.txt" "key" "vec"

# Same plaintext + key + IV should produce the same ciphertext (deterministic).
out1=$("$BINARY" "$TMPDIR/hello.txt" "key" "vec" | grep -A2 "Encrypted Vigenere Cypher:")
out2=$("$BINARY" "$TMPDIR/hello.txt" "key" "vec" | grep -A2 "Encrypted Vigenere Cypher:")
if [ "$out1" = "$out2" ]; then
    echo "  PASS: Same input produces same ciphertext (deterministic)"
    PASS=$((PASS + 1))
else
    echo "  FAIL: Same input produces same ciphertext (deterministic)"
    FAIL=$((FAIL + 1))
fi

# Different IVs should produce different ciphertext (CBC property).
outA=$("$BINARY" "$TMPDIR/hello.txt" "key" "aaa" | grep -A2 "Encrypted Vigenere Cypher:")
outB=$("$BINARY" "$TMPDIR/hello.txt" "key" "bbb" | grep -A2 "Encrypted Vigenere Cypher:")
if [ "$outA" != "$outB" ]; then
    echo "  PASS: Different IVs produce different ciphertext"
    PASS=$((PASS + 1))
else
    echo "  FAIL: Different IVs produce different ciphertext"
    FAIL=$((FAIL + 1))
fi

# Different keywords should produce different ciphertext.
outC=$("$BINARY" "$TMPDIR/hello.txt" "abc" "vec" | grep -A2 "Encrypted Vigenere Cypher:")
outD=$("$BINARY" "$TMPDIR/hello.txt" "xyz" "vec" | grep -A2 "Encrypted Vigenere Cypher:")
if [ "$outC" != "$outD" ]; then
    echo "  PASS: Different keywords produce different ciphertext"
    PASS=$((PASS + 1))
else
    echo "  FAIL: Different keywords produce different ciphertext"
    FAIL=$((FAIL + 1))
fi

# ---------- case handling ----------

echo ""
echo "=== Case Handling ==="

# Uppercase and lowercase input should produce the same ciphertext
# (both get lowercased before encryption).
echo -n "HELLO" > "$TMPDIR/upper.txt"
echo -n "hello" > "$TMPDIR/lower.txt"
outUpper=$("$BINARY" "$TMPDIR/upper.txt" "key" "vec" | grep -A2 "Encrypted Vigenere Cypher:")
outLower=$("$BINARY" "$TMPDIR/lower.txt" "key" "vec" | grep -A2 "Encrypted Vigenere Cypher:")
if [ "$outUpper" = "$outLower" ]; then
    echo "  PASS: Upper and lowercase input produce same ciphertext"
    PASS=$((PASS + 1))
else
    echo "  FAIL: Upper and lowercase input produce same ciphertext"
    FAIL=$((FAIL + 1))
fi

# ---------- original test file ----------

echo ""
echo "=== Original Test File ==="

run_test "message.txt with keyword/vect runs successfully" 0 \
    "message.txt" "keyword" "vect"

# ---------- summary ----------

echo ""
echo "================================"
echo "  Results: $PASS passed, $FAIL failed"
echo "================================"

# Clean up the binary.
rm -f "$BINARY"

# Exit with failure if any test failed.
[ "$FAIL" -eq 0 ]
