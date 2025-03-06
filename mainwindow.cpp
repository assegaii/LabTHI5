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

    AddEditDialog addEditDialog;
    addEditDialog.setPlaylistData(playlistName, tracks);

    connect(&addEditDialog, &AddEditDialog::playlistCreated, this, &MainWindow::addPlaylist);
    addEditDialog.setModal(true);
    if (addEditDialog.exec() == QDialog::Accepted) {
        updateTotalDuration();
    }
}


void MainWindow::addPlaylist(const QString &name, const QVector<MusicTrack *> &tracks)
{
    double totalDuration = 0;
    for (const auto &track : tracks) {
        totalDuration += track->getDuration();
    }

    QTreeWidgetItem *playlistItem = new QTreeWidgetItem(ui->treeWidget);
    playlistItem->setText(0, name);
    playlistItem->setText(1, QString::number(totalDuration) + " мин");
    playlistItem->setData(0, Qt::UserRole, QVariant::fromValue(tracks));

    ui->treeWidget->addTopLevelItem(playlistItem);
}


void MainWindow::on_deleteButton_clicked()
{
    QTreeWidgetItem *selectedItem = ui->treeWidget->currentItem();

    if (!selectedItem) {
        QMessageBox::warning(this, "Ошибка", "Выберите плейлист для удаления.");
        return;
    }

    QVariant data = selectedItem->data(0, Qt::UserRole);
    QVector<MusicTrack *> tracks = data.value<QVector<MusicTrack *>>();

    for (MusicTrack *track : tracks) {
        delete track;
    }

    delete selectedItem;

    updateTotalDuration();
}

//обн дурейшена
void MainWindow::updateTotalDuration()
{
    double totalDuration = 0.0;


    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *playlistItem = ui->treeWidget->topLevelItem(i);
        QVariant data = playlistItem->data(0, Qt::UserRole);
        QVector<MusicTrack *> tracks = data.value<QVector<MusicTrack *>>();


        for (MusicTrack *track : tracks) {
            totalDuration += track->getDuration();
        }
    }

    ui->label->setText("Всего длительность: " + QString::number(totalDuration) + " мин.");
}
