/*
 *  Copyright (c) 2011 Ahmad Amireh <ahmad@amireh.net>
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the 
 *  Software is furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in 
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE. 
 *
 */
 
#include "PixyLogLayout.h"
#include "log4cpp/Priority.hh"
#include "log4cpp/FactoryParams.hh"
#ifdef LOG4CPP_HAVE_SSTREAM
#include <sstream>
#endif

namespace Pixy {

  PixyLogLayout::PixyLogLayout() {
	  fTimestampsOn = false;
	  fVanilla = false;
  }
  
  PixyLogLayout::~PixyLogLayout() {
  }

  std::string PixyLogLayout::format(const LoggingEvent& event) {

	if (fVanilla)
		return event.message;
		
	
	std::ostringstream message;        
	
      const std::string& priorityName = Priority::getPriorityName(event.priority);
	if (fTimestampsOn)
		message << event.timeStamp.getSeconds() << " ";
      
	// start off with priority
	message << priorityName	<< "\t| ";
	
	// append NDC
	if (event.ndc != "")
		message << event.ndc << ": ";
	
	message << event.message << "\n";
	
      return message.str();
  }

  std::auto_ptr<Layout> create__layout(const FactoryParams& params)
  {
	return std::auto_ptr<Layout>(new PixyLogLayout);
  }

  void PixyLogLayout::setTimestamps(bool fLogTimestamps) {
	  fTimestampsOn = fLogTimestamps;
  }

  void PixyLogLayout::setVanilla(bool inVanilla) {
	  fVanilla = inVanilla;
  }

}
