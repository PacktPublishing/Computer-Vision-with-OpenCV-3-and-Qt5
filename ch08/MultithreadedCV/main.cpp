#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}



QString getVersionString(QString fName)
{
    // first of all, GetFileVersionInfoSize
    DWORD dwHandle;
    DWORD dwLen = GetFileVersionInfoSize(fName.toStdWString().c_str(), &dwHandle);
    // GetFileVersionInfo
    LPVOID lpData = new BYTE[dwLen];
    if(!GetFileVersionInfo(fName.toStdWString().c_str(), dwHandle, dwLen, lpData))
    {
        qDebug() << "error in GetFileVersionInfo";
        delete[] lpData;
        return “”;
    }
    // VerQueryValue
    VS_FIXEDFILEINFO *lpBuffer = NULL;
    UINT uLen;
    if(!VerQueryValue(lpData,
                      QString(“\”).toStdWString().c_str(),
                      (LPVOID*)&lpBuffer,
                      &uLen))
    {
        qDebug() <<
                    QString::number(( lpBuffer->dwFileVersionMS >> 16 ) & 0xffff ) + "." +
                    QString::number( ( lpBuffer->dwFileVersionMS) & 0xffff ) + "." +
                    QString::number( ( lpBuffer->dwFileVersionLS >> 16 ) & 0xffff ) + "." +
                    QString::number( ( lpBuffer->dwFileVersionLS) & 0xffff );
    }
}
