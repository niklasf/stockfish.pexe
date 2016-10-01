#include <iostream>
#include <sstream>
#include <string>

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

#include "bitboard.h"
#include "position.h"
#include "search.h"
#include "thread.h"
#include "tt.h"
#include "uci.h"

namespace PSQT {
  void init();
}

void initialize() {
  std::cout << engine_info() << std::endl;

  UCI::init(Options);
  PSQT::init();
  Bitboards::init();
  Position::init();
  Bitbases::init();
  Search::init();
  Pawns::init();
  Threads.init();
  TT.resize(Options["Hash"]);
}

class CaptureBuf : public std::streambuf {
public:
  CaptureBuf(pp::Instance* inst) {
    instance = inst;
    pos = 0;
  }

protected:
  pp::Instance *instance;
  char buffer[8192];
  int pos;

  virtual int overflow(int c) {
    if (c == '\n') {
      buffer[pos] = 0;
      pos = 0;
      instance->PostMessage(pp::Var(buffer));
    } else if (pos < sizeof(buffer) - 2) {
      buffer[pos++] = c;
    }
    return 0;
  }
};

class StockfishInstance : public pp::Instance {
public:
  explicit StockfishInstance(PP_Instance instance) : pp::Instance(instance), captureBuf(this) {
    origBuf = std::cout.rdbuf(&captureBuf);
    origBufErr = std::cerr.rdbuf(&captureBuf);
    initialize();
  }

  virtual ~StockfishInstance() {
    std::cout.rdbuf(origBuf);
    std::cerr.rdbuf(origBufErr);
  }

  virtual void HandleMessage(const pp::Var& var_message) {
    if (!var_message.is_string())
      return;
    std::string message = var_message.AsString();
    UCI::command(message);
  }

private:
  CaptureBuf captureBuf;
  std::streambuf* origBuf;
  std::streambuf* origBufErr;
};

class StockfishModule : public pp::Module {
public:
  StockfishModule() : pp::Module() {}
  virtual ~StockfishModule() {}

  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new StockfishInstance(instance);
  }
};

namespace pp {
  Module *CreateModule() {
    return new StockfishModule();
  }
}
