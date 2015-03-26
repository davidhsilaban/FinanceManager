#include "FinanceData.h"

//#include "moc_FinanceData.cpp"

QStringList FinanceData::getCategories()
{
	getHTTPResponseData("");
	return QStringList();
}

QString FinanceData::getHTTPResponseData(QString url)
{
	QNetworkRequest req(QUrl("http://davidhs.usa.cc/titip/lagu1.mp3"));
	progDialog->setWindowTitle("Please wait...");
	progDialog->open();
	reply = nam->get(req);
	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(downloadProgress(qint64,qint64)));
	connect(reply, SIGNAL(finished()), this, SLOT(downloadFinished()));
	return NULL;
}

void FinanceData::downloadProgress(qint64 received, qint64 total)
{
	progDialog->setValue(received*100/total);
	onDownloadProgress(received, total);
}

void FinanceData::downloadFinished()
{
	progDialog->hide();
	onDownloadFinished();
}

FinanceData::FinanceData(void)
{
	nam = new QNetworkAccessManager();
	progDialog = new QProgressDialog();
}


FinanceData::~FinanceData(void)
{
	delete nam;
}
