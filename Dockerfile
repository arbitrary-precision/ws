# SPDX-FileCopyrightText: (c) 2023 Volodymyr Zakalyk <volodymyr.zakalyk@gmail.com>
# SPDX-License-Identifier: MIT

FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update

# Setup the locale.
RUN apt-get install -y locales locales-all
ENV LC_ALL en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US.UTF-8

# Setup bash.
RUN ln -sf /bin/bash /bin/sh

# Install dependencies.
RUN apt-get install -y \
    cmake \
    clang
