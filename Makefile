# SPDX-FileCopyrightText: (c) 2023 Volodymyr Zakalyk <volodymyr.zakalyk@gmail.com>
# SPDX-License-Identifier: MIT

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

CMAKE_SRC_DIR := /ws
CMAKE_BIN_DIR := $(CMAKE_SRC_DIR)/bin
CMAKE_LOG_DIR := ${CMAKE_BIN_DIR}/log

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

TARGETS_TEST := $(filter test%,$(TARGETS))
.PHONY: $(TARGETS_TEST)
$(TARGETS_TEST): docker-image
	@docker run $(DOCKER_PARAMS) \
		bash -c "true \
			&& cmake -B $(CMAKE_BIN_DIR) $(CMAKE_SRC_DIR) \
			&& cmake --build $(CMAKE_BIN_DIR) --target test \
			&& mkdir -p $(CMAKE_LOG_DIR)"
	@-docker run $(DOCKER_PARAMS) \
		bash -c "\
			$(CMAKE_BIN_DIR)/test \
				--gtest_output=\"xml:$(CMAKE_LOG_DIR)/$@.xml\" \
				--gtest_filter="$@*" \
			> $(CMAKE_LOG_DIR)/$@.txt 2>&1"; \
		test "$$?" = 0 \
			&& echo -e "\nTest result: PASS" \
			|| echo -e "\nTest result: FAIL"
	@printf "Logs for \"$@\" are located under:\n - txt: %s\n - xml: %s\n" \
		$$(realpath $$PWD/$(subst $(CMAKE_SRC_DIR),,$(CMAKE_LOG_DIR)))/$@.txt \
		$$(realpath $$PWD/$(subst $(CMAKE_SRC_DIR),,$(CMAKE_LOG_DIR)))/$@.xml

#
# Add definitions for non-callable targets below.
#

.PHONY: docker-image
docker-image:
	@docker build . -t $(DOCKER_IMAGE)
