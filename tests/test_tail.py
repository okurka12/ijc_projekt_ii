# test the first part of the project - utility `tail`
import testutils as tu
import os

COMMAND="tail"  # command to be tested
LINES_NUM = 99_999  # number of lines with whitch test for long inputs
TMP_FILE_PATH = "test_tail_tmp.txt"


def test_input(start: int, end: int) -> str:
    """returns string of numbered lines from start to end"""
    return "\n".join([str(i) for i in range(start, end + 1)])


def test1() -> None:
    """print last ten lines of 15 lines from stdin"""
    result = tu.run(COMMAND, input_str=test_input(1, 15))

    conditions = [
        result.rcode == 0,
        result.stdout == test_input(6, 15),
        result.stderr == ""
    ]
    
    tu.print_result("tail: basic functionality", conditions, result)


def test2() -> None:
    """output nothing with empty input"""
    result = tu.run(COMMAND, input_str="")

    conditions = [
        result.rcode == 0,
        result.stdout == "",
        result.stderr == ""
    ]

    tu.print_result("tail: nothing at the input", conditions, result)


def test3() -> None:
    """output last ten lines of a really long input (99 999 lines)"""
    length = 99_999
    result = tu.run(COMMAND, input_str=test_input(1, length))

    conditions = [
        result.rcode == 0,
        result.stdout == test_input(length - 9, length),
        result.stderr == ""
    ]

    tu.print_result(f"tail: {length:_} lines", conditions, result)


def test4() -> None:
    """tail: basic functionality with file"""
    
    # create a test input file
    with open(TMP_FILE_PATH, "w") as f:
        f.write(test_input(1, 15)) 
    
    result = tu.run(f"{COMMAND} {TMP_FILE_PATH}")

    os.unlink(TMP_FILE_PATH)  # delete a test input file

    conditions = [
        result.rcode == 0,
        result.stderr == "",
        result.stdout == test_input(6, 15)
    ]

    tu.print_result("tail: basic functionality with file", conditions, result)


def test5() -> None:
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

    tu.print_result("tail: empty input file", conditions, result)


def test6() -> None:
    """tail: input file with 99 999 lines"""
    
    number_of_lines = 99_999
    
    with open(TMP_FILE_PATH, "w") as f:
        f.write(test_input(1, number_of_lines))
    
    result = tu.run(f"{COMMAND} {TMP_FILE_PATH}")

    os.unlink(TMP_FILE_PATH)

    conditions = [
        result.rcode == 0,
        result.stderr == "",
        result.stdout == test_input(number_of_lines - 9, number_of_lines)
    ]

    tu.print_result(f"tail: file with {number_of_lines} lines", conditions, 
                    result)


def test7() -> None:
    """tail: invalid number of lines for `-n` option"""

    # \u011b LATIN SMALL LETTER E WITH CARON
    invalid_nums = "a ff ` , : . / * - + \u011b"

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
    tu.print_result("tail: invalid number of lines for `-n` option", conditions, 
                    result)



def main():
    test1()
    test2()
    test3()
    test4()
    test5()
    test6()
    test7()
    # doplnit testy:
    #    kdyz je jako argument prepinace -n neco co neni cislo
    #    kdyz je radek delsi nez implementacni limit
    

if __name__ == "__main__":
    main()
    