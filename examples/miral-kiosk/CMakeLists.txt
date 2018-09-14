pkg_check_modules(SYSTEMD REQUIRED libsystemd)

mir_add_wrapped_executable(miral-kiosk
    kiosk_main.cpp
    kiosk_window_manager.cpp    kiosk_window_manager.h
)

target_include_directories(miral-kiosk PRIVATE ${SYSTEMD_INCLUDE_DIRS})
target_link_libraries(miral-kiosk PRIVATE example-shell-lib ${SYSTEMD_LIBRARIES})

# I'm not sure why this is needed in a chroot, but it's not worth finding out
if(DEFINED MIR_CHROOT)
    target_link_libraries(miral-kiosk EGL ${GLESv2_LIBRARIES})
endif()
