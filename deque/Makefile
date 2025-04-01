# 1 правило моих проектов → помечать концы названий пользовательских директорий приставкой _dir 
# 2 перед изменением Мейкфайла запушить изменения в Гитлаб

###--------→ сборка и компиляция ←--------------------------------------------------------------------###

GPP = g++ -Wall -Werror -Wextra -std=c++20 -pedantic
VALGRIND_CHECK_FLAGS = -lcheck -lm -lsubunit

# директории
DEQUE_TEST_DIR = deque_test_dir

# файлы для компиляции
DEQUE_C_FILES = $(wildcard ) 
DEQUE_H_FILES = $(wildcard )
DEQUE_TEST_FILES = $(wildcard $(DEQUE_TEST_DIR)/*.c)
DEQUE_OBJ_FILES = $(patsubst %.c, %.o, $(DEQUE_C_FILES))

# скомпилированные файлы
DEQUE_LIB_FILE = deque.a
DEQUE_TEST_EXE_FILE = deque_test


###--------→ главные функции по заданию ←--------------------------------------------------------------###

all: $(deque_LIB_FILE)

rebuild: clean cl all

r: clean cl $(deque_LIB_FILE)
	$(GPP) deque_main.c $(DEQUE_LIB_FILE) $(VALGRIND_CHECK_FLAGS) -o $(DEQUE_TEST_EXE_FILE)
	./$(DEQUE_TEST_EXE_FILE)

g: clean cl $(deque_LIB_FILE)
	$(GPP) deque_main.c $(deque_LIB_FILE) $(VALGRIND_CHECK_FLAGS) -o $(deque_TEST_EXE_FILE) -g
	gdb --tty=/dev/pts/5 -tui -x .gdbinit $(DEQUE_TEST_EXE_FILE)


# сборка библиотек и обджект файлов
$(deque_LIB_FILE): $(deque_OBJ_FILES)
	ar rcs $@ $^
	ranlib $@

%.o: %.c
	$(GPP) -c $< -o $@ -g


###--------→ тестирование ←--------------------------------------------------------------------###

deque_test: clean cl $(deque_TEST_EXE_FILE)
	./$(deque_TEST_EXE_FILE)

deque_test_valgrind: clean cl $(deque_TEST_EXE_FILE)
	valgrind --tool=memcheck --leak-check=full ./$(deque_TEST_EXE_FILE)

deque_test_compile: $(deque_LIB_FILE)
	$(GPP) $(deque_TEST_FILES) $(deque_LIB_FILE) $(VALGRIND_CHECK_FLAGS) -o $(deque_TEST_EXE_FILE)


###--------→ покрытие кода ←--------------------------------------------------------------------###

gcov_report: clean 
	$(GPP) $(CPPFILES) $(TEST_FILES) $(GT_FLAGS) --coverage -o gcov_test
	./gcov_test
	geninfo --ignore-errors mismatch --ignore-errors gcov . -o coverage.info
	genhtml coverage.info -o coverage_report


###--------→ clang и удаление ←--------------------------------------------------------------------###

FILES_TO_DEL = *.o *.a $(deque_TEST_EXE_FILE) $(deque_LIB_FILE)\
 $(deque_OBJ_FILES) *.gcno *.gcda *.gcov gcov_test coverage.info\
 coverage_report errors.log
# не меняй название с test_f на test

clean: 
	rm -rf $(FILES_TO_DEL)

cl:
	clang-format -i $(deque_C_FILES) $(deque_H_FILES) $(deque_TEST_FILES) 
