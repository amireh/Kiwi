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

#include "Kiwi.h"
#include "PixyLogLayout.h"

namespace Pixy
{
	Kiwi* Kiwi::__instance;


	Kiwi::Kiwi() {
	}

	Kiwi::~Kiwi() {

    delete Patcher::getSingletonPtr();

		mLog->infoStream() << "++++++ " << PIXY_APP_NAME << " cleaned up successfully ++++++";
		if (mLog)
		  delete mLog;

		log4cpp::Category::shutdown();
	}

	Kiwi* Kiwi::getSingletonPtr() {
		if( !__instance ) {
		    __instance = new Kiwi();
		}

		return __instance;
	}

	Kiwi& Kiwi::getSingleton() {
		return *getSingletonPtr();
	}

	void Kiwi::go(int argc, char** argv) {

		// init logger
		initLogger();

		Patcher::getSingletonPtr();

    mApp = new QApplication(argc, argv);
    mApp->setOrganizationName("Kiwi");
    mApp->setApplicationName("Kiwi");

    this->setupWidgets();

    mApp->exec();
	}

	void Kiwi::initLogger() {

		std::string lLogPath = PROJECT_LOG_DIR;
#if PIXY_PLATFORM == PIXY_PLATFORM_WINDOWS
		lLogPath += "\\Kiwi.log";
#elif PIXY_PLATFORM == PIXY_PLATFORM_APPLE
		lLogPath = macBundlePath() + "/Contents/Logs/Kiwi.log";
#else
		lLogPath += "/Kiwi.log";
#endif
		std::cout << "| Initting log4cpp logger @ " << lLogPath << "!\n";

		log4cpp::Appender* lApp = new
		log4cpp::FileAppender("FileAppender", lLogPath, false);

    log4cpp::Layout* lLayout = new PixyLogLayout();
		/* used for header logging */
		PixyLogLayout* lHeaderLayout = new PixyLogLayout();
		lHeaderLayout->setVanilla(true);

		lApp->setLayout(lHeaderLayout);

		std::string lCatName = PIXY_LOG_CATEGORY;
		log4cpp::Category* lCat = &log4cpp::Category::getInstance(lCatName);

    lCat->setAdditivity(false);
		lCat->setAppender(lApp);
		lCat->setPriority(log4cpp::Priority::DEBUG);

		lCat->infoStream()
		<< "\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+";
		lCat->infoStream()
		<< "\n+                                 " << PIXY_APP_NAME << "                                    +";
		lCat->infoStream()
		<< "\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";

		lApp->setLayout(lLayout);

		lApp = 0;
		lCat = 0;
		lLayout = 0;
		lHeaderLayout = 0;

		mLog = new log4cpp::FixedContextCategory(PIXY_LOG_CATEGORY, "Kiwi");
	}

	void Kiwi::setupWidgets() {

    mWindow = new QMainWindow();
    mUi.setupUi(mWindow);

    mDlgAbout = new QDialog();
    mDlgAboutUi.setupUi(mDlgAbout);

    this->bindWidgets();

    mWindow->show();
	};

  void Kiwi::bindWidgets() {
    // Menu actions
    connect(mUi.actionAbout, SIGNAL(activated()), this, SLOT(evtShowAboutDialog()));

    // General tab

    // Edit tab

    // Commit tab

    // Tools tab

  };

  void Kiwi::evtShowAboutDialog() {
    mDlgAbout->exec();
  }

} // end of namespace Pixy
