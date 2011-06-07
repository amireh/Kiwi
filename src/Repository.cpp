/*
 *  COpyright (c) 2011 Ahmad Amireh <ahmad@amireh.net>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  cOpy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, cOpy, modify, merge, publish, distribute, sublicense,
 *  and/or sell cOpies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above cOpyright notice and this permission notice shall be included in
 *  all cOpies or substantial portions of the Software.
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

#include "Repository.h"

namespace Pixy {

	Repository::Repository(const Version inVersion) : mVersion(inVersion) {
	  mVersion = inVersion;
    mRoot = "";
    fFlat = false;
    mEntries.clear();
  }

	Repository::~Repository() {

		PatchEntry* lEntry = 0;
		while (!mEntries.empty()) {
		  lEntry = mEntries.back();
		  mEntries.pop_back();
		  delete lEntry;
		}
		lEntry = 0;

	}


  PatchEntry*
  Repository::registerEntry(PATCHOP Op,
                            std::string Local,
                            std::string Remote,
                            std::string Temp,
                            std::string Checksum
                            )
  {
    PatchEntry *lEntry = new PatchEntry();

    lEntry->Op = Op;
    lEntry->Local = Local;
    lEntry->Remote = Remote;
    lEntry->Checksum = Checksum;
    lEntry->Repo = this;

    if (Op == MODIFY)
      lEntry->Aux = Remote;

    // make sure the entry doesn't exist yet
    std::vector<PatchEntry*>::const_iterator _itr;
    bool exists = false;
    for (_itr = mEntries.begin(); _itr != mEntries.end(); ++_itr) {
      if ((**_itr) == *lEntry) {
        exists = true;
        break;
      }
    }
    if (exists) {
      delete lEntry;
      lEntry = 0;
      return 0;
    }

    mEntries.push_back(lEntry);
    lEntry = 0;

    return mEntries.back();
  }

  std::vector<PatchEntry*>
  Repository::getEntries(PATCHOP inOp) {

    std::vector<PatchEntry*> entries;
    std::vector<PatchEntry*>::const_iterator _itr;
    for (_itr = mEntries.begin(); _itr != mEntries.end(); ++_itr) {
      if ((*_itr)->Op == inOp)
        entries.push_back((*_itr));
    }

    return entries;
  }

  const std::vector<PatchEntry*>&
  Repository::getEntries() {
    return mEntries;
  }

  Version Repository::getVersion() {
    return mVersion;
  }

  void Repository::refreshPaths() {

  }

  void Repository::setVersion(const Version inV) {
    mVersion = inV;
  }
};
