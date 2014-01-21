/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2013 Regents of the University of California.
 * @author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 * @author: Zhenkai Zhu <zhenkai@cs.ucla.edu>
 * See COPYING for copyright and distribution information.
 */

#ifndef NDN_LOGGING_HPP
#define NDN_LOGGING_HPP

#include <ndn-cpp-dev/common.hpp>

#ifdef NDN_CPP_HAVE_LOG4CXX

#include <log4cxx/logger.h>

#define MEMBER_LOGGER                           \
  static log4cxx::LoggerPtr staticModuleLogger;

#define INIT_MEMBER_LOGGER(className,name)          \
  log4cxx::LoggerPtr className::staticModuleLogger =  log4cxx::Logger::getLogger (name);

#define INIT_LOGGER(name) \
  static log4cxx::LoggerPtr staticModuleLogger = log4cxx::Logger::getLogger (name);

#define _LOG_DEBUG(x) \
  LOG4CXX_DEBUG(staticModuleLogger, x);

#define _LOG_TRACE(x) \
  LOG4CXX_TRACE(staticModuleLogger, x);

#define _LOG_FUNCTION(x) \
  LOG4CXX_TRACE(staticModuleLogger, __FUNCTION__ << "(" << x << ")");

#define _LOG_FUNCTION_NOARGS \
  LOG4CXX_TRACE(staticModuleLogger, __FUNCTION__ << "()");

#define _LOG_ERROR(x) \
  LOG4CXX_ERROR(staticModuleLogger, x);

#define _LOG_ERROR_COND(cond,x) \
  if (cond) { _LOG_ERROR(x) }

#define _LOG_DEBUG_COND(cond,x) \
  if (cond) { _LOG_DEBUG(x) }

void
INIT_LOGGERS ();

#else // else NDN_CPP_HAVE_LOG4CXX

#define INIT_LOGGER(name)
#define _LOG_FUNCTION(x)
#define _LOG_FUNCTION_NOARGS
#define _LOG_TRACE(x)
#define INIT_LOGGERS(x)
#define _LOG_ERROR(x)
#define _LOG_ERROR_COND(cond,x)
#define _LOG_DEBUG_COND(cond,x)

#define MEMBER_LOGGER
#define INIT_MEMBER_LOGGER(className,name)

#ifdef _DEBUG

#include <sys/time.h>
#include <iostream>

#define _LOG_DEBUG(x) \
  { time_t now = time(0); std::string s = std::string(ctime(&now)); std::clog << s.substr(0, s.size() - 1) << " " << x << std::endl; }

#else
#define _LOG_DEBUG(x)
#endif

#endif // NDN_CPP_HAVE_LOG4CXX

#endif
