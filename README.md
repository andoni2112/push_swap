*This activity has been created as part of the 42 curriculum by andpascu, jhansilv.*

# push_swap

## Description

`push_swap` is a 42 project focused on algorithmic complexity, sorting strategies, stack manipulation and optimization.

The goal is to sort a list of integers using two stacks, `a` and `b`, and a limited set of allowed operations while trying to minimize the number of instructions produced.

At the beginning:

- Stack `a` contains all the numbers.
- Stack `b` is empty.

At the end:

- Stack `a` must be sorted in ascending order.
- Stack `b` must be empty.

The program does not print the sorted numbers themselves. Instead, it prints the sequence of Push_swap instructions required to sort them.

The available operations are:

- `sa`: swap the first two elements of stack `a`
- `sb`: swap the first two elements of stack `b`
- `ss`: execute `sa` and `sb`
- `pa`: push the first element of stack `b` to stack `a`
- `pb`: push the first element of stack `a` to stack `b`
- `ra`: rotate stack `a`
- `rb`: rotate stack `b`
- `rr`: execute `ra` and `rb`
- `rra`: reverse rotate stack `a`
- `rrb`: reverse rotate stack `b`
- `rrr`: execute `rra` and `rrb`

This implementation provides four sorting strategies:

- Simple strategy: `O(n²)`
- Medium strategy: `O(n√n)`
- Complex strategy: `O(n log n)`
- Adaptive strategy: selects an internal strategy according to the disorder level of the input

The program also supports an optional benchmark mode.

---

## Instructions

### Compilation

Compile the project with:

```bash
make
```

This creates the executable:

```bash
./push_swap
```

Available Makefile rules:

```bash
make
make clean
make fclean
make re
```

The project is compiled using:

```text
-Wall -Wextra -Werror
```

---

## Usage

Basic example:

```bash
./push_swap 3 2 1
```

Possible output:

```text
sa
rra
```

These instructions transform:

```text
3 2 1
```

into:

```text
1 2 3
```

---

## Strategy selection

The program supports four strategy selectors.

### Simple

```bash
./push_swap --simple 5 4 3 2 1
```

### Medium

```bash
./push_swap --medium 5 4 3 2 1
```

### Complex

```bash
./push_swap --complex 5 4 3 2 1
```

### Adaptive

```bash
./push_swap --adaptive 5 4 3 2 1
```

If no strategy flag is provided, the adaptive strategy is used by default:

```bash
./push_swap 5 4 3 2 1
```

Only one sorting strategy can be explicitly selected at a time.

---

## Benchmark mode

Benchmark mode can be enabled with:

```bash
./push_swap --bench 5 4 3 2 1
```

It can also be combined with a strategy:

```bash
./push_swap --bench --simple 5 4 3 2 1
```

Sorting operations are written to standard output.

Benchmark information is written to standard error.

Example:

```text
[bench] disorder:   100.00%
[bench] strategy:   Simple / O(n^2)
[bench] total_ops:  8
```

The current benchmark reports:

- Initial disorder percentage
- Selected strategy
- Theoretical complexity class
- Total number of generated operations

---

## Project structure

```text
push_swap/
├── Makefile
├── README.md
├── includes/
│   └── push_swap.h
├── src/
│   ├── main.c
│   ├── algorithms/
│   │   ├── sort_small.c
│   │   ├── strategy_simple.c
│   │   ├── strategy_medium.c
│   │   ├── strategy_complex.c
│   │   └── strategy_adaptive.c
│   ├── operations/
│   │   ├── push.c
│   │   ├── swap.c
│   │   ├── rotate.c
│   │   └── reverse_rotate.c
│   ├── parsing/
│   │   ├── parsing.c
│   │   ├── check_errors.c
│   │   └── free_utils.c
│   └── utils/
│       ├── stack_utils.c
│       ├── indexation.c
│       ├── disorder.c
│       └── bench.c
└── Libft/
```

---

## Stack representation

The two stacks are represented using singly linked lists.

Each node contains:

```c
typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;
```

### `value`

Stores the original integer received by the program.

### `index`

Stores the normalized position of the value after indexation.

### `next`

Points to the next element of the stack.

Using linked lists makes stack operations such as push, swap and rotation easier to implement without using arrays for the actual stack structure.

---

## Indexation

Before executing the main sorting algorithms, the values are converted into indexes according to their relative order.

Example:

```text
Values:
42  -10  100  7
```

becomes:

```text
Indexes:
2    0    3    1
```

The smallest value receives index `0`.

The next smallest receives index `1`.

The process continues until the largest value receives index `n - 1`.

Indexation has several advantages:

- comparisons become simpler
- negative numbers no longer require special handling during sorting
- very large and very small integer values are normalized
- binary Radix Sort can work directly with indexes

---

## Disorder calculation

Before any sorting movement is performed, the program calculates the initial disorder of stack `a`.

The disorder value ranges between:

```text
0.0
```

and:

```text
1.0
```

Where:

```text
0.0 = completely sorted
1.0 = completely reverse sorted
```

The calculation is based on inversions.

For every possible pair of elements where:

```text
i < j
```

the program checks whether:

```text
a[i] > a[j]
```

If this condition is true, the pair is considered an inversion.

The disorder is calculated using:

```text
number of inversions / total number of possible pairs
```

For example:

```text
1 2 3 4 5
```

produces:

```text
0.00%
```

while:

```text
5 4 3 2 1
```

produces:

```text
100.00%
```

This value is used by the adaptive strategy to decide which sorting approach should be selected.

---

## Small inputs

Inputs containing five elements or fewer use dedicated sorting logic.

This avoids running more expensive general algorithms when only a few operations are needed.

### Two elements

If two elements are in the wrong order:

```text
2 1
```

the program only needs:

```text
sa
```

### Three elements

Different combinations of `sa`, `ra` and `rra` are used depending on the order of the three indexes.

For example:

```text
3 2 1
```

can be sorted using:

```text
sa
rra
```

### Four and five elements

The smallest indexed values are moved temporarily to stack `b`.

The remaining three elements are sorted.

The elements stored in `b` are then pushed back into `a`.

This provides a small and efficient solution for inputs up to five numbers.

---

## Simple strategy — O(n²)

The simple strategy uses a minimum-extraction approach.

The algorithm repeatedly searches stack `a` for the smallest remaining indexed value.

Once the minimum is found, its position is calculated.

If the minimum is closer to the top of the stack, it is moved using:

```text
ra
```

If it is closer to the bottom, it is moved using:

```text
rra
```

When the minimum reaches the top, it is moved to stack `b` using:

```text
pb
```

This process continues until only a few elements remain in stack `a`.

Those elements are sorted using the small-input sorter.

Finally, every element stored in stack `b` is pushed back using:

```text
pa
```

### Complexity

Searching for the minimum requires traversing the stack.

This search is repeated for many elements.

Therefore the strategy belongs to the:

```text
O(n²)
```

complexity class.

### Advantages

- Simple to understand
- Predictable behavior
- Useful as a baseline strategy
- Efficient enough for small inputs

### Disadvantages

- Scales poorly for large inputs
- Performs many searches and rotations

---

## Medium strategy — O(n√n)

The medium strategy uses a chunk-based approach.

Instead of extracting only one minimum at a time, the algorithm processes groups of indexed values.

The approximate chunk size is based on:

```text
√n
```

where `n` is the number of elements.

For example, if the stack contains approximately 100 elements, the algorithm works with ranges around the square root of 100.

Elements belonging to the current range are progressively moved from stack `a` to stack `b`.

Depending on the index of the element, stack `b` may also be rotated to improve the distribution of its values.

Once stack `a` is empty, the algorithm rebuilds it.

The largest remaining index in stack `b` is located.

If it is closer to the top, it is moved using:

```text
rb
```

Otherwise:

```text
rrb
```

The value is then pushed to stack `a` using:

```text
pa
```

This continues until stack `b` is empty.

### Complexity

Using approximately `√n` sized ranges reduces the number of searches and rotations compared with the simple strategy.

The intended operation complexity is:

```text
O(n√n)
```

### Advantages

- Much better performance than the simple strategy on medium inputs
- Relatively easy to understand
- Good balance between complexity and performance

---

## Complex strategy — O(n log n)

The complex strategy is based on binary LSD Radix Sort.

Instead of sorting the original integer values, it works with the normalized indexes.

Example indexes:

```text
0
1
2
3
4
```

can be represented in binary as:

```text
0 = 000
1 = 001
2 = 010
3 = 011
4 = 100
```

The algorithm processes one bit at a time.

For each element in stack `a`, the current bit is inspected.

If the bit is:

```text
1
```

the element remains in stack `a` and is rotated using:

```text
ra
```

If the bit is:

```text
0
```

the element is moved to stack `b` using:

```text
pb
```

After all elements have been processed for that bit, all elements in stack `b` are pushed back to stack `a` using:

```text
pa
```

The algorithm then continues with the next bit.

This repeats until all necessary bits have been processed.

### Complexity

Each bit requires processing the complete stack.

The number of bits required to represent the indexes grows logarithmically with the number of values.

The intended operation complexity is therefore:

```text
O(n log n)
```

### Advantages

- Predictable behavior
- Works well with large inputs
- Does not depend strongly on the initial order
- Easy to implement once values are indexed

---

## Adaptive strategy

The adaptive strategy calculates the disorder of the initial stack and selects an internal approach according to that value.

The thresholds used are:

```text
disorder < 0.2
```

```text
0.2 <= disorder < 0.5
```

```text
disorder >= 0.5
```

### Low disorder

For:

```text
disorder < 0.2
```

the input is already relatively close to being sorted.

The implementation first attempts a limited number of linear passes using swaps and rotations.

During a pass, adjacent elements are inspected.

When two neighboring indexes are in the wrong order:

```text
sa
```

can be used.

The stack is then rotated and the pass continues.

Because the number of these initial passes is bounded, this stage performs a number of operations proportional to the size of the stack.

If these passes are not sufficient to completely sort the input, the implementation uses the medium strategy as a safety fallback to preserve correctness.

### Medium disorder

For:

```text
0.2 <= disorder < 0.5
```

the chunk-based medium strategy is selected.

This is useful when the stack contains a significant amount of disorder but still benefits from range-based partitioning.

### High disorder

For:

```text
disorder >= 0.5
```

the complex binary Radix strategy is selected.

Highly disordered inputs benefit from the predictable scaling of Radix Sort.

### Why use an adaptive strategy?

A nearly sorted stack and a completely reversed or randomized stack have very different characteristics.

Using the same algorithm for every possible input can produce unnecessary operations.

The adaptive strategy attempts to choose an approach that better matches the structure of the initial data.

---

## Error management

The program validates all input before sorting.

The following cases are handled as errors:

- Non-numeric parameters
- Duplicate integer values
- Values greater than `INT_MAX`
- Values smaller than `INT_MIN`
- Empty input strings
- Invalid combinations of strategy selectors

When an error occurs, the program writes:

```text
Error
```

followed by a newline to standard error.

Example:

```bash
./push_swap a 2 3
```

Output:

```text
Error
```

Duplicate example:

```bash
./push_swap 1 2 1
```

Output:

```text
Error
```

Overflow example:

```bash
./push_swap 2147483648
```

Output:

```text
Error
```

If the program is executed without parameters:

```bash
./push_swap
```

nothing is displayed and the program returns normally.

---

## Already sorted inputs

If stack `a` is already sorted, the program does not produce unnecessary operations.

Examples:

```bash
./push_swap 42
```

```bash
./push_swap 2 3
```

```bash
./push_swap 0 1 2 3
```

```bash
./push_swap 0 1 2 3 4 5 6 7 8 9
```

All these examples produce:

```text
0 instructions
```

---

## Testing

The project was tested using the official `checker_linux`.

Example:

```bash
ARG="5 4 3 2 1"
./push_swap $ARG | ./checker_linux $ARG
```

Expected result:

```text
OK
```

The four strategies were also tested independently:

```bash
ARG="5 4 3 2 1"

./push_swap --simple $ARG | ./checker_linux $ARG
./push_swap --medium $ARG | ./checker_linux $ARG
./push_swap --complex $ARG | ./checker_linux $ARG
./push_swap --adaptive $ARG | ./checker_linux $ARG
```

All tested strategies returned:

```text
OK
```

---

## Performance tests

### Three numbers

Test:

```text
2 1 0
```

Result:

```text
2 operations
```

Test:

```text
0 2 1
```

Result:

```text
2 operations
```

Test:

```text
1 0 2
```

Result:

```text
1 operation
```

All were validated with the official checker.

### Five numbers

For:

```text
5 4 3 2 1
```

the small-input sorter produced:

```text
8 operations
```

and the checker returned:

```text
OK
```

### Fifty numbers

A test using the same set of 50 random numbers produced:

```text
Simple:   455 operations
Medium:   241 operations
Complex:  467 operations
Adaptive: 241 operations
```

All four strategies produced a valid sorted result.

### One hundred numbers

Multiple random tests with 100 numbers produced results approximately between:

```text
563
```

and:

```text
1084
```

operations.

All tested cases returned:

```text
OK
```

with the official checker.

### Five hundred numbers

Random tests with 500 numbers produced results including:

```text
5456 operations
```

and:

```text
5265 operations
```

Both tests returned:

```text
OK
```

with the official checker.

---

## Memory management

All dynamically allocated stack nodes are freed before the program terminates.

The project was tested using Valgrind.

Example:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./push_swap 5 4 3 2 1
```

Result:

```text
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors from 0 contexts
```

The same test was also performed using 100 random numbers.

The result was:

```text
100 allocs
100 frees
0 bytes in use at exit
0 errors
```

---

## Norminette

The complete project was checked using:

```bash
norminette
```

All project source files, headers and Libft files passed Norminette.

---

## Contributions

This project was developed as a group project by two learners.

Both learners are expected to understand and be able to explain the complete codebase.

### jhansilv

Main contributions:

- Initial project architecture
- Initial directory and file organization
- Stack representation
- Basic stack utilities
- Push_swap operations
- Initial parsing implementation
- Initial indexation implementation
- Initial disorder calculation
- Initial Simple strategy
- Initial Medium strategy
- Initial Complex strategy
- Initial Adaptive strategy
- Initial benchmark implementation
- First working version of the project

### andpascu

Main contributions:

- Review of the initial implementation
- Correction of small-input handling
- Correction of the two-element case
- Integration of dedicated sorting for inputs up to five elements
- Prevention of unnecessary operations on already sorted stacks
- Improvements to strategy selection
- Validation of Simple, Medium, Complex and Adaptive modes
- Improvements to parsing
- Handling of conflicting strategy flags
- Overflow validation
- Duplicate validation
- Error-management testing
- Norminette corrections
- Refactoring functions to comply with Norminette limits
- Checker validation
- Testing with 3 elements
- Testing with 5 elements
- Testing with 50 elements
- Testing with 100 elements
- Testing with 500 elements
- Performance validation
- Disorder validation
- Benchmark validation
- Valgrind testing
- Memory-leak validation
- Final project cleanup and documentation

---

## Resources

The following resources were used during development:

- Official 42 Push_swap subject
- Official 42 Push_swap evaluation scale
- 42 Norminette
- Official `checker_linux`
- C language documentation
- Linked-list documentation
- Algorithmic complexity references
- Selection-sort concepts
- Chunk-based sorting concepts
- Binary Radix Sort documentation
- Binary representation and bitwise operations documentation
- Inversion counting concepts
- Valgrind documentation

---

## Use of AI

AI tools were used as a support resource during the development and review of the project.

AI was used for tasks such as:

- Explaining Push_swap concepts
- Explaining stacks and linked lists
- Understanding the allowed operations
- Reviewing the project architecture
- Explaining algorithmic complexity
- Explaining binary Radix Sort
- Explaining chunk-based sorting
- Explaining disorder and inversion counting
- Identifying possible edge cases
- Suggesting testing scenarios
- Reviewing parsing behavior
- Analyzing Norminette errors
- Suggesting refactoring approaches
- Reviewing error handling
- Preparing checker tests
- Preparing performance tests
- Reviewing Valgrind results
- Helping prepare documentation

AI-generated suggestions were not accepted blindly.

The code was manually reviewed, compiled and tested using:

```text
-Wall -Wextra -Werror
```

as well as:

```text
Norminette
checker_linux
Valgrind
randomized performance tests
```

Both learners remain responsible for understanding, maintaining and defending the final implementation.

---

## Authors

- `andpascu`
- `jhansilv`