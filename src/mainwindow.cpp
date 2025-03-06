#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addeditdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    while (ui->treeWidget->topLevelItemCount() > 0) {
        QTreeWidgetItem *item = ui->treeWidget->takeTopLevelItem(0);
        QVariant data = item->data(0, Qt::UserRole);
        QVector<MusicTrack *> tracks = data.value<QVector<MusicTrack *>>();

        for (MusicTrack *track : tracks) {
            delete track;
        }

        delete item;
    }

    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    AddEditDialog addEditDialog;
    connect(&addEditDialog, &AddEditDialog::playlistCreated, this, &MainWindow::addPlaylist);
    addEditDialog.setModal(true);
    if (addEditDialog.exec() == QDialog::Accepted) {
        updateTotalDuration();
    }
}

void MainWindow::on_editButton_clicked()
{
    QTreeWidgetItem *selectedItem = ui->treeWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Ошибка", "Выберите плейлист для редактирования.");
        return;
    }

    QString playlistName = selectedItem->text(0);
    QVector<MusicTrack *> tracks = selectedItem->data(0, Qt::UserRole).value<QVector<MusicTrack *>>();
    int year = selectedItem->data(1, Qt::UserRole).toInt();

    AddEditDialog addEditDialog;
    addEditDialog.setPlaylistData(playlistName, tracks, year);
    addEditDialog.setCurrentPlaylistItem(selectedItem);

    connect(&addEditDialog, &AddEditDialog::playlistEdited, this, &MainWindow::updatePlaylist);

    addEditDialog.setModal(true);
    if (addEditDialog.exec() == QDialog::Accepted) {
        updateTotalDuration();
    }
}

double MainWindow::calculateTotalDurationFromTracks(const QVector<MusicTrack *> &tracks)
{
    int totalMinutes = 0;
    int totalSeconds = 0;

    for (const auto &track : tracks) {
        double duration = track->getDuration();

        int minutes = static_cast<int>(duration);
        int seconds = static_cast<int>((duration - minutes) * 100);

        totalMinutes += minutes;
        totalSeconds += seconds;
    }


    totalMinutes += totalSeconds / 60;
    totalSeconds = totalSeconds % 60;

    return totalMinutes + totalSeconds / 100.0;
}

void MainWindow::addPlaylist(const QString &name, const QVector<MusicTrack *> &tracks, int year)
{
    double totalDuration = calculateTotalDurationFromTracks(tracks);

    QTreeWidgetItem *playlistItem = new QTreeWidgetItem(ui->treeWidget);
    playlistItem->setText(0, name);
    playlistItem->setText(1, QString::number(totalDuration, 'f', 2) + " мин");
    playlistItem->setData(0, Qt::UserRole, QVariant::fromValue(std::move(tracks)));
    playlistItem->setData(1, Qt::UserRole, year);

    ui->treeWidget->addTopLevelItem(playlistItem);
}

void MainWindow::on_deleteButton_clicked()
{

    QTreeWidgetItem *selectedItem = ui->treeWidget->currentItem();


    if (!selectedItem) {
        QMessageBox::warning(this, "Ошибка", "Выберите плейлист для удаления.");
        return;
    }

    delete selectedItem;


    updateTotalDuration();
}

void MainWindow::updatePlaylist(QTreeWidgetItem *playlistItem, const QString &name, const QVector<MusicTrack *> &tracks, int year)
{
    int totalMinutes = 0;
    int totalSeconds = 0;

    for (const auto &track : tracks) {
        double duration = track->getDuration();

        int minutes = static_cast<int>(duration);
        int seconds = static_cast<int>((duration - minutes) * 60);

        totalMinutes += minutes;
        totalSeconds += seconds;
    }

    totalMinutes += totalSeconds / 60;
    totalSeconds = totalSeconds % 60;
    double totalDuration = totalMinutes + totalSeconds / 60.0;

    playlistItem->setText(0, name);
    playlistItem->setText(1, QString::number(totalDuration) + " мин");

    QVector<MusicTrack *> oldTracks = playlistItem->data(0, Qt::UserRole).value<QVector<MusicTrack *>>();
    for (MusicTrack *track : oldTracks) {
        delete track;
    }

    playlistItem->setData(0, Qt::UserRole, QVariant::fromValue(tracks));
    playlistItem->setData(1, Qt::UserRole, year);

    delete playlistItem;
}
double MainWindow::calculateTotalDuration()
{
    int totalMinutes = 0;
    int totalSeconds = 0;

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *playlistItem = ui->treeWidget->topLevelItem(i);
        QVariant data = playlistItem->data(0, Qt::UserRole);
        QVector<MusicTrack *> tracks = data.value<QVector<MusicTrack *>>();

        for (MusicTrack *track : tracks) {
            double duration = track->getDuration();

            int minutes = static_cast<int>(duration);
            int seconds = static_cast<int>((duration - minutes) * 100);

            totalMinutes += minutes;
            totalSeconds += seconds;
        }
    }

    totalMinutes += totalSeconds / 60;
    totalSeconds = totalSeconds % 60;


    return totalMinutes + totalSeconds / 100.0;
}

void MainWindow::updateTotalDuration()
{
    double totalDuration = calculateTotalDuration();

    ui->label->setText("Всего длительность: " + QString::number(totalDuration, 'f', 2) + " мин.");
}
