# 1 правило моих проектов → помечать концы названий пользовательских директорий приставкой _dir 
# 2 перед изменением Мейкфайла запушить изменения в Гитлаб

###--------→ сборка и компиляция ←--------------------------------------------------------------------###

GPP := g++ -Wall -Werror -Wextra -std=c++20 -pedantic
VALGRIND_FLAGS := -lcheck -lm -lsubunit

# директории
TEST_DIR := test_dir
INST_DIR := install_dir

# файлы для компиляции
CC_FILES := $(wildcard deque_map/src/*.cc)
H_FILES := deque_map/deque.h
TEST_FILES := $(wildcard $(TEST_DIR)/*.cc)
OBJ_FILES := $(patsubst %.cc, $(INST_DIR)/%.o, $(CC_FILES))

# скомпилированные файлы
LIB_FILE := $(INST_DIR)/deque.a
TEST_EXE_FILE := deque_test


###--------→ главные функции по заданию ←----------------------------------------------------###

all: $(LIB_FILE)

rebuild: clean cl all

###--------→ МАНКИ ТЕСТЫ ←-----------------------------------------------------------###
T_DIR := testing
MAIN_EXE := main.exe

r: clean cl $(LIB_FILE)
	@$(GPP) $(T_DIR)/main.cc -o $(T_DIR)/$(MAIN_EXE) $(LIB_FILE)
	./$(T_DIR)/$(MAIN_EXE)

# g: clean cl $(LIB_FILE)
# 	$(GPP) deque_main.c $(LIB_FILE) $(VALGRIND_FLAGS) -o $(TEST_EXE_FILE) -g
# 	gdb --tty=/dev/pts/5 -tui -x .gdbinit $(TEST_EXE_FILE)


###--------→ СБОРКА БИБЛИОТЕКИ ←-----------------------------------------------------------###
$(LIB_FILE): $(OBJ_FILES)
	ar rcs $@ $^
	ranlib $@

# КОМПИЛЯЦИЯ ОБДЖЕКТ ФАЙЛОВ 
$(INST_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	@$(GPP) -c $< -o $@


###--------→ тестирование ←--------------------------------------------------------------###

test: clean cl $(TEST_EXE_FILE)
	./$(TEST_EXE_FILE)

test_valgrind: clean cl $(TEST_EXE_FILE)
	valgrind --tool=memcheck --leak-check=full ./$(TEST_EXE_FILE)

$(TEST_EXE_FILE): $(LIB_FILE)
	$(GPP) $(TEST_FILES) $(LIB_FILE) $(VALGRIND_FLAGS) -o $@


###--------→ покрытие кода ←--------------------------------------------------------------------###
TETRIS_GCOV_DIRS := coverage_report gcov_report_dir coverage.info

gcov_report: clean 
	@mkdir gcov_report_dir
	@$(GPP) $(CC_FILES) $(TEST_FILES) $(GT_FLAGS) --coverage -o gcov_report_dir/gcov_test
	./gcov_report_dir/gcov_test
	geninfo --ignore-errors mismatch --ignore-errors gcov . -o coverage.info
	genhtml coverage.info -o coverage_report
	@echo "GCOV done"


###--------→ clang и удаление ←--------------------------------------------------------------------###

FILES_TO_DEL = $(INST_DIR)

clean: 
	rm -rf $(FILES_TO_DEL)

cl:
	clang-format -i $(CC_FILES) $(H_FILES)


###--------→ сборка и пользовательские обезьяние тесты ←-------------------------------------------###

# t: 
# 	clang-format -i $(T_DIR)/t.cc
# 	g++ -Wall -Werror -Wextra $(T_DIR)/t.cc -o $(T_DIR)/t.exe
# 	./$(T_DIR)/t.exe

