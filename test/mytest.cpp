#include <limits>
#include <string>
#include <iostream>
#include <memory>

typedef enum CASE_RESULT {
    OK = 0,
    FAILED = 1,
    NOT_DETERMINED = 2,
    CASE_NOT_FOUND = 3
} CASE_RESULT;

static CASE_RESULT case_1() {
    return CASE_RESULT::OK;
}

static CASE_RESULT case_2() {
    return CASE_RESULT::OK;
}

static CASE_RESULT case_3() {
    return CASE_RESULT::OK;
}

static CASE_RESULT case_4() {
    return CASE_RESULT::OK;
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        std::cout << "No test was selected; test suite fails" << std::endl;
        return 1;
    }
    std::cout << "Running test case (" << argv[1][0] << ")" << std::endl;
    CASE_RESULT result = NOT_DETERMINED;
    switch (argv[1][0]) {
    case '1':
        result = case_1();
        break;
    case '2':
        result = case_2();
        break;
    case '3':
        result = case_3();
        break;
    case '4':
        result = case_4();
        break;
    default:
        std::cout << "Invalid test case, error: CASE_NOT_FOUND" << std::endl;
        return CASE_RESULT::CASE_NOT_FOUND;
    }
    return result;
}
