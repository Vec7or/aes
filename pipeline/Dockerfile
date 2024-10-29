FROM ubuntu:24.04

ARG UID=1001
ARG GID=1001

RUN apt update \
    && apt dist-upgrade -y

#
# --- Basic APT packages ---
#
RUN apt-get update \
    && apt-get upgrade --assume-yes \
    && apt-get install --assume-yes --no-install-recommends \
    cmake \
    clang \
    ninja-build \
    && rm --recursive --force /var/lib/apt/lists/*

#
# --- Pipeline APT packages ---
#
RUN apt-get update \
    && apt-get upgrade --assume-yes \
    && apt-get install --assume-yes --no-install-recommends \
    jq \
    shellcheck \
    shfmt \
    nodejs \
    npm \
    python3 \
    python3-venv \
    python3-pip \
    git \
    yamllint \
    && rm --recursive --force /var/lib/apt/lists/*

#
# --- Pipeline NPM packages ---
#
RUN npm install -g \
    cspell@latest

#
# --- Remove 'ubuntu' user and create 'user' user ---
#
RUN userdel --remove ubuntu \
    && groupadd --gid $GID --non-unique user \
    && mkdir --parents /etc/sudoers.d \
    && useradd --uid $UID --create-home --gid user --groups plugdev,dialout user \
    && echo "user ALL = NOPASSWD: ALL" > /etc/sudoers.d/user \
    && chmod 0440 /etc/sudoers.d/user \
    && chsh --shell /bin/bash user

#
# --- Become user ---
#
USER user

#
# --- Pipeline PIP packages ---
#
RUN python3 -m venv ~/venv \
    && . ~/venv/bin/activate \
    && pip install \
    gitlint \
    mdformat \
    yamlfix \
    yamllint \
    clang-format \
    clang-tidy
ENV PATH="~/venv/bin:$PATH"