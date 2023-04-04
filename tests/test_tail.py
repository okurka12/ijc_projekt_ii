# test the first part of the project - utility `tail`
import testutils as tu

COMMAND="tail"  # command to be tested


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


def main():
    test1()
    test2()
    test3()
    

if __name__ == "__main__":
    main()
    