#include "skywriter.hpp"
#include "skywriterConstants.hpp"

/*
Convenient Singleton instance of Skywriter that handles creation
of the Asio IO Context, a worker thread and instantiation of the
Skywriter.

Constructor guaranteed to be called once and registered handlers are
called from the worker thread running the Asio IO Context.

Cleanup is handle in the destructor including joining and deleting
the worker thread.
 */
class SkywriterSingleton
{
public:
  Skywriter &Instance()
  {
    static SkywriterSingleton instance;
    return instance.GetSkywriter();
  }
  SkywriterSingleton(SkywriterSingleton const &) = delete;
  void operator=(SkywriterSingleton const &) = delete;
  ~SkywriterSingleton();

private:
  SkywriterSingleton();
  asio::thread *_worker_thread;
  asio::io_context mIo;
  asio::executor_work_guard<asio::io_context::executor_type> _guard;
  Skywriter _skywriter;

  Skywriter &GetSkywriter();
};