# 1 правило моих проектов → помечать концы названий пользовательских директорий приставкой _dir 
# 2 перед изменением Мейкфайла запушить изменения в Гитлаб

###--------→ сборка и компиляция ←---------------------------------------------###

GPP := g++ -Wall -Werror -Wextra -std=c++20 -pedantic
VALGRIND_FLAGS := -lgtest -lgmock -pthread

# директории
TEST_DIR := test_dir
INST_DIR := install_dir

# файлы для компиляции
H_FILES := deque_map/deque.h
TEST_FILES := $(shell find $(TEST_DIR) -name '*.cc')
OBJ_FILES := $(patsubst %.cc, $(INST_DIR)/%.o, $(CC_FILES))

# скомпилированные файлы
DEQUE_H_FILE := deque_map/deque.h
TEST_EXE_FILE := test_dir/deque_test


###--------→ главные функции по заданию ←--------------------------------------###

all: $(DEQUE_H_FILE)

rebuild: clean cl all

###--------→ МАНКИ ТЕСТЫ ←-----------------------------------------------------------###
T_DIR := testing
MAIN_EXE := main.exe
T_EXE := t.exe

r: clean cl $(DEQUE_H_FILE)
	@$(GPP) $(T_DIR)/main.cc -o $(T_DIR)/$(MAIN_EXE) $(DEQUE_H_FILE)
	@echo main running...
	@./$(T_DIR)/$(MAIN_EXE)

t: clean cl $(DEQUE_H_FILE)
	@$(GPP) $(T_DIR)/t.cc -o $(T_DIR)/$(T_EXE) $(DEQUE_H_FILE)
	@echo t running...
	@./$(T_DIR)/$(T_EXE)

# g: clean cl $(DEQUE_H_FILE)
# 	$(GPP) deque_main.c $(DEQUE_H_FILE) $(VALGRIND_FLAGS) -o $(TEST_EXE_FILE) -g
# 	gdb --tty=/dev/pts/5 -tui -x .gdbinit $(TEST_EXE_FILE)


# ###--------→ СБОРКА БИБЛИОТЕКИ ←-----------------------------------------------------------###
# $(DEQUE_H_FILE): 
# 	@mkdir -p $(dir $@)
# 	ar rcs $@ deque_map/deque.h
# 	ranlib $@

# КОМПИЛЯЦИЯ ОБДЖЕКТ ФАЙЛОВ 
$(INST_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	@$(GPP) -c $< -o $@
	@echo OBJS compiled


###--------→ тестирование ←--------------------------------------------------------------###

test: clean cl $(TEST_EXE_FILE)
	./$(TEST_EXE_FILE)

test_valgrind: clean cl $(TEST_EXE_FILE)
	valgrind --tool=memcheck --leak-check=full ./$(TEST_EXE_FILE)

$(TEST_EXE_FILE): 
	$(GPP) $(TEST_FILES) $(DEQUE_H_FILE) -o $@ $(VALGRIND_FLAGS)


###--------→ покрытие кода ←--------------------------------------------------------------------###
TETRIS_GCOV_DIRS := coverage_report gcov_report_dir coverage.info

gcov_report: clean 
	@mkdir gcov_report_dir
	@$(GPP) $(CC_FILES) $(TEST_FILES) $(GT_FLAGS) --coverage -o gcov_report_dir/gcov_test
	./gcov_report_dir/gcov_test
	geninfo --ignore-errors mismatch --ignore-errors gcov . -o coverage.info
	genhtml coverage.info -o coverage_report
	@echo "GCOV done"


###--------→ clang и удаление ←---------------------------------------------------------------###

FILES_TO_DEL := test_dir/deque_test 

clean: 
	@rm -rf $(FILES_TO_DEL)
	@echo clean done

FILES_TO_CLANG := $(H_FILES) $(TEST_FILES)
cl:
	@clang-format -i $(FILES_TO_CLANG)
	@echo clang done

###--------→ сборка и пользовательские обезьяние тесты ←-------------------------------------------###

# t: 
# 	clang-format -i $(T_DIR)/t.cc
# 	g++ -Wall -Werror -Wextra $(T_DIR)/t.cc -o $(T_DIR)/t.exe
# 	./$(T_DIR)/t.exe

