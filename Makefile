SHELL := /bin/bash

#
# All targets that are supposed to be called via "make <TARGET>" (callable targets)
# must be listed under TARGETS, and its short description must be added to HELPS.
#

TARGETS := \
	help \
	clean \
	docker \
	test \

HELPS := \
	"Show this help and exit" \
	"Remove all build artifacts" \
	"Run the Docker container interactively" \
	"Test everything" \

#
# Other environment variables should be placed below.
#

DOCKER_IMAGE := "arbitrary-precision-ws-$$USER"
DOCKER_PARAMS := \
	--rm \
	-v /etc/passwd:/etc/passwd:ro \
	-v /etc/group:/etc/group:ro \
	-v $$PWD:/ws:rw \
	-w /ws \
	-u $$UID:$$GID \
	-h ap \
	$(DOCKER_IMAGE)

CMAKE_BIN_DIR := /ws/bin
CMAKE_LOG_DIR := ${CMAKE_BIN_DIR}/log
CMAKE_SRC_DIR := /ws

#
# Add definitions for callable targets below.
#

.PHONY: help
help:
	@echo "Available targets:" \
	&& TARGETS=($(TARGETS)) \
	&& HELPS=($(HELPS)) \
	&& for (( i=0; i<$${#TARGETS[@]}; i++ )); do \
		printf " * %-20s - %s\n" "$${TARGETS[$$i]}" "$${HELPS[$$i]}"; \
	done

.PHONY: clean
clean: docker-image
	@docker run $(DOCKER_PARAMS) bash -c "rm -rf \
		$(CMAKE_BIN_DIR) \
	"

.PHONY: docker
docker: docker-image
	@docker run -it $(DOCKER_PARAMS)

# Due to complexity, each "&&" introduces a single command:
# 1. Generate build files via CMake.
# 2. Build "test" via CMake.
# 3. Create directory for logs.
# 4. Launch "test", but run only the subset prefixed by the target name.
#    It is expected that every single test starts with "test".
#    This way "make test" will run all the tests.
TARGETS_TEST := $(filter test%,$(TARGETS))
.PHONY: $(TARGETS_TEST)
$(TARGETS_TEST): docker-image
	@docker run $(DOCKER_PARAMS) bash -c "true \
	&& cmake -B $(CMAKE_BIN_DIR) \
		$(CMAKE_SRC_DIR) \
	&& cmake --build $(CMAKE_BIN_DIR) --target test \
	&& mkdir -p $(CMAKE_LOG_DIR) \
	&& $(CMAKE_BIN_DIR)/test \
		--gtest_output="xml:$(CMAKE_LOG_DIR)/$@.xml" \
		--gtest_filter="$@*" \
		> $(CMAKE_LOG_DIR)/$@.log 2>&1 \
	"
	@echo "Logs for $@ were written under $$(realpath $$PWD/$(subst $(CMAKE_SRC_DIR),,$(CMAKE_LOG_DIR)))"

#
# Add definitions for non-callable targets below.
#

.PHONY: docker-image
docker-image:
	@docker build . -t $(DOCKER_IMAGE)
