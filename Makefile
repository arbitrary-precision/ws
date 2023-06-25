SHELL := /bin/bash

#
# All targets that are supposed to be called via "make <TARGET>" (callable targets)
# must be listed under TARGETS, and its short description must be added to HELPS.
#

TARGETS := \
	help \

HELPS := \
	"Show this help and exit" \

#
# Other environment variables should be placed below.
#

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

#
# Add definitions for non-callable targets below.
#
