#include <3D-renderer/application.h>

#include <glog/logging.h>
#include <iostream>

int main(int /*argc*/, const char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    try {
        NRenderer::TApplication app("3D renderer", 1200, 800);
        app.Load("resources/cube.json");
        app.Run();
    } catch (std::exception& ex) {
        std::cerr << "Got exception " << ex.what() << std::endl;
        return 1;
    }
}
