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

# ************
# *** epel ***
# ************

RUN curl -o epel.rpm https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm -LOk && \
    rpm -Uvh epel.rpm

# **************
# *** nodejs ***
# **************

RUN yum install -y nodejs

# ***************
# *** chrome  ***
# ***************

RUN yum -y update; yum clean all
RUN yum -y install mesa-dri-drivers libexif libcanberra-gtk2 libcanberra; yum clean all
ADD https://dl.google.com/linux/direct/google-chrome-stable_current_x86_64.rpm /root/google-chrome-stable_current_x86_64.rpm
RUN yum -y install /root/google-chrome-stable_current_x86_64.rpm; yum clean all
RUN dbus-uuidgen > /etc/machine-id
RUN yum install -y chromium
RUN yum -y install  liberation-mono-fonts  liberation-narrow-fonts liberation-sans-fonts  liberation-serif-fonts

# ==============================================================================
# START
# ==============================================================================

WORKDIR /app


