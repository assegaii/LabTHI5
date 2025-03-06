#ifndef ADDEDITDIALOG_H
#define ADDEDITDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "ui_addeditdialog.h"
#include "track.h"

namespace Ui {
class AddEditDialog;
}

class AddEditDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddEditDialog(QWidget *parent = nullptr);
    ~AddEditDialog();

    void setPlaylistData(const QString &name, const QVector<MusicTrack *> &tracks);

signals:
    void playlistCreated(QString name, QVector<MusicTrack *> tracks);
    void playlistUpdated(QString name, QVector<MusicTrack *> tracks);
private slots:


    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();




private:
    Ui::AddEditDialog *ui;
    void validateAndAccept();
};

#endif
