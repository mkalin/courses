#include <stdio.h>

#define SetCount (4)
#define WordCount (4)
#define Empty (-1)
#define True (1)
#define False (0)

int sets[SetCount][WordCount];

int lru[SetCount];

int already_in_p(int word, int set_index) {
  int w = 0;

  while (w < WordCount) 
    if (word == sets[set_index][w]) return True;
    else w++;

  return False;
}

int main() {
  int reference_string[ ] = 
    { 1, 4, 8, 5, 20, 17, 19, 56, 9, 11, 4, 43, 5, 6, 9, 17, 9, 56, 9, Empty };

  int i, j;
  /* Initialize the cache to empty. */
  for (i = 0; i < SetCount; i++) 
    for (j = 0; j < WordCount; j++)
      sets[i][j] = -1;

  /* Initialize the LRU pointers to -1 */
  for (i = 0; i < SetCount; i++)
    lru[i] = -1;

  /* Iterate through the reference string. */
  i = 0;
  while (reference_string[i] != Empty) {
    int next_word = reference_string[i];
    int set_index = next_word % SetCount;

    if (already_in_p(next_word, set_index))
      printf("Hit for word %i in Set %i\n", next_word, set_index);
    else {
      printf("Miss for word %i in Set %i\n", next_word, set_index);

      lru[set_index] = (lru[set_index] + 1) % SetCount;

      sets[set_index][lru[set_index]] = next_word;

      printf("Word %i inserted into Set %i at position %i\n",
	     next_word, set_index, lru[set_index]);
    }
    i++;
  }

  return 0;
}
/*
  Miss for word 1 in Set 1
  Word 1 inserted into Set 1 at position 0

  Miss for word 4 in Set 0
  Word 4 inserted into Set 0 at position 0

  Miss for word 8 in Set 0
  Word 8 inserted into Set 0 at position 1

  Miss for word 5 in Set 1
  Word 5 inserted into Set 1 at position 1

  Miss for word 20 in Set 0
  Word 20 inserted into Set 0 at position 2

  Miss for word 17 in Set 1
  Word 17 inserted into Set 1 at position 2

  Miss for word 19 in Set 3
  Word 19 inserted into Set 3 at position 0

  Miss for word 56 in Set 0
  Word 56 inserted into Set 0 at position 3

  Miss for word 9 in Set 1
  Word 9 inserted into Set 1 at position 3

  Miss for word 11 in Set 3
  Word 11 inserted into Set 3 at position 1

  Hit for word 4 in Set 0

  Miss for word 43 in Set 3
  Word 43 inserted into Set 3 at position 2

  Hit for word 5 in Set 1

  Miss for word 6 in Set 2
  Word 6 inserted into Set 2 at position 0

  Hit for word 9 in Set 1
  Hit for word 17 in Set 1
  Hit for word 9 in Set 1
  Hit for word 56 in Set 0
  Hit for word 9 in Set 1
*/
