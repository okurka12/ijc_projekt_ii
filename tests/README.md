# IJC project 2 tests

### How to use:
- Put content of this repository (you can use `git clone`) into a subdirectory of your project directory, for example `~/IJC/project2/tests`. This is not even necessary, but I recommend it
- Change constants in `test_tail.py`.
- Run `python3 tests/test_tail.py`

### Constants in `test_tail.py`:
- `COMMAND` the desired command. Set this to path of your executable. If you put the tests in a subdirectory, this will probably look like `../tail` or whatever is the filename of your executable.
- `LEN_LIM` for a line length implementation limit you chose. This can be (but doesn't have to be) 4096 including LF.
- The other constants need not to be changed, but you can tweak them too if you want.

### Requirements & notes:
- I was running the tests using Python 3.9.2 on GNU/Linux 
- If you choose to test GNU `tail`, 4 tests fail (tests for long lines and invalid `-n` arguments). The assignment specifies that the number following `-n` is unsigned and to implement a line length limit, which GNU `tail` doesn't have.
- I recommend making a `make test` recipe for building  the executable and then running the tests on it.
- For now I only have tests for `tail` but if I make tests for the second part of the project too, I'll put them here.
- If you run the tests and after some amount of tests nothing happens, your program might be waiting for input somewhere I gave it none, just press `^D` (EOF).

### Tests:

 1. `tail: basic functionality, stdin`
 2. `tail: output nothing with empty input, stdin`
 3. `tail: many lines, stdin` - test with `LONG_NUM` lines (a constant you can change)
 4. `tail: basic functionality, file`
 5. `tail: empty input, file`
 6. `tail: many lines, file` - test with `LONG_NUM` lines, but in a file
 7. `tail: invalid number of lines for '-n' option`
 8. `tail: non-existent file`
 9. `tail with -n option, stdin`
 10. `tail with -n option, file` 
 11. `tail with -n 0, stdin`
 12. `tail with -n 0, file`
 13. `tail: line too long, stdin`
 14. `tail: line too long, file`
 15. `tail: line too long with -n, stdin`
  
