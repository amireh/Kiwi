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

    delete mRepo;
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

	void Kiwi::go(int argc, char** argv) {

		// init logger
		initLogger();

		Patcher::getSingletonPtr();
    mRepo = new Repository(Version(0,0,0));

    mApp = new QApplication(argc, argv);
    mApp->setOrganizationName("Kiwi");
    mApp->setApplicationName("Kiwi");

    this->setupWidgets();

    mApp->exec();
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
    connect(mUi.btnChangeRoot, SIGNAL(released()), this, SLOT(evtClickChangeRoot()));

    // Edit tab
    connect(mUi.btnCreate, SIGNAL(released()), this, SLOT(evtClickCreate()));
    connect(mUi.btnModify, SIGNAL(released()), this, SLOT(evtClickModify()));
    connect(mUi.btnRename, SIGNAL(released()), this, SLOT(evtClickRename()));
    connect(mUi.btnDelete, SIGNAL(released()), this, SLOT(evtClickDelete()));

    // Commit tab

    // Tools tab

  };

  void Kiwi::refreshTree() {
    mUi.treeRepo->setHeaderHidden(false);
  }

  void Kiwi::evtShowAboutDialog() {
    mDlgAbout->exec();
  }

  void Kiwi::evtClickChangeRoot() {

    QString dir =
      QFileDialog::getExistingDirectory(
        mUi.centralwidget, tr("Choose Application Root"),
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    mRepo->setRoot(dir.toStdString());

    mUi.txtRoot->setText(dir);
  }

  void Kiwi::evtClickCreate() {
    QFileDialog dialog(mUi.centralwidget);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);
    if (mRepo->isRootSet())
      dialog.setDirectory(QString::fromStdString(mRepo->getRoot()));

    QStringList fileNames;
    if (dialog.exec())
      fileNames = dialog.selectedFiles();
    else
      return;

    MD5 md5;
    QString lLocal;
    QString lFull;
    QString tmp = QString::fromStdString(mRepo->getRoot());
    for (int i=0; i < fileNames.size(); ++i) {

      lFull = fileNames.at(i);
      lLocal = QString(fileNames.at(i)).remove(tmp);

      std::string lFilename = lLocal.toStdString();
      std::string lChecksum = md5.digestFile((char*)(lFull.toStdString()).c_str());

      // only add it if it hasn't been added yet
      if (!mRepo->registerEntry(CREATE, lFilename, "", "", lChecksum))
        continue;

      QTreeWidgetItem* lItem = new QTreeWidgetItem();
      lItem->setData(0, Qt::DisplayRole, tr("C"));
      lItem->setData(1, Qt::DisplayRole, lLocal);
      lItem->setData(4, Qt::DisplayRole, QString(lChecksum.c_str()));
      mUi.treeRepo->addTopLevelItem(lItem);
      lItem = 0;
    }
    this->refreshTree();
  }

  void Kiwi::evtClickModify() {
    QString lSrc, lDiff;
    QFileDialog dialog(mUi.centralwidget);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    if (mRepo->isRootSet())
      dialog.setDirectory(QString::fromStdString(mRepo->getRoot()));

    if (dialog.exec())
      lSrc = dialog.selectedFiles().at(0);
    else
      return;

    if (dialog.exec())
      lDiff = dialog.selectedFiles().at(0);
    else
      return;

    MD5 md5;
    std::string lChecksum = md5.digestFile((char*)((lDiff.toStdString()).c_str()));

    if (!mRepo->registerEntry(MODIFY, lSrc.toStdString(), lDiff.toStdString(), "", lChecksum))
      return;

    QTreeWidgetItem* lItem = new QTreeWidgetItem();
    lItem->setData(0, Qt::DisplayRole, tr("M"));
    lItem->setData(1, Qt::DisplayRole, lSrc);
    lItem->setData(2, Qt::DisplayRole, lDiff);
    lItem->setData(4, Qt::DisplayRole, QString(lChecksum.c_str()));
    mUi.treeRepo->addTopLevelItem(lItem);
    lItem = 0;

    this->refreshTree();
  }

  void Kiwi::evtClickRename() {
    QString lSrc, lDest;
    QFileDialog dialog(mUi.centralwidget);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    if (mRepo->isRootSet())
      dialog.setDirectory(QString::fromStdString(mRepo->getRoot()));

    if (dialog.exec())
      lSrc = dialog.selectedFiles().at(0);
    else
      return;

    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    if (dialog.exec())
      lDest = dialog.selectedFiles().at(0);
    else
      return;

    MD5 md5;
    std::string lChecksum = md5.digestFile((char*)((lSrc.toStdString()).c_str()));

    if (!mRepo->registerEntry(RENAME, lSrc.toStdString(), lDest.toStdString(), "", lChecksum))
      return;

    QTreeWidgetItem* lItem = new QTreeWidgetItem();
    lItem->setData(0, Qt::DisplayRole, tr("R"));
    lItem->setData(1, Qt::DisplayRole, lSrc);
    lItem->setData(2, Qt::DisplayRole, lDest);
    lItem->setData(4, Qt::DisplayRole, QString(lChecksum.c_str()));
    mUi.treeRepo->addTopLevelItem(lItem);
    lItem = 0;

    this->refreshTree();
  }

  void Kiwi::evtClickDelete() {
    QFileDialog dialog(mUi.centralwidget);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);
    if (mRepo->isRootSet())
      dialog.setDirectory(QString::fromStdString(mRepo->getRoot()));

    QStringList fileNames;
    if (dialog.exec())
      fileNames = dialog.selectedFiles();
    else
      return;

    for (int i=0; i < fileNames.size(); ++i) {
      std::string lFilename = fileNames.at(i).toStdString();

      // only add it if it hasn't been added yet
      if (!mRepo->registerEntry(DELETE, lFilename))
        continue;

      QTreeWidgetItem* lItem = new QTreeWidgetItem();
      lItem->setData(0, Qt::DisplayRole, tr("D"));
      lItem->setData(1, Qt::DisplayRole, fileNames.at(i));
      mUi.treeRepo->addTopLevelItem(lItem);
      lItem = 0;
    }
    this->refreshTree();
  }



} // end of namespace Pixy
