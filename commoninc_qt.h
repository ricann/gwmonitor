#ifndef QT_COMMONINC_H
#define QT_COMMONINC_H

#include <QMainWindow>
#include <QMap>
#include <QPen>
#include <QDialog>
#include <QTreeWidget>
#include <QLabel>
#include <QImage>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QWebFrame>
#include <QWebView>
#include <QWebPage>
#include <QWidget>
#include <QWebSecurityOrigin>
#include <QPainter>
#include <QtGui>
#include <QDateTime>
#include <QMultiMap>
#include <QPixmap>
#include <QMimeData>
#include <QDrag>
#include <QTableView>

#include <QThread>
#include <QMutex>
#include <QSemaphore>
#include <QUdpSocket>
#include <QtNetwork>
#include <QEventLoop>
#include <QHostAddress>

#include <QApplication>
#include <QCoreApplication>
#include <QTextCodec>
#include <QByteArray>
#include <QDir>
#include <QDate>
#include <QTimer>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

#include <QObject>
#include <QWeakPointer>

#include <QPaintEvent>
#include <QMouseEvent>
#include <QCloseEvent>

#include <QVector>
#include <QString>
#include <QStringList>

#include <QFlags>
#include <QDebug>
#include <QMessageBox>
#include <QVector2D>
#include <QStack>
#include <QCache>
#include <QMargins>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#  include <qnumeric.h>
#  include <QPrinter>
#else
#  include <QtNumeric>
#  include <QPrinter>
#endif

#endif // QT_COMMONINC_H
