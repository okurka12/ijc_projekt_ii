# test the first part of the project - utility `tail`
import testutils as tu

COMMAND="tail"  # command to be tested


def test_input(start: int, end: int) -> str:
    """returns string of numbered lines from start to end"""
    return "\n".join([str(i) for i in range(start, end + 1)])


def test1() -> None:
    """print last ten lines of 15 lines from stdin"""

    rcode, out_out, err_out = tu.run(COMMAND, input_str=test_input(1, 15))
    
    if rcode == 0 and out_out == test_input(6, 15):
        tu.print_ok("basic tail")
    else:
        tu.print_err(f"basic tail (return code {rcode})")
    pass


def test2() -> None:
    pass


def main():
    test1()
    

if __name__ == "__main__":
    main()
    