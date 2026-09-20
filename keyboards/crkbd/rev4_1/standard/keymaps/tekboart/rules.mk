VIA_ENABLE = yes
# [ME] Remove the below line to keep Keychron's default [insecure] VIA implementation
# [ME] Removing the lines enables VIA_INSECURE, which might allow keyloaggers to read your keystrokes. Use at your own risk.
OPT_DEFS += -UVIA_INSECURE

# Enable QMK's deferred execution for delayed mod activation--Needed for Home Row Mods to work properly.
# https://sunaku.github.io/home-row-mods.html
# https://github.com/manna-harbour/qmk_firmware/pull/56
DEFERRED_EXEC_ENABLE = yes

# Enable QMK's Community Modules
COMMUNITY_MODULES_ENABLE = yes

# Enable OS Detection
# This is used for Getreuer's MacOS remap
OS_DETECTION_ENABLE = yes

# Enable Tap Dance
# TAP_DANCE_ENABLE = yes
