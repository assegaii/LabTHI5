#ifndef ADDEDITDIALOG_H
#define ADDEDITDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "qtreewidget.h"
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
    int getYear() const;
    void setPlaylistData(const QString &name, const QVector<MusicTrack *> &tracks, int year);
    void setCurrentPlaylistItem(QTreeWidgetItem *item) { currentPlaylistItem = item; }

signals:
    void playlistCreated(QString name, QVector<MusicTrack *> &tracks, int year);
    void playlistUpdated(QString name, QVector<MusicTrack *> &tracks, int year);
    void playlistEdited(QTreeWidgetItem *playlistItem, const QString &name, const QVector<MusicTrack *> &tracks, int year);
private slots:


    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

public slots:
    void accept() override;

friend class tst_MainWindow;
private:
    Ui::AddEditDialog *ui;
    void validateAndAccept();
    QTreeWidgetItem *currentPlaylistItem = nullptr;
};


#endif
