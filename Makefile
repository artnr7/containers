NPROC := $(shell expr $$(nproc) - 2)
ifeq ($(shell expr $(NPROC) \< 1), 1)
  NPROC := 1
endif

.PHONY: build
build:
	mkdir -p build
	cd build && cmake -DCOVERAGE=ON -S .. && cmake --build . --parallel $(NPROC)

.PHONY: test
test:
	cd build && ctest --parallel $(NPROC) --output-on-failure

.PHONY: test-%
test-%:
	ctest --parallel $(NPROC) -R ^$*$$ --output-on-failure

.PHONY: test-verbose-%
test-verbose-%:
	cd build && ctest --parallel $(NPROC) -V -R ^$*$$

.PHONY: clang-format-test
clang-format-test:
	cmake --build build --target clang-format-test

.PHONY: clang-format-fix
clang-format-fix:
	cmake --build build --target clang-format-fix

.PHONY: valgrind
valgrind:
	cmake --build build --target valgrind-test 

.PHONY: coverage
coverage:
	cmake --build build --target coverage

.PHONY: help
help:
	@echo 'make build                  — собрать проект'
	@echo 'make test                   — все тесты (ctest)'
	@echo 'make test-<имя_теста>       — один тест (make test-s21_test_rb_tree)'
	@echo 'make test-verbose-<имя>     — один тест подробно'
	@echo 'make clang-format           — check code style'
	@echo 'make clang-format-fix       — автоисправить стиль'
	@echo 'make valgrind               — все тесты с valgrind'
	@echo 'make coverage               — code coverage с генерацией html'

.PHONY: clean
clean:
	rm -rf build
