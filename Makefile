# COMP 201 - Fall 2026 - Assignment 1
# Strings in C: Shannon's Word Predictor
#
#   make              build ./ngram from main.c
#   make test         run every task on all three test sets
#   make test_easy    run one test set (also test_medium, test_hard)
#   make clean        remove the binary and the student_output folders
#
# Each check runs one task on the provided correct input, compares the
# output file with expected_output/ byte by byte, and prints a diff on
# failure.  Your outputs are kept in test_<set>/student_output/.

CC      = gcc
CFLAGS  = -std=c99
LDLIBS  = -lm
MAIN    = main.c
BIN     = ngram

# Longest diff shown for one failed check.
DIFF_LINES = 30

# Use a 30 second limit per run where `timeout` exists (Linux). On macOS it
# is simply absent and the program runs without a limit.
TIMEOUT := $(shell command -v timeout >/dev/null 2>&1 && echo "timeout 30")

TEST_SETS = easy medium hard
TEST_TARGETS = $(addprefix test_,$(TEST_SETS))

.PHONY: all test $(TEST_TARGETS) clean

all: $(BIN)

$(BIN): $(MAIN)
	$(CC) $(CFLAGS) $(MAIN) -o $(BIN) $(LDLIBS)

test: $(TEST_TARGETS)

$(TEST_TARGETS): $(BIN)
	$(call RUN_SET,$(patsubst test_%,%,$@))

clean:
	rm -rf $(BIN) $(BIN).dSYM $(addsuffix /student_output,$(TEST_TARGETS))

# ---------------------------------------------------------------------------
# RUN_SET <name>: one shell invocation that runs the five tasks of test_<name>.
#   run   LABEL SUBCOMMAND ARGS...   runs ./ngram and reports a bad exit status
#   check LABEL FILE                 compares student_output/FILE with expected
# ---------------------------------------------------------------------------
define RUN_SET
@dir=test_$(1); in=$$dir/input; exp=$$dir/expected_output; out=$$dir/student_output; \
mkdir -p "$$out"; rm -f "$$out"/*; pass=0; total=0; \
echo "=== $$dir ==="; \
run() { label=$$1; shift; \
  $(TIMEOUT) ./$(BIN) "$$@" >"$$out/.stderr" 2>&1; st=$$?; \
  if [ $$st -ne 0 ]; then \
    echo "  ($$label: program exited with status $$st)"; \
    head -n 5 "$$out/.stderr" | sed 's/^/  | /'; \
  fi; rm -f "$$out/.stderr"; }; \
check() { total=$$((total+1)); \
  if [ ! -f "$$out/$$2" ]; then \
    printf '[FAIL] %-18s (%s)  no output file produced\n' "$$1" "$$2"; \
  elif cmp -s "$$exp/$$2" "$$out/$$2"; then \
    printf '[PASS] %-18s (%s)\n' "$$1" "$$2"; pass=$$((pass+1)); \
  else \
    printf '[FAIL] %-18s (%s)\n' "$$1" "$$2"; \
    echo "--- expected"; echo "+++ yours"; \
    diff -u "$$exp/$$2" "$$out/$$2" | tail -n +3 | head -n $(DIFF_LINES); \
  fi; }; \
run "Task 1" normalize "$$in/corpus.txt" "$$out/corpus_normalized.txt"; \
check "Task 1 normalize" corpus_normalized.txt; \
run "Task 2" count "$$in/corpus_normalized.txt" "$$out/unigrams.txt" "$$out/bigrams.txt"; \
check "Task 2 count" unigrams.txt; \
check "Task 2 count" bigrams.txt; \
run "Task 3" predict "$$in/bigrams.txt" "$$in/contexts.txt" "$$out/predictions.txt"; \
check "Task 3 predict" predictions.txt; \
mw=$$(cat "$$in/max_words.txt"); \
run "Task 4" generate "$$in/bigrams.txt" "$$in/seeds.txt" "$$mw" "$$out/generated.txt"; \
check "Task 4 generate" generated.txt; \
run "Task 5" score "$$in/unigrams.txt" "$$in/bigrams.txt" "$$in/sentences.txt" "$$out/results.txt"; \
check "Task 5 score" results.txt; \
echo "$$dir: $$pass/$$total checks passed"; echo
endef
