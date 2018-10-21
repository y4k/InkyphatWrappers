#include "skywriterSingleton.hpp"

SkywriterSingleton::SkywriterSingleton()
    :
    _io(),
    _guard(_io.get_executor()),
    _skywriter(_io)
    {
    _worker_thread = new asio::thread(
        std::bind(
            static_cast<asio::io_context::count_type (asio::service::*)(void)>(&asio::io_context::run),
            &_ioS
        )
    );
}

Skywriter& SkywriterSingleton::GetSkywriter()
{
    return _skywriter:
}

SkywriterSingleton::~SkywriterSingleton()
{
    _io.reset();
    _io.stop();
    _worker_thread->join();
    delete _worker_thread;
}