# COMP 201 – Fall 2026 – Assignment 1: Shannon's Word Predictor

## Repository Contents

- **`main.c`** — The code file you will implement. Contains the provided `main` function, fixed-size parallel count arrays, implemented table loaders, and stubs for all five tasks. You may design your own helper functions.
- **`test_easy/`**, **`test_medium/`**, **`test_hard/`** — Three test cases of increasing difficulty. Each contains:
  - `input/` — Input files to feed into your program
  - `expected_output/` — Ground truth outputs to compare against
- **`Makefile`** — Builds your program and checks it against the test cases.

Use C strings and fixed-size arrays; dynamic allocation and variable-length arrays are not allowed. Test inputs fit the provided limits. Generation uses `1 <= max_words <= MAX_SENT_WORDS` (256); scoring has at most `MAX_SENTENCES` (1024) candidates. Input and generated lines, including their newline when present, fit in `MAX_LINE_LEN - 1` characters, leaving room for the terminating null character.

## Building

```bash
make            # same as: gcc -std=c99 main.c -o ngram -lm
```

`-std=c99` is required on linuxpool and `-lm` links the math library for `log10`.

The medium and hard stories include tabs, repeated punctuation, unterminated final sentences, ASCII ties, and exact/prefix queries. Medium uses `max_words=1`; hard uses the complete cleaned Alice book plus the Shannon story and edge-case messages, including a 31-character word and longer generation.

## Testing

`make test` runs every task on every test case with the correct input files and compares your output files byte by byte with `expected_output/`. On a mismatch it prints a diff (`---` is the expected file, `+++` is yours). Your output files are kept in `test_<set>/student_output/`.

```bash
make test           # all three test cases
make test_easy      # one test case (also test_medium, test_hard)
make clean          # remove the binary and the student_output folders
```

Grading uses the same checks on linuxpool, so make sure `make test` passes there before you submit.
