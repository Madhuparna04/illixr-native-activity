#include "extended_window.hpp"
#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <android/log.h>
#include <thread>
#include <vector>
#include "runtime/main.h"

using namespace ILLIXR;

#define LOG(...) ((void)__android_log_print(ANDROID_LOG_INFO, "android-main", __VA_ARGS__))

static void handle_cmd(struct android_app* app, int32_t cmd) {
    switch(cmd) {
        case APP_CMD_INIT_WINDOW:
        {
            std::vector<std::string> arguments = { "", "libpose_lookup.so",  "libcommon_lock.so", "libtimewarp_gl.so", "libgldemo.so"};
            std::vector<char*> argv;
            for (const auto& arg : arguments)
                argv.push_back((char*)arg.data());
            setenv("ILLIXR_DATA", "/sdcard/Android/data/com.example.native_activity/mav0", true);
            setenv("ILLIXR_DEMO_DATA", "/sdcard/Android/data/com.example.native_activity/demo_data", true);
            setenv("ILLIXR_OFFLOAD_ENABLE", "False", true);
            setenv("ILLIXR_ALIGNMENT_ENABLE", "False", true);
            setenv("ILLIXR_ENABLE_VERBOSE_ERRORS", "False", true);
            setenv("ILLIXR_RUN_DURATION", "1000", true);
            setenv("ILLIXR_ENABLE_PRE_SLEEP", "False", true);
            setenv("ILLIXR_ENABLE_PRE_SLEEP", "False", true);
            std::thread runtime_thread(runtime_main, argv.size(), argv.data(), app->window);
            runtime_thread.join();
            break;
        }
        default:
            LOG("Some other command");
    }
}


void android_main(struct android_app* state) {

    state->onAppCmd = handle_cmd;
    while(true) {
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(0, nullptr, &events,
                                      (void**)&source)) >= 0) {

            // Process this event.
            if (source != nullptr) {
                source->process(state, source);
            }
        }
    }
}