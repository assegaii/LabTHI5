#include <QtTest>
#include <QPushButton>
#include <QTreeWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class tst_MainWindow : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_RemoveOldPlaylistAfterEdit();
    void test_CalculateTotalDuration();
    void test_EditPlaylistYear();


private:
    QApplication *app;
    MainWindow *mainWindow;
};

void tst_MainWindow::initTestCase()
{
    int argc = 0;
    char *argv[] = { nullptr };
    app = new QApplication(argc, argv);
    mainWindow = new MainWindow();
}

void tst_MainWindow::cleanupTestCase()
{
    delete mainWindow;
}

//дублирование плейлистов
void tst_MainWindow::test_RemoveOldPlaylistAfterEdit() {
    QVector<MusicTrack *> tracks;
    tracks.append(new MusicTrack("Song 1", "Artist 1", 3.4, "Pop"));
    tracks.append(new MusicTrack("Song 2", "Artist 2", 4.3, "Rock"));


    mainWindow->addPlaylist("Test Playlist", tracks, 2020);
    //проверяем кол-во плейлистов после создания одного
    int initialCount = mainWindow->ui->treeWidget->topLevelItemCount();
    QCOMPARE(initialCount, 1);
    //редактируем его
    AddEditDialog dialog;
    dialog.setPlaylistData("Test Playlist", tracks, 2020);
    dialog.ui->lineEdit->setText("Updated Playlist");
    dialog.accept();

    //проверяем кол-во плейлистов
    int updatedCount = mainWindow->ui->treeWidget->topLevelItemCount();
    QCOMPARE(updatedCount, 1);  // ожидаем один плейлист

    mainWindow->ui->treeWidget->setCurrentItem(mainWindow->ui->treeWidget->topLevelItem(0));
    mainWindow->on_deleteButton_clicked();

    // плейлист был удален
    int finalCount = mainWindow->ui->treeWidget->topLevelItemCount();
    QCOMPARE(finalCount, 0);
}
//тестирование подсчета продолжительности
void tst_MainWindow::test_CalculateTotalDuration()
{
    // Создаем треки
    MusicTrack *track1 = new MusicTrack("Song 1", "Artist 1", 3.4, "Pop");
    MusicTrack *track2 = new MusicTrack("Song 2", "Artist 2", 4.4, "Rock");

    QVector<MusicTrack *> tracks;
    tracks.append(track1);
    tracks.append(track2);

    mainWindow->addPlaylist("Test Playlist", tracks, 2020);

    double totalDuration = mainWindow->calculateTotalDuration();

    const double tolerance = 0.2;
    QVERIFY(qAbs(totalDuration - 8.2) < tolerance);  // Ожидаемая длительность 8.2

}
//тестирование обновления релиза
void tst_MainWindow::test_EditPlaylistYear()
{

    QVector<MusicTrack *> tracks;
    tracks.append(new MusicTrack("Song 1", "Artist 1", 3.4, "Pop"));
    tracks.append(new MusicTrack("Song 2", "Artist 2", 4.3, "Rock"));

    mainWindow->addPlaylist("Test Playlist", tracks, 2020);
    AddEditDialog dialog;
    dialog.setPlaylistData("Test Playlist", tracks, 2020);
    int year = dialog.getYear();
    QCOMPARE(year, 2020);  // Проверяем, что год релиза обновился
}


QTEST_MAIN(tst_MainWindow)
#include "tst_mainwindow.moc"
