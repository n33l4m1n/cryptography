# Cryptography

Implementations of classical cipher algorithms in C.

## Vigenere Cipher with Cipher Block Chaining (CBC)

### Overview

This program encrypts a plaintext message using the Vigenere cipher combined
with Cipher Block Chaining (CBC) mode, a technique borrowed from modern
block cipher design.

The program reads a message from a file, strips all non-alphabetic characters,
pads it to a multiple of the block size (determined by the keyword length),
and produces an encrypted ciphertext. Each block of plaintext is first combined
(mod 26 addition) with the previous ciphertext block (or the initialization
vector for the first block), then encrypted with the repeating Vigenere key.

### Usage

```
gcc -Wall -o vigenere_cypher vigenere_cypher/vigenere_cypher.c
./vigenere_cypher message.txt keyword vect
```

Arguments:
- `message.txt` -- path to the plaintext file
- `keyword` -- the Vigenere key (also determines the block size)
- `vect` -- the initialization vector (IV) for CBC mode

### Historical Context

The Vigenere cipher dates to the 16th century and is attributed to Blaise de
Vigenere, though Giovan Battista Bellaso described the core mechanism earlier
in 1553. It extends the simple Caesar (shift) cipher by using a repeating
keyword to vary the shift at each position, producing a polyalphabetic
substitution. For nearly 300 years it was considered unbreakable and earned the
nickname "le chiffre indechiffrable." Friedrich Kasiski published a general
method of cryptanalysis for it in 1863, and Charles Babbage had independently
discovered a similar attack even earlier.

Cipher Block Chaining (CBC) is a mode of operation introduced by Ehrsam,
Meyer, Smith, and Tuchman in 1976 for use with modern block ciphers like DES.
In CBC mode, each plaintext block is XOR'd with the previous ciphertext block
before encryption, which means identical plaintext blocks produce different
ciphertext -- eliminating the pattern-leaking weakness of encrypting blocks
independently (ECB mode). An initialization vector (IV) provides the "previous
block" for the first plaintext block.

Combining the Vigenere cipher with CBC mode is a pedagogical exercise that
demonstrates how chaining works. The Vigenere cipher itself is not
cryptographically secure by modern standards -- it is vulnerable to Kasiski
examination and frequency analysis -- but layering CBC on top illustrates the
principle of diffusion: a change in one plaintext block propagates through all
subsequent ciphertext blocks.

### Tests

Run the test suite with:

```
cd vigenere_cypher
bash test.sh
```

| Category | What's tested |
|---|---|
| Argument Validation | 0, 1, 2 args all exit with code 1 and print usage |
| File Handling | Non-existent file exits with code 1 and prints an error |
| Edge Case Inputs | Empty file, single character, symbols-only (all stripped), mixed alphanumeric |
| Padding Edge Cases | Message == keyword length, message shorter than keyword, message that's an exact multiple |
| Encryption Output | Ciphertext present, deterministic output, different IVs/keywords produce different ciphertext |
| Case Handling | HELLO and hello encrypt to the same ciphertext |
| Integration | Original `message.txt` with `keyword`/`vect` runs to completion |

Since C doesn't have a built-in test framework like Python or JavaScript, and
this program's logic lives entirely in `main()`, the tests are written as a
shell script that compiles the program, creates temp files with edge-case
content, runs the binary, and checks exit codes and output for expected values.