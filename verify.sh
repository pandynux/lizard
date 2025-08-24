#!/bin/bash

# A script to provide a stable execution context for verification.
set -e
echo "--- Starting Verification Script ---"

echo "Step 1: Generating project..."
python3 idf_project_generator.py --non-interactive --project-name test-project --chip esp32 --bt None --log-level INFO

echo "Step 2: Sourcing environment and building..."
cd test-project
. /opt/esp/esp-idf/export.sh
idf.py set-target esp32
idf.py build

echo "--- Verification Script Finished Successfully ---"
