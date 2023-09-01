ifeq ($(OS), Windows_NT)
	$(error "The Windows platform is not supported.")
endif
OS := $(shell uname -s)
ifeq ($(OS), Linux)
	OPEN := xdg-open
endif
ifeq ($(OS), Darwin)
	OPEN := open
endif

NAME := s21_containers

### Files and directories

SRC_DIR := ./src
HEADERS = $(shell find $(SRC_DIR) -type f -name "*.h")
HEADER_DIRS = $(shell find $(SRC_DIR) -type f -name "*.h" -exec dirname {} \; | uniq)
SOURCES := $(shell find $(SRC_DIR) -type f -name "*.cc")
SOURCE_OBJECTS := $(SOURCES:.cc=.o)

TEST_DIR := ./tests
TEST_HEADERS := $(shell mkdir -p $(TEST_DIR); find $(TEST_DIR) -type f -name "*.h")
TEST_HEADER_DIRS = $(shell find $(TEST_DIR) -type f -name "*.h" -exec dirname {} \; | uniq)
TEST_SOURCES := $(shell find $(TEST_DIR) -type f -name "*.cc")
TEST_OBJECTS := $(TEST_SOURCES:.cc=.o)
TEST_RUNNER := $(TEST_DIR)/test_runner.out

ALL_HEADERS := $(HEADERS) $(TEST_HEADERS)
ALL_SOURCES := $(SOURCES) $(TEST_SOURCES)
ALL_FILES := $(ALL_HEADERS) $(ALL_SOURCES)

### Commands and options

# -fsanitize=address
CC := g++
CFLAGS := -Wall -Werror -Wextra -lstdc++ --std=c++17 -fsanitize=address
DFLAGS := -g
GFLAGS := -lgtest -lgtest_main -lpthread
GTRUN_FLAGS := --gtest_break_on_failure --gtest_shuffle

CFORMAT := clang-format
FORMAT_GSTYLE := $(CFORMAT) -style=google

SRC_HEADERS_INCS := $(foreach HDIR, $(HEADER_DIRS), -I $(HDIR))
TEST_HEADERS_INCS := $(foreach THDIR, $(TEST_HEADER_DIRS), -I $(THDIR))
INCS := $(TEST_HEADERS_INCS) $(SRC_HEADERS_INCS)

### Coverage

COV_DIR := ./gcov_report
COV_OUT := $(NAME).report
COV_INFO := $(NAME).info
REPORT_DIR := $(COV_DIR)/report

### Checkers

LEAKS := leaks
LEAKS_OPTS := --atExit --

### Targets

.PHONY: all clean re format style test test-leaks cov clean-cov

all: $(SOURCE_OBJECTS)

%.o: %.cc $(HEADERS)
	$(CC) $(CFLAGS) $(SRC_HEADERS_INCS) -c $< -o $@

format:
	$(FORMAT_GSTYLE) -i $(ALL_FILES)

style:
	$(FORMAT_GSTYLE) -n $(ALL_FILES)

test:
	$(CC) $(CFLAGS) $(INCS) $(TEST_SOURCES) $(GFLAGS) -o $(TEST_RUNNER)
	$(TEST_RUNNER) $(GTRUN_FLAGS)

test-leaks: test
	$(LEAKS) $(LEAKS_OPTS) $(TEST_RUNNER) $(GTRUN_FLAGS)

gcov_report: add_coverage_flag test
	$(TEST_DIR)/test_runner.out
	gcov -b -l -p -c *.gcno *.gcov
	gcovr -o gcov_report.html --html --html-details

add_coverage_flag:
	$(eval FLAGS += --coverage)

# https://ps-group.github.io/cxx/coverage_gcc
cov: clean-cov
	@mkdir -p $(COV_DIR)
	$(CC) `pkg-config --cflags --libs gtest` $(CFLAGS) $(GFLAGS)  --coverage $(INCS) $(ALL_SOURCES) -o $(COV_OUT)
	./$(COV_OUT)
	lcov -b . -c -d . -t $(COV_NAME) -c -o $(COV_INFO)
	lcov -r $(COV_INFO) "/usr*" -o $(COV_INFO)
	genhtml -o $(REPORT_DIR) $(COV_INFO)
	@mv *.gcda *.gcno *.info *.report $(COV_DIR)
	$(OPEN) $(REPORT_DIR)/index.html

clean-cov:
	rm -rf $(COV_DIR)

clean:
	rm -rf $(shell find -E . -regex '.*\.(d|o|out|dSYM)')
	@make clean-cov

re: clean all
