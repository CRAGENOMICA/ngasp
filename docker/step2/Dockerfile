# ==============================================================================
# STEP 2 DOCKERFILE
# ==============================================================================
# 
# Usage:
#
#   - Build : docker build -t step2 .
#   - Run   : docker run -ti --rm step2 /bin/bash
#

# ==============================================================================
# BASE IMAGE
# ==============================================================================

FROM step1

# ==============================================================================
# NODE JS SERVER
# ==============================================================================

# **************
# *** nodejs ***
# **************

RUN yum install -y nodejs

# ***************
# *** chrome  ***
# ***************

RUN echo "[google-chrome]" > /etc/yum.repos.d/google-chrome.repo && \
    echo "name=google-chrome - \$basearch" >> /etc/yum.repos.d/google-chrome.repo && \
    echo "baseurl=http://dl.google.com/linux/chrome/rpm/stable/\$basearch" >> /etc/yum.repos.d/google-chrome.repo && \
    echo "enabled=1" >> /etc/yum.repos.d/google-chrome.repo && \
    echo "gpgcheck=1" >> /etc/yum.repos.d/google-chrome.repo && \
    echo "gpgkey=https://dl-ssl.google.com/linux/linux_signing_key.pub" >> /etc/yum.repos.d/google-chrome.repo
# RUN cat  /etc/yum.repos.d/google-chrome.repo
RUN yum install -y google-chrome-stable
# ==============================================================================
# START
# ==============================================================================

WORKDIR /app


