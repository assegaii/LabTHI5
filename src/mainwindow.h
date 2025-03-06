#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTreeWidgetItem>
#include "addeditdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_addButton_clicked();
    void on_editButton_clicked();
    void addPlaylist(const QString &name, const QVector<MusicTrack *> &tracks, int year);
    double calculateTotalDuration();
    void updateTotalDuration();
    void on_deleteButton_clicked();
    void updatePlaylist(QTreeWidgetItem *playlistItem, const QString &name, const QVector<MusicTrack *> &tracks, int year);
friend class tst_MainWindow;
private:
    Ui::MainWindow *ui;


    double calculateTotalDurationFromTracks(const QVector<MusicTrack *> &tracks);
};
#endif // MAINWINDOW_H
