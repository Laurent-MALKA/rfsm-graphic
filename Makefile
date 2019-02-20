.PHONY: all run test check help

.DEFAULT_GOAL= all

help: # Display the aivailables commands
	@grep -E '(^[a-zA-Z_-]+:.*?##.*$$)|(^##)' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[32m%-10s\033[0m %s\n", $$1, $$2}' | sed -e 's/\[32m##/[33m/'

all: ## Compile the app
	@mkdir -p build
	@cmake . -Bbuild
	@$(MAKE) -s -C build

run: all ## Run the app
	@cd build &&	./app

test: all ## Run the tests
	@cd build && ./tests

check:
	@cppcheck --enable=style --suppress='*:includes/*' src/ 2> cppcheck.txt

clean:
	rm -rf build/
	