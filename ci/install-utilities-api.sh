#!/bin/bash
# Copyright (c) 2020 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for license information.
#
# Name: install-utilities-api.sh - Version 1.0.0
# Author: crdrisko
# Date: 03/03/2020-18:38:17
# Description: Install utilities-api prior to install

mkdir ~/Utilities-API && cd ~/Utilities-API

git clone https://github.com/crdrisko/utilities-api.git

mkdir build && cd build

cmake ../utilities-api/.

make && sudo make install

cd ../

bash utilities-api/ci/getVersions.sh
bash utilities-api/ci/install-gtest.sh
