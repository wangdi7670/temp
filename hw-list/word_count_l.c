/*
 * Implementation of the word_count interface using Pintos lists.
 *
 * You may modify this file, and are expected to modify it.
 */

/*
 * Copyright © 2021 University of California, Berkeley
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PINTOS_LIST
#error "PINTOS_LIST must be #define'd when compiling word_count_l.c"
#endif

#include "word_count.h"
#include "debug.h"

void init_words(word_count_list_t* wclist) { /* TODO */
  ASSERT(wclist != NULL);

  list_init(wclist);
}

size_t len_words(word_count_list_t* wclist) {
  /* TODO */
  ASSERT(wclist != NULL);

  size_t len = 0; 
  struct list_elem *e;
  for (e = list_begin(wclist); e != list_end(wclist); e = list_next(e)) {
    word_count_t *wc = list_entry(e, word_count_t, elem);
    len += wc->count;
  }

  return len;
}

word_count_t* find_word(word_count_list_t* wclist, char* word) {
  /* TODO */
  ASSERT(wclist != NULL);

  word_count_t *wc = NULL;
  struct list_elem *e;

  for (e = list_begin(wclist); e != list_end(wclist); e = list_next(e)) {
    wc = list_entry(e, word_count_t, elem);

    if (wc->word && strcmp(wc->word, word) == 0) {
      return wc;
    }
  }

  return NULL;
}

word_count_t* add_word(word_count_list_t* wclist, char* word) {
  /* TODO */
  ASSERT(wclist != NULL);

  word_count_t *wc;
  if ((wc = find_word(wclist, word)) != NULL) {
    wc->count += 1;
  } else {
    struct list_elem *e = malloc(sizeof(struct list_elem));
    wc = list_entry(e, word_count_t, elem);

    wc->word = (char *) malloc(strlen(word) + 1);
    ASSERT(wc->word != NULL);
    strcpy(wc->word, word);

    wc->count = 1;

    struct list_elem *tail = &wclist->tail;
    list_insert(tail, e);
  }
  return wc;
}

void fprint_words(word_count_list_t* wclist, FILE* outfile) { /* TODO */
  ASSERT(wclist != NULL);
  ASSERT(outfile != NULL);

  struct list_elem *e;
  for (e = list_begin(wclist); e != list_end(wclist); e = list_next(e)) {
    word_count_t *wc = list_entry(e, word_count_t, elem);
    fprintf(outfile, "%i\t%s\n", wc->count, wc->word);
  }
}

static bool less_list(const struct list_elem* ewc1, const struct list_elem* ewc2, void* aux) {
  /* TODO */
  return false;
}

void wordcount_sort(word_count_list_t* wclist,
                    bool less(const word_count_t*, const word_count_t*)) {
  list_sort(wclist, less_list, less);
}
