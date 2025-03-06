#ifndef TRACKDIALOG_H
#define TRACKDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "ui_trackdialog.h"

namespace Ui {
class TrackDialog;
}

class TrackDialog : public QDialog {
    Q_OBJECT

public:
    explicit TrackDialog(QWidget *parent = nullptr);
    ~TrackDialog();

    QString getTitle() const;
    QString getArtist() const;
    double getDuration() const;
    QString getGenre() const;

    void setTitle(const QString &title);
    void setArtist(const QString &artist);
    void setDuration(double duration);
    void setGenre(const QString &genre);

private slots:
    void validateAndAccept();

    void on_spinDuration_valueChanged(double arg1);

private:
    Ui::TrackDialog *ui;
friend class tst_MainWindow;
};

#endif
