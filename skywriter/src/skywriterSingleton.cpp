#include "skywriterSingleton.hpp"

SkywriterSingleton::SkywriterSingleton()
    : mIo{},
      _guard{mIo.get_executor()},
      _skywriter{mIo}
{
    _worker_thread = new asio::thread(
        std::bind(
            static_cast<asio::io_context::count_type (asio::io_service::*)(void)>(
                &asio::io_context::run),
            &mIo));
}

Skywriter &SkywriterSingleton::GetSkywriter()
{
    return _skywriter;
}

SkywriterSingleton::~SkywriterSingleton()
{
    mIo.reset();
    mIo.stop();
    _worker_thread->join();
    delete _worker_thread;
}