// lab7.c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 100

typedef struct {
  int line_number;
  int value;
} Input;

typedef struct {
  int line_number;
  int doubled_value;
} IntermediateInput;

typedef struct {
  int doubled_value;           // the "group key"
  int line_numbers[MAX_INPUT]; // all line numbers that mapped to this doubled
                               // value
  int count;                   // how many line numbers stored
} Output;

void map(Input *input, IntermediateInput *intermediate_input);
void groupByKey(IntermediateInput *input, Output *output, int *result_count);
void reduce(Output *output);

int main(void) {
  Input input_data[MAX_INPUT];
  int input_size = 0;

  printf("Enter values (one per line). Type 'end' to finish:\n");

  // Read until "end" or MAX_INPUT reached
  while (input_size < MAX_INPUT) {
    char buffer[100];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
      break; // EOF
    }

    // trim trailing newline for a clean compare
    buffer[strcspn(buffer, "\r\n")] = '\0';

    if (strcmp(buffer, "end") == 0) {
      break;
    }

    // try parse integer
    int value;
    if (sscanf(buffer, "%d", &value) == 1) {
      input_data[input_size].line_number = input_size + 1; // 1-based
      input_data[input_size].value = value;
      input_size++;
    } else {
      printf("Invalid input. Please enter an integer or 'end' to finish.\n");
    }
  }

  // Step 1: Map
  IntermediateInput mapped_results[MAX_INPUT] = {0};
  for (int i = 0; i < input_size; i++) {
    map(&input_data[i], &mapped_results[i]);
  }

  // Step 2: Group
  Output output_results[MAX_INPUT] = {0};
  int result_count = 0;
  for (int i = 0; i < input_size; i++) {
    groupByKey(&mapped_results[i], output_results, &result_count);
  }

  // Step 3: Reduce (print)
  for (int i = 0; i < result_count; i++) {
    if (output_results[i].count > 0) {
      reduce(&output_results[i]);
    }
  }

  return 0;
}

void map(Input *input, IntermediateInput *intermediate_input) {
  // Double the value and preserve the line number (key)
  intermediate_input->line_number = input->line_number;
  intermediate_input->doubled_value = input->value * 2;
}

void groupByKey(IntermediateInput *input, Output *output, int *result_count) {
  // Search for an existing group with the same doubled_value
  for (int i = 0; i < *result_count; i++) {
    if (output[i].doubled_value == input->doubled_value) {
      // Append this line number to the existing group's list
      if (output[i].count < MAX_INPUT) {
        output[i].line_numbers[output[i].count++] = input->line_number;
      } else {
        // Defensive: avoid overflow in degenerate cases
        fprintf(stderr, "Warning: line_numbers overflow ignored for value %d\n",
                input->doubled_value);
      }
      return;
    }
  }

  // Not found: create a new group at output[*result_count]
  assert(*result_count < MAX_INPUT); // optional safety check
  Output *slot = &output[*result_count];
  slot->doubled_value = input->doubled_value;
  slot->count = 0;
  slot->line_numbers[slot->count++] = input->line_number;
  (*result_count)++;
}

void reduce(Output *output) {
  // Print in the format: (value, [l1, l2, l3])
  printf("(%d, [", output->doubled_value);
  for (int i = 0; i < output->count; i++) {
    if (i > 0)
      printf(", ");
    printf("%d", output->line_numbers[i]);
  }
  printf("])\n");
}
