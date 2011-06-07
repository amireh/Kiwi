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

#ifndef H_Kiwi_H
#define H_Kiwi_H

#include <exception>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Pixy.h"
#include "Tarball.h"
#include "Repository.h"
#include "md5.hpp"
#include <bzlib.h>

// Qt stuff
#include <QObject>
#include <QThread>
#include <QtGui/QApplication>
#include <QtGui/QtGui>
#include "ui_kiwi.h"
#include "ui_kiwi_about.h"

namespace Pixy
{
  /*! \class Kiwi
   *  \brief
   *  The Kiwi is the application's "root", initialises the components,
   *  the Renderer, maintains the main loop, and launches the target application.
   *
   *  Renderers can be attached to the Kiwi which will handle all the UI
   *  events and interact with the Patcher/Downloader. See OgreRenderer for
   *  an example Renderer.
   */
	class Kiwi : public QObject {
    Q_OBJECT
	public:
		~Kiwi( void );

		static Kiwi* getSingletonPtr();
		static Kiwi& getSingleton();

		/*! \brief
		 *	Starts up Qt, connects widgets, and begins the event loop.
		 */
		void go(int argc, char** argv);

  public slots:
    void evtTabChanged(int inIdx);
    void evtShowAboutDialog();
    void evtClickChangeRoot();
    void evtClickUpdateRoot();
    void evtClickCreate();
    void evtClickModify();
    void evtClickRename();
    void evtClickDelete();
    void evtClickFindDiffOriginal();
    void evtClickFindDiffModified();
    void evtClickFindDiffDest();
    void evtClickDiff();
    void evtClickFindMD5Source();
    void evtClickGenerateMD5();
    void evtChangeStructure(bool);

    void evtClickGenerateScript();
    void evtClickGenerateTarball();

  protected:
    void setupWidgets();
    void bindWidgets();

    bool validateEntry(const QString& inPath);

    Ui::KiwiUi mUi;
    Ui::KiwiAbout mDlgAboutUi;

		QApplication* mApp;
		QMainWindow *mWindow;
    QDialog *mDlgAbout;

    Repository *mRepo;

    void refreshTree();
    void addTreeEntry(PatchEntry* inEntry);

	private:
		Kiwi();
		Kiwi(const Kiwi&) {}
		Kiwi& operator=(const Kiwi&);

		void (Kiwi::*goFunc)();

		void goWithRenderer();
		void goVanilla();

		static Kiwi *__instance;

	};
} // end of namespace

#endif
