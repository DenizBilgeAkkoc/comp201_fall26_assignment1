/**
 * COMP 201 - Fall 2026
 * Assignment 1 - Strings in C: Shannon's Word Predictor
 *
 * This file contains the main function for the word predictor program.
 * The main function parses command-line arguments and calls the functions
 * to be implemented by the students. Do NOT modify main() or the function
 * signatures. You may add as many helper functions as you like.
 *
 * Build:  gcc -std=c99 main.c -o ngram -lm   (or simply: make)
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Test inputs fit these limits. You may increase them or add more.
 * max_words is at most MAX_SENT_WORDS; sentences.txt has at most
 * MAX_SENTENCES lines. Line lengths include the newline and exclude the
 * terminating null character, so they are at most MAX_LINE_LEN - 1. */
#define MAX_LINE_LEN 8192
#define MAX_WORD_LEN 32
#define MAX_SENT_WORDS 256
#define MAX_VOCAB 4096
#define MAX_BIGRAMS 16384
#define MAX_SENTENCES 1024

#define START_TOKEN "<s>"
#define END_TOKEN "</s>"

/* ------------------------------------------------------------------------ */
/* Count tables and provided loaders                                        */
/*                                                                          */
/* Keep the fixed-size parallel-array representation. The loaders below     */
/* are provided; implement the five tasks yourself.                        */
/* You may add your own helper functions.                                  */
/* ------------------------------------------------------------------------ */

/* Unigram table: the token vocab[i] occurs vocab_count[i] times. */
char vocab[MAX_VOCAB][MAX_WORD_LEN];
int vocab_count[MAX_VOCAB];
int num_vocab = 0;

/* Bigram table: the pair "bigram_w1[i] bigram_w2[i]" occurs bigram_count[i]
 * times. The three arrays are parallel: index i describes one pair. */
char bigram_w1[MAX_BIGRAMS][MAX_WORD_LEN];
char bigram_w2[MAX_BIGRAMS][MAX_WORD_LEN];
int bigram_count[MAX_BIGRAMS];
int num_bigrams = 0;

/* You may write your own helper functions to split strings, search the
 * tables, compare or swap entries for sorting, and share prediction logic
 * between tasks. */

/*
 * Read a unigram table (one "TOKEN COUNT" line per entry, as written by
 * Task 2) into vocab and vocab_count. Returns 0 on success and 1 if the
 * file cannot be opened. The scan width is MAX_WORD_LEN - 1, leaving
 * room for the terminating null character in each word buffer.
 */
int load_unigrams(const char *path) {
  FILE *f = fopen(path, "r");
  if (f == NULL) return 1;
  char line[MAX_LINE_LEN], word[MAX_WORD_LEN];
  char format[64];
  snprintf(format, sizeof format, "%%%ds %%d", MAX_WORD_LEN - 1);
  int count;
  num_vocab = 0;
  while (fgets(line, sizeof line, f) != NULL && num_vocab < MAX_VOCAB) {
    if (sscanf(line, format, word, &count) == 2) {
      strcpy(vocab[num_vocab], word);
      vocab_count[num_vocab] = count;
      num_vocab++;
    }
  }
  fclose(f);
  return 0;
}

/* Same for a bigram table with "W1 W2 COUNT" lines. */
int load_bigrams(const char *path) {
  FILE *f = fopen(path, "r");
  if (f == NULL) return 1;
  char line[MAX_LINE_LEN], w1[MAX_WORD_LEN], w2[MAX_WORD_LEN];
  char format[64];
  snprintf(format, sizeof format, "%%%ds %%%ds %%d",
           MAX_WORD_LEN - 1, MAX_WORD_LEN - 1);
  int count;
  num_bigrams = 0;
  while (fgets(line, sizeof line, f) != NULL && num_bigrams < MAX_BIGRAMS) {
    if (sscanf(line, format, w1, w2, &count) == 3) {
      strcpy(bigram_w1[num_bigrams], w1);
      strcpy(bigram_w2[num_bigrams], w2);
      bigram_count[num_bigrams] = count;
      num_bigrams++;
    }
  }
  fclose(f);
  return 0;
}

/**
 * Task 1: Normalization
 *
 * Turn raw text into one sentence per line of the form
 *   <s> word word ... word </s>
 * Letters are lowercased, apostrophes are deleted, '.', '!' and '?' end a
 * sentence, and every other character acts as a space.
 *
 * @param in_path: path to the raw text file
 * @param out_path: path to write the normalized sentences
 * @return 0 on success, non-zero on failure
 */
int normalize_file(const char *in_path, const char *out_path) {
  // TEMP: echo arguments to verify wiring. Delete this block after testing.
  printf("[normalize] in=\"%s\" out=\"%s\"\n", in_path, out_path);
  // TODO: Implement according to description.
  return 0;
}

/**
 * Task 2: Counting Unigrams and Bigrams
 *
 * Count every token and every pair of consecutive tokens in the normalized
 * corpus. Write "TOKEN COUNT" and "W1 W2 COUNT" lines sorted by count
 * descending, then ASCII order.
 *
 * @param normalized_path: path to the normalized corpus
 * @param unigrams_path: path to write the unigram table
 * @param bigrams_path: path to write the bigram table
 * @return 0 on success, non-zero on failure
 */
int count_ngrams(const char *normalized_path, const char *unigrams_path,
                 const char *bigrams_path) {
  // TEMP: echo arguments to verify wiring. Delete this block after testing.
  printf("[count] normalized=\"%s\" unigrams=\"%s\" bigrams=\"%s\"\n",
         normalized_path, unigrams_path, bigrams_path);
  // TODO: Implement according to description.
  return 0;
}

/**
 * Task 3: Next-Word Prediction
 *
 * For each context line, predict the most frequent successor of the last
 * word (ASCII tie-break). A trailing token ending in '*' is a prefix the
 * predicted word must start with. Write "CONTEXT -> WORD" or
 * "CONTEXT -> <none>".
 *
 * @param bigrams_path: path to the bigram table
 * @param contexts_path: path to the partial sentences
 * @param output_path: path to write the predictions
 * @return 0 on success, non-zero on failure
 */
int predict_next(const char *bigrams_path, const char *contexts_path,
                 const char *output_path) {
  // TEMP: echo arguments to verify wiring. Delete this block after testing.
  printf("[predict] bigrams=\"%s\" contexts=\"%s\" output=\"%s\"\n",
         bigrams_path, contexts_path, output_path);
  // TODO: Implement according to description.
  return 0;
}

/**
 * Task 4: Text Generation
 *
 * For each seed, repeatedly predict the next word until </s>, <none> or
 * max_words words have been produced. Write one sentence per seed.
 *
 * @param bigrams_path: path to the bigram table
 * @param seeds_path: path to the seed words (one per line)
 * @param max_words: maximum number of words in a generated sentence
 * @param output_path: path to write the generated sentences
 * @return 0 on success, non-zero on failure
 */
int generate_text(const char *bigrams_path, const char *seeds_path,
                  int max_words, const char *output_path) {
  // TEMP: echo arguments to verify wiring. Delete this block after testing.
  printf("[generate] bigrams=\"%s\" seeds=\"%s\" max_words=%d output=\"%s\"\n",
         bigrams_path, seeds_path, max_words, output_path);
  // TODO: Implement according to description.
  return 0;
}

/**
 * Task 5: Sentence Scoring
 *
 * Compute the add-one smoothed log10 probability of each candidate sentence
 * and write the results file, marking the best sentence.
 *
 * @param unigrams_path: path to the unigram table
 * @param bigrams_path: path to the bigram table
 * @param sentences_path: path to the candidate sentences
 * @param results_path: path to write the scores
 * @return 0 on success, non-zero on failure
 */
int score_sentences(const char *unigrams_path, const char *bigrams_path,
                    const char *sentences_path, const char *results_path) {
  // TEMP: echo arguments to verify wiring. Delete this block after testing.
  printf("[score] unigrams=\"%s\" bigrams=\"%s\" sentences=\"%s\" "
         "results=\"%s\"\n",
         unigrams_path, bigrams_path, sentences_path, results_path);
  // TODO: Implement according to description.
  return 0;
}

/* ------------------------------------------------------------------------ */
/* Provided main: do not modify                                             */
/* ------------------------------------------------------------------------ */

void print_usage(const char *prog_name) {
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "  %s normalize <corpus_file> <normalized_file>\n", prog_name);
  fprintf(stderr,
          "  %s count <normalized_file> <unigrams_file> <bigrams_file>\n",
          prog_name);
  fprintf(stderr,
          "  %s predict <bigrams_file> <contexts_file> <predictions_file>\n",
          prog_name);
  fprintf(stderr,
          "  %s generate <bigrams_file> <seeds_file> <max_words> "
          "<generated_file>\n",
          prog_name);
  fprintf(stderr,
          "  %s score <unigrams_file> <bigrams_file> <sentences_file> "
          "<results_file>\n",
          prog_name);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Error: No subcommand provided.\n");
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  const char *command = argv[1];

  if (strcmp(command, "normalize") == 0) {
    if (argc != 4) {
      fprintf(stderr, "Error: Invalid arguments for 'normalize'\n");
      print_usage(argv[0]);
      return EXIT_FAILURE;
    }
    return normalize_file(argv[2], argv[3]);
  }

  if (strcmp(command, "count") == 0) {
    if (argc != 5) {
      fprintf(stderr, "Error: Invalid arguments for 'count'\n");
      print_usage(argv[0]);
      return EXIT_FAILURE;
    }
    return count_ngrams(argv[2], argv[3], argv[4]);
  }

  if (strcmp(command, "predict") == 0) {
    if (argc != 5) {
      fprintf(stderr, "Error: Invalid arguments for 'predict'\n");
      print_usage(argv[0]);
      return EXIT_FAILURE;
    }
    return predict_next(argv[2], argv[3], argv[4]);
  }

  if (strcmp(command, "generate") == 0) {
    if (argc != 6) {
      fprintf(stderr, "Error: Invalid arguments for 'generate'\n");
      print_usage(argv[0]);
      return EXIT_FAILURE;
    }
    int max_words = atoi(argv[4]);
    if (max_words < 1) {
      fprintf(stderr, "Error: max_words must be at least 1\n");
      return EXIT_FAILURE;
    }
    return generate_text(argv[2], argv[3], max_words, argv[5]);
  }

  if (strcmp(command, "score") == 0) {
    if (argc != 6) {
      fprintf(stderr, "Error: Invalid arguments for 'score'\n");
      print_usage(argv[0]);
      return EXIT_FAILURE;
    }
    return score_sentences(argv[2], argv[3], argv[4], argv[5]);
  }

  fprintf(stderr, "Error: Unknown subcommand '%s'\n", command);
  print_usage(argv[0]);
  return EXIT_FAILURE;
}
