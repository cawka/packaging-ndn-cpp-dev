/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2013 Regents of the University of California.
 * @author: Jeff Thompson <jefft0@remap.ucla.edu>
 * See COPYING for copyright and distribution information.
 */

#include <stdexcept>
#include <ndn-cpp-dev/encoding/wire-format.hpp>

using namespace std;

namespace ndn {

static bool gotInitialDefaultWireFormat = false;

WireFormat* WireFormat::defaultWireFormat_ = 0;

WireFormat*
WireFormat::getDefaultWireFormat()
{
  if (!defaultWireFormat_ && !gotInitialDefaultWireFormat) {
    // There is no defaultWireFormat_ and we have not yet initialized initialDefaultWireFormat_, so initialize and use it.
    gotInitialDefaultWireFormat = true;
    // NOTE: This allocates one object which we never free for the life of the application.
    defaultWireFormat_ = newInitialDefaultWireFormat();
  }
  
  return defaultWireFormat_;
}

Blob 
WireFormat::encodeInterest(const Interest& interest) 
{
  throw logic_error("unimplemented");
}

void 
WireFormat::decodeInterest(Interest& interest, const uint8_t *input, size_t inputLength) 
{
  throw logic_error("unimplemented");
}

Blob 
WireFormat::encodeData(const Data& data, size_t *signedPortionBeginOffset, size_t *signedPortionEndOffset) 
{
  throw logic_error("unimplemented");
}

void 
WireFormat::decodeData
  (Data& data, const uint8_t *input, size_t inputLength, size_t *signedPortionBeginOffset, size_t *signedPortionEndOffset) 
{
  throw logic_error("unimplemented");
}

Blob 
WireFormat::encodeForwardingEntry(const ForwardingEntry& forwardingEntry) 
{
  throw logic_error("unimplemented");
}

void 
WireFormat::decodeForwardingEntry(ForwardingEntry& forwardingEntry, const uint8_t *input, size_t inputLength) 
{
  throw logic_error("unimplemented");
}

}
