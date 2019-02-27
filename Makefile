.PHONY: help all run test check format

.DEFAULT_GOAL = all
NINJA = $(shell which ninja)
SAN ?=
CMAKE_FLAGS = -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ifneq ($(SAN),)
	CMAKE_FLAGS += -DCMAKE_CXX_FLAGS="-fsanitize=$(SAN)"
endif

help: # Display the aivailables commands
	@grep -E '(^[a-zA-Z_-]+:.*?##.*$$)|(^##)' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[32m%-10s\033[0m %s\n", $$1, $$2}' | sed -e 's/\[32m##/[33m/'

all: ## Compile the app
	@mkdir -p build
ifneq ($(NINJA),)
	@cmake . $(CMAKE_FLAGS) -GNinja
	@ninja -C build
else
	@cmake . $(CMAKE_FLAGS)
	@$(MAKE) -s -C build
endif
	@cp build/app .

run: all ## Run the app
	@./app

test: all ## Run the tests
	@cd build && ./tests

check: ## Checks for issues in code with ccpcheck
	@cppcheck --enable=style --suppress='*:includes/*' src/ 2> cppcheck.txt

format: ## Formats code with clang-format
	clang-format -i -style=file src/gui/* src/engine/*

clean: ## Cleans build/ folder
	rm -rf build/
	