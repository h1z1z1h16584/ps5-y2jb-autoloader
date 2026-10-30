#!/usr/bin/env bash
set -euo pipefail

export PS5_PAYLOAD_SDK="${PS5_PAYLOAD_SDK:-/opt/ps5-payload-sdk}"
export LLVM_CONFIG="${LLVM_CONFIG:-/usr/lib/llvm-18/bin/llvm-config}"

if [ ! -d "$PS5_PAYLOAD_SDK" ]; then
  echo "Error: PS5_PAYLOAD_SDK not found at $PS5_PAYLOAD_SDK" >&2
  exit 1
fi

mkdir -p build
make -C payload
echo "Built build/usb-y2jb-installer.elf successfully."
