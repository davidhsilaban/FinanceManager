#pragma once

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QVariantMap>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QUrl>
#include <QtGui/QProgressDialog>
#include <QJson/Parser>

//#include "MainApp.h"

class FinanceData :
	public QObject
{
	Q_OBJECT

public:
	FinanceData(void);
	~FinanceData(void);

	QStringList getCategories();

private:
	QString getHTTPResponseData(QString url);
	QVariantMap parseJSONData(QString json_data);

private slots:
	void downloadProgress(qint64 received, qint64 total);
	void downloadFinished();

private:
	QNetworkAccessManager *nam;
	QNetworkReply *reply;
	QProgressDialog *progDialog;

signals:
	void onDownloadProgress(qint64 received, qint64 total);
	void onDownloadFinished();
};

