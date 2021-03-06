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

#ifndef DAILYMOTIONCOMMENTDIALOG_H
#define DAILYMOTIONCOMMENTDIALOG_H

#include "dialog.h"
#include "dailymotioncomment.h"

class QTextEdit;
class QDialogButtonBox;
class QGridLayout;

class DailymotionCommentDialog : public Dialog
{
    Q_OBJECT
    
public:
    explicit DailymotionCommentDialog(const QString &videoId, QWidget *parent = 0);
    
private Q_SLOTS:
    void addComment();
    
    void onCommentChanged();
    void onCommentStatusChanged(QDailymotion::ResourcesRequest::Status);
    
private:
    DailymotionComment *m_comment;
    QString m_id;
    
    QTextEdit *m_edit;
    QDialogButtonBox *m_buttonBox;
    QGridLayout *m_layout;
};

#endif // DAILYMOTIONCOMMENTDIALOG_H
