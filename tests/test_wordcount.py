# tests for the first part of IJC assignment
# author: Vit Pavlik (https://github.com/okurka12/)

import testutils as tu

# static executable
ST_EX = "./wordcount"

# utilities
LDD = "ldd"

def test1() -> None:
    """wordcount: staticness"""
    return "libhtab.so" not in tu.run(f"{LDD} {ST_EX}").stdout


def test2() -> None:
    pass


def main():
    tests = [
        test1
    ]

    # execute tests and count passed
    passed_n = 0
    for test in tests:
        if test():
            tu.print_ok(test.__doc__)
            passed_n += 1
        else:
            tu.print_err(test.__doc__)


    # inform how many tests passed
    msg = f"{passed_n} of {len(tests)} passed"
    if passed_n == len(tests):
        tu.print_ok(msg)
    else:
        print(msg)


if __name__ == "__main__":
    main()

