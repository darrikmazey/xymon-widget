
#include <QtDebug>

#include "xymonwidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QInputDialog>
#include <QLineEdit>

XymonWidget::XymonWidget(QWidget *parent) :
	QWidget(parent)
{
	qDebug() << QString("XymonWidget::XymonWidget()");
	resize(144,178);

	QVBoxLayout *layout = new QVBoxLayout();
	QWidget *w = new QWidget();
	w->setMinimumSize(144,148);
	layout->addWidget(w);
	QPalette p;
	p.setColor(QPalette::Window, QColor(0, 0, 255));
	w->setPalette(p);
	m_label = new QLabel("No Server");
	m_label->setAlignment(Qt::AlignCenter);
	if (m_serverAddress.length() > 0) {
		m_label->setText(m_serverAddress);
	}
	layout->addWidget(m_label);
	setLayout(layout);
}

XymonWidget::~XymonWidget()
{
	qDebug() << QString("XymonWidget::~XymonWidget()");
}

void XymonWidget::showSettingsDialog()
{
	qDebug() << QString("XymonWidget::showSettingsDialog()");
	bool isOk;
	QString newText = QInputDialog::getText(this, tr("Server Address"), tr("Server address:"), QLineEdit::Normal, m_label->text(), &isOk);
	if (isOk) {
		m_label->setText(newText);
		m_serverAddress = newText;
	}
}
