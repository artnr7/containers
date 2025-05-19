# 1 правило моих проектов → помечать концы названий пользовательских директорий приставкой _dir 
# 2 перед изменением Мейкфайла запушить изменения в Гитлаб

###--------→ сборка и компиляция ←--------------------------------------------------------------------###

GPP = g++ -Wall -Werror -Wextra -std=c++20 -pedantic
VALGRIND_CHECK_FLAGS = -lcheck -lm -lsubunit

# директории
DEQUE_TEST_DIR = test_dir

# файлы для компиляции
DEQUE_CPP_FILES = $(wildcard deque_map/src/*.c)
DEQUE_H_FILES := deque_map/deque.h
DEQUE_TEST_FILES = $(wildcard $(DEQUE_TEST_DIR)/*.c)
DEQUE_OBJ_FILES = $(patsubst %.c, %.o, $(DEQUE_CPP_FILES))

# скомпилированные файлы
DEQUE_LIB_FILE = deque.a
DEQUE_TEST_EXE_FILE = deque_test


###--------→ главные функции по заданию ←--------------------------------------------------------------###

all: $(DEQUE_LIB_FILE)

rebuild: clean cl all

r: clean cl $(DEQUE_LIB_FILE)
	$(GPP) deque_main.c $(DEQUE_LIB_FILE) $(VALGRIND_CHECK_FLAGS) -o $(DEQUE_TEST_EXE_FILE)
	./$(DEQUE_TEST_EXE_FILE)

g: clean cl $(DEQUE_LIB_FILE)
	$(GPP) deque_main.c $(DEQUE_LIB_FILE) $(VALGRIND_CHECK_FLAGS) -o $(DEQUE_TEST_EXE_FILE) -g
	gdb --tty=/dev/pts/5 -tui -x .gdbinit $(DEQUE_TEST_EXE_FILE)


# сборка библиотек и обджект файлов
$(DEQUE_LIB_FILE): $(DEQUE_OBJ_FILES)
	ar rcs $@ $^
	ranlib $@

%.o: %.c
	$(GPP) -c $< -o $@


###--------→ тестирование ←--------------------------------------------------------------------###

deque_test: clean cl $(DEQUE_TEST_EXE_FILE)
	./$(DEQUE_TEST_EXE_FILE)

deque_test_valgrind: clean cl $(DEQUE_TEST_EXE_FILE)
	valgrind --tool=memcheck --leak-check=full ./$(DEQUE_TEST_EXE_FILE)

deque_test_compile: $(DEQUE_LIB_FILE)
	$(GPP) $(DEQUE_TEST_FILES) $(DEQUE_LIB_FILE) $(VALGRIND_CHECK_FLAGS) -o $(DEQUE_TEST_EXE_FILE)


###--------→ покрытие кода ←--------------------------------------------------------------------###

gcov_report: clean 
	$(GPP) $(CPPFILES) $(TEST_FILES) $(GT_FLAGS) --coverage -o gcov_test
	./gcov_test
	geninfo --ignore-errors mismatch --ignore-errors gcov . -o coverage.info
	genhtml coverage.info -o coverage_report


###--------→ clang и удаление ←--------------------------------------------------------------------###

FILES_TO_DEL = *.o *.a $(DEQUE_TEST_EXE_FILE) $(DEQUE_LIB_FILE)\
 $(DEQUE_OBJ_FILES) *.gcno *.gcda *.gcov gcov_test coverage.info\
 coverage_report errors.log
# не меняй название с test_f на test

clean: 
	rm -rf $(FILES_TO_DEL)

cl:
	clang-format -i $(DEQUE_CPP_FILES) $(DEQUE_H_FILES)



T_DIR := testing
t: 
	clang-format -i $(T_DIR)/t.cc
	g++ -Wall -Werror -Wextra $(T_DIR)/t.cc -o $(T_DIR)/t.exe
	./$(T_DIR)/t.exe

ma: $(DEQUE_LIB_FILE) cl
	$(GPP) $(T_DIR)/main.cc -o $(T_DIR)/main.exe
	./$(T_DIR)/main.exe