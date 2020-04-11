/*
slowmoUI is a user interface for slowmoVideo.
Copyright (C) 2011  Simon A. Eugster (Granjow)  <simon.eu@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
*/

#include <QApplication>
#include <QPointer>
#include <QtCore/QTranslator>
#include <QtCore/QDebug>

#include "opencv2/core/version.hpp"

#include "mainwindow.h"
#include "logbrowserdialog.h"

QPointer<LogBrowserDialog> logBrowser;

/**
 * Message handler; see https://doc.qt.io/qt-5/qtglobal.html#qInstallMessageHandler
 */
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    if (logBrowser) {
        logBrowser->outputMessage(type, msg);
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Set up preferences for the QSettings file
    QCoreApplication::setOrganizationName("Granjow");
    QCoreApplication::setOrganizationDomain("granjow.net");
    QCoreApplication::setApplicationName("slowmoUI");

    // Setup debug output system.
    logBrowser = new LogBrowserDialog;
    qInstallMessageHandler(myMessageOutput);


    // startup...
    QString projectPath;
    qDebug() << "threading info : " << QThread::idealThreadCount();
    qDebug() << QApplication::arguments();

    //TODO: place this in About ...
    qDebug() << "OpenCV version: " << CV_MAJOR_VERSION << "."
             << CV_MINOR_VERSION << "." << CV_SUBMINOR_VERSION;

    const int N = app.arguments().size();
    for (int n = 1; n < N; n++) {
        QString arg = app.arguments().at(n);
        if (arg.startsWith("--")) {

            bool langUpdated = true;

            // Changes the file loaded from the resource container
            // to force a different language
            if (arg == "--fr") {
                QLocale::setDefault(QLocale::French);
            } else if (arg == "--de") {
                QLocale::setDefault(QLocale::German);
            } else if (arg == "--en") {
                QLocale::setDefault(QLocale::English);
            } else if (arg == "--it") {
                QLocale::setDefault(QLocale::Italian);
            } else {
                langUpdated = false;
            }

            if (langUpdated) {
                qDebug() << "Changed locale to " << QLocale::languageToString(QLocale().language());
            } else {
                qDebug() << "Not handled: " << arg;
            }

        } else {
            QFileInfo info(arg);
            if (info.exists() && info.isReadable() && info.isFile()) {
                projectPath = info.absoluteFilePath();
                qDebug() << "Loading project: " << projectPath;
            } else {
                qDebug() << projectPath << " does not exist.";
            }
        }
    }

    // Load the translation file from the resource container and use it
    QTranslator translator;
    translator.load(":translations");
    app.installTranslator(&translator);

    MainWindow w(projectPath);

    w.show();

    //use menu here : logBrowser->show();

    int result = app.exec();
    qDebug() << "application exec return result =" << result;
    delete logBrowser;
    return result;
}
