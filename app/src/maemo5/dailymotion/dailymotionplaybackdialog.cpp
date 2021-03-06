/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dailymotionplaybackdialog.h"
#include "resources.h"
#include "settings.h"
#include "valueselector.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

DailymotionPlaybackDialog::DailymotionPlaybackDialog(QWidget *parent) :
    Dialog(parent),
    m_model(new DailymotionStreamModel(this)),
    m_streamSelector(new ValueSelector(tr("Video format"), this)),
    m_buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Vertical, this)),
    m_layout(new QHBoxLayout(this))
{
    setWindowTitle(tr("Play video"));
    
    m_streamSelector->setModel(m_model);
    
    m_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    
    m_layout->addWidget(m_streamSelector, Qt::AlignBottom);
    m_layout->addWidget(m_buttonBox, Qt::AlignBottom);
    m_layout->setStretch(0, 1);
    
    connect(m_model, SIGNAL(statusChanged(QDailymotion::StreamsRequest::Status)), this,
            SLOT(onModelStatusChanged(QDailymotion::StreamsRequest::Status)));
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

QString DailymotionPlaybackDialog::streamUrl() const {
    return m_streamSelector->currentValue().toMap().value("url").toString();
}

void DailymotionPlaybackDialog::accept() {
    Settings::setDefaultPlaybackFormat(Resources::DAILYMOTION, m_streamSelector->valueText());
    Dialog::accept();
}

void DailymotionPlaybackDialog::list(const QString &videoId) {
    m_model->list(videoId);
}

void DailymotionPlaybackDialog::onModelStatusChanged(QDailymotion::StreamsRequest::Status status) {
    switch (status) {
    case QDailymotion::StreamsRequest::Loading:
        showProgressIndicator();
        return;
    case QDailymotion::StreamsRequest::Ready:
        if (m_model->rowCount() > 0) {
            m_streamSelector->setCurrentIndex(qMax(0, m_model->match("name",
                                                   Settings::defaultPlaybackFormat(Resources::DAILYMOTION))));
        }
        else {
            QMessageBox::critical(this, tr("Error"), tr("No streams available'"));
        }
        
        break;
    case QDailymotion::StreamsRequest::Failed:
        QMessageBox::critical(this, tr("Error"), tr("No streams available"));
        break;
    default:
        break;
    }
    
    hideProgressIndicator();
    m_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_model->rowCount() > 0);
}
