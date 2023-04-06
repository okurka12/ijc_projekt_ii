# test the first part of the project - utility `tail`
import testutils as tu
import os

# command to be tested
COMMAND="tail"

# implementation limit for the length of a line (including LF)
LEN_LIM = 4096

# basic functionality will be tested with this many 
LINES_NUM = 15

# number of lines with which test for long inputs (`many lines`)
LONG_NUM = 99_999

# number with which to test functionality of `-n` option
N_OPT = 5

# when testing `-n` option, file will have N_BASE + N_OPT lines
N_BASE = 25

# path to a temporary file this script will create
TMP_FILE_PATH = "test_tail_tmp.txt"

# path to non-existent file for testing purposes
NONEXISTENT_FILE = "no_n-exi-s_tent.file"


def test_input(start: int, end: int) -> str:
    """returns string of numbered lines from start to end"""
    return "\n".join([str(i) for i in range(start, end + 1)])


def test1() -> tuple[bool, int]:
    """print last ten lines of LINES_NUM lines from stdin"""
    result = tu.run(COMMAND, input_str=test_input(1, LINES_NUM))

    conditions = [
        result.rcode == 0,
        result.stdout == test_input(LINES_NUM - 9, LINES_NUM),
        result.stderr == ""
    ]
    return all(conditions), result.rcode
    


def test2() -> tuple[bool, int]:
    """output nothing with empty input"""
    result = tu.run(COMMAND, input_str="")

    conditions = [
        result.rcode == 0,
        result.stdout == "",
        result.stderr == ""
    ]

    return all(conditions), result.rcode


def test3() -> tuple[bool, int]:
    """output last ten lines of many lines"""
    result = tu.run(COMMAND, input_str=test_input(1, LONG_NUM))

    conditions = [
        result.rcode == 0,
        result.stdout == test_input(LONG_NUM - 9, LONG_NUM),
        result.stderr == ""
    ]

    return all(conditions), result.rcode


def test4() -> tuple[bool, int]:
    """tail: basic functionality with file"""
    
    # create a test input file
    with open(TMP_FILE_PATH, "w") as f:
        f.write(test_input(1, LINES_NUM)) 
    
    result = tu.run(f"{COMMAND} {TMP_FILE_PATH}")

    os.unlink(TMP_FILE_PATH)  # delete a test input file

    conditions = [
        result.rcode == 0,
        result.stderr == "",
        result.stdout == test_input(LINES_NUM - 9, LINES_NUM)
    ]

    return all(conditions), result.rcode


def test5() -> tuple[bool, int]:
    """tail: empty input file"""

    # create a test file
    with open(TMP_FILE_PATH, "w") as f:
        f.write("")
    
    result = tu.run(f"{COMMAND} {TMP_FILE_PATH}")

    os.unlink(TMP_FILE_PATH)

    conditions = [
        result.rcode == 0,
        result.stderr == "",
        result.stdout == ""
    ]

    return all(conditions), result.rcode


def test6() -> tuple[bool, int]:
    """tail: input file with many lines"""
        
    with open(TMP_FILE_PATH, "w") as f:
        f.write(test_input(1, LONG_NUM))
    
    result = tu.run(f"{COMMAND} {TMP_FILE_PATH}")

    os.unlink(TMP_FILE_PATH)

    conditions = [
        result.rcode == 0,
        result.stderr == "",
        result.stdout == test_input(LONG_NUM - 9, LONG_NUM)
    ]

    return all(conditions), result.rcode


def test7() -> tuple[bool, int]:
    """tail: invalid number of lines for `-n` option"""

    # \u011b LATIN SMALL LETTER E WITH CARON
    invalid_nums = "a ff ` , : . / * - + \u011b -5"

    rcodes = []
    stdouts = []
    stderrs = []
    
    for invalid_num in invalid_nums.split(" "):
        result = tu.run(f"{COMMAND} -n {invalid_num}", 
                        input_str=test_input(1, 15))
        rcodes.append(result.rcode)
        stdouts.append(result.stdout)
        stderrs.append(result.stderr)

    conditions = [rcode != 0 for rcode in rcodes]
    conditions.extend([len(stderr) > 0 for stderr in stderrs])
    conditions.extend([stdout == "" for stdout in stdouts])

    # here the last result_t is used if the test fails even though
    # it may not be the reason it failed
    return all(conditions), result.rcode


def test8() -> tuple[bool, int]:
    """tail: non-existent file"""
    result = tu.run(f"{COMMAND} {NONEXISTENT_FILE}")
    conditions = [
        result.rcode != 0,
        len(result.stderr) > 0,
        result.stdout == ""
    ]

    return all(conditions), result.rcode
    return all(conditions), result.rcode


def test9() -> tuple[bool, int]:
    """tail with -n option, stdin"""

    result = tu.run(f"{COMMAND} -n {N_OPT}", 
                    input_str=test_input(1, N_BASE + N_OPT))

    conditions = [
        result.rcode == 0,
        result.stdout == test_input(N_BASE + 1, N_BASE + N_OPT),
        result.stderr == ""
    ]

    return all(conditions), result.rcode


def test9_1() -> tuple[bool, int]:
    """tail with -n 0, stdin"""
    result = tu.run(f"{COMMAND} -n 0", input_str=test_input(1, 15))
    
    conditions = [
        result.rcode == 0,
        result.stderr == "",
        result.stdout == ""
    ]

    return all(conditions), result.rcode


def test9_2() -> tuple[bool, int]:
    """tail with -n 0, file"""
    with open(TMP_FILE_PATH, "w") as f:
        f.write(test_input(1, 15))
    result = tu.run(f"{COMMAND} -n 0 {TMP_FILE_PATH}")
    os.unlink(TMP_FILE_PATH)

    conditions = [
        result.rcode == 0,
        result.stderr == "",
        result.stdout == ""
    ]

    return all(conditions), result.rcode


def test10() -> tuple[bool, int]:
    """tail with -n option, file"""

    with open(TMP_FILE_PATH, "w") as f:
        f.write(test_input(1, N_OPT + N_BASE))
    
    result = tu.run(f"{COMMAND} -n {N_OPT} {TMP_FILE_PATH}")

    os.unlink(TMP_FILE_PATH)

    conditions = [
        result.rcode == 0,
        result.stdout == test_input(N_BASE + 1, N_BASE + N_OPT)
    ]

    return all(conditions), result.rcode


def test11() -> tuple[bool, int]:
    """tail: line too long, stdin"""

    test_input_str = ""
    for i in range(15):
        test_input_str += (LEN_LIM + 10) * "a"
        test_input_str += "\n"
    result = tu.run(COMMAND, input_str=test_input_str)

    conditions = [
        len(result.stdout.split("\n")) == 10,
        len(result.stdout.split("\n")[5]) == LEN_LIM - 1,
        len(result.stderr) > 0,
        result.rcode != 0
    ]

    return all(conditions), result.rcode


def test12() -> tuple[bool, int]:
    """tail: line too long, file"""

    test_input_str = ""
    for i in range(15):
        test_input_str += (LEN_LIM + 10) * "a"
        test_input_str += "\n"

    with open(TMP_FILE_PATH, "w") as f:
        f.write(test_input_str)

    result = tu.run(f"{COMMAND} {TMP_FILE_PATH}", input_str=test_input_str)

    os.unlink(TMP_FILE_PATH)

    conditions = [
        len(result.stdout.split("\n")) == 10,
        len(result.stdout.split("\n")[5]) == LEN_LIM - 1,
        len(result.stderr) > 0,
        result.rcode != 0
    ]

    return all(conditions), result.rcode


def test13() -> tuple[bool, int]:
    """tail: line too long with -n, stdin"""

    test_input_str = ""
    for i in range(N_BASE + N_OPT):
        test_input_str += (LEN_LIM + 10) * "a"
        test_input_str += "\n"
    result = tu.run(f"{COMMAND} -n {N_OPT}", input_str=test_input_str)

    conditions = [
        len(result.stdout.split("\n")) == N_OPT,
        len(result.stdout.split("\n")[0]) == LEN_LIM - 1,
        len(result.stderr) > 0,
        result.rcode != 0
    ]

    return all(conditions), result.rcode


def main():
    tests = [
        test1,
        test2,
        test3,
        test4,
        test5,
        test6,
        test7,
        test8,
        test9,
        test9_1,
        test9_2,
        test10,
        test11,
        test12,
        test13,
    ]

    for test in tests:
        passed, rcode = test()
        if passed:
            tu.print_ok(test.__doc__)
        else:
            tu.print_err(test.__doc__, f"(return code {rcode})")



if __name__ == "__main__":
    main()
    