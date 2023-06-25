SHELL := /bin/bash

#
# All targets that are supposed to be called via "make <TARGET>" (callable targets)
# must be listed under TARGETS, and its short description must be added to HELPS.
#

TARGETS := \
	help \
	docker \

HELPS := \
	"Show this help and exit" \
	"Run the Docker container interactively" \

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

.PHONY: docker
docker: docker-image
	@docker run -it $(DOCKER_PARAMS)

#
# Add definitions for non-callable targets below.
#

.PHONY: docker-image
docker-image:
	@docker build . -t $(DOCKER_IMAGE)
