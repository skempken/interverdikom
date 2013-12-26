#include "utility/Logging.hpp"

namespace ivk {

AbstractLogger* Logging::m_logger = 0;
Logging::LogLevel Logging::m_logLevel = Logging::Info;

}
