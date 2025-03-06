#include "addeditdialog.h"
#include "trackdialog.h"


AddEditDialog::AddEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditDialog)
{
    ui->setupUi(this);
    ui->buttonBox->disconnect(SIGNAL(accepted()));

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddEditDialog::validateAndAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

AddEditDialog::~AddEditDialog() {
    delete ui;
}

//проВерка
void AddEditDialog::validateAndAccept() {
    if (ui->lineEdit->text().trimmed().isEmpty() ||
        ui->spinBox->value() <= 0 ||
        ui->listWidget->count() == 0)
    {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля и добавьте хотя бы один трек.");
        return;
    }



    QString name = ui->lineEdit->text();
    QVector<MusicTrack *> tracks;


    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        QString trackInfo = item->text();

        QRegularExpression regex(R"((.+) - (.+) \(([\d.]+) мин\) \[(.+)\])");
        QRegularExpressionMatch match = regex.match(trackInfo);

        if (match.hasMatch()) {
            tracks.append(new MusicTrack(match.captured(1), match.captured(2), match.captured(3).toDouble(), match.captured(4)));
        }
    }
    int year = ui->spinBox->value();
    emit playlistCreated(name, tracks, year);

    QDialog::accept();
}

//Чето да
void AddEditDialog::setPlaylistData(const QString &name, const QVector<MusicTrack *> &tracks, int year) {
    ui->lineEdit->setText(name);
    ui->spinBox->setValue(year);
    ui->listWidget->clear();

    for (auto track : tracks) {
        QString trackInfo = track->getTitle() + " - " + track->getArtist() +
                            " (" + QString::number(track->getDuration()) + " мин) [" +
                            track->getGenre() + "]";
        ui->listWidget->addItem(trackInfo);
    }
}
int AddEditDialog::getYear() const {
    return ui->spinBox->value();
}

//Добавить
void AddEditDialog::on_pushButton_clicked()
{
    TrackDialog trackDialog;
    if (trackDialog.exec() == QDialog::Accepted)
    {
        QString title = trackDialog.getTitle();
        QString artist = trackDialog.getArtist();
        double duration = trackDialog.getDuration();
        QString genre = trackDialog.getGenre();

        MusicTrack newTrack(title, artist, duration, genre);

        QString trackInfo = title + " - " + artist + " (" + QString::number(duration) + " мин) [" + genre + "]";

        ui->listWidget->addItem(trackInfo);

    };
}

//Изменить
void AddEditDialog::on_pushButton_3_clicked()
{
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();

    if (!selectedItem) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите элемент из списка.");
        return;
    }

    QString trackInfo = selectedItem->text();
    QRegularExpression regex(R"((.+) - (.+) \(([\d.]+) мин\) \[(.+)\])");
    QRegularExpressionMatch match = regex.match(trackInfo);

    QString title = match.captured(1);
    QString artist = match.captured(2);
    double duration = match.captured(3).toDouble();
    QString genre = match.captured(4);

    TrackDialog trackDialog;
    trackDialog.setTitle(title);
    trackDialog.setArtist(artist);
    trackDialog.setDuration(duration);
    trackDialog.setGenre(genre);

    //обн данные
    if (trackDialog.exec() == QDialog::Accepted)
    {
        title = trackDialog.getTitle();
        artist = trackDialog.getArtist();
        duration = trackDialog.getDuration();
        genre = trackDialog.getGenre();

        selectedItem->setText(title + " - " + artist + " (" + QString::number(duration) + " мин) [" + genre + "]");
    }
}
void AddEditDialog::accept()
{
    QString name = ui->lineEdit->text();
    int year = ui->spinBox->value();
    QVector<MusicTrack *> tracks;

    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        QString trackInfo = item->text();

        QRegularExpression regex(R"((.+) - (.+) \(([\d.]+) мин\) \[(.+)\])");
        QRegularExpressionMatch match = regex.match(trackInfo);

        if (match.hasMatch()) {
            QString title = match.captured(1);
            QString artist = match.captured(2);
            double duration = match.captured(3).toDouble();
            QString genre = match.captured(4);

            tracks.append(new MusicTrack(title, artist, duration, genre));
        }
    }

    if (currentPlaylistItem) {
        emit playlistEdited(currentPlaylistItem, name, tracks, year);
    } else {
        emit playlistCreated(name, tracks, year);
    }

    QDialog::accept();
}
//Удалить
void AddEditDialog::on_pushButton_2_clicked()
{
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    delete selectedItem;
}



