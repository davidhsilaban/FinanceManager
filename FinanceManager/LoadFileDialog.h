#ifndef LOADFILEDIALOG_H
#define LOADFILEDIALOG_H

#include <QDialog>
#include "ui_LoadFileDialog.h"

class LoadFileDialog : public QDialog
{
	Q_OBJECT

public:
	LoadFileDialog(QWidget *parent = 0);
	~LoadFileDialog();

private:
	Ui::LoadFileDialog ui;
};

#endif // LOADFILEDIALOG_H
