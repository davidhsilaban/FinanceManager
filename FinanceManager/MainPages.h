#pragma once

#include <QtGui/QtGui>
//#include <QtGui/QWidget>
//#include <QtSql/QSqlRelationalDelegate>
#include <QtSql/QtSql>
#include "MainApp.h"

// Define all the page widget classes

class NoFileOpenedPage : public QWidget {
	Q_OBJECT

public:
	NoFileOpenedPage(QWidget *parent = 0);

private:
	// Objects for the widgets in this page
	QVBoxLayout *mainLayout;
	QLabel *lblMessage;

	// Parent object reference
	MainApp *myParent;

};

class InitialPage : public QWidget {
	Q_OBJECT

public:
	InitialPage(QWidget *parent = 0);

private:
	// Objects for the widgets in this page
	QVBoxLayout *mainLayout;
	QLabel *lblMessage;

	// Parent object reference
	MainApp *myParent;

};

class InsertDataPage : public QWidget {
	Q_OBJECT

public:
	InsertDataPage(QWidget *parent = 0);

private slots:
	void addTransaction();
	void resetForm();
	void refreshCategories();

private:
	// Objects for the widgets in this page
	QBoxLayout *pageLayout;
	QGridLayout *mainLayout;
	QGroupBox *grpMain;
	QLabel *lblDate, *lblType, *lblCategory, *lblDescription, *lblAmount;
	QComboBox *cboDate, *cboMonth, *cboType, *cboCategory;
	QSpinBox *spnYear;
	QTextEdit *edtDescription;
	QLineEdit *edtAmount;
	QPushButton *btnSubmit, *btnReset, *btnRefresh;

	// Parent object reference
	MainApp *myParent;

};

class ViewDataPage : public QWidget {
	Q_OBJECT

public:
	ViewDataPage(QWidget *parent = 0);

private:
	// Objects for the widgets in this page
	QVBoxLayout *mainLayout;
	QGridLayout *filterFormLayout;
	QGroupBox *grpFilter;
	QLabel *lblDate, *lblType, *lblCategory, *lblDescription, *lblAmount;
	QComboBox *cboDate, *cboMonth, *cboType, *cboCategory;
	QSpinBox *spnYear;
	QLineEdit *edtDescription;
	QLineEdit *edtAmount;
	QPushButton *btnClearFilter, *btnFilter, *btnRefresh;

	QTableView *tblTransaction;
	QSqlRelationalTableModel *tblModel;

	// Parent object reference
	MainApp *myParent;

private slots:
	// Define slots for this page
	void refreshTable();

};